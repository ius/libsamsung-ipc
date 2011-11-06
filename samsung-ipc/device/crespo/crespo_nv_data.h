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

#ifndef __CRESPO_NV_DATA_H__
#define __CRESPO_NV_DATA__

#include <radio.h>

#define	NV_DATA_MD5_SECRET	"Samsung_Android_RIL"
#define NV_DATA_SIZE		0x200000

#define MD5_STRING_SIZE		MD5_DIGEST_LENGTH * 2 + 1

void md5hash2string(char *out, uint8_t *in);
void nv_data_generate(struct ipc_client *client);
void nv_data_md5_compute(void *data_p, int size, void *hash);
void nv_data_backup_create(struct ipc_client *client);
void nv_data_backup_restore(struct ipc_client *client);
void nv_data_check(struct ipc_client *client);
void nv_data_md5_check(struct ipc_client *client);

#endif

// vim:ts=4:sw=4:expandtab
