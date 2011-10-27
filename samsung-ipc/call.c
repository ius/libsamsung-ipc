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

    message->type = type;
    message->identity = identity;
    message->prefix = prefix;
    strncpy(message->number, number, OUTGOING_NUMBER_MAX_LENGTH);
}

