/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2011 Paul Kocialkowski <contact@paulk.fr>
 *                    Joerie de Gram <j.de.gram@gmail.com>
 *                    Simon Busch <morphis@gravedo.de>
 *
 * libsamsung-ipc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libsamsung-ipc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libsamsung-ipc.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <asm/types.h>
#include <mtd/mtd-abi.h>
#include <assert.h>

#include <radio.h>

#include "crespo_modem_ctl.h"
#include "crespo_nv_data.h"
#include "crespo_ipc.h"
#include "ipc_private.h"

int wake_lock_fd=   -1;
int wake_unlock_fd= -1;

int crespo_modem_bootstrap(struct ipc_client *client)
{
    int s3c2410_serial3_fd= -1;
    int modem_ctl_fd=   -1;

    /* Control variables. */
    int boot_tries_count=0;
    int rc=0;

    /* Boot variables */
    uint8_t *radio_img_p=NULL;
    uint8_t bootcore_version=0;
    uint8_t info_size=0;
    uint8_t crc_byte=0;
    int block_size=0;

    /* s3c2410 serial setup variables. */
    struct termios termios;
    int serial;

    /* fds maniplation variables */
    struct timeval timeout;
    fd_set fds;

    /* nv_data variables */
    void *nv_data_p;

    /* General purpose variables. */
    uint8_t data;
    uint16_t data_16;
    uint8_t *data_p;
    int i;

    printf("crespo_ipc_bootstrap: enter\n");

boot_loop_start:
    if(boot_tries_count > 5)
    {
        printf("crespo_ipc_bootstrap: boot has failed too many times.\n");
        goto error;
    }

    /* Read the radio.img image. */
    printf("crespo_ipc_bootstrap: reading radio image\n");
    radio_img_p=mtd_read("/dev/mtd/mtd5ro", RADIO_IMG_SIZE, 0x1000);
    if (radio_img_p == NULL) {
        radio_img_p = mtd_read("/dev/mtd5ro", RADIO_IMG_SIZE, 0x1000);
        if (radio_img_p == NULL)
            goto error;
    }
    printf("crespo_ipc_bootstrap: radio image read\n");

    printf("crespo_ipc_bootstrap: open modem_ctl\n");
    modem_ctl_fd=open("/dev/modem_ctl", O_RDWR | O_NDELAY);
    if(modem_ctl_fd < 0)
        goto error_loop;

    /* Reset the modem before init to send the first part of modem.img. */
    ioctl(modem_ctl_fd, IOCTL_MODEM_RESET);
    usleep(400000);

    printf("crespo_ipc_bootstrap: open s3c2410_serial3\n");
    s3c2410_serial3_fd=open("/dev/s3c2410_serial3", O_RDWR | O_NDELAY);
    if(s3c2410_serial3_fd < 0)
        goto error_loop;

    /* Setup the s3c2410 serial. */
    printf("crespo_ipc_bootstrap: setup s3c2410_serial3\n");
    tcgetattr(s3c2410_serial3_fd, &termios);

    cfmakeraw(&termios);
    cfsetispeed(&termios, B115200);
    cfsetospeed(&termios, B115200);

    tcsetattr(s3c2410_serial3_fd, TCSANOW, &termios);

    ioctl(s3c2410_serial3_fd, TIOCMGET, &serial); //FIXME
    ioctl(s3c2410_serial3_fd, TIOCMSET, &serial); //FIXME

    tcgetattr(s3c2410_serial3_fd, &termios); //FIXME
    tcsetattr(s3c2410_serial3_fd, TCSANOW, &termios); //FIXME

    /* Send 'AT' in ASCII. */
    printf("crespo_ipc_bootstrap: sending AT in ASCII\n");
    for(i=0 ; i < 20 ; i++)
    {
        rc = write(s3c2410_serial3_fd, "AT", 2);
        usleep(50000);
    }
    printf("crespo_ipc_bootstrap: sending AT in ASCII done\n");

    usleep(50000); //FIXME

    /* Get and check bootcore version. */
    read(s3c2410_serial3_fd, &bootcore_version, sizeof(bootcore_version));
    printf("crespo_ipc_bootstrap: got bootcore version: 0x%x\n", bootcore_version);

    if(bootcore_version != BOOTCORE_VERSION)
        goto error_loop;

    /* Get info_size. */
    read(s3c2410_serial3_fd, &info_size, sizeof(info_size));
    printf("crespo_ipc_bootstrap: got info_size: 0x%x\n", info_size);

    /* Send PSI magic. */
    data=PSI_MAGIC;
    write(s3c2410_serial3_fd, &data, sizeof(data));
    printf("crespo_ipc_bootstrap: sent PSI_MAGIC (0x%x)\n", PSI_MAGIC);

    /* Send PSI data len. */
    data_16=PSI_DATA_LEN;
    data_p=(uint8_t *)&data_16;

    for(i=0 ; i < 2 ; i++)
    {
        write(s3c2410_serial3_fd, data_p, 1);
        data_p++;
    }
    printf("crespo_ipc_bootstrap: sent PSI_DATA_LEN (0x%x)\n", PSI_DATA_LEN);

    /* Write the first part of modem.img. */
    FD_ZERO(&fds);
    FD_SET(s3c2410_serial3_fd, &fds);

    timeout.tv_sec=4;
    timeout.tv_usec=0;

    data_p=radio_img_p;

    printf("crespo_ipc_bootstrap: sending the first part of radio.img\n");

    for(i=0 ; i < PSI_DATA_LEN ; i++)
    {
        if(select(FD_SETSIZE, NULL, &fds, NULL, &timeout) == 0)
        {
            printf("crespo_ipc_bootstrap: select timeout passed\n");
            goto error_loop;
        }

        write(s3c2410_serial3_fd, data_p, 1);
        crc_byte=crc_byte ^ *data_p;

        data_p++;
    }

    printf("crespo_ipc_bootstrap: first part of radio.img sent; crc_byte is 0x%x\n", crc_byte);

    if(select(FD_SETSIZE, NULL, &fds, NULL, &timeout) == 0)
    {
        printf("crespo_ipc_bootstrap: select timeout passed\n");
        goto error_loop;
    }

    write(s3c2410_serial3_fd, &crc_byte, sizeof(crc_byte));

    printf("crespo_ipc_bootstrap: crc_byte sent\n");

    data = 0;
    for(i = 0 ; data != 0x01 ; i++)
    {
        if(select(FD_SETSIZE, &fds, NULL, NULL, &timeout) == 0)
        {
            printf("crespo_ipc_bootstrap: select timeout passed\n");
            goto error_loop;
        }

        read(s3c2410_serial3_fd, &data, sizeof(data));

        if(i > 50)
        {
            printf("crespo_ipc_bootstrap: fairly too much attempts to get ACK\n");
            goto error_loop;
        }
    }

    printf("crespo_ipc_bootstrap: close s3c2410_serial3\n");
    close(s3c2410_serial3_fd);

    printf("crespo_ipc_bootstrap: writing the rest of radio.img to modem_ctl.\n");
    /* Seek to the begining of modem_ctl_fd (should already be so). */
    lseek(modem_ctl_fd, 0, SEEK_SET);

    /* Pointer to the remaining part of radio.img. */
    data_p=radio_img_p + PSI_DATA_LEN;

    FD_ZERO(&fds);
    FD_SET(modem_ctl_fd, &fds);

    block_size = 0x100000;

    for(i=0 ; i < (RADIO_IMG_SIZE - PSI_DATA_LEN) / block_size ; i++)
    {
        if(select(FD_SETSIZE, NULL, &fds, NULL, &timeout) == 0)
        {
            printf("crespo_ipc_bootstrap: select timeout passed\n");
            goto error_loop;
        }

        write(modem_ctl_fd, data_p, block_size);
        data_p += block_size;
    }

    free(radio_img_p);

    /* nv_data part. */

    /* Check if all the nv_data files are ok. */
    nv_data_check();

    /* Check if the MD5 is ok. */
    nv_data_md5_check();

    /* Write nv_data.bin to modem_ctl. */
    printf("crespo_ipc_bootstrap: write nv_data to modem_ctl\n");

    nv_data_p = file_read("/efs/nv_data.bin", NV_DATA_SIZE, 1024);
    if (nv_data_p == NULL)
        goto error;
    data_p = nv_data_p;

    lseek(modem_ctl_fd, RADIO_IMG_SIZE, SEEK_SET);

    for(i=0 ; i < 2 ; i++)
    {
        write(modem_ctl_fd, data_p, NV_DATA_SIZE / 2);
        data_p += NV_DATA_SIZE / 2;
    }

    free(nv_data_p);

    rc = 0;
    goto exit;

error_loop:
    printf("%s: something went wrong\n", __func__);
    boot_tries_count++;
    sleep(2);

    goto boot_loop_start;

error:
    printf("%s: something went wrong\n", __func__);
    rc = 1;
exit:
    printf("crespo_ipc_bootstrap: exit\n");
    return rc;
}

