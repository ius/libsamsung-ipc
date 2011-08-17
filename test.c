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
#include <unistd.h>

#include <radio.h>

void handle_msg(struct ipc_response *response)
{
	if(response->command == IPC_PWR_PHONE_PWR_UP &&
		response->type == IPC_TYPE_NOTI) {
		printf(">> received PWR_PHONE_ONLINE, requesting IMEI\n");

		/* h1 requires a short delay for nvram to be available */
		usleep(25000);
		ipc_msg_send(IPC_MISC_ME_SN, IPC_TYPE_GET, NULL, 0, 0x42);
	}
}

int main(int argc, char *argv[])
{
	struct ipc_response response;
	int error;

	printf("ipc_open\n");
	error = ipc_open();

	if(error) {
		fprintf(stderr, "ipc_open failed!\n");
		return 1;
	}

	printf("ipc_power_on\n");
	ipc_power_on();

	printf("entering recv loop...\n");

	while(1) {
		error = ipc_recv(&response);

		if(!error) {
			printf("%s %s (%u/%u) type=%04x mseq=%02x aseq=%02x\n",
				ipc_str(&response), ipc_response_type(&response),
				(response.data_length + 7), response.data_length,
				response.type, response.mseq, response.aseq);

			hex_dump(response.data, response.data_length);
			printf("\n");

			handle_msg(&response);

			free(response.data);
		} else {
			fprintf(stderr, "ipc_recv failed!\n");
			return 1;
		}
	}

	error = ipc_close();

	if(error) {
		fprintf(stderr, "ipc_close failed!\n");
		return 1;
	}

	return 0;
}
