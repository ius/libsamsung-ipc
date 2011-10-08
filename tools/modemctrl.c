/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2010-2011 Joerie de Gram <j.de.gram@gmail.com>
 *               2011 Simon Busch <morphis@gravedo.de>
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
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <radio.h>

void print_help()
{
	printf("usage: modemctrl <command>\n");
	printf("commands:\n");
	printf("\tbootstrap             bootstrap modem to be ready for processing\n");
	printf("\tpower-on              power on the modem\n");
	printf("\tpower-off             power off the modem\n");
}

int main(int argc, char *argv[])
{
	struct ipc_response response;
	int error;

	if (argc != 2) {
		print_help();
		exit(1);
	}

	ipc_init(IPC_CLIENT_TYPE_CRESPO);

	if (!strncmp(argv[1], "bootstrap", 9)) {
		ipc_bootstrap();
	}
	else if (!strncmp(argv[1], "power-on", 8)) {
		ipc_open();
		ipc_power_on();
		ipc_close();
	}
	else if (!strncmp(argv[1], "power-off", 9)) {
		ipc_open();
		ipc_power_off();
		ipc_close();
	}

	return 0;
}