int crespo_ipc_client_send(struct ipc_client *client, struct ipc_request *request)
{
    struct modem_io modem_data;
    struct ipc_header reqhdr;
    int rc = 0;

    memset(&modem_data, 0, sizeof(struct modem_io));
    modem_data.data = malloc(MAX_MODEM_DATA_SIZE);
    modem_data.size = request->length + sizeof(struct ipc_header);

    reqhdr.mseq = request->mseq;
    reqhdr.aseq = request->aseq;
    reqhdr.group = request->group;
    reqhdr.index = request->index;
    reqhdr.type = request->type;
    reqhdr.length = (uint16_t) (request->length + sizeof(struct ipc_header));

    modem_data.data = malloc(reqhdr.length);

    memcpy(modem_data.data, &reqhdr, sizeof(struct ipc_header));
    memcpy(modem_data.data + sizeof(struct ipc_header), request->data, request->length);

    assert(client->write != NULL);

    rc = client->write((uint8_t*) &modem_data, sizeof(struct modem_io), client->write_data);
    return rc;
}

int wake_lock(char *lock_name, int size)
{
    int rc = 0;

    wake_lock_fd = open("/sys/power/wake_lock", O_RDWR);
    rc = write(wake_lock_fd, lock_name, size);
    close(wake_lock_fd);

    return rc;
}

