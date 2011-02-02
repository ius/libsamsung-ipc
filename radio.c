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
static struct msm_info *msm = NULL;

void msm_rx_callback(struct msm_request_info *info)
{
	msm->on_receive(info);
}

void msm_register(struct msm_info *msm_data)
{
	msm = msm_data;
}

void msm_open()
{
	fd = open(msm->tty, O_RDWR | O_NDELAY);

	if(fd < 0) {
		printf("Failed to open dpram tty\n");
	}

	struct termios termios;

	tcgetattr(fd, &termios);
	cfmakeraw(&termios);
	tcsetattr(fd, TCSANOW, &termios);
}

void msm_close()
{
	if(fd) {
		close(fd);
	}
}

void msm_power_on()
{
	ioctl(fd, IOCTL_PHONE_ON);
}

void msm_power_off()
{
	ioctl(fd, IOCTL_PHONE_OFF);
}

const char *msm_type(struct msm_hdr *frame) {
	switch(frame->type) {
		case MSM_TYPE_INDI:
			return "INDI";
		case MSM_TYPE_RESP:
			return "RESP";
		case MSM_TYPE_NOTI:
			return "NOTI";
		default:
			return "UNKNOWN";
	}
}

const char *msm_str(struct msm_hdr *frame) {
	switch(FRAME_ID(frame)) {
		FRAME_STR(MSM_PWR_PHONE_PWR_UP)
		FRAME_STR(MSM_PWR_PHONE_PWR_OFF)
		FRAME_STR(MSM_PWR_PHONE_RESET)
		FRAME_STR(MSM_PWR_BATT_STATUS)
		FRAME_STR(MSM_PWR_BATT_TYPE)
		FRAME_STR(MSM_PWR_BATT_COMP)
		FRAME_STR(MSM_PWR_PHONE_ONLINE)
		FRAME_STR(MSM_CALL_OUTGOING)
		FRAME_STR(MSM_CALL_INCOMING)
		FRAME_STR(MSM_CALL_RELEASE)
		FRAME_STR(MSM_CALL_ANSWER)
		FRAME_STR(MSM_CALL_STATUS)
		FRAME_STR(MSM_CALL_LIST)
		FRAME_STR(MSM_CALL_BURST_DTMF)
		FRAME_STR(MSM_CALL_CONT_DTMF)
		FRAME_STR(MSM_CALL_WAITING)
		FRAME_STR(MSM_CALL_LINE_ID)
		FRAME_STR(MSM_SMS_SEND_MSG)
		FRAME_STR(MSM_SMS_INCOMING_MSG)
		FRAME_STR(MSM_SMS_READ_MSG)
		FRAME_STR(MSM_SMS_SAVE_MSG)
		FRAME_STR(MSM_SMS_DEL_MSG)
		FRAME_STR(MSM_SMS_DELIVER_REPORT)
		FRAME_STR(MSM_SMS_DEVICE_READY)
		FRAME_STR(MSM_SMS_SEL_MEM)
		FRAME_STR(MSM_SMS_STORED_MSG_COUNT)
		FRAME_STR(MSM_SMS_SVC_CENTER_ADDR)
		FRAME_STR(MSM_SMS_SVC_OPTION)
		FRAME_STR(MSM_SMS_MEM_STATUS)
		FRAME_STR(MSM_SMS_CBS_MSG)
		FRAME_STR(MSM_SMS_CBS_CONFIG)
		FRAME_STR(MSM_SMS_STORED_MSG_STATUS)
		FRAME_STR(MSM_SMS_PARAM_COUNT)
		FRAME_STR(MSM_SMS_PARAM)
		FRAME_STR(MSM_SEC_PIN_STATUS)
		FRAME_STR(MSM_SEC_PHONE_LOCK)
		FRAME_STR(MSM_SEC_CHANGE_LOCKING_PW)
		FRAME_STR(MSM_SEC_SIM_LANG)
		FRAME_STR(MSM_SEC_RSIM_ACCESS)
		FRAME_STR(MSM_SEC_GSIM_ACCESS)
		FRAME_STR(MSM_SEC_SIM_ICC_TYPE)
		FRAME_STR(MSM_SEC_LOCK_INFO)
		FRAME_STR(MSM_SEC_ISIM_AUTH)
		FRAME_STR(MSM_PB_ACCESS)
		FRAME_STR(MSM_PB_STORAGE)
		FRAME_STR(MSM_PB_STORAGE_LIST)
		FRAME_STR(MSM_PB_ENTRY_INFO)
		FRAME_STR(MSM_PB_CAPABILITY_INFO)
		FRAME_STR(MSM_DISP_ICON_INFO)
		FRAME_STR(MSM_DISP_HOMEZONE_INFO)
		FRAME_STR(MSM_NET_PREF_PLMN)
		FRAME_STR(MSM_NET_PLMN_SEL)
		FRAME_STR(MSM_NET_CURRENT_PLMN)
		FRAME_STR(MSM_NET_PLMN_LIST)
		FRAME_STR(MSM_NET_REGIST)
		FRAME_STR(MSM_NET_SUBSCRIBER_NUM)
		FRAME_STR(MSM_NET_BAND_SEL)
		FRAME_STR(MSM_NET_SERVICE_DOMAIN_CONFIG)
		FRAME_STR(MSM_NET_POWERON_ATTACH)
		FRAME_STR(MSM_NET_MODE_SEL)
		FRAME_STR(MSM_NET_ACQ_ORDER)
		FRAME_STR(MSM_NET_IDENTITY)
		FRAME_STR(MSM_NET_CURRENT_RRC_STATUS)
		FRAME_STR(MSM_MISC_ME_VERSION)
		FRAME_STR(MSM_MISC_ME_IMSI)
		FRAME_STR(MSM_MISC_ME_SN)
		FRAME_STR(MSM_MISC_TIME_INFO)
		FRAME_STR(MSM_GPRS_DEFINE_PDP_CONTEXT)
		FRAME_STR(MSM_GPRS_QOS)
		FRAME_STR(MSM_GPRS_PS)
		FRAME_STR(MSM_GPRS_PDP_CONTEXT)
		FRAME_STR(MSM_GPRS_SHOW_PDP_ADDR)
		FRAME_STR(MSM_GPRS_MS_CLASS)
		FRAME_STR(MSM_GPRS_3G_QUAL_SERVICE_PROFILE)
		FRAME_STR(MSM_GPRS_IP_CONFIGURATION)
		FRAME_STR(MSM_GPRS_DEFINE_SEC_PDP_CONTEXT)
		FRAME_STR(MSM_GPRS_TFT)
		FRAME_STR(MSM_GPRS_HSDPA_STATUS)
		FRAME_STR(MSM_GPRS_CURRENT_SESSION_DATA_COUNT)
		FRAME_STR(MSM_GPRS_DATA_DORMANT)
		FRAME_STR(MSM_GPRS_DUN_PIN_CTRL)
		FRAME_STR(MSM_GPRS_CALL_STATUS)
		FRAME_STR(MSM_SAT_PROFILE_DOWNLOAD)
		FRAME_STR(MSM_SAT_ENVELOPE_CMD)
		FRAME_STR(MSM_SAT_PROACTIVE_CMD)
		FRAME_STR(MSM_SAT_TERMINATE_USAT_SESSION)
		FRAME_STR(MSM_SAT_EVENT_DOWNLOAD)
		FRAME_STR(MSM_SAT_PROVIDE_LOCAL_INFO)
		FRAME_STR(MSM_SAT_POLLING)
		FRAME_STR(MSM_SAT_REFRESH)
		FRAME_STR(MSM_SAT_SETUP_EVENT_LIST)
		FRAME_STR(MSM_SAT_CALL_CONTROL_RESULT)
		FRAME_STR(MSM_SAT_IMAGE_CLUT)
		FRAME_STR(MSM_SAT_CALL_PROCESSING)
		FRAME_STR(MSM_IMEI_START)
		FRAME_STR(MSM_IMEI_CHECK_DEVICE_INFO)
		default:
			return "UNKNOWN_FRAME";
	}
}

