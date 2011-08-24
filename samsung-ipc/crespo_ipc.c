/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2011 Paul Kocialkowski <contact@paulk.fr>
 * Copyright (C) 2011 Joerie de Gram <j.de.gram@gmail.com>
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
 *
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

#include <radio.h>

#include "modem_ctl.h"
#include "nv_data.h"
#include "ipc.h"

int s3c2410_serial3_fd=	-1;
int modem_ctl_fd=	-1;
int modem_fmt_fd=	-1;
int modem_rfs_fd=	-1;
int wake_lock_fd=	-1;
int wake_unlock_fd=	-1;

void *mtd_read(char *mtd_name, int size, int block_size)
{
	void *mtd_p=NULL;
	uint8_t *data_p=NULL;

	loff_t offs;
	int fd;
	int i;

	if(mtd_name == NULL || size <= 0 || block_size <= 0)
		goto error;

	printf("mtd_read: reading 0x%x bytes from %s with 0x%x bytes block size\n", size, mtd_name, block_size);

	mtd_p=malloc(size);
	if(mtd_p == NULL)
		goto error;

	memset(mtd_p, 0, size);

	data_p=(uint8_t *) mtd_p;

	fd=open(mtd_name, O_RDONLY);
	if(fd < 0)
		goto error;

	for(i=0 ; i < size / block_size ; i++)
	{
		offs=i * block_size;
		if(ioctl(fd, MEMGETBADBLOCK, &offs) == 1)
		{
			printf("mtd_read: warning: bad block at offset %lld\n", offs);
			data_p+=block_size;
			continue;
		}

		read(fd, data_p, block_size);
		data_p+=block_size;
	}

	close(fd);

	return mtd_p;

error:
	printf("%s: something went wrong\n", __func__);
	return NULL;
}

void *file_read(char *file_name, int size, int block_size)
{
	void *file_p=NULL;
	uint8_t *data_p=NULL;

	int fd;
	int i;

	if(file_name == NULL || size <= 0 || block_size <= 0)
		goto error;

	printf("file_read: reading 0x%x bytes from %s with 0x%x bytes block size\n", size, file_name, block_size);

	file_p=malloc(size);
	if(file_p == NULL)
		goto error;

	memset(file_p, 0, size);

	data_p=(uint8_t *) file_p;

	fd=open(file_name, O_RDONLY);
	if(fd < 0)
		goto error;

	for(i=0 ; i < size / block_size ; i++)
	{
		read(fd, data_p, block_size);
		data_p+=block_size;
	}

	close(fd);

	return file_p;

error:
	printf("%s: something went wrong\n", __func__);
	return NULL;
}

