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

char* ipc_sec_rsim_access_response_get_file_data(struct ipc_response *response)
{
    if (response == NULL)
        return NULL;

    struct ipc_sec_rsim_access_response *rsimresp = (struct ipc_sec_rsim_access_response*) response->data;
    char *file_data = (char*) malloc(sizeof(char) * rsimresp->len);
    memcpy(file_data, response->data + sizeof(struct ipc_sec_rsim_access_response), rsimresp->len);
    return file_data;
}
