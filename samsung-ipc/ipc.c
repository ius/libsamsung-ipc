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
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#include <radio.h>

#include "ipc_private.h"

extern struct ipc_ops crespo_ipc_ops;
// extern struct ipc_ops h1_ipc_ops;


void log_handler_default(const char *message, void *user_data)
{
    printf("%s\n", message);
}

void ipc_client_log(struct ipc_client *client, const char *message, ...)
{
    assert(client->log_handler != NULL);

    va_list args;
    char buffer[4096];

    va_start(args, message);
    vsprintf(buffer, message, args);
    client->log_handler(buffer, client->log_data);
    va_end(args);
}

struct ipc_client* ipc_client_new(int client_type)
{
    struct ipc_client *client;
    struct ips_ops *ops = NULL;

    switch (client_type)
    {
        case IPC_CLIENT_TYPE_CRESPO_FMT:
        case IPC_CLIENT_TYPE_CRESPO_RFS:
            ops = &crespo_ipc_ops;
            break;
        case IPC_CLIENT_TYPE_H1:
            // ops = &h1_ipc_ops;
            break;
        default:
            break;
    }

    client = (struct ipc_client*) malloc(sizeof(struct ipc_client));
    client->type = client_type;
    client->ops = ops;
    client->log_handler = log_handler_default;

    return client;
}

int ipc_client_free(struct ipc_client *client)
{
    free(client);
    client = NULL;
    return 0;
}

int ipc_client_set_log_handler(struct ipc_client *client, ipc_client_log_handler_cb log_handler_cb, void *user_data)
{
    if (client == NULL)
        return -1;

    client->log_handler = log_handler_cb;
    client->log_data = user_data;
}


int ipc_client_set_delegates(struct ipc_client *client,
                             ipc_client_transport_cb write, void *write_data,
                             ipc_client_transport_cb read, void *read_data)
{
    if (client == NULL)
        return -1;

    client->read = read;
    client->read_data = read_data;
    client->write = write;
    client->write_data = write_data;

    return 0;
}

int ipc_client_bootstrap_modem(struct ipc_client *client)
{
    if (client == NULL ||
        client->ops == NULL ||
        client->ops->bootstrap == NULL)
        return -1;

    return client->ops->bootstrap(client);
}

int ipc_client_open(struct ipc_client *client)
{
    if (client == NULL ||
        client->ops == NULL ||
        client->ops->open == NULL)
        return -1;

    return client->ops->open(client);
}

int ipc_client_close(struct ipc_client *client)
{
    if (client == NULL ||
        client->ops == NULL ||
        client->ops->close == NULL)
        return -1;

    return client->ops->close(client);
}

int _ipc_client_send(struct ipc_client *client, struct ipc_request *request)
{
    if (client == NULL ||
        client->ops == NULL ||
        client->ops->send == NULL)
        return -1;

    return client->ops->send(client, request);
}

/* Convenience functions for ipc_send */
inline void ipc_client_send_get(struct ipc_client *client, const int command, unsigned char aseq)
{
    ipc_client_send(client, command, IPC_TYPE_GET, 0, 0, aseq);
}

inline void ipc_client_send_exec(struct ipc_client *client, const int command, unsigned char aseq)
{
    ipc_client_send(client, command, IPC_TYPE_EXEC, 0, 0, aseq);
}

/* Wrapper for ipc_send */
void ipc_client_send(struct ipc_client *client, const int command, const int type, unsigned char *data, const int length, unsigned char mseq)
{
    struct ipc_request request;

    request.mseq = mseq;
    request.aseq = 0xff;
    request.group = IPC_GROUP(command);
    request.index = IPC_INDEX(command);
    request.type = type;
    request.length = length;
    request.data = data;

    _ipc_client_send(client, &request);
}

int ipc_client_recv(struct ipc_client *client, struct ipc_response *response)
{
    if (client == NULL ||
        client->ops == NULL ||
        client->ops->recv == NULL)
        return -1;

    return client->ops->recv(client, response);
}

