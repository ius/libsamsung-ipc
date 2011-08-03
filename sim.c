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

#include "radio_internal.h"

void msm_sec_rsim_access(unsigned char command, unsigned short file_id,
			 unsigned char p1, unsigned char p2, unsigned char p3,
			 unsigned char *rdata, unsigned int length, int request_id)
{
	unsigned char msg[262];
	struct msm_sec_rsim_access_request *rsim_req = (struct msm_sec_rsim_access_request*)&msg[0];
	unsigned char *data = (msg + sizeof(*rsim_req));

	memset(msg, 0, sizeof(msg));

	rsim_req->command = command;
	rsim_req->fileid = file_id;
	rsim_req->p1 = p1;
	rsim_req->p2 = p2;
	rsim_req->p3 = p3;

	if(length > 256) {
		length = 256;
	}

	memcpy(data, rdata, length);

	msm_send(MSM_SEC_RSIM_ACCESS, MSM_TYPE_GET, msg, sizeof(msg), request_id);
}

