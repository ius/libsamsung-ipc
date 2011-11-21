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

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <asm/types.h>
#include <mtd/mtd-abi.h>

#include <radio.h>

const char *plmn_lookup(const char *plmn)
{
    unsigned int mcc, mnc;
    sscanf(plmn, "%3u%2u", &mcc, &mnc);

    switch(mcc) {
        case 204:
            switch(mnc) {
                case 1: return "VastMobiel";
                case 2: return "Tele2";
                case 4: return "Vodafone";
                case 8: case 10: return "KPN";
                case 12: return "Telfort";
                case 16: case 20: return "T-Mobile";
            }
        break;
        case 208:
            switch(mnc) {
                case 0: return "Orange";
                case 1: return "Orange";
                case 2: return "Orange";
                case 5: case 6: case 7: return "Globalstar Europe";
                case 9: return "SFR";
                case 10: return "SFR";
                case 11: return "SFR";
                case 13: return "SFR";
                case 14: return "Free Mobile";
                case 15: return "Free Mobile";
                case 20: return "Bouygues";
                case 21: return "Bouygues";
                case 22: return "Transatel Mobile";
                case 23: return "Virgin Mobile";
                case 25: return "Lycamobile";
                case 26: return "NRJ Mobile";
                case 27: return "Afone Mobile";
                case 88: return "Bouygues";
                case 90: return "Association Images & Réseaux";
            }
        break;
    }

    return NULL;
}

char *plmn_string(const char *plmn)
{
    int length = (plmn[5] == '#') ? 6 : 7;

    char *plmn_str = (char*)malloc(length);

    memcpy(plmn_str, plmn, length);
    plmn_str[length-1] = '\0';

    return plmn_str;
}

// vim:ts=4:sw=4:expandtab
