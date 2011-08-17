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

#include <stdio.h>
#include <radio.h>
#include "radio_internal.h"

void ipc_misc_me_version(int request_id)
{
	ipc_send_get(IPC_MISC_ME_VERSION, request_id);
}

void ipc_misc_me_imsi(int request_id)
{
	ipc_send_get(IPC_MISC_ME_IMSI, request_id);
}

/**
 * Requests the device's IMEI/IMEISV
 */
void ipc_misc_me_sn(int request_id)
{
	ipc_send_get(IPC_MISC_ME_SN, request_id);
}

void ipc_rx_misc_me_sn(struct ipc_request_info *info, char *data, int len)
{
	unsigned char *imei_len = (unsigned char*)data;
	char *imei = (data+1);

	printf("IMEISV (%u): %s\n", *imei_len, imei);

	info->data = imei;
	info->length = *imei_len;
	ipc_rx_callback(info);
}

void ipc_rx_misc_time_info(struct ipc_request_info *info, char *data, int len)
{
	if(len != sizeof(struct ipc_misc_time_info)) {
		printf("Invalid NITZ message length\n");
		return;
	}

	struct ipc_misc_time_info *nitz = (struct ipc_misc_time_info*)data;
	printf("%s: %02u-%02u-%04u %02u:%02u:%02u %02u\n",
		__FUNCTION__, nitz->day, nitz->mon, (2000 + nitz->year),
		nitz->hour, nitz->min, nitz->sec, nitz->tz);

	info->data = nitz;
	info->length = sizeof(*nitz);
	ipc_rx_callback(info);
}
