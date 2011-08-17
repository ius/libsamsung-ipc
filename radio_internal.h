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

#include <radio.h>

#define IOCTL_PHONE_ON			0x68d0
#define IOCTL_PHONE_OFF			0x68d1
#define IOCTL_PHONE_GETSTATUS		0x68d2
#define IOCTL_PHONE_RESET		0x68d3
#define IOCTL_PHONE_RAMDUMP		0x68d4
#define IOCTL_PHONE_BOOTTYPE		0x68d5
#define IOCTL_MEM_RW			0x68d6
#define IOCTL_WAKEUP			0x68d7
#define IOCTL_SILENT_RESET		0x68d8

#ifdef ANDROID

#define LOG_TAG "RIL"
#include <utils/Log.h>
#define printf LOGI

#endif

/* Receive callback */
void ipc_rx_callback(struct ipc_request_info *info);

void ipc_send_get(const int type, int request_id);
void ipc_send_exec(const int type, int request_id);

/* Misc */
void ipc_rx_misc_me_sn(struct ipc_request_info *info, char *data, int len);
void ipc_rx_misc_time_info(struct ipc_request_info *info, char *data, int len);

/* Net */
void ipc_rx_net_current_plmn(struct ipc_request_info *info, char *data, int len);
void ipc_rx_net_plmn_list(struct ipc_request_info *info, char *data, int len);
void ipc_rx_net_regist(struct ipc_request_info *info, const char *data, int len);


struct ipc_hdr {
	unsigned short frame_len;
	unsigned char unk;
	unsigned short len;
	unsigned char seqnum, reqid, group, index, type;
} __attribute__((__packed__));
