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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/select.h>
#include <radio.h>

#include "radio_internal.h"
#include "hexdump.h"

static int fd = 0;
static struct ipc_info *ipc = NULL;

void ipc_rx_callback(struct ipc_request_info *info)
{
	ipc->on_receive(info);
}

void ipc_register(struct ipc_info *ipc_data)
{
	ipc = ipc_data;
}

void ipc_open()
{
	fd = open(ipc->tty, O_RDWR | O_NDELAY);

	if(fd < 0) {
		printf("Failed to open dpram tty\n");
	}

	struct termios termios;

	tcgetattr(fd, &termios);
	cfmakeraw(&termios);
	tcsetattr(fd, TCSANOW, &termios);
}

void ipc_close()
{
	if(fd) {
		close(fd);
	}
}

void ipc_power_on()
{
	ioctl(fd, IOCTL_PHONE_ON);
}

void ipc_power_off()
{
	ioctl(fd, IOCTL_PHONE_OFF);
}

const char *ipc_type(struct ipc_hdr *frame) {
	switch(frame->type) {
		case IPC_TYPE_INDI:
			return "INDI";
		case IPC_TYPE_RESP:
			return "RESP";
		case IPC_TYPE_NOTI:
			return "NOTI";
		default:
			return "UNKNOWN";
	}
}

