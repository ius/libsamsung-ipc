/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2010-2011 Joerie de Gram <j.de.gram@gmail.com>
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

#ifndef __RADIO_H__
#define __RADIO_H__

#include <stdint.h>

#include "types.h"
#include "util.h"

#define IPC_CLIENT_TYPE_CRESPO_FMT      1
#define IPC_CLIENT_TYPE_CRESPO_RFS      2
#define IPC_CLIENT_TYPE_H1              3

#define IPC_COMMAND(f)  ((f->group << 8) | f->index)
#define IPC_GROUP(m)    (m >> 8)
#define IPC_INDEX(m)    (m & 0xff)

struct ipc_header {
    unsigned short length;
    unsigned char mseq, aseq;
    unsigned char group, index, type;
} __attribute__((__packed__));

struct ipc_request {
    unsigned char mseq;
    unsigned char aseq;
    unsigned char group;
    unsigned char index;
    unsigned char type;
    unsigned int length;
    unsigned char *data;
};

struct ipc_response {
    unsigned char mseq, aseq;
    unsigned short command;
    unsigned char type;
    unsigned int data_length;
    unsigned char *data;
};

struct ipc_client;
struct ipc_handlers;

typedef void (*ipc_client_log_handler_cb)(const char *message, void *user_data);

typedef void *(*ipc_handler_data_cb)(void);
typedef int (*ipc_io_handler_cb)(void *data, unsigned int size, void *io_data);
typedef int (*ipc_handler_cb)(void *data);

struct ipc_client *ipc_client_new(int client_type);
int ipc_client_free(struct ipc_client *client);

int ipc_client_set_log_handler(struct ipc_client *client, ipc_client_log_handler_cb log_handler_cb, void *user_data);

int ipc_client_set_handlers(struct ipc_client *client, struct ipc_handlers *handlers);
int ipc_client_set_io_handlers(struct ipc_client *client, void *io_data,
                               ipc_io_handler_cb read, ipc_io_handler_cb write,
                               ipc_io_handler_cb open, ipc_io_handler_cb close);
void *ipc_client_get_handlers_io_data(struct ipc_client *client);
int ipc_client_set_handlers_io_data(struct ipc_client *client, void *io_data);

int ipc_client_bootstrap_modem(struct ipc_client *client);
int ipc_client_open(struct ipc_client *client);
int ipc_client_close(struct ipc_client *client);
int ipc_client_power_on(struct ipc_client *client);
int ipc_client_power_off(struct ipc_client *client);

int ipc_client_recv(struct ipc_client *client, struct ipc_response *response);

/* Convenience functions for ipc_send */
void ipc_client_send(struct ipc_client *client, const unsigned short command, const char type, unsigned char *data,
                     const int length, unsigned char mseq);
void ipc_client_send_get(struct ipc_client *client, const unsigned short command, unsigned char aseq);
void ipc_client_send_exec(struct ipc_client *client, const unsigned short command, unsigned char aseq);

/* Utility functions */
const char *ipc_command_type_to_str(int command);
const char *ipc_response_type_to_str(int type);

#endif

