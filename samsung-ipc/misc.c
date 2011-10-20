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

#define DEFAULT_IMSI_LENGTH         15

char* ipc_parse_misc_me_imsi(uint8_t *data, unsigned int size)
{
    if (data == NULL || size != DEFAULT_IMSI_LENGTH + 1 || data[0] != DEFAULT_IMSI_LENGTH)
        return NULL;

    char *buffer = (char*) malloc(sizeof(char) * DEFAULT_IMSI_LENGTH);
    memcpy(buffer, &data[1], DEFAULT_IMSI_LENGTH);
    return buffer;
}