const char *ipc_str(struct ipc_hdr *frame) {
	switch(FRAME_ID(frame)) {
		FRAME_STR(IPC_PWR_PHONE_PWR_UP)
		FRAME_STR(IPC_PWR_PHONE_PWR_OFF)
		FRAME_STR(IPC_PWR_PHONE_RESET)
		FRAME_STR(IPC_PWR_BATT_STATUS)
		FRAME_STR(IPC_PWR_BATT_TYPE)
		FRAME_STR(IPC_PWR_BATT_COMP)
		FRAME_STR(IPC_PWR_PHONE_ONLINE)
		FRAME_STR(IPC_CALL_OUTGOING)
		FRAME_STR(IPC_CALL_INCOMING)
		FRAME_STR(IPC_CALL_RELEASE)
		FRAME_STR(IPC_CALL_ANSWER)
		FRAME_STR(IPC_CALL_STATUS)
		FRAME_STR(IPC_CALL_LIST)
		FRAME_STR(IPC_CALL_BURST_DTMF)
		FRAME_STR(IPC_CALL_CONT_DTMF)
		FRAME_STR(IPC_CALL_WAITING)
		FRAME_STR(IPC_CALL_LINE_ID)
		FRAME_STR(IPC_SMS_SEND_MSG)
		FRAME_STR(IPC_SMS_INCOMING_MSG)
		FRAME_STR(IPC_SMS_READ_MSG)
		FRAME_STR(IPC_SMS_SAVE_MSG)
		FRAME_STR(IPC_SMS_DEL_MSG)
		FRAME_STR(IPC_SMS_DELIVER_REPORT)
		FRAME_STR(IPC_SMS_DEVICE_READY)
		FRAME_STR(IPC_SMS_SEL_MEM)
		FRAME_STR(IPC_SMS_STORED_MSG_COUNT)
		FRAME_STR(IPC_SMS_SVC_CENTER_ADDR)
		FRAME_STR(IPC_SMS_SVC_OPTION)
		FRAME_STR(IPC_SMS_MEM_STATUS)
		FRAME_STR(IPC_SMS_CBS_MSG)
		FRAME_STR(IPC_SMS_CBS_CONFIG)
		FRAME_STR(IPC_SMS_STORED_MSG_STATUS)
		FRAME_STR(IPC_SMS_PARAM_COUNT)
		FRAME_STR(IPC_SMS_PARAM)
		FRAME_STR(IPC_SEC_PIN_STATUS)
		FRAME_STR(IPC_SEC_PHONE_LOCK)
		FRAME_STR(IPC_SEC_CHANGE_LOCKING_PW)
		FRAME_STR(IPC_SEC_SIM_LANG)
		FRAME_STR(IPC_SEC_RSIM_ACCESS)
		FRAME_STR(IPC_SEC_GSIM_ACCESS)
		FRAME_STR(IPC_SEC_SIM_ICC_TYPE)
		FRAME_STR(IPC_SEC_LOCK_INFO)
		FRAME_STR(IPC_SEC_ISIM_AUTH)
		FRAME_STR(IPC_PB_ACCESS)
		FRAME_STR(IPC_PB_STORAGE)
		FRAME_STR(IPC_PB_STORAGE_LIST)
		FRAME_STR(IPC_PB_ENTRY_INFO)
		FRAME_STR(IPC_PB_CAPABILITY_INFO)
		FRAME_STR(IPC_DISP_ICON_INFO)
		FRAME_STR(IPC_DISP_HOMEZONE_INFO)
		FRAME_STR(IPC_NET_PREF_PLMN)
		FRAME_STR(IPC_NET_PLMN_SEL)
		FRAME_STR(IPC_NET_CURRENT_PLMN)
		FRAME_STR(IPC_NET_PLMN_LIST)
		FRAME_STR(IPC_NET_REGIST)
		FRAME_STR(IPC_NET_SUBSCRIBER_NUM)
		FRAME_STR(IPC_NET_BAND_SEL)
		FRAME_STR(IPC_NET_SERVICE_DOMAIN_CONFIG)
		FRAME_STR(IPC_NET_POWERON_ATTACH)
		FRAME_STR(IPC_NET_MODE_SEL)
		FRAME_STR(IPC_NET_ACQ_ORDER)
		FRAME_STR(IPC_NET_IDENTITY)
		FRAME_STR(IPC_NET_CURRENT_RRC_STATUS)
		FRAME_STR(IPC_MISC_ME_VERSION)
		FRAME_STR(IPC_MISC_ME_IMSI)
		FRAME_STR(IPC_MISC_ME_SN)
		FRAME_STR(IPC_MISC_TIME_INFO)
		FRAME_STR(IPC_SS_WAITING)
		FRAME_STR(IPC_SS_CLI)
		FRAME_STR(IPC_SS_BARRING)
		FRAME_STR(IPC_SS_BARRING_PW)
		FRAME_STR(IPC_SS_FORWARDING)
		FRAME_STR(IPC_SS_INFO)
		FRAME_STR(IPC_SS_MANAGE_CALL)
		FRAME_STR(IPC_SS_USSD)
		FRAME_STR(IPC_SS_AOC)
		FRAME_STR(IPC_SS_RELEASE_COMPLETE)
		FRAME_STR(IPC_GPRS_DEFINE_PDP_CONTEXT)
		FRAME_STR(IPC_GPRS_QOS)
		FRAME_STR(IPC_GPRS_PS)
		FRAME_STR(IPC_GPRS_PDP_CONTEXT)
		FRAME_STR(IPC_GPRS_SHOW_PDP_ADDR)
		FRAME_STR(IPC_GPRS_MS_CLASS)
		FRAME_STR(IPC_GPRS_3G_QUAL_SERVICE_PROFILE)
		FRAME_STR(IPC_GPRS_IP_CONFIGURATION)
		FRAME_STR(IPC_GPRS_DEFINE_SEC_PDP_CONTEXT)
		FRAME_STR(IPC_GPRS_TFT)
		FRAME_STR(IPC_GPRS_HSDPA_STATUS)
		FRAME_STR(IPC_GPRS_CURRENT_SESSION_DATA_COUNT)
		FRAME_STR(IPC_GPRS_DATA_DORMANT)
		FRAME_STR(IPC_GPRS_DUN_PIN_CTRL)
		FRAME_STR(IPC_GPRS_CALL_STATUS)
		FRAME_STR(IPC_SAT_PROFILE_DOWNLOAD)
		FRAME_STR(IPC_SAT_ENVELOPE_CMD)
		FRAME_STR(IPC_SAT_PROACTIVE_CMD)
		FRAME_STR(IPC_SAT_TERMINATE_USAT_SESSION)
		FRAME_STR(IPC_SAT_EVENT_DOWNLOAD)
		FRAME_STR(IPC_SAT_PROVIDE_LOCAL_INFO)
		FRAME_STR(IPC_SAT_POLLING)
		FRAME_STR(IPC_SAT_REFRESH)
		FRAME_STR(IPC_SAT_SETUP_EVENT_LIST)
		FRAME_STR(IPC_SAT_CALL_CONTROL_RESULT)
		FRAME_STR(IPC_SAT_IMAGE_CLUT)
		FRAME_STR(IPC_SAT_CALL_PROCESSING)
		FRAME_STR(IPC_IMEI_START)
		FRAME_STR(IPC_IMEI_CHECK_DEVICE_INFO)
		FRAME_STR(IPC_GEN_PHONE_RES)
		default:
			return "UNKNOWN_FRAME";
	}
}

