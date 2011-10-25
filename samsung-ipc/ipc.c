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
    struct ipc_ops *ops = NULL;

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
    client->handlers = (struct ipc_handlers *) malloc(sizeof(struct ipc_handlers));
    client->log_handler = log_handler_default;

    return client;
}

int ipc_client_free(struct ipc_client *client)
{
    if(client->handlers->io_data != NULL)
        client->handlers->io_data_unreg(client->handlers->io_data);
    free(client->handlers);
    free(client);
    client = NULL;
    return 0;
}

int ipc_client_set_log_handler(struct ipc_client *client, ipc_client_log_handler_cb log_handler_cb, void *user_data)
{
    if(client == NULL)
        return -1;

    client->log_handler = log_handler_cb;
    client->log_data = user_data;

    return 0;
}

int ipc_client_set_io_handlers(struct ipc_client *client, void *io_data,
                               ipc_io_handler_cb read, ipc_io_handler_cb write,
                               ipc_io_handler_cb open, ipc_io_handler_cb close)
{
    if(client == NULL)
        return -1;

    if(read != NULL)
        client->handlers->read = read;
    if(write != NULL)
        client->handlers->write = write;
    if(open != NULL)
        client->handlers->open = open;
    if(close != NULL)
        client->handlers->close = close;
    if(io_data != NULL)
    {
        client->handlers->io_data = io_data;
        if(client->handlers->io_data_reg != NULL)
            client->handlers->io_data = client->handlers->io_data_reg();
    }

    return 0;
}

int ipc_client_set_handlers(struct ipc_client *client, struct ipc_handlers *handlers)
{
    if(client == NULL)
        return -1;
    if(handlers == NULL)
        return -1;

    memcpy(client->handlers, handlers, sizeof(struct ipc_handlers));

    if(client->handlers->io_data_reg != NULL)
        client->handlers->io_data = client->handlers->io_data_reg();

    return 0;
}

void *ipc_client_get_handlers_io_data(struct ipc_client *client)
{
    return client->handlers->io_data;
}

int ipc_client_set_handlers_io_data(struct ipc_client *client, void *io_data)
{
    if(client == NULL)
        return -1;
    if(io_data == NULL)
        return -1;

    client->handlers->io_data=io_data;

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
    int type;
    int fd;

    if (client == NULL ||
        client->handlers == NULL ||
        client->handlers->open == NULL)
        return -1;

    type = client->type;

    return client->handlers->open(&type, 0, client->handlers->io_data);
}

int ipc_client_close(struct ipc_client *client)
{
    if (client == NULL ||
        client->handlers == NULL ||
        client->handlers->open == NULL)
        return -1;

    return client->handlers->close(NULL, 0, client->handlers->io_data);
}

int ipc_client_power_on(struct ipc_client *client)
{
    if (client == NULL ||
        client->handlers == NULL ||
        client->handlers->open == NULL)
        return -1;

    return client->handlers->power_on(NULL);
}

int ipc_client_power_off(struct ipc_client *client)
{
    if (client == NULL ||
        client->handlers == NULL ||
        client->handlers->open == NULL)
        return -1;

    return client->handlers->power_off(NULL);
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
inline void ipc_client_send_get(struct ipc_client *client, const unsigned short command, unsigned char aseq)
{
    ipc_client_send(client, command, IPC_TYPE_GET, 0, 0, aseq);
}

inline void ipc_client_send_exec(struct ipc_client *client, const unsigned short command, unsigned char aseq)
{
    ipc_client_send(client, command, IPC_TYPE_EXEC, 0, 0, aseq);
}

/* Wrapper for ipc_send */
void ipc_client_send(struct ipc_client *client, const unsigned short command, const char type, unsigned char *data, const int length, unsigned char mseq)
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

