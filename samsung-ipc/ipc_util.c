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

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <asm/types.h>
#include <mtd/mtd-abi.h>

#include <radio.h>
#include "ipc_private.h"

#define IPC_STR(f)	case f: return strdup(#f);

const char *ipc_response_type_to_str(int type) {
	switch(type) {
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

const char *ipc_request_type_to_str(int type) {
    switch(type) {
        case IPC_TYPE_EXEC:
            return "EXEC";
        case IPC_TYPE_GET:
            return "GET";
        case IPC_TYPE_SET:
            return "SET";
        case IPC_TYPE_CFRM:
            return "CFRM";
        case IPC_TYPE_EVENT:
            return "EVENT";
		default:
			return "UNKNOWN";
    }
}

const char *ipc_command_type_to_str(int command) {
	switch(command) {
		IPC_STR(IPC_PWR_PHONE_PWR_UP)
		IPC_STR(IPC_PWR_PHONE_PWR_OFF)
		IPC_STR(IPC_PWR_PHONE_RESET)
		IPC_STR(IPC_PWR_BATT_STATUS)
		IPC_STR(IPC_PWR_BATT_TYPE)
		IPC_STR(IPC_PWR_BATT_COMP)
		IPC_STR(IPC_PWR_PHONE_STATE)
		IPC_STR(IPC_CALL_OUTGOING)
		IPC_STR(IPC_CALL_INCOMING)
		IPC_STR(IPC_CALL_RELEASE)
		IPC_STR(IPC_CALL_ANSWER)
		IPC_STR(IPC_CALL_STATUS)
		IPC_STR(IPC_CALL_LIST)
		IPC_STR(IPC_CALL_BURST_DTMF)
		IPC_STR(IPC_CALL_CONT_DTMF)
		IPC_STR(IPC_CALL_WAITING)
		IPC_STR(IPC_CALL_LINE_ID)
		IPC_STR(IPC_SMS_SEND_MSG)
		IPC_STR(IPC_SMS_INCOMING_MSG)
		IPC_STR(IPC_SMS_READ_MSG)
		IPC_STR(IPC_SMS_SAVE_MSG)
		IPC_STR(IPC_SMS_DEL_MSG)
		IPC_STR(IPC_SMS_DELIVER_REPORT)
		IPC_STR(IPC_SMS_DEVICE_READY)
		IPC_STR(IPC_SMS_SEL_MEM)
		IPC_STR(IPC_SMS_STORED_MSG_COUNT)
		IPC_STR(IPC_SMS_SVC_CENTER_ADDR)
		IPC_STR(IPC_SMS_SVC_OPTION)
		IPC_STR(IPC_SMS_MEM_STATUS)
		IPC_STR(IPC_SMS_CBS_MSG)
		IPC_STR(IPC_SMS_CBS_CONFIG)
		IPC_STR(IPC_SMS_STORED_MSG_STATUS)
		IPC_STR(IPC_SMS_PARAM_COUNT)
		IPC_STR(IPC_SMS_PARAM)
		IPC_STR(IPC_SEC_PIN_STATUS)
		IPC_STR(IPC_SEC_PHONE_LOCK)
		IPC_STR(IPC_SEC_CHANGE_LOCKING_PW)
		IPC_STR(IPC_SEC_SIM_LANG)
		IPC_STR(IPC_SEC_RSIM_ACCESS)
		IPC_STR(IPC_SEC_GSIM_ACCESS)
		IPC_STR(IPC_SEC_SIM_ICC_TYPE)
		IPC_STR(IPC_SEC_LOCK_INFO)
		IPC_STR(IPC_SEC_ISIM_AUTH)
		IPC_STR(IPC_PB_ACCESS)
		IPC_STR(IPC_PB_STORAGE)
		IPC_STR(IPC_PB_STORAGE_LIST)
		IPC_STR(IPC_PB_ENTRY_INFO)
		IPC_STR(IPC_PB_CAPABILITY_INFO)
		IPC_STR(IPC_DISP_ICON_INFO)
		IPC_STR(IPC_DISP_HOMEZONE_INFO)
		IPC_STR(IPC_NET_PREF_PLMN)
		IPC_STR(IPC_NET_PLMN_SEL)
		IPC_STR(IPC_NET_CURRENT_PLMN)
		IPC_STR(IPC_NET_PLMN_LIST)
		IPC_STR(IPC_NET_REGIST)
		IPC_STR(IPC_NET_SUBSCRIBER_NUM)
		IPC_STR(IPC_NET_BAND_SEL)
		IPC_STR(IPC_NET_SERVICE_DOMAIN_CONFIG)
		IPC_STR(IPC_NET_POWERON_ATTACH)
		IPC_STR(IPC_NET_MODE_SEL)
		IPC_STR(IPC_NET_ACQ_ORDER)
		IPC_STR(IPC_NET_IDENTITY)
		IPC_STR(IPC_NET_CURRENT_RRC_STATUS)
		IPC_STR(IPC_MISC_ME_VERSION)
		IPC_STR(IPC_MISC_ME_IMSI)
		IPC_STR(IPC_MISC_ME_SN)
		IPC_STR(IPC_MISC_TIME_INFO)
		IPC_STR(IPC_SS_WAITING)
		IPC_STR(IPC_SS_CLI)
		IPC_STR(IPC_SS_BARRING)
		IPC_STR(IPC_SS_BARRING_PW)
		IPC_STR(IPC_SS_FORWARDING)
		IPC_STR(IPC_SS_INFO)
		IPC_STR(IPC_SS_MANAGE_CALL)
		IPC_STR(IPC_SS_USSD)
		IPC_STR(IPC_SS_AOC)
		IPC_STR(IPC_SS_RELEASE_COMPLETE)
		IPC_STR(IPC_GPRS_DEFINE_PDP_CONTEXT)
		IPC_STR(IPC_GPRS_QOS)
		IPC_STR(IPC_GPRS_PS)
		IPC_STR(IPC_GPRS_PDP_CONTEXT)
		IPC_STR(IPC_GPRS_SHOW_PDP_ADDR)
		IPC_STR(IPC_GPRS_MS_CLASS)
		IPC_STR(IPC_GPRS_3G_QUAL_SERVICE_PROFILE)
		IPC_STR(IPC_GPRS_IP_CONFIGURATION)
		IPC_STR(IPC_GPRS_DEFINE_SEC_PDP_CONTEXT)
		IPC_STR(IPC_GPRS_TFT)
		IPC_STR(IPC_GPRS_HSDPA_STATUS)
		IPC_STR(IPC_GPRS_CURRENT_SESSION_DATA_COUNT)
		IPC_STR(IPC_GPRS_DATA_DORMANT)
		IPC_STR(IPC_GPRS_DUN_PIN_CTRL)
		IPC_STR(IPC_GPRS_CALL_STATUS)
		IPC_STR(IPC_SAT_PROFILE_DOWNLOAD)
		IPC_STR(IPC_SAT_ENVELOPE_CMD)
		IPC_STR(IPC_SAT_PROACTIVE_CMD)
		IPC_STR(IPC_SAT_TERMINATE_USAT_SESSION)
		IPC_STR(IPC_SAT_EVENT_DOWNLOAD)
		IPC_STR(IPC_SAT_PROVIDE_LOCAL_INFO)
		IPC_STR(IPC_SAT_POLLING)
		IPC_STR(IPC_SAT_REFRESH)
		IPC_STR(IPC_SAT_SETUP_EVENT_LIST)
		IPC_STR(IPC_SAT_CALL_CONTROL_RESULT)
		IPC_STR(IPC_SAT_IMAGE_CLUT)
		IPC_STR(IPC_SAT_CALL_PROCESSING)
		IPC_STR(IPC_IMEI_START)
		IPC_STR(IPC_IMEI_CHECK_DEVICE_INFO)
		IPC_STR(IPC_GEN_PHONE_RES)
		default:
			return "IPC_UNKNOWN";
	}
}

void ipc_hex_dump(struct ipc_client *client, void *data, int size)
{
    /* dumps size bytes of *data to stdout. Looks like:
     * [0000] 75 6E 6B 6E 6F 77 6E 20
     *                  30 FF 00 00 00 00 39 00 unknown 0.....9.
     * (in a single line of course)
     */

    unsigned char *p = data;
    unsigned char c;
    int n;
    char bytestr[4] = {0};
    char addrstr[10] = {0};
    char hexstr[ 16*3 + 5] = {0};
    char charstr[16*1 + 5] = {0};
    for(n=1;n<=size;n++) {
        if (n%16 == 1) {
            /* store address for this line */
            snprintf(addrstr, sizeof(addrstr), "%.4x",
               ((unsigned int)p-(unsigned int)data) );
        }

        c = *p;
        if (isalnum(c) == 0) {
            c = '.';
        }

        /* store hex str (for left side) */
        snprintf(bytestr, sizeof(bytestr), "%02X ", *p);
        strncat(hexstr, bytestr, sizeof(hexstr)-strlen(hexstr)-1);

        /* store char str (for right side) */
        snprintf(bytestr, sizeof(bytestr), "%c", c);
        strncat(charstr, bytestr, sizeof(charstr)-strlen(charstr)-1);

        if(n%16 == 0) {
            /* line completed */
            ipc_client_log(client, "[%4.4s]   %-50.50s  %s", addrstr, hexstr, charstr);
            hexstr[0] = 0;
            charstr[0] = 0;
        } else if(n%8 == 0) {
            /* half line: add whitespaces */
            strncat(hexstr, "  ", sizeof(hexstr)-strlen(hexstr)-1);
            strncat(charstr, " ", sizeof(charstr)-strlen(charstr)-1);
        }
        p++; /* next byte */
    }

    if (strlen(hexstr) > 0) {
        /* print rest of buffer if not empty */
        ipc_client_log(client, "[%4.4s]   %-50.50s  %s\n", addrstr, hexstr, charstr);
    }
}

void *ipc_mtd_read(struct ipc_client *client, char *mtd_name, int size, int block_size)
{
    void *mtd_p=NULL;
    uint8_t *data_p=NULL;

    loff_t offs;
    int fd;
    int i;

    if(mtd_name == NULL || size <= 0 || block_size <= 0)
        goto error;

    ipc_client_log(client, "mtd_read: reading 0x%x bytes from %s with 0x%x bytes block size\n", size, mtd_name, block_size);

    fd=open(mtd_name, O_RDONLY);
    if(fd < 0)
        goto error;

    mtd_p=malloc(size);
    if(mtd_p == NULL)
        goto error;

    memset(mtd_p, 0, size);

    data_p=(uint8_t *) mtd_p;

    for(i=0 ; i < size / block_size ; i++)
    {
        offs = i * block_size;
        if(ioctl(fd, MEMGETBADBLOCK, &offs) == 1)
        {
            ipc_client_log(client, "mtd_read: warning: bad block at offset %lld\n", (long long int) offs);
            data_p+=block_size;
            continue;
        }

        read(fd, data_p, block_size);
        data_p+=block_size;
    }

    close(fd);

    return mtd_p;

error:
    ipc_client_log(client, "%s: something went wrong\n", __func__);
    return NULL;
}

void *ipc_file_read(struct ipc_client *client, char *file_name, int size, int block_size)
{
    void *file_p=NULL;
    uint8_t *data_p=NULL;

    int fd;
    int i;

    if(file_name == NULL || size <= 0 || block_size <= 0)
        goto error;

    ipc_client_log(client, "file_read: reading 0x%x bytes from %s with 0x%x bytes block size\n", size, file_name, block_size);

    fd=open(file_name, O_RDONLY);
    if(fd < 0)
        goto error;

    file_p=malloc(size);
    if(file_p == NULL)
        goto error;

    memset(file_p, 0, size);

    data_p=(uint8_t *) file_p;

    for(i=0 ; i < size / block_size ; i++)
    {
        read(fd, data_p, block_size);
        data_p+=block_size;
    }

    close(fd);

    return file_p;

error:
    ipc_client_log(client, "%s: something went wrong\n", __func__);
    return NULL;
}

// vim:ts=4:sw=4:expandtab
