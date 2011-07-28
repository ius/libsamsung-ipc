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

void msm_sms_send_msg(unsigned char *data, unsigned char length, int request_id)
{
	msm_send(MSM_SMS_SEND_MSG, MSM_TYPE_EXEC, data, length, request_id);
}

void msm_sms_deliver_report(int request_id)
{
	unsigned char data[247] = { 0x00, 0x00, 0x03, 0x00, 0x02 };
	msm_send(MSM_SMS_DELIVER_REPORT, MSM_TYPE_EXEC, data, sizeof(data), request_id);
}

