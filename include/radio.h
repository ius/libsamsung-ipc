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

/* MSM message groups */
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

/* Call */
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

/* SMS */
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

/* Sec */
#define MSM_SEC_PIN_STATUS				0x0501
#define MSM_SEC_PHONE_LOCK				0x0502
#define MSM_SEC_CHANGE_LOCKING_PW			0x0503
#define MSM_SEC_SIM_LANG				0x0504
#define MSM_SEC_RSIM_ACCESS				0x0505
#define MSM_SEC_GSIM_ACCESS				0x0506
#define MSM_SEC_SIM_ICC_TYPE				0x0507
#define MSM_SEC_LOCK_INFO				0x0508
#define MSM_SEC_ISIM_AUTH				0x0509

/* Pb */
#define MSM_PB_ACCESS					0x0601
#define MSM_PB_STORAGE					0x0602
#define MSM_PB_STORAGE_LIST				0x0603
#define MSM_PB_ENTRY_INFO				0x0604
#define MSM_PB_CAPABILITY_INFO				0x0605

/* Disp */
#define MSM_DISP_ICON_INFO				0x0701
#define MSM_DISP_HOMEZONE_INFO				0x0702

/* Net */
#define MSM_NET_PREF_PLMN				0x0801
#define MSM_NET_PLMN_SEL				0x0802
#define MSM_NET_CURRENT_PLMN				0x0803
#define MSM_NET_PLMN_LIST				0x0804
#define MSM_NET_REGIST					0x0805
#define MSM_NET_SUBSCRIBER_NUM				0x0806
#define MSM_NET_BAND_SEL				0x0807
#define MSM_NET_SERVICE_DOMAIN_CONFIG			0x0808
#define MSM_NET_POWERON_ATTACH				0x0809
#define MSM_NET_MODE_SEL				0x080A
#define MSM_NET_ACQ_ORDER				0x080B
#define MSM_NET_IDENTITY				0x080C
#define MSM_NET_CURRENT_RRC_STATUS			0x080D

/* Misc */
#define MSM_MISC_ME_VERSION				0x0A01
#define MSM_MISC_ME_IMSI				0x0A02
#define MSM_MISC_ME_SN					0x0A03
#define MSM_MISC_TIME_INFO				0x0A07

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

/* Call info */
#define MSM_CALL_TYPE_VOICE				0x01
#define MSM_CALL_TYPE_DATA				0x03

#define MSM_CALL_IDENTITY_DEFAULT			0x00
#define MSM_CALL_IDENTITY_HIDE				0x01
#define MSM_CALL_IDENTITY_SHOW				0x02

#define MSM_CALL_PREFIX_NONE				0x00
#define MSM_CALL_PREFIX_INTL				0x11

#define MSM_CALL_STATE_DIALING				0x00
#define MSM_CALL_STATE_IGNORING_INCOMING_STATUS		0x01
#define MSM_CALL_STATE_CONNECTED			0x02
#define MSM_CALL_STATE_RELEASED				0x03
#define MSM_CALL_STATE_CONNECTING			0x04

/* Sec pin status */
#define MSM_SEC_PIN_SIM_INITIALIZING			0x00
#define MSM_SEC_PIN_SIM_NSIDE_PF_ERROR			0x02
#define MSM_SEC_PIN_SIM_LOCK_SC				0x03
#define MSM_SEC_PIN_SIM_LOCK_FD				0x04
#define MSM_SEC_PIN_SIM_CARD_NOT_PRESENT		0x80
#define MSM_SEC_PIN_SIM_CARD_ERROR			0x81
#define MSM_SEC_PIN_SIM_INIT_COMPLETE			0x82
#define MSM_SEC_PIN_SIM_PB_INIT_COMPLETE		0x83

#define MSM_SEC_PIN_SIM_LOCK_SC_PIN1_REQ		0x01
#define MSM_SEC_PIN_SIM_LOCK_SC_PUK_REQ			0x02
#define MSM_SEC_PIN_SIM_LOCK_SC_CARD_BLOCKED		0x05

/* Network info */
#define MSM_NET_SERVICE_TYPE_GSM			0x01
#define MSM_NET_SERVICE_TYPE_GSM2			0x02
#define MSM_NET_SERVICE_TYPE_GPRS			0x03
#define MSM_NET_SERVICE_TYPE_EDGE			0x04
#define MSM_NET_SERVICE_TYPE_UMTS			0x05

#define MSM_NET_SERVICE_LEVEL_NONE			0x01
#define MSM_NET_SERVICE_LEVEL_HOME			0x02
#define MSM_NET_SERVICE_LEVEL_SEARCHING			0x03
#define MSM_NET_SERVICE_LEVEL_EMERGENCY			0x04
#define MSM_NET_SERVICE_LEVEL_NONE2			0x05
#define MSM_NET_SERVICE_LEVEL_ROAMING			0x06

#define FRAME_START	0x7f
#define FRAME_END	0x7e

#define FRAME_ID(f)	((f->group << 8) | f->index)
#define FRAME_GRP(m)	(m >> 8)
#define FRAME_IDX(m)	(m & 0xff)
#define FRAME_STR(f)	case f: return #f;

#define SWAP16(x)	((x >> 8) | ((x & 0xff) << 8))

struct msm_request_info {
	unsigned short type;
	unsigned char id;
	void *data;
	int length;
};

struct msm_info {
	char *tty;
	void (*on_receive)(struct msm_request_info *info);
};

struct msm_time_info {
	char unk[2];
	unsigned char year, mon, day;
	unsigned char hour, min, sec;
	unsigned char unk2, tz, unk3;
	unsigned char plmn[6];
} __attribute__((__packed__));

struct msm_pin_status {
	unsigned char type;
	unsigned char key;
} __attribute__((__packed__));

struct msm_call_outgoing {
	unsigned char type, identity;
	unsigned char length, prefix;
	unsigned char number[86];
} __attribute__((__packed__));

struct msm_call_incoming {
	unsigned char type, id, line;
} __attribute__((__packed__));

struct msm_call_status {
	unsigned char type, id, state;
	unsigned char reason, end_cause;
} __attribute__((__packed__));

struct msm_disp_icon_info {
	unsigned char rssi, battery, act, reg;
} __attribute__((__packed__));

struct msm_net_current_plmn {
	char unk;
	unsigned char slevel;
	unsigned char plmn[6];
	unsigned char type;
	unsigned short lac;
} __attribute__((__packed__));

struct msm_net_regist {
	unsigned char act, unk0, status, unk1;
	unsigned short lac;
	unsigned int cid;
	char unk2;
} __attribute__((__packed__));

struct msm_net_plmn_entry {
	unsigned char slevel;
	unsigned char plmn[6];
	unsigned char type;
	char unk[2];
} __attribute__((__packed__));

struct msm_net_plmn_entries {
	unsigned char num;
	struct msm_net_plmn_entry *data;
};

void msm_register(struct msm_info *msm);
void msm_open();
void msm_close();
void msm_power_on();
void msm_power_off();
void msm_loop();

void msm_misc_me_sn(int request_id);
void msm_net_current_plmn(int request_id);
void msm_net_plmn_list(int request_id);
void msm_net_identity(int request_id);

#endif