int ipc_open(void)
{
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

	printf("ipc_open: enter\n");

boot_loop_start:
	if(boot_tries_count > 5)
	{
		printf("ipc_open: boot has failed too many times.\n");
		goto error;
	}

	/* Read the radio.img image. */
	printf("ipc_open: reading radio image\n");
	radio_img_p=mtd_read("/dev/mtd/mtd5ro", RADIO_IMG_SIZE, 0x1000);
	printf("ipc_open: radio image read\n");

	printf("ipc_open: open modem_ctl\n");
	modem_ctl_fd=open("/dev/modem_ctl", O_RDWR | O_NDELAY);
	if(modem_ctl_fd < 0)
		goto error_loop;

	/* Reset the modem before init to send the first part of modem.img. */
	ioctl(modem_ctl_fd, IOCTL_MODEM_RESET);
	usleep(400000);

	printf("ipc_open: open s3c2410_serial3\n");
	s3c2410_serial3_fd=open("/dev/s3c2410_serial3", O_RDWR | O_NDELAY);
	if(s3c2410_serial3_fd < 0)
		goto error_loop;

	/* Setup the s3c2410 serial. */
	printf("ipc_open: setup s3c2410_serial3\n");
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
	printf("ipc_open: sending AT in ASCII\n");
	for(i=0 ; i < 20 ; i++)
	{
		write(s3c2410_serial3_fd, "AT", 2);
		usleep(50000);
	}
	printf("ipc_open: sending AT in ASCII done\n");

	usleep(50000); //FIXME

	/* Get and check bootcore version. */
	read(s3c2410_serial3_fd, &bootcore_version, sizeof(bootcore_version));
	printf("ipc_open: got bootcore version: 0x%x\n", bootcore_version);

	if(bootcore_version != BOOTCORE_VERSION)
		goto error_loop;

	/* Get info_size. */
	read(s3c2410_serial3_fd, &info_size, sizeof(info_size));
	printf("ipc_open: got info_size: 0x%x\n", info_size);

	/* Send PSI magic. */
	data=PSI_MAGIC;
	write(s3c2410_serial3_fd, &data, sizeof(data));
	printf("ipc_open: sent PSI_MAGIC (0x%x)\n", PSI_MAGIC);

	/* Send PSI data len. */
	data_16=PSI_DATA_LEN;
	data_p=(uint8_t *)&data_16;

	for(i=0 ; i < 2 ; i++)
	{
		write(s3c2410_serial3_fd, data_p, 1);
		data_p++;
	}
	printf("ipc_open: sent PSI_DATA_LEN (0x%x)\n", PSI_DATA_LEN);

	/* Write the first part of modem.img. */
	FD_ZERO(&fds);
	FD_SET(s3c2410_serial3_fd, &fds);

	timeout.tv_sec=4;
	timeout.tv_usec=0;

	data_p=radio_img_p;

	printf("ipc_open: sending the first part of radio.img\n");

	for(i=0 ; i < PSI_DATA_LEN ; i++)
	{
		if(select(FD_SETSIZE, NULL, &fds, NULL, &timeout) == 0)
		{
			printf("ipc_open: select timeout passed\n");
			goto error_loop;
		}

		write(s3c2410_serial3_fd, data_p, 1);
		crc_byte=crc_byte ^ *data_p;

		data_p++;
	}

	printf("ipc_open: first part of radio.img sent; crc_byte is 0x%x\n", crc_byte);

	if(select(FD_SETSIZE, NULL, &fds, NULL, &timeout) == 0)
	{
		printf("ipc_open: select timeout passed\n");
		goto error_loop;
	}

	write(s3c2410_serial3_fd, &crc_byte, sizeof(crc_byte));

	printf("ipc_open: crc_byte sent\n");

	data=0;
	for(i=0 ; data != 0x01 ; i++)
	{
		if(select(FD_SETSIZE, &fds, NULL, NULL, &timeout) == 0)
		{
			printf("ipc_open: select timeout passed\n");
			goto error_loop;
		}

		read(s3c2410_serial3_fd, &data, sizeof(data));

		if(i > 50)
		{
			printf("ipc_open: fairly too much attempts to get ACK\n");
			goto error_loop;
		}
	}

	printf("ipc_open: close s3c2410_serial3\n");
	close(s3c2410_serial3_fd);

	printf("ipc_open: writing the rest of radio.img to modem_ctl.\n");
	/* Seek to the begining of modem_ctl_fd (should already be so). */
	lseek(modem_ctl_fd, 0, SEEK_SET);

	/* Pointer to the remaining part of radio.img. */
	data_p=radio_img_p + PSI_DATA_LEN;

	FD_ZERO(&fds);
	FD_SET(modem_ctl_fd, &fds);

	block_size=0x100000;

	for(i=0 ; i < (RADIO_IMG_SIZE - PSI_DATA_LEN) / block_size ; i++)
	{
		if(select(FD_SETSIZE, NULL, &fds, NULL, &timeout) == 0)
		{
			printf("ipc_open: select timeout passed\n");
			goto error_loop;
		}

		write(modem_ctl_fd, data_p, block_size);
		data_p+=block_size;
	}

	free(radio_img_p);

	/* nv_data part. */

	/* Check if all the nv_data files are ok. */
	nv_data_check();

	/* Check if the MD5 is ok. */
	nv_data_md5_check();

	/* Write nv_data.bin to modem_ctl. */
	printf("ipc_open: write nv_data to modem_ctl\n");

	nv_data_p=file_read("/efs/nv_data.bin", NV_DATA_SIZE, 1024);
	data_p=nv_data_p;

	lseek(modem_ctl_fd, RADIO_IMG_SIZE, SEEK_SET);

	for(i=0 ; i < 2 ; i++)
	{
		write(modem_ctl_fd, data_p, NV_DATA_SIZE / 2);
		data_p+=NV_DATA_SIZE / 2;
	}

	free(nv_data_p);

	modem_fmt_fd=open("/dev/modem_fmt", O_RDWR | O_NDELAY);
	modem_rfs_fd=open("/dev/modem_rfs", O_RDWR | O_NDELAY);

	rc=0;
	goto exit;

error_loop:
	printf("%s: something went wrong\n", __func__);
	boot_tries_count++;
	sleep(2);

	goto boot_loop_start;

error:
	printf("%s: something went wrong\n", __func__);
	rc=1;
exit:
	printf("ipc_open: exit\n");
	return rc;
}