void msm_tx(const char *data, const int length)
{
	unsigned int frame_len = (length+2);

	char *hdlc = malloc(frame_len);
	hdlc[0] = FRAME_START;
	hdlc[length+1] = FRAME_END;

	memcpy(hdlc+1, data, length);

	printf("\n%s\n", __FUNCTION__);
	hex_dump(hdlc, frame_len);
	write(fd, hdlc, frame_len);
	free(hdlc);
}

void msm_send(const int type, const int method, const char *data, const int data_length, int request_id)
{
	struct msm_hdr header;
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

	msm_tx(frame, frame_length);
	free(frame);
}

void msm_send_get(const int type, int request_id)
{
	msm_send(type, MSM_TYPE_GET, NULL, 0, request_id);
}

void mem_pwr_phone_pwr_up(struct msm_request_info *info, const char *data, const int len)
{
	usleep(25000);
	msm_rx_callback(info);
}

void msm_call_outgoing(const char *number, int request_id)
{
	if(strlen(number) > 82) {
		printf("Outgoing call number too long\n");
		return;
	}

	struct msm_call_outgoing call;
	memset(&call, 0x00, sizeof(call));
	call.type = MSM_CALL_TYPE_VOICE;
	call.identity = MSM_CALL_IDENTITY_DEFAULT;
	call.length = strlen(number);
	call.prefix = MSM_CALL_PREFIX_NONE;
	memcpy(call.number, number, call.length);

	msm_send(MSM_CALL_OUTGOING, MSM_TYPE_EXEC, (const char*)&call, sizeof(call), request_id);
}

void msm_sec_pin_status(char *data, int len)
{
}

void msm_decode_frame(char *frame, int length) {
	struct msm_hdr *header = (struct msm_hdr*)frame;
	char *data = frame + sizeof(*header);

	unsigned short data_len = (header->frame_len - sizeof(*header));
	unsigned char request_id = header->reqid;

	struct msm_request_info request_info;
	request_info.type = FRAME_ID(header);
	request_info.id = request_id;

	printf("%s %s (%u/%u) seq=%d req=%d\n", msm_str(header), msm_type(header), header->frame_len, data_len, header->seqnum, header->reqid);
	hex_dump(frame, length);

	switch(request_info.type) {
		/* Power */
		case MSM_PWR_PHONE_PWR_UP:
			mem_pwr_phone_pwr_up(&request_info, data, data_len);
			break;
		/* Misc */
		case MSM_MISC_ME_SN:
			msm_rx_misc_me_sn(&request_info, data, data_len);
			break;
		case MSM_MISC_TIME_INFO:
			msm_rx_misc_time_info(&request_info, data, data_len);
			break;
		/* Sec */
		case MSM_SEC_PIN_STATUS:
			msm_sec_pin_status(data, data_len); //fixme
			break;
		/* Net */
		case MSM_NET_CURRENT_PLMN:
			msm_rx_net_current_plmn(&request_info, data, data_len);
			break;
		case MSM_NET_PLMN_LIST:
			msm_rx_net_plmn_list(&request_info, data, data_len);
			break;
		case MSM_NET_REGIST:
			msm_rx_net_regist(&request_info, data, data_len);
			break;
		default:
			msm_rx_callback(&request_info);
			break;
	}

	printf("\n");
}

void msm_loop()
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
				msm_decode_frame(frame, (p - frame));
			}

			p++;
		}
	}
}
