/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2010-2011 Joerie de Gram <j.de.gram@gmail.com>
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

#ifndef __DEVICE_CRESPO_CALL_H__
#define __DEVICE_CRESPO_CALL_H__

struct ipc_call_outgoing {
    unsigned char unk;
    unsigned char type; // IPC_CALL_TYPE_...
    unsigned char identity; // IPC_CALL_IDENTITY_...
    unsigned char length;
    unsigned char prefix; // IPC_CALL_PREFIX_...
    unsigned char number[86];
} __attribute__((__packed__));

#endif

// vim:ts=4:sw=4:expandtab
