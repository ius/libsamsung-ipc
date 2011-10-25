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

void ipc_sec_pin_status_set_setup(struct ipc_sec_pin_status_set *message,
                                  unsigned char pin_type, char *pin1, char *pin2)
{
    assert(message != NULL);

    message->type = pin_type;

    if (pin1 != NULL)
    {
        strncpy(message->pin1, pin1, 8);
        message->length1 = strlen(pin1);
    }

    if (pin2 != NULL)
    {
        strncpy(message->pin2, pin2, 8);
        message->length2 = strlen(pin2);
    }
}

char* ipc_sec_rsim_access_response_get_file_data(struct ipc_response *response)
{
    int n = 0;
    int offset = (int) sizeof(struct ipc_sec_rsim_access_response);
    int size = 0;

    if (response == NULL)
        return NULL;

    struct ipc_sec_rsim_access_response *rsimresp = (struct ipc_sec_rsim_access_response*) response->data;
    char *file_data = (char*) malloc(sizeof(char) * rsimresp->len);

    for (n = 0; n < rsimresp->len; n++)
    {
        if (response->data[offset + n] == 0x0)
            continue;
        else if (response->data[offset + n] == 0xff)
            break;
        else {
            file_data[size] = response->data[offset + n];
            size++;
        }
    }

    if (size < rsimresp->len)
        file_data = (char*) realloc(file_data, sizeof(char) * size);

    return file_data;
}
