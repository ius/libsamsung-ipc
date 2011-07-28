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

#ifndef __CALL_H__
#define __CALL_H__

/* Message types */
#define MSM_CALL_OUTGOING				0x0201
#define MSM_CALL_INCOMING				0x0202
#define MSM_CALL_RELEASE				0x0203
#define MSM_CALL_ANSWER					0x0204
#define MSM_CALL_STATUS					0x0205
#define MSM_CALL_LIST					0x0206
#define MSM_CALL_BURST_DTMF				0x0207
#define MSM_CALL_CONT_DTMF				0x0208
#define MSM_CALL_WAITING				0x0209
#define MSM_CALL_LINE_ID				0x020A

/* Enum values */
#define MSM_CALL_TYPE_VOICE				0x01
#define MSM_CALL_TYPE_DATA				0x03

#define MSM_CALL_IDENTITY_DEFAULT			0x00
#define MSM_CALL_IDENTITY_HIDE				0x01
#define MSM_CALL_IDENTITY_SHOW				0x02

#define MSM_CALL_PREFIX_NONE				0x00
#define MSM_CALL_PREFIX_INTL				0x11

#define MSM_CALL_STATE_DIALING				0x01
#define MSM_CALL_STATE_IGNORING_INCOMING_STATUS		0x02
#define MSM_CALL_STATE_CONNECTED			0x03
#define MSM_CALL_STATE_RELEASED				0x04
#define MSM_CALL_STATE_CONNECTING			0x05

struct msm_call_outgoing {
	unsigned char type, identity;
	unsigned char length, prefix;
	unsigned char number[86];
} __attribute__((__packed__));

struct msm_call_incoming {
	unsigned char type, id, line;
} __attribute__((__packed__));

struct msm_call_list_entry {
	unsigned char type, idx;
	unsigned char term, state, unk3;
	unsigned char number_len;
	unsigned char unk4;
} __attribute__((__packed__));

struct msm_call_status {
	unsigned char type, id, state;
	unsigned char reason, end_cause;
} __attribute__((__packed__));

void msm_call_outgoing(const char *number, int identity, int request_id);
void msm_call_release(int request_id);
void msm_call_answer(int request_id);
void msm_call_list(int request_id);

#endif

