/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2010-2011 Joerie de Gram <j.de.gram@gmail.com>
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

#ifndef __DEVICE_CRESPO_NET_H__
#define __DEVICE_CRESPO_NET_H__

#define IPC_NET_ACCESS_TECHNOLOGY_UNKNOWN                           0xff
#define IPC_NET_ACCESS_TECHNOLOGY_GSM                               0x00
#define IPC_NET_ACCESS_TECHNOLOGY_GSM2                              0x01
#define IPC_NET_ACCESS_TECHNOLOGY_GPRS                              0x02
#define IPC_NET_ACCESS_TECHNOLOGY_EDGE                              0x03
#define IPC_NET_ACCESS_TECHNOLOGY_UMTS                              0x04

struct ipc_net_current_plmn {
    char unk0;
    unsigned char slevel;
    char unk1;
    unsigned char plmn[5];
    unsigned char type; // IPC_NET_SERVICE_TYPE_... ?
    unsigned short lac;
} __attribute__((__packed__));

#endif

// vim:ts=4:sw=4:expandtab
