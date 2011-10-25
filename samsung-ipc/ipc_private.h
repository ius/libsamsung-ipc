/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2011 Simon Busch <morphis@gravedo.de>
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

#ifndef __IPC_PRIVATE_H__
#define __IPC_PRIVATE_H__

struct ipc_client;

void ipc_client_log(struct ipc_client *client, const char *message, ...);

struct ipc_ops {
    int (*bootstrap)(struct ipc_client *client);
    int (*send)(struct ipc_client *client, struct ipc_request*);
    int (*recv)(struct ipc_client *client, struct ipc_response*);
};

struct ipc_handlers {
    /* Transport handlers/data */
    ipc_io_handler_cb read;
    ipc_io_handler_cb write;
    ipc_io_handler_cb open;
    ipc_io_handler_cb close;

    ipc_handler_data_cb io_data_reg;
    ipc_handler_cb io_data_unreg;
    void *io_data;

    /* Power handlers */
    ipc_handler_cb power_on;
    ipc_handler_cb power_off;
};

struct ipc_client {
    int type;

    ipc_client_log_handler_cb log_handler;
    void *log_data;

    struct ipc_ops *ops;
    struct ipc_handlers *handlers;
};



#endif
