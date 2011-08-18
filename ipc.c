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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <radio.h>

/* Convenience functions for ipc_send */
inline void ipc_msg_send_get(const int command, unsigned char aseq)
{
	ipc_msg_send(command, IPC_TYPE_GET, 0, 0, aseq);
}

inline void ipc_msg_send_exec(const int command, unsigned char aseq)
{
	ipc_msg_send(command, IPC_TYPE_EXEC, 0, 0, aseq);
}

/* Wrapper for ipc_send */
void ipc_msg_send(const int command, const int type, unsigned char *data, const int length, unsigned char mseq)
{
	struct ipc_request request;

	request.mseq = mseq;
	request.aseq = 0xff;
	request.group = IPC_GROUP(command);
	request.index = IPC_INDEX(command);
	request.type = type;
	request.length = length;
	request.data = data;

	ipc_send(&request);
}

