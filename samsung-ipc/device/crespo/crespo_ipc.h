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

#ifndef __CRESPO_IPC_H__
#define __CRESPO_IPC_H__

#define BOOTCORE_VERSION        0xf0
#define PSI_MAGIC               0x30
#define PSI_DATA_LEN            0x5000
#define RADIO_IMG_SIZE          0xd80000

#define MAX_MODEM_DATA_SIZE     0x1000

struct samsung_rfs_msg
{
    uint32_t offset;
    uint32_t size;
};

struct samsung_rfs_cfrm
{
    uint8_t confirmation;
    struct samsung_rfs_msg msg;
};

void *mtd_read(char *mtd_name, int size, int block_size);
void *file_read(char *file_name, int size, int block_size);
int wake_lock(char *lock_name, int size);
int wake_unlock(char *lock_name, int size);

extern struct ipc_handlers crespo_ipc_default_handlers;

#endif
