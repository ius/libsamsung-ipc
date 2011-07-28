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

#ifndef __SEC_H__
#define __SEC_H__

#define MSM_SEC_PIN_STATUS				0x0501
#define MSM_SEC_PHONE_LOCK				0x0502
#define MSM_SEC_CHANGE_LOCKING_PW			0x0503
#define MSM_SEC_SIM_LANG				0x0504
#define MSM_SEC_RSIM_ACCESS				0x0505
#define MSM_SEC_GSIM_ACCESS				0x0506
#define MSM_SEC_SIM_ICC_TYPE				0x0507
#define MSM_SEC_LOCK_INFO				0x0508
#define MSM_SEC_ISIM_AUTH				0x0509

#define MSM_SEC_PIN_SIM_INITIALIZING			0x00
#define MSM_SEC_PIN_SIM_SIM_LOCK_REQUIRED		0x01
#define MSM_SEC_PIN_SIM_INSIDE_PF_ERROR			0x02
#define MSM_SEC_PIN_SIM_LOCK_SC				0x03
#define MSM_SEC_PIN_SIM_LOCK_FD				0x04
#define MSM_SEC_PIN_SIM_LOCK_PN				0x05
#define MSM_SEC_PIN_SIM_LOCK_PU				0x06
#define MSM_SEC_PIN_SIM_LOCK_PP				0x07
#define MSM_SEC_PIN_SIM_LOCK_PC				0x08
#define MSM_SEC_PIN_SIM_CARD_NOT_PRESENT		0x80
#define MSM_SEC_PIN_SIM_CARD_ERROR			0x81
#define MSM_SEC_PIN_SIM_INIT_COMPLETE			0x82
#define MSM_SEC_PIN_SIM_PB_INIT_COMPLETE		0x83

/* Key types for the SIM card (SC) facility */
#define MSM_SEC_PIN_SIM_LOCK_SC_PIN1_REQ		0x01
#define MSM_SEC_PIN_SIM_LOCK_SC_PUK_REQ			0x02
#define MSM_SEC_PIN_SIM_LOCK_SC_CARD_BLOCKED		0x05

#define MSM_SEC_SIM_CARD_TYPE_UNKNOWN			0x00
#define MSM_SEC_SIM_CARD_TYPE_SIM			0x01
#define MSM_SEC_SIM_CARD_TYPE_USIM			0x02

struct msm_sec_pin_status {
	unsigned char type;
	unsigned char key;
} __attribute__((__packed__));

#endif