int wake_unlock(char *lock_name, int size)
{
    int rc = 0;

    wake_lock_fd = open("/sys/power/wake_unlock", O_RDWR);
    rc = write(wake_unlock_fd, lock_name, size);
    close(wake_unlock_fd);

    return rc;
}

int crespo_ipc_client_recv(struct ipc_client *client, struct ipc_response *response)
{
    struct modem_io modem_data;
    struct ipc_header *resphdr;
    int bread = 0;

    memset(&modem_data, 0, sizeof(struct modem_io));
    modem_data.data = malloc(MAX_MODEM_DATA_SIZE);
    modem_data.size = MAX_MODEM_DATA_SIZE;

    memset(response, 0, sizeof(struct ipc_response));

    wake_lock("secril_fmt-interface", sizeof("secril_fmt-interface") - 1); // FIXME sizeof("...") is ugly!

    assert(client->read != NULL);
    bread = client->read((uint8_t*) &modem_data, sizeof(struct modem_io) + MAX_MODEM_DATA_SIZE, client->read_data);
    if (bread <= 0)
    {
        printf("ERROR: crespo_ipc_client_recv: can't receive enough bytes from modem to process incoming response!\n");
        return 1;
    }

    printf("INFO: crespo_ipc_client_recv: Modem RECV FMT (id=%d cmd=%d size=%d)!\n", modem_data.id, modem_data.cmd, modem_data.size);

    if(modem_data.size <= 0 || modem_data.size >= 0x1000 || modem_data.data == NULL)
    {
        printf("ERROR: crespo_ipc_client_recv: we retrieve less bytes from the modem than we exepected!\n");
        return 1;
    }

    resphdr = (struct ipc_header *) modem_data.data;

    response->mseq = resphdr->mseq;
    response->aseq = resphdr->aseq;
    response->command = IPC_COMMAND(resphdr);
    response->type = resphdr->type;
    response->data_length = modem_data.size - sizeof(struct ipc_header);

    if(response->data_length > 0)
    {
        response->data = malloc(response->data_length);
        memcpy(response->data, (uint8_t *) modem_data.data + sizeof(struct ipc_header), response->data_length);
    }
    else
    {
        response->data = NULL;
    }

    free(modem_data.data);

    wake_unlock("secril_fmt-interface", sizeof("secril_fmt-interface") - 1); // FIXME sizeof("...") is ugly!

    return 0;
}

struct ipc_ops crespo_ipc_ops = {
    .open = NULL,
    .close = NULL,
    .send = crespo_ipc_client_send,
    .recv = crespo_ipc_client_recv,
    .bootstrap = crespo_modem_bootstrap,
};

