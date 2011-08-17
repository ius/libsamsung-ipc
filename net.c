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
#include "radio_internal.h"

/**
 * Requests the current PLMN
 */
void ipc_net_current_plmn(int request_id)
{
	ipc_send_get(IPC_NET_CURRENT_PLMN, request_id);
}

void ipc_rx_net_current_plmn(struct ipc_request_info *info, char *data, int len)
{
	struct ipc_net_current_plmn *plmndata = (struct ipc_net_current_plmn*)data;

	info->data = plmndata;
	info->length = sizeof(*plmndata);
	ipc_rx_callback(info);
}

void ipc_net_plmn_list(int request_id)
{
	ipc_send_get(IPC_NET_PLMN_LIST, request_id);
}

void ipc_rx_net_plmn_list(struct ipc_request_info *info, char *data, int len)
{
	unsigned char num_entries = *((unsigned char*)data);

	struct ipc_net_plmn_entries entries;
	entries.num = num_entries;
	entries.data = (struct ipc_net_plmn_entry*)(data+1);

	info->data = &entries;
	info->length = sizeof(entries);
	ipc_rx_callback(info);
}

void ipc_rx_net_regist(struct ipc_request_info *info, const char *data, int len)
{
	struct ipc_net_regist *netinfo = (struct ipc_net_regist*)data;

	info->data = netinfo;
	info->length = sizeof(*netinfo);
	ipc_rx_callback(info);
}

void ipc_net_identity(int request_id)
{
	ipc_send_get(IPC_NET_IDENTITY, request_id);
}

void ipc_net_regist(int request_id, unsigned char type)
{
	unsigned char data[] = { 0xff, 0x00 };
	if(type == 0) {
		ipc_send_get(IPC_NET_REGIST, request_id);
	} else {
		data[1] = type;
		ipc_send(IPC_NET_REGIST, IPC_TYPE_GET, data, sizeof(data), request_id);
	}
}

