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

#ifndef __SEC_H__
#define __SEC_H__

struct ipc_response;

#define IPC_SEC_PIN_STATUS              0x0501
#define IPC_SEC_PHONE_LOCK              0x0502
#define IPC_SEC_CHANGE_LOCKING_PW           0x0503
#define IPC_SEC_SIM_LANG                0x0504
#define IPC_SEC_RSIM_ACCESS             0x0505
#define IPC_SEC_GSIM_ACCESS             0x0506
#define IPC_SEC_SIM_ICC_TYPE                0x0507
#define IPC_SEC_LOCK_INFO               0x0508
#define IPC_SEC_ISIM_AUTH               0x0509

#define IPC_SEC_PIN_SIM_INITIALIZING            0x00
#define IPC_SEC_PIN_SIM_SIM_LOCK_REQUIRED       0x01
#define IPC_SEC_PIN_SIM_INSIDE_PF_ERROR         0x02
#define IPC_SEC_PIN_SIM_LOCK_SC             0x03
#define IPC_SEC_PIN_SIM_LOCK_FD             0x04
#define IPC_SEC_PIN_SIM_LOCK_PN             0x05
#define IPC_SEC_PIN_SIM_LOCK_PU             0x06
#define IPC_SEC_PIN_SIM_LOCK_PP             0x07
#define IPC_SEC_PIN_SIM_LOCK_PC             0x08
#define IPC_SEC_PIN_SIM_CARD_NOT_PRESENT        0x80
#define IPC_SEC_PIN_SIM_CARD_ERROR          0x81
#define IPC_SEC_PIN_SIM_INIT_COMPLETE           0x82
#define IPC_SEC_PIN_SIM_PB_INIT_COMPLETE        0x83

/* Key types for the SIM card (SC) facility */
#define IPC_SEC_PIN_SIM_LOCK_SC_PIN1_REQ        0x01
#define IPC_SEC_PIN_SIM_LOCK_SC_PUK_REQ         0x02
#define IPC_SEC_PIN_SIM_LOCK_SC_CARD_BLOCKED        0x05

#define IPC_SEC_PIN_TYPE_PIN1               0x03
#define IPC_SEC_PIN_TYPE_PIN2               0x09

#define IPC_SEC_SIM_CARD_TYPE_UNKNOWN           0x00
#define IPC_SEC_SIM_CARD_TYPE_SIM           0x01
#define IPC_SEC_SIM_CARD_TYPE_USIM          0x02

#define IPC_SEC_RSIM_COMMAND_READ_BINARY    0xb0
#define IPC_SEC_RSIM_COMMAND_READ_RECORD    0xc0
#define IPC_SEC_RSIM_COMMAND_UPDATE_BINARY  0xd6
#define IPC_SEC_RSIM_COMMAND_STATUS         0xf2

struct ipc_sec_pin_status_noti {
    unsigned char type;
    unsigned char key;
} __attribute__((__packed__));

struct ipc_sec_pin_status_set {
    unsigned char type;
    unsigned char length1;
    unsigned char length2;
    unsigned char pin1[8];
    unsigned char pin2[8];
} __attribute__((__packed__));

struct ipc_sec_phone_lock_request {
    unsigned char lock_type;
};

struct ipc_sec_phone_lock_response {
    unsigned char type;
    unsigned char status;
} __attribute__((__packed__));

struct ipc_sec_rsim_access_request {
    unsigned char command;
    unsigned short fileid;
    unsigned char p1, p2, p3;
} __attribute__((__packed__));

struct ipc_sec_rsim_access_response {
    unsigned char sw1, sw2;
    unsigned char len;
} __attribute__((__packed__));

struct ipc_sec_lock_info_request {
    unsigned char unk0;
    unsigned char pin_type;
} __attribute__((__packed__));

struct ipc_sec_lock_info_response {
    unsigned char num;
    unsigned char type;
    unsigned char key;
    unsigned char attempts;
} __attribute__((__packed__));

char* ipc_sec_rsim_access_response_get_file_data(struct ipc_response *response);

void ipc_sec_pin_status_set_setup(struct ipc_sec_pin_status_set *message,
                                  unsigned char pin_type, char *pin1, char *pin2);

#endif

