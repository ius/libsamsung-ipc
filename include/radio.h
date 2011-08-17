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

#ifndef __RADIO_H__
#define __RADIO_H__

#include "call.h"
#include "disp.h"
#include "misc.h"
#include "net.h"
#include "sec.h"
#include "sms.h"

/* AP -> Baseband */
#define IPC_TYPE_EXEC		                        0x01
#define IPC_TYPE_GET		                        0x02
#define IPC_TYPE_SET		                        0x03
#define IPC_TYPE_CFRM		                        0x04
#define IPC_TYPE_EVENT		                        0x05

/* Baseband -> AP */
#define IPC_TYPE_INDI		                        0x01
#define IPC_TYPE_RESP		                        0x02
#define IPC_TYPE_NOTI		                        0x03

/* Message groups */
#define IPC_GROUP_PWR		                        0x01
#define IPC_GROUP_CALL		                        0x02
#define IPC_GROUP_SMS		                        0x04
#define IPC_GROUP_SEC		                        0x05
#define IPC_GROUP_PB		                        0x06
#define IPC_GROUP_DISP		                        0x07
#define IPC_GROUP_NET		                        0x08
#define IPC_GROUP_SND		                        0x09
#define IPC_GROUP_MISC		                        0x0A
#define IPC_GROUP_SVC		                        0x0B
#define IPC_GROUP_SS		                        0x0C
#define IPC_GROUP_GPRS	                        	0x0D
#define IPC_GROUP_SAT	                        	0x0E
#define IPC_GROUP_CFG	                        	0x0F
#define IPC_GROUP_IMEI	                        	0x10
#define IPC_GROUP_GPS	                        	0x11
#define IPC_GROUP_SAP		                        0x12
#define IPC_GROUP_GEN		                        0x80

/* Power */
#define IPC_PWR_PHONE_PWR_UP				0x0101
#define IPC_PWR_PHONE_PWR_OFF				0x0102
#define IPC_PWR_PHONE_RESET				0x0103
#define IPC_PWR_BATT_STATUS				0x0104
#define IPC_PWR_BATT_TYPE				0x0105
#define IPC_PWR_BATT_COMP				0x0106
#define IPC_PWR_PHONE_ONLINE				0x0107

/* Pb */
#define IPC_PB_ACCESS					0x0601
#define IPC_PB_STORAGE					0x0602
#define IPC_PB_STORAGE_LIST				0x0603
#define IPC_PB_ENTRY_INFO				0x0604
#define IPC_PB_CAPABILITY_INFO				0x0605

/* SS */
#define IPC_SS_WAITING					0x0C01
#define IPC_SS_CLI					0x0C02
#define IPC_SS_BARRING					0x0C03
#define IPC_SS_BARRING_PW				0x0C04
#define IPC_SS_FORWARDING				0x0C05
#define IPC_SS_INFO					0x0C06
#define IPC_SS_MANAGE_CALL				0x0C07
#define IPC_SS_USSD					0x0C08
#define IPC_SS_AOC					0x0C09
#define IPC_SS_RELEASE_COMPLETE				0x0C0A

/* GPRS */
#define IPC_GPRS_DEFINE_PDP_CONTEXT			0x0D01
#define IPC_GPRS_QOS					0x0D02
#define IPC_GPRS_PS					0x0D03
#define IPC_GPRS_PDP_CONTEXT				0x0D04
#define IPC_GPRS_SHOW_PDP_ADDR				0x0D05
#define IPC_GPRS_MS_CLASS				0x0D06
#define IPC_GPRS_3G_QUAL_SERVICE_PROFILE		0x0D07
#define IPC_GPRS_IP_CONFIGURATION			0x0D08
#define IPC_GPRS_DEFINE_SEC_PDP_CONTEXT			0x0D09
#define IPC_GPRS_TFT					0x0D0A
#define IPC_GPRS_HSDPA_STATUS				0x0D0B
#define IPC_GPRS_CURRENT_SESSION_DATA_COUNT		0x0D0C
#define IPC_GPRS_DATA_DORMANT				0x0D0D
#define IPC_GPRS_DUN_PIN_CTRL				0x0D0E
#define IPC_GPRS_CALL_STATUS				0x0D0F

/* Sat */
#define IPC_SAT_PROFILE_DOWNLOAD			0x0E01
#define IPC_SAT_ENVELOPE_CMD				0x0E02
#define IPC_SAT_PROACTIVE_CMD				0x0E03
#define IPC_SAT_TERMINATE_USAT_SESSION			0x0E04
#define IPC_SAT_EVENT_DOWNLOAD				0x0E05
#define IPC_SAT_PROVIDE_LOCAL_INFO			0x0E06
#define IPC_SAT_POLLING					0x0E07
#define IPC_SAT_REFRESH					0x0E08
#define IPC_SAT_SETUP_EVENT_LIST			0x0E09
#define IPC_SAT_CALL_CONTROL_RESULT			0x0E0A
#define IPC_SAT_IMAGE_CLUT				0x0E0B
#define IPC_SAT_CALL_PROCESSING				0x0E0C

/* IMEI */
#define IPC_IMEI_START					0x1001
#define IPC_IMEI_CHECK_DEVICE_INFO			0x1002

/* Gen */
#define IPC_GEN_PHONE_RES				0x8001

#define FRAME_START	0x7f
#define FRAME_END	0x7e

#define FRAME_ID(f)	((f->group << 8) | f->index)
#define FRAME_GRP(m)	(m >> 8)
#define FRAME_IDX(m)	(m & 0xff)
#define FRAME_STR(f)	case f: return #f;

#define SWAP16(x)	((x >> 8) | ((x & 0xff) << 8))

struct ipc_request_info {
	unsigned short type;
	unsigned char method;
	unsigned char id;
	void *data;
	int length;
};

struct ipc_info {
	char *tty;
	void (*on_receive)(struct ipc_request_info *info);
};

struct ipc_gen_phone_res {
	unsigned char group, type;
	unsigned short code;
	unsigned char unk;
} __attribute__((__packed__));

void ipc_register(struct ipc_info *ipc);
void ipc_open();
void ipc_close();
void ipc_power_on();
void ipc_power_off();
void ipc_loop();

void ipc_send(const int type, const int method, const unsigned char *data, const int data_length, int request_id);

#endif