void ipc_tx(const char *data, const int length)
{
	unsigned int frame_len = (length+2);

	char *hdlc = malloc(frame_len);
	hdlc[0] = FRAME_START;
	hdlc[length+1] = FRAME_END;

	memcpy(hdlc+1, data, length);

	hex_dump(hdlc, frame_len);
	printf("\n");

	write(fd, hdlc, frame_len);
	free(hdlc);
}

void ipc_send(const int type, const int method, const unsigned char *data, const int data_length, int request_id)
{
	struct ipc_hdr header;
	unsigned int len = sizeof(header);
	unsigned int frame_length = (len + data_length);
	char *frame = malloc(frame_length);

	memset(&header, 0x00, len);
	header.frame_len = frame_length;
	header.seqnum = request_id; //fixme
	header.reqid = 0xff; //fixme
	header.len = (frame_length - 3);
	header.group = FRAME_GRP(type);
	header.index = FRAME_IDX(type);
	header.type = method;

	memcpy(frame, &header, sizeof(header));
	memcpy(frame+len, data, data_length);

	printf("\n%s: %s\n", __FUNCTION__, ipc_str(&header));
	ipc_tx(frame, frame_length);
	free(frame);
}

void ipc_send_get(const int type, int request_id)
{
	ipc_send(type, IPC_TYPE_GET, NULL, 0, request_id);
}

void ipc_send_exec(const int type, int request_id)
{
	ipc_send(type, IPC_TYPE_EXEC, NULL, 0, request_id);
}

void ipc_pwr_phone_pwr_up(struct ipc_request_info *info, const char *data, const int len)
{
	/* Modem reports bogus IMEI if queried right after powerup */
	usleep(25000);
	ipc_rx_callback(info);
}

void ipc_decode_frame(char *frame, int length) {
	struct ipc_hdr *header = (struct ipc_hdr*)frame;
	char *data = frame + sizeof(*header);

	unsigned short data_len = (header->frame_len - sizeof(*header));
	unsigned char request_id = header->reqid;

	struct ipc_request_info request_info;
	request_info.type = FRAME_ID(header);
	request_info.id = request_id;
	request_info.method = header->type;

	/* FIXME: These args are also passed to each handler below? */
	request_info.data = data;
	request_info.length = data_len;

	printf("%s %s (%u/%u) seq=%d req=%d\n", ipc_str(header), ipc_type(header), header->frame_len, data_len, header->seqnum, header->reqid);
	hex_dump(frame, length);

	switch(request_info.type) {
		/* Power */
		case IPC_PWR_PHONE_PWR_UP:
			ipc_pwr_phone_pwr_up(&request_info, data, data_len);
			break;
		/* Misc */
		case IPC_MISC_ME_SN:
			ipc_rx_misc_me_sn(&request_info, data, data_len);
			break;
		case IPC_MISC_TIME_INFO:
			ipc_rx_misc_time_info(&request_info, data, data_len);
			break;
		/* Net */
		case IPC_NET_CURRENT_PLMN:
			ipc_rx_net_current_plmn(&request_info, data, data_len);
			break;
		case IPC_NET_PLMN_LIST:
			ipc_rx_net_plmn_list(&request_info, data, data_len);
			break;
		case IPC_NET_REGIST:
			ipc_rx_net_regist(&request_info, data, data_len);
			break;
		default:
			ipc_rx_callback(&request_info);
			break;
	}

	printf("\n");
}

void ipc_loop()
{
	unsigned char frame_len;
	char *buf = malloc(1024);
	if(!buf) {
		printf("Failed to alloc receive buf\n");
		return;
	}

	fd_set fds;

	FD_ZERO(&fds);
	FD_SET(fd, &fds);

	while(1) {
		select(fd+1, &fds, NULL, NULL, NULL);
		int num_read = read(fd, buf, 1024);

		char *p = buf;
		char *frame = NULL;

		while(p < (buf+num_read)) {
			if(*p == FRAME_START) {
				frame = (p+1);
				frame_len = *frame;
			} else if(*p == FRAME_END && p == (frame+frame_len)) {
				ipc_decode_frame(frame, (p - frame));
			}

			p++;
		}
	}
}
