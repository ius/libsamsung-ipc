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

#ifndef __MISC_H__
#define __MISC_H__

#define MSM_MISC_ME_VERSION				0x0A01
#define MSM_MISC_ME_IMSI				0x0A02
#define MSM_MISC_ME_SN					0x0A03
#define MSM_MISC_TIME_INFO				0x0A07

struct msm_misc_time_info {
	unsigned char tzv, dlv;
	unsigned char year, mon, day;
	unsigned char hour, min, sec;
	unsigned char tz, dl, dv;
	char plmn[6];
} __attribute__((__packed__));

void msm_misc_me_sn(int request_id);

#endif

