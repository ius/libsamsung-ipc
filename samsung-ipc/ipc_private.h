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

#include <radio.h>

struct ipc_client;

void ipc_client_log(struct ipc_client *client, const char *message, ...);

struct ipc_ops {
    int (*bootstrap)(struct ipc_client *client);
    int (*send)(struct ipc_client *client, struct ipc_message_info *);
    int (*recv)(struct ipc_client *client, struct ipc_message_info *);
};

struct ipc_handlers {
    /* Transport handlers/data */
    ipc_io_handler_cb read;
    void *read_data;
    ipc_io_handler_cb write;
    void *write_data;
    ipc_io_handler_cb open;
    void *open_data;
    ipc_io_handler_cb close;
    void *close_data;

    /* Power handlers */
    ipc_handler_cb power_on;
    void *power_on_data;
    ipc_handler_cb power_off;
    void *power_off_data;
};

struct ipc_client {
    int type;

    ipc_client_log_handler_cb log_handler;
    void *log_data;

    struct ipc_ops *ops;
    struct ipc_handlers *handlers;
};

#endif

// vim:ts=4:sw=4:expandtab
