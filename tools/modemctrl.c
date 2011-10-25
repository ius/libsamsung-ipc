/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2010-2011 Joerie de Gram <j.de.gram@gmail.com>
 *               2011 Simon Busch <morphis@gravedo.de>
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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>

#include <radio.h>
#include <crespo_ipc.h>

#define RC_CHECK    printf("line %d, rc = %d\n", __LINE__, rc);

void print_help()
{
    printf("usage: modemctrl <command>\n");
    printf("commands:\n");
    printf("\tbootstrap             bootstrap modem to be ready for processing\n");
    printf("\tpower-on              power on the modem\n");
    printf("\tpower-off             power off the modem\n");
}

int crespo_read_loop(struct ipc_client *client)
{
    struct ipc_response resp;
    void *io_data = NULL;
    int fd = -1;
    fd_set fds;

    io_data = ipc_client_get_handlers_io_data(client);
    fd = *((int *) io_data);

    if(fd < 0) {
        return -1;
    }

    memset(&resp, 0, sizeof(resp));

    FD_ZERO(&fds);
    FD_SET(fd, &fds);

    while(1) {
        usleep(3000);

        select(fd + 1, &fds, NULL, NULL, NULL);

        if(FD_ISSET(fd, &fds))
        {
            ipc_client_recv(client, &resp);
            if(resp.data != NULL)
                free(resp.data);
        }
    }
}

int modem_start(struct ipc_client *client)
{
    int rc;

    ipc_client_set_handlers(client, &crespo_ipc_default_handlers);
    ipc_client_bootstrap_modem(client);

    rc = ipc_client_power_on(client);
    if(rc < 0)
        return -1;

    rc = ipc_client_open(client);
    if(rc < 0)
        return -1;


    return 0;
}

int modem_stop(struct ipc_client *client)
{
    ipc_client_close(client);
    ipc_client_power_off(client);

    return 0;
}

int main(int argc, char *argv[])
{
    struct ipc_client *crespo_fmt_client;
    struct ipc_client *crespo_rfs_client;
    int rc;

    if (argc != 2) {
        print_help();
        exit(1);
    }

    crespo_fmt_client = ipc_client_new(IPC_CLIENT_TYPE_CRESPO_FMT);
    crespo_rfs_client = ipc_client_new(IPC_CLIENT_TYPE_CRESPO_RFS);

    if (!strncmp(argv[1], "power-on", sizeof("power-on"))) {
        ipc_client_power_on(crespo_fmt_client);
    }

    else if (!strncmp(argv[1], "power-off", sizeof("power-off"))) {
        ipc_client_power_off(crespo_fmt_client);
    }

    else if (!strncmp(argv[1], "stop-all", 8)) {
        ipc_client_close(crespo_fmt_client);
        ipc_client_close(crespo_rfs_client);
        ipc_client_power_off(crespo_fmt_client);
    }

    else if (!strncmp(argv[1], "start-fmt", 9)) {
        printf("Starting modem on FMT client\n");
        rc = modem_start(crespo_fmt_client);
        if(rc < 0) {
            printf("Somethign went wrong\n");
            modem_stop(crespo_fmt_client);
            return 1;
        }

        printf("Starting crespo_read_loop on FMT client\n");
        crespo_read_loop(crespo_fmt_client);

        modem_stop(crespo_fmt_client);
    }

    else if (!strncmp(argv[1], "start-rfs", 9)) {
        printf("Starting modem on RFS client\n");
        rc = modem_start(crespo_rfs_client);
        if(rc < 0) {
            printf("Somethign went wrong\n");
            modem_stop(crespo_rfs_client);
            return 1;
        }

        printf("Starting crespo_read_loop on RFS client\n");
        crespo_read_loop(crespo_rfs_client);

        modem_stop(crespo_rfs_client);
    }
    else {
        printf("Unknown command!\n");
    }

    ipc_client_free(crespo_fmt_client);
    ipc_client_free(crespo_rfs_client);

    return 0;
}
