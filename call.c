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

#include <call.h>
#include "radio_internal.h"

void ipc_call_outgoing(const char *number, int identity, int request_id)
{
	struct ipc_call_outgoing call;

	memset(&call, 0x00, sizeof(call));

	if(strlen(number) > 82) {
		printf("Outgoing call number too long\n");
		return;
	}

	call.type = IPC_CALL_TYPE_VOICE;
	call.identity = identity;
	call.prefix = IPC_CALL_PREFIX_NONE;

	call.length = strlen(number);
	memcpy(call.number, number, strlen(number));

	ipc_send(IPC_CALL_OUTGOING, IPC_TYPE_EXEC, (unsigned char*)&call, sizeof(call), request_id);
}

void ipc_call_release(int request_id)
{
	ipc_send_exec(IPC_CALL_RELEASE, request_id);
}

void ipc_call_answer(int request_id)
{
	ipc_send_exec(IPC_CALL_ANSWER, request_id);
}

void ipc_call_list(int request_id)
{
	ipc_send_get(IPC_CALL_LIST, request_id);
}

