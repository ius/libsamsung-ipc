/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2011 Simon Busch <morphis@gravedo.de>
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

#ifndef __GPRS_H__
#define __GPRS_H__

#define IPC_GPRS_DEFINE_PDP_CONTEXT         0x0D01
#define IPC_GPRS_QOS                        0x0D02
#define IPC_GPRS_PS                         0x0D03
#define IPC_GPRS_PDP_CONTEXT                0x0D04
#define IPC_GPRS_SHOW_PDP_ADDR              0x0D05
#define IPC_GPRS_MS_CLASS                   0x0D06
#define IPC_GPRS_3G_QUAL_SERVICE_PROFILE    0x0D07
#define IPC_GPRS_DEFINE_SEC_PDP_CONTEXT     0x0D08
#define IPC_GPRS_IP_CONFIGURATION           0x0D09
#define IPC_GPRS_TFT                        0x0D0A
#define IPC_GPRS_HSDPA_STATUS               0x0D0B
#define IPC_GPRS_CURRENT_SESSION_DATA_COUNT 0x0D0C
#define IPC_GPRS_DATA_DORMANT               0x0D0D
#define IPC_GPRS_DUN_PIN_CTRL               0x0D0E
#define IPC_GPRS_CALL_STATUS                0x0D0F

#define IPC_GPRS_CALL_STATUS_TYPE_ON        0x0
#define IPC_GPRS_CALL_STATUS_TYPE_OFF       0x3

#define IPC_GPRS_ERROR_UNAVAILABLE          0x94

struct ipc_gprs_define_pdp_context {
    unsigned char unk0[3];
    unsigned char apn[124];
};

struct ipc_gprs_ip_configuration {
    unsigned char unk0;
    unsigned char field_flag;
    unsigned char unk1;
    unsigned char ip[4];
    unsigned char dns1[4];
    unsigned char dns2[4];
    unsigned char gateway[4];
    unsigned char subnet_mask[4];
    unsigned char unk2[4];
};

struct ipc_gprs_ip_configuration_response {
    unsigned char unk0[376];
};

struct ipc_gprs_call_status {
    unsigned char cid;
    unsigned char state; // IPC_GPRS_CALL_STATUS_TYPE_...
    unsigned short reason;
};

struct ipc_gprs_hsdpa_status {
    unsigned char unk;
};

struct ipc_gprs_pdp_context {
    unsigned char unk0[6];
    unsigned char username[32];
    unsigned char password[32];
    unsigned char unk1[32];
    unsigned char unk2;
};

struct ipc_gprs_ps {
    unsigned char unk[2];
};

struct ipc_gprs_current_session_data_counter {
    unsigned char unk[9];
};

void ipc_gprs_pdp_context_setup(struct ipc_gprs_pdp_context *message, char *username, char *password);

#endif

