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

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "ipc_private.h"
#include "h1_ipc.h"

/* FIXME: move to io_data */
static int fd = 0;

int h1_ipc_open()
{
	struct termios termios;

	fd = open(DPRAM_TTY, O_RDWR);

	if(fd < 0) {
		return 1;
	}

	tcgetattr(fd, &termios);
	cfmakeraw(&termios);
	tcsetattr(fd, TCSANOW, &termios);

	return 0;
}

int h1_ipc_close()
{
	if(fd) {
		return close(fd);
	}

	return 0;
}

int h1_ipc_power_on()
{
	ioctl(fd, IOCTL_PHONE_ON);

	return 0;
}

int h1_ipc_power_off()
{
	ioctl(fd, IOCTL_PHONE_OFF);

	return 0;
}

int  h1_ipc_send(struct ipc_client *client, struct ipc_message_info *request)
{
	struct hdlc_header *hdlc;
	unsigned char *frame;
	int frame_length;

	/* Frame length: HDLC/IPC header + payload length + HDLC flags (2) */
	frame_length = (sizeof(*hdlc) + request->length + 2);

	frame = (unsigned char*)malloc(frame_length);
	frame[0] = FRAME_START;
	frame[frame_length-1] = FRAME_END;

	/* Setup HDLC header */
	hdlc = (struct hdlc_header*)(frame + 1);

	hdlc->length = (sizeof(*hdlc) + request->length);
	hdlc->unknown = 0;

	/* IPC data */
	hdlc->ipc.length = (sizeof(hdlc->ipc) + request->length);
	hdlc->ipc.mseq = request->mseq;
	hdlc->ipc.aseq = request->aseq;
	hdlc->ipc.group = request->group;
	hdlc->ipc.index = request->index;
	hdlc->ipc.type = request->type;

	ipc_client_log(client, "sending %s %s\n",
			ipc_command_type_to_str(IPC_COMMAND(request)),
			ipc_response_type_to_str(request->type));

	hex_dump(frame, frame_length);

	client->handlers->write(frame, frame_length, client->handlers->io_data);

	free(frame);

	return 0;
}

int h1_ipc_recv(struct ipc_client *client, struct ipc_message_info *response)
{
	unsigned char buf[4];
	unsigned char *data;
	unsigned short *frame_length;
	struct ipc_header *ipc;
	int num_read;
	int left;

	num_read = client->handlers->read((void*)buf, sizeof(buf), client->handlers->io_data);

	if(num_read == sizeof(buf) && *buf == FRAME_START) {
		frame_length = (unsigned short*)&buf[1];
		left = (*frame_length - 3 + 1);

		data = (unsigned char*)malloc(left);
		num_read = client->handlers->read((void*)data, left, client->handlers->io_data);

		if(num_read == left && data[left-1] == FRAME_END) {
			ipc = (struct ipc_header*)data;
			response->mseq = ipc->mseq;
			response->aseq = ipc->aseq;
			response->group = ipc->group;
			response->index = ipc->index;
			response->type = ipc->type;
			response->length = (ipc->length - sizeof(*ipc));

			response->data = (unsigned char*)malloc(response->length);
			memcpy(response->data, (data + sizeof(*ipc)), response->length);

			ipc_client_log(client, "received %s %s\n",
					ipc_command_type_to_str(IPC_COMMAND(response)),
					ipc_response_type_to_str(response->type));

			hex_dump(data, num_read-1);

			return 0;
		}
	}

	return 0;
}

int h1_ipc_read(void *data, unsigned int size, void *io_data)
{
	return read(fd, data, size);
}

int h1_ipc_write(void *data, unsigned int size, void *io_data)
{
	return write(fd, data, size);
}

struct ipc_handlers ipc_default_handlers = {
    .open = h1_ipc_open,
    .close = h1_ipc_close,
    .power_on = h1_ipc_power_on,
    .power_off = h1_ipc_power_off,
    .read = h1_ipc_read,
    .write = h1_ipc_write,
    .io_data_reg = NULL,
    .io_data_unreg = NULL,
    .io_data = NULL,
};

struct ipc_ops ipc_ops = {
    .send = h1_ipc_send,
    .recv = h1_ipc_recv,
    .bootstrap = NULL,
};
