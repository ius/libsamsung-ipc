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

#include <call.h>
#include "radio_internal.h"

void msm_call_outgoing(const char *number, int identity, int request_id)
{
	struct msm_call_outgoing call;

	memset(&call, 0x00, sizeof(call));

	if(strlen(number) > 82) {
		printf("Outgoing call number too long\n");
		return;
	}

	call.type = MSM_CALL_TYPE_VOICE;
	call.identity = identity;
	call.prefix = MSM_CALL_PREFIX_NONE;

	call.length = strlen(number);
	memcpy(call.number, number, call.length);

	msm_send(MSM_CALL_OUTGOING, MSM_TYPE_EXEC, (unsigned char*)&call, sizeof(call), request_id);
}

void msm_call_release(int request_id)
{
	msm_send_exec(MSM_CALL_RELEASE, request_id);
}

void msm_call_answer(int request_id)
{
	msm_send_exec(MSM_CALL_ANSWER, request_id);
}

void msm_call_list(int request_id)
{
	msm_send_get(MSM_CALL_LIST, request_id);
}

