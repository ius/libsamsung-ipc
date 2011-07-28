/**
 * This file is part of libmsm-h1.
 *
 * Copyright (C) 2010-2011 Joerie de Gram <j.de.gram@gmail.com>
 *
 * libmsm-h1 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libmsm-h1 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libmsm-h1.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <radio.h>
#include "radio_internal.h"

/**
 * Requests the current PLMN
 */
void msm_net_current_plmn(int request_id)
{
	msm_send_get(MSM_NET_CURRENT_PLMN, request_id);
}

void msm_rx_net_current_plmn(struct msm_request_info *info, char *data, int len)
{
	struct msm_net_current_plmn *plmndata = (struct msm_net_current_plmn*)data;

	info->data = plmndata;
	info->length = sizeof(*plmndata);
	msm_rx_callback(info);
}

void msm_net_plmn_list(int request_id)
{
	msm_send_get(MSM_NET_PLMN_LIST, request_id);
}

void msm_rx_net_plmn_list(struct msm_request_info *info, char *data, int len)
{
	unsigned char num_entries = *((unsigned char*)data);

	struct msm_net_plmn_entries entries;
	entries.num = num_entries;
	entries.data = (struct msm_net_plmn_entry*)(data+1);

	info->data = &entries;
	info->length = sizeof(entries);
	msm_rx_callback(info);
}

void msm_rx_net_regist(struct msm_request_info *info, const char *data, int len)
{
	struct msm_net_regist *netinfo = (struct msm_net_regist*)data;

	info->data = netinfo;
	info->length = sizeof(*netinfo);
	msm_rx_callback(info);
}

void msm_net_identity(int request_id)
{
	msm_send_get(MSM_NET_IDENTITY, request_id);
}