int ipc_close(void)
{
	close(modem_fmt_fd);
	close(modem_rfs_fd);
	close(modem_ctl_fd);

	return 0;
}

void ipc_power_on(void)
{
	ioctl(modem_ctl_fd, IOCTL_MODEM_START);
}

void ipc_power_off(void)
{
	ioctl(modem_ctl_fd, IOCTL_MODEM_OFF);
}

void ipc_send(struct ipc_request *request)
{
	struct modem_io modem_data;
	struct ipc_header hdlc_data;
	uint8_t *data_p;

	memset(&modem_data, 0, sizeof(struct modem_io));
	modem_data.data=malloc(0x1000);
	modem_data.size=request->length + sizeof(struct ipc_header);

	hdlc_data.mseq=request->mseq;
	hdlc_data.aseq=request->aseq;
	hdlc_data.group=request->group;
	hdlc_data.index=request->index;
	hdlc_data.type=request->type;
	hdlc_data.length=(uint16_t) (request->length + sizeof(struct ipc_header));

	modem_data.data=malloc(hdlc_data.length);
	data_p=modem_data.data;

	memcpy(data_p, &hdlc_data, sizeof(struct ipc_header));
	data_p+=sizeof(struct ipc_header);
	memcpy(data_p, request->data, request->length);

	ioctl(modem_fmt_fd, IOCTL_MODEM_SEND, &modem_data);
}

void wake_lock(char *lock_name, int size)
{
	if(wake_lock_fd < 0)
		wake_lock_fd=open("/sys/power/wake_lock", O_RDWR);

	write(wake_lock_fd, lock_name, size);
}

void wake_unlock(char *lock_name, int size)
{
	if(wake_unlock_fd < 0)
		wake_lock_fd=open("/sys/power/wake_unlock", O_RDWR);

	write(wake_unlock_fd, lock_name, size);
}

int ipc_recv(struct ipc_response *response)
{
	struct modem_io modem_data;
	struct ipc_header *hdlc_data;

	fd_set fds;

recv_loop_start:
	memset(&modem_data, 0, sizeof(struct modem_io));
	modem_data.data=malloc(0x1000);
	modem_data.size=0x1000;

	memset(response, 0, sizeof(struct ipc_response));

	/* TODO: Should be with the wakelocks. */

	wake_lock("secril_fmt-interface", sizeof("secril_fmt-interface") - 1);

	FD_ZERO(&fds);
	FD_SET(modem_fmt_fd, &fds);
	FD_SET(modem_rfs_fd, &fds);

	select(FD_SETSIZE, &fds, NULL, NULL, NULL);

	if(FD_ISSET(modem_rfs_fd, &fds))
	{
		ioctl(modem_rfs_fd, IOCTL_MODEM_RECV, &modem_data);
		printf("ipc_recv: Modem RECV RFS (id=%d cmd=%d size=%d)!\n", modem_data.id, modem_data.cmd, modem_data.size);
		free(modem_data.data);
		wake_unlock("secril_fmt-interface", sizeof("secril_fmt-interface") - 1);

		goto recv_loop_start;
		return 0;
	}

	if(FD_ISSET(modem_fmt_fd, &fds))
	{
		ioctl(modem_fmt_fd, IOCTL_MODEM_RECV, &modem_data);
		printf("ipc_recv: Modem RECV FMT (id=%d cmd=%d size=%d)!\n", modem_data.id, modem_data.cmd, modem_data.size);

		if(modem_data.size <= 0 || modem_data.size >= 0x1000 || modem_data.data == NULL)
		{
			printf("ipc_recv: Something is wrong with the received message\n");
			return 1;
		}

		hdlc_data=(struct ipc_header *) modem_data.data;

		response->mseq=hdlc_data->mseq;
		response->aseq=hdlc_data->aseq;
		response->command=IPC_COMMAND(hdlc_data);
		response->type=hdlc_data->type;
		response->data_length=modem_data.size - sizeof(struct ipc_header);

		if(response->data_length > 0)
		{
			response->data=malloc(response->data_length);
			memcpy(response->data, (uint8_t *)modem_data.data + sizeof(struct ipc_header), response->data_length);
		}
		else
		{
			response->data=NULL;
		}

		free(modem_data.data);

		wake_unlock("secril_fmt-interface", sizeof("secril_fmt-interface") - 1);
		return 0;
	}

	return 1;
}
