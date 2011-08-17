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

#ifndef __RADIO_H__
#define __RADIO_H__

#include "types.h"
#include "util.h"

#define IPC_COMMAND(f)	((f->group << 8) | f->index)
#define IPC_GROUP(m)	(m >> 8)
#define IPC_INDEX(m)	(m & 0xff)

/* IPC header for use by device specific code*/
struct ipc_header {
	unsigned short length;
	unsigned char mseq, aseq;
	unsigned char group, index, type;
} __attribute__((__packed__));

/* Request struct passed as parameter to ipc_send() */
struct ipc_request {
	unsigned char mseq, aseq, group, index, type;
	unsigned int length;
	unsigned char *data;
};

/* Response struct returned by ipc_recv() */
struct ipc_response {
	unsigned char mseq, aseq;
	unsigned short command;
	unsigned char type;
	unsigned int data_length;
	unsigned char *data;
};

int ipc_open();
int ipc_close();

void ipc_power_on();
void ipc_power_off();

void ipc_send(struct ipc_request *request);
int ipc_recv(struct ipc_response *response);

/* Convenience functions for ipc_send */
void ipc_msg_send(const int command, const int type, unsigned char *data, const int length, unsigned char aseq);
void ipc_msg_send_get(const int command, unsigned char aseq);
void ipc_msg_send_exec(const int command, unsigned char aseq);

/* Utility functions */
const char *ipc_str(struct ipc_response *frame);
const char *ipc_response_type(struct ipc_response *frame);

#endif

