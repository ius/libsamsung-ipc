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

#include "../../include/radio.h"

#define DPRAM_TTY			"/dev/dpram0"

#define IOCTL_PHONE_ON			0x68d0
#define IOCTL_PHONE_OFF			0x68d1
#define IOCTL_PHONE_GETSTATUS		0x68d2
#define IOCTL_PHONE_RESET		0x68d3
#define IOCTL_PHONE_RAMDUMP		0x68d4
#define IOCTL_PHONE_BOOTTYPE		0x68d5
#define IOCTL_MEM_RW			0x68d6
#define IOCTL_WAKEUP			0x68d7
#define IOCTL_SILENT_RESET		0x68d8

#define FRAME_START	0x7f
#define FRAME_END	0x7e

struct hdlc_header {
	unsigned short length;
	unsigned char unknown;

	struct ipc_header ipc;
} __attribute__((__packed__));

