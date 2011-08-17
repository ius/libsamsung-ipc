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

#include <radio.h>

static void on_receive(struct ipc_request_info *info)
{
}

static struct ipc_info ipc = {
	.tty		= "/dev/dpram0",
	.on_receive	= on_receive,
};

int main(int argc, char *argv[])
{
	ipc_register(&ipc);
	ipc_open();
	ipc_power_on();

	ipc_loop();

	ipc_close();

	return 0;
}
