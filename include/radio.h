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

#ifndef __RADIO_H__
#define __RADIO_H__

#include "call.h"
#include "disp.h"
#include "misc.h"
#include "net.h"
#include "sec.h"
#include "sms.h"

/* AP -> Baseband */
#define MSM_TYPE_EXEC		                        0x01
#define MSM_TYPE_GET		                        0x02
#define MSM_TYPE_SET		                        0x03
#define MSM_TYPE_CFRM		                        0x04
#define MSM_TYPE_EVENT		                        0x05

/* Baseband -> AP */
#define MSM_TYPE_INDI		                        0x01
#define MSM_TYPE_RESP		                        0x02
#define MSM_TYPE_NOTI		                        0x03

/* Message groups */
#define MSM_GROUP_PWR		                        0x01
#define MSM_GROUP_CALL		                        0x02
#define MSM_GROUP_SMS		                        0x04
#define MSM_GROUP_SEC		                        0x05
#define MSM_GROUP_PB		                        0x06
#define MSM_GROUP_DISP		                        0x07
#define MSM_GROUP_NET		                        0x08
#define MSM_GROUP_SND		                        0x09
#define MSM_GROUP_MISC		                        0x0A
#define MSM_GROUP_SVC		                        0x0B
#define MSM_GROUP_SS		                        0x0C
#define MSM_GROUP_GPRS	                        	0x0D
#define MSM_GROUP_SAT	                        	0x0E
#define MSM_GROUP_CFG	                        	0x0F
#define MSM_GROUP_IMEI	                        	0x10
#define MSM_GROUP_GPS	                        	0x11
#define MSM_GROUP_SAP		                        0x12

/* Power */
#define MSM_PWR_PHONE_PWR_UP				0x0101
#define MSM_PWR_PHONE_PWR_OFF				0x0102
#define MSM_PWR_PHONE_RESET				0x0103
#define MSM_PWR_BATT_STATUS				0x0104
#define MSM_PWR_BATT_TYPE				0x0105
#define MSM_PWR_BATT_COMP				0x0106
#define MSM_PWR_PHONE_ONLINE				0x0107

/* Pb */
#define MSM_PB_ACCESS					0x0601
#define MSM_PB_STORAGE					0x0602
#define MSM_PB_STORAGE_LIST				0x0603
#define MSM_PB_ENTRY_INFO				0x0604
#define MSM_PB_CAPABILITY_INFO				0x0605

/* SS */
#define MSM_SS_WAITING					0x0C01
#define MSM_SS_CLI					0x0C02
#define MSM_SS_BARRING					0x0C03
#define MSM_SS_BARRING_PW				0x0C04
#define MSM_SS_FORWARDING				0x0C05
#define MSM_SS_INFO					0x0C06
#define MSM_SS_MANAGE_CALL				0x0C07
#define MSM_SS_USSD					0x0C08
#define MSM_SS_AOC					0x0C09
#define MSM_SS_RELEASE_COMPLETE				0x0C0A

/* GPRS */
#define MSM_GPRS_DEFINE_PDP_CONTEXT			0x0D01
#define MSM_GPRS_QOS					0x0D02
#define MSM_GPRS_PS					0x0D03
#define MSM_GPRS_PDP_CONTEXT				0x0D04
#define MSM_GPRS_SHOW_PDP_ADDR				0x0D05
#define MSM_GPRS_MS_CLASS				0x0D06
#define MSM_GPRS_3G_QUAL_SERVICE_PROFILE		0x0D07
#define MSM_GPRS_IP_CONFIGURATION			0x0D08
#define MSM_GPRS_DEFINE_SEC_PDP_CONTEXT			0x0D09
#define MSM_GPRS_TFT					0x0D0A
#define MSM_GPRS_HSDPA_STATUS				0x0D0B
#define MSM_GPRS_CURRENT_SESSION_DATA_COUNT		0x0D0C
#define MSM_GPRS_DATA_DORMANT				0x0D0D
#define MSM_GPRS_DUN_PIN_CTRL				0x0D0E
#define MSM_GPRS_CALL_STATUS				0x0D0F

/* Sat */
#define MSM_SAT_PROFILE_DOWNLOAD			0x0E01
#define MSM_SAT_ENVELOPE_CMD				0x0E02
#define MSM_SAT_PROACTIVE_CMD				0x0E03
#define MSM_SAT_TERMINATE_USAT_SESSION			0x0E04
#define MSM_SAT_EVENT_DOWNLOAD				0x0E05
#define MSM_SAT_PROVIDE_LOCAL_INFO			0x0E06
#define MSM_SAT_POLLING					0x0E07
#define MSM_SAT_REFRESH					0x0E08
#define MSM_SAT_SETUP_EVENT_LIST			0x0E09
#define MSM_SAT_CALL_CONTROL_RESULT			0x0E0A
#define MSM_SAT_IMAGE_CLUT				0x0E0B
#define MSM_SAT_CALL_PROCESSING				0x0E0C

/* IMEI */
#define MSM_IMEI_START					0x1001
#define MSM_IMEI_CHECK_DEVICE_INFO			0x1002

#define FRAME_START	0x7f
#define FRAME_END	0x7e

#define FRAME_ID(f)	((f->group << 8) | f->index)
#define FRAME_GRP(m)	(m >> 8)
#define FRAME_IDX(m)	(m & 0xff)
#define FRAME_STR(f)	case f: return #f;

#define SWAP16(x)	((x >> 8) | ((x & 0xff) << 8))

struct msm_request_info {
	unsigned short type;
	unsigned char method;
	unsigned char id;
	void *data;
	int length;
};

struct msm_info {
	char *tty;
	void (*on_receive)(struct msm_request_info *info);
};

void msm_register(struct msm_info *msm);
void msm_open();
void msm_close();
void msm_power_on();
void msm_power_off();
void msm_loop();

void msm_send(const int type, const int method, const unsigned char *data, const int data_length, int request_id);

#endif

