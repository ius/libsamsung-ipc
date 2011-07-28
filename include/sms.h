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

#ifndef __SMS_H__
#define __SMS_H__

#define MSM_SMS_SEND_MSG				0x0401
#define MSM_SMS_INCOMING_MSG				0x0402
#define MSM_SMS_READ_MSG				0x0403
#define MSM_SMS_SAVE_MSG				0x0404
#define MSM_SMS_DEL_MSG					0x0405
#define MSM_SMS_DELIVER_REPORT				0x0406
#define MSM_SMS_DEVICE_READY				0x0407
#define MSM_SMS_SEL_MEM					0x0408
#define MSM_SMS_STORED_MSG_COUNT			0x0409
#define MSM_SMS_SVC_CENTER_ADDR				0x040A
#define MSM_SMS_SVC_OPTION				0x040B
#define MSM_SMS_MEM_STATUS				0x040C
#define MSM_SMS_CBS_MSG					0x040D
#define MSM_SMS_CBS_CONFIG				0x040E
#define MSM_SMS_STORED_MSG_STATUS			0x040F
#define MSM_SMS_PARAM_COUNT				0x0410
#define MSM_SMS_PARAM					0x0411

#define MSM_SMS_MSG_MULTIPLE		1
#define MSM_SMS_MSG_SINGLE		2

#define MSM_SMS_TYPE_POINT_TO_POINT	1
#define MSM_SMS_TYPE_STATUS_REPORT	2

struct msm_sms_send_msg {
	unsigned char hint, length;
} __attribute__((__packed__));

struct msm_sms_incoming_msg {
	unsigned char type, unk, length;
} __attribute__((__packed__));

void msm_sms_send_msg(unsigned char *data, unsigned char length, int request_id);
void msm_sms_deliver_report(int request_id);

#endif

