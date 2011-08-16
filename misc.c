/**
 * This file is part of libmsm-h1.
 *
 * Copyright (C) 2010-2011 Joerie de Gram <j.de.gram@gmail.com>
 *
 * libmsm-h1 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libmsm-h1 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libmsm-h1.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <radio.h>
#include "radio_internal.h"

void msm_misc_me_version(int request_id)
{
	msm_send_get(MSM_MISC_ME_VERSION, request_id);
}

void msm_misc_me_imsi(int request_id)
{
	msm_send_get(MSM_MISC_ME_IMSI, request_id);
}

/**
 * Requests the device's IMEI/IMEISV
 */
void msm_misc_me_sn(int request_id)
{
	msm_send_get(MSM_MISC_ME_SN, request_id);
}

void msm_rx_misc_me_sn(struct msm_request_info *info, char *data, int len)
{
	unsigned char *imei_len = (unsigned char*)data;
	char *imei = (data+1);

	printf("IMEISV (%u): %s\n", *imei_len, imei);

	info->data = imei;
	info->length = *imei_len;
	msm_rx_callback(info);
}

void msm_rx_misc_time_info(struct msm_request_info *info, char *data, int len)
{
	if(len != sizeof(struct msm_misc_time_info)) {
		printf("Invalid NITZ message length\n");
		return;
	}

	struct msm_misc_time_info *nitz = (struct msm_misc_time_info*)data;
	printf("%s: %02u-%02u-%04u %02u:%02u:%02u %02u\n",
		__FUNCTION__, nitz->day, nitz->mon, (2000 + nitz->year),
		nitz->hour, nitz->min, nitz->sec, nitz->tz);

	info->data = nitz;
	info->length = sizeof(*nitz);
	msm_rx_callback(info);
}
