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

extern struct ipc_ops ipc_ops;
extern struct ipc_handlers ipc_default_handlers;

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
        case IPC_CLIENT_TYPE_FMT:
        case IPC_CLIENT_TYPE_RFS:
            ops = &ipc_ops;
            break;
        default:
            return NULL;
    }

    client = (struct ipc_client*) malloc(sizeof(struct ipc_client));
    client->type = client_type;
    client->ops = ops;
    client->handlers = (struct ipc_handlers *) malloc(sizeof(struct ipc_handlers));
    client->log_handler = log_handler_default;

    /* FIXME: WE DONT WANT THIS FOR FSO!!! */
    /* Set default handlers */
    ipc_client_set_handlers(client, &ipc_default_handlers);

    return client;
}

int ipc_client_free(struct ipc_client *client)
{
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

int ipc_client_set_handlers(struct ipc_client *client, struct ipc_handlers *handlers)
{
    if(client == NULL)
        return -1;
    if(handlers == NULL)
        return -1;

    memcpy(client->handlers, handlers, sizeof(struct ipc_handlers));

    return 0;
}

int ipc_client_set_io_handlers(struct ipc_client *client, 
                               ipc_io_handler_cb read, void *read_data,
                               ipc_io_handler_cb write, void *write_data)
{
    if(client == NULL)
        return -1;

    if(read != NULL)
        client->handlers->read = read;
    if(read_data != NULL)
        client->handlers->read_data = read_data;
    if(write != NULL)
        client->handlers->write = write;
    if(write_data != NULL)
        client->handlers->write_data = write_data;

    return 0;
}

int ipc_client_set_all_handlers_data(struct ipc_client *client, void *data)
{
    if(client == NULL)
        return -1;
    if(data == NULL)
        return -1;

    client->handlers->read_data = data;
    client->handlers->write_data = data;
    client->handlers->open_data = data;
    client->handlers->close_data = data;
    client->handlers->power_on_data = data;
    client->handlers->power_off_data = data;

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

    return client->handlers->open(&type, 0, client->handlers->open_data);
}

int ipc_client_close(struct ipc_client *client)
{
    if (client == NULL ||
        client->handlers == NULL ||
        client->handlers->open == NULL)
        return -1;

    return client->handlers->close(NULL, 0, client->handlers->close_data);
}

int ipc_client_power_on(struct ipc_client *client)
{
    if (client == NULL ||
        client->handlers == NULL ||
        client->handlers->open == NULL)
        return -1;

    return client->handlers->power_on(client->handlers->power_on_data);
}

int ipc_client_power_off(struct ipc_client *client)
{
    if (client == NULL ||
        client->handlers == NULL ||
        client->handlers->open == NULL)
        return -1;

    return client->handlers->power_off(client->handlers->power_off_data);
}

int _ipc_client_send(struct ipc_client *client, struct ipc_message_info *request)
{
    if (client == NULL ||
        client->ops == NULL ||
        client->ops->send == NULL)
        return -1;

    return client->ops->send(client, request);
}

/* Convenience functions for ipc_send */
inline void ipc_client_send_get(struct ipc_client *client, const unsigned short command, unsigned char mseq)
{
    ipc_client_send(client, command, IPC_TYPE_GET, 0, 0, mseq);
}

inline void ipc_client_send_exec(struct ipc_client *client, const unsigned short command, unsigned char mseq)
{
    ipc_client_send(client, command, IPC_TYPE_EXEC, 0, 0, mseq);
}

/* Wrapper for ipc_send */
void ipc_client_send(struct ipc_client *client, const unsigned short command, const char type, unsigned char *data, const int length, unsigned char mseq)
{
    struct ipc_message_info request;

    request.mseq = mseq;
    request.aseq = 0xff;
    request.group = IPC_GROUP(command);
    request.index = IPC_INDEX(command);
    request.type = type;
    request.length = length;
    request.data = data;

    _ipc_client_send(client, &request);
}

int ipc_client_recv(struct ipc_client *client, struct ipc_message_info *response)
{
    if (client == NULL ||
        client->ops == NULL ||
        client->ops->recv == NULL)
        return -1;

    return client->ops->recv(client, response);
}

// vim:ts=4:sw=4:expandtab

