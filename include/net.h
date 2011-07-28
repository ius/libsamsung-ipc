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

#ifndef __NET_H__
#define __NET_H__

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

#define MSM_NET_PLMN_STATUS_AVAILABLE			2
#define MSM_NET_PLMN_STATUS_CURRENT			3
#define MSM_NET_PLMN_STATUS_FORBIDDEN			4

struct msm_net_current_plmn {
	char unk;
	unsigned char slevel;
	char plmn[6];
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
	unsigned char status;
	char plmn[6];
	unsigned char type;
	char unk[2];
} __attribute__((__packed__));

struct msm_net_plmn_entries {
	unsigned char num;
	struct msm_net_plmn_entry *data;
};

void msm_net_current_plmn(int request_id);
void msm_net_plmn_list(int request_id);
void msm_net_identity(int request_id);

#endif

