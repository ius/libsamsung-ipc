/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2011 Paul Kocialkowski <contact@paulk.fr>
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

#ifndef __DEVICE_H1_SMS_H__
#define __DEVICE_H1_SMS_H__

#define IPC_SMS_ACK_NO_ERROR            0x0000
#define IPC_SMS_ACK_PDA_FULL_ERROR      0x8080
#define IPC_SMS_ACK_MALFORMED_REQ_ERROR 0x8061
#define IPC_SMS_ACK_UNSPEC_ERROR        0x806F

struct ipc_sms_incoming_msg {
    unsigned char type, unk, length;
} __attribute__((__packed__));

struct ipc_sms_send_msg {
    unsigned char hint, length;
} __attribute__((__packed__));


#endif

// vim:ts=4:sw=4:expandtab
