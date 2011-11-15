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

#include <radio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define OUTGOING_NUMBER_MAX_LENGTH      86

void ipc_call_outgoing_setup(struct ipc_call_outgoing *message, unsigned char type,
                             unsigned char identity, unsigned char prefix, char *number)
{
    assert(message != NULL);

    memset(message, 0, sizeof(struct ipc_call_outgoing));

    message->type = type;
    message->identity = identity;
    message->prefix = prefix;
    message->length = strlen(number);

    assert(message->length <= OUTGOING_NUMBER_MAX_LENGTH);

    strncpy(message->number, number, message->length);
}

/**
 * Retrieve number of calls in list of calls.
 **/
unsigned int ipc_call_list_response_get_num_entries(struct ipc_message_info *response)
{
    unsigned int count = 0, n = 0;

    assert(response != NULL);
    assert(response->data != NULL);

    count = (unsigned int) *((unsigned char*) response->data);
    return count;
}

/**
 * Retrieve one specific entry from a list of calls.
 **/
struct ipc_call_list_entry* ipc_call_list_response_get_entry(struct ipc_message_info *response, unsigned int num)
{
    unsigned int count = 0, pos = 1, n = 0;
    struct ipc_call_list_entry *entry = NULL;

    assert(response != NULL);
    assert(response->data != NULL);

    count = ipc_call_list_response_get_num_entries(response);
    if (num > count)
        return NULL;

    for (n = 0; n < num + 1; n++)
    {
        entry = (struct ipc_call_list_entry*) (response->data + pos);
        pos += (unsigned int) (sizeof(struct ipc_call_list_entry) + entry->number_len);
    }

    return entry;
}

/**
 * Retrieve the number of a call entry in the list of calls
 **/
char* ipc_call_list_response_get_entry_number(struct ipc_message_info *response, unsigned int num)
{
    unsigned int count = 0, pos = 1, n = 0;
    struct ipc_call_list_entry *entry = NULL;
    char *number = NULL;

    assert(response != NULL);
    assert(response->data != NULL);

    count = ipc_call_list_response_get_num_entries(response);
    if (num > count)
        return NULL;

    for (n = 0; n < num; n++)
    {
        entry = (struct ipc_call_list_entry*) (response->data + pos);
        pos += (unsigned int) (sizeof(struct ipc_call_list_entry) + entry->number_len);
    }

    if (entry == NULL ||
        (unsigned char*) (response->data + pos) == NULL ||
        (unsigned char*) (response->data + pos + entry->number_len) == NULL)
        return NULL;

    number = (char*) malloc(sizeof(char) * entry->number_len);
    strncpy(number, response->data + pos, entry->number_len);

    return number;
}

// vim:ts=4:sw=4:expandtab
