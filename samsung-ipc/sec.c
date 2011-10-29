/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2011 Simon Busch <morphis@gravedo.de>
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

#include <radio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/* 
 * ipc_sec_sim_file_system[] 
 * Source: cornucopia fsogsmd/src/lib/consts.vala
 * Git HEAD: f2e0268075ffb15ef237371cd2e1896561567665
 *
 * Copyright (C) 2009-2011 Michael 'Mickey' Lauer <mlauer@vanille-media.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 *
 */

struct ipc_sec_sim_filesystem_entry ipc_sec_sim_file_system[] =
{
    { 0x3F00,0x0000,  "MF" },   // root

    { 0x2FE2,0x3F00,  "EFiccid" },
    { 0x2F05,0x3F00,  "EFelp" },

    { 0x7F10,0x3F00,  "DFtelecom" },
    { 0x6F3A,0x7F10,  "EFadn" },
    { 0x6F3B,0x7F10,  "EFfdn" },
    { 0x6F3C,0x7F10,  "EFsms" },
    { 0x6F3D,0x7F10,  "EFccp" },
    { 0x6F40,0x7F10,  "EFmsisdn" },
    { 0x6F42,0x7F10,  "EFsmsp" },
    { 0x6F43,0x7F10,  "EFsmss" },
    { 0x6F44,0x7F10,  "EFlnd" },
    { 0x6F47,0x7F10,  "EFsmsr" },
    { 0x6F49,0x7F10,  "EFsdn" },
    { 0x6F4A,0x7F10,  "EFext1" },
    { 0x6F4B,0x7F10,  "EFext2" },
    { 0x6F4C,0x7F10,  "EFext3" },
    { 0x6F4D,0x7F10,  "EFbdn" },
    { 0x6F4E,0x7F10,  "EFext4" },
    { 0x6F4F,0x7F10,  "EFeccp" },  // 51.011
    { 0x6F58,0x7F10,  "EFcmi" },   // 51.011

    { 0x5F50,0x7F10,  "DFgraphics" },
    { 0x4F20,0x5F50,  "EFimg" },
    { 0x4F01,0x5F50,  "EFimg1" },  // Usual names of
    { 0x4F02,0x5F50,  "EFimg2" },  // Image data files.
    { 0x4F03,0x5F50,  "EFimg3" },
    { 0x4F04,0x5F50,  "EFimg4" },
    { 0x4F05,0x5F50,  "EFimg5" },

    { 0x7F20,0x3F00,  "DFgsm" },
    { 0x6F05,0x7F20,  "EFlp" },
    { 0x6F07,0x7F20,  "EFimsi" },
    { 0x6F20,0x7F20,  "EFkc" },
    { 0x6F2C,0x7F20,  "EFdck" },   // 51.011
    { 0x6F30,0x7F20,  "EFplmnsel" },
    { 0x6F31,0x7F20,  "EFhpplmn" },
    { 0x6F32,0x7F20,  "EFcnl" },   // 51.011
    { 0x6F37,0x7F20,  "EFacmmax" },
    { 0x6F38,0x7F20,  "EFsst" },
    { 0x6F39,0x7F20,  "EFacm" },
    { 0x6F3E,0x7F20,  "EFgid1" },
    { 0x6F3F,0x7F20,  "EFgid2" },
    { 0x6F41,0x7F20,  "EFpuct" },
    { 0x6F45,0x7F20,  "EFcbmi" },
    { 0x6F46,0x7F20,  "EFspn" },   // SIM Provider Name
    { 0x6F48,0x7F20,  "EFcbmid" },
    { 0x6F50,0x7F20,  "EFcbmir" },
    { 0x6F51,0x7F20,  "EFnia" },
    { 0x6F52,0x7F20,  "EFkcgprs" },
    { 0x6F53,0x7F20,  "EFlocigprs" },
    { 0x6F54,0x7F20,  "EFsume" },
    { 0x6F60,0x7F20,  "EFplmnwact" },
    { 0x6F61,0x7F20,  "EFoplmnwact" },
    { 0x6F62,0x7F20,  "EFhplmnwact" },
    { 0x6F63,0x7F20,  "EFcpbcch" },
    { 0x6F64,0x7F20,  "EFinvscan" },
    { 0x6F74,0x7F20,  "EFbcch" },
    { 0x6F78,0x7F20,  "EFacc" },
    { 0x6F7B,0x7F20,  "EFfplmn" },
    { 0x6F7E,0x7F20,  "EFloci" },
    { 0x6FAD,0x7F20,  "EFad" },
    { 0x6FAE,0x7F20,  "EFphase" },
    { 0x6FB1,0x7F20,  "EFvgcs" },
    { 0x6FB2,0x7F20,  "EFvgcss" },
    { 0x6FB3,0x7F20,  "EFvbs" },
    { 0x6FB4,0x7F20,  "EFvbss" },
    { 0x6FB5,0x7F20,  "EFemlpp" },
    { 0x6FB6,0x7F20,  "EFaaem" },
    { 0x6FB7,0x7F20,  "EFecc" },
    { 0x6FC5,0x7F20,  "EFpnn" },   // 51.011
    { 0x6FC6,0x7F20,  "EFopl" },   // 51.011
    { 0x6FC7,0x7F20,  "EFmbdn" },  // 51.011
    { 0x6FC8,0x7F20,  "EFext6" },  // Ext record for EFmbdn
    { 0x6FC9,0x7F20,  "EFmbi" },   // 51.011
    { 0x6FCA,0x7F20,  "EFmwis" },  // 51.011
    { 0x6FCB,0x7F20,  "EFcfis" },  // 51.011
    { 0x6FCC,0x7F20,  "EFext7" },  // 51.011
    { 0x6FCD,0x7F20,  "EFspdi" },  // 51.011
    { 0x6FCE,0x7F20,  "EFmmsn" },  // 51.011
    { 0x6FCF,0x7F20,  "EFext8" },  // 51.011
    { 0x6FD0,0x7F20,  "EFmmsicp" },// 51.011
    { 0x6FD1,0x7F20,  "EFmmsup" }, // 51.011
    { 0x6FD2,0x7F20,  "EFmmsucp" },// 51.011

    { 0x6F17,0x7F20,  "EF_MAILBOX_CPHS" },  // CPHS phase 2
    { 0x6F11,0x7F20,  "EF_VOICE_MAIL_INDICATOR_CPHS" }, // CPHS phase 2
    { 0x6F13,0x7F20,  "EF_CFF_CPHS" },  // CPHS phase 2
    { 0x6f14,0x7F20,  "EF_SPN_CPHS" },  // CPHS phase 2
    { 0x6f18,0x7F20,  "EF_SPN_SHORT_CPHS" },// CPHS phase 2
    { 0x6f16,0x7F20,  "EF_INFO_CPHS" }, // CPHS phase 2

    { 0x5F30,0x7F20,  "DFiridium" },
    { 0x5F31,0x7F20,  "DFglobst" },
    { 0x5F32,0x7F20,  "DFico" },
    { 0x5F33,0x7F20,  "DFaces" },

    { 0x5F40,0x7F20,  "DFeia/tia-553" },
    { 0x4F80,0x5F40,  "EFsid" },   // 51.011
    { 0x4F81,0x5F40,  "EFgpi" },   // 51.011
    { 0x4F82,0x5F40,  "EFipc" },   // 51.011
    { 0x4F83,0x5F40,  "EFcount" }, // 51.011
    { 0x4F84,0x5F40,  "EFnsid" },  // 51.011
    { 0x4F85,0x5F40,  "EFpsid" },  // 51.011
    { 0x4F86,0x5F40,  "EFnetsel" },// 51.011
    { 0x4F87,0x5F40,  "EFspl" },   // 51.011
    { 0x4F88,0x5F40,  "EFmin" },   // 51.011
    { 0x4F89,0x5F40,  "EFaccolc" },// 51.011
    { 0x4F8A,0x5F40,  "EFfc1" },   // 51.011
    { 0x4F8B,0x5F40,  "EFs-esn" }, // 51.011
    { 0x4F8C,0x5F40,  "EFcsid" },  // 51.011
    { 0x4F8D,0x5F40,  "EFreg-thresh" },// 51.011
    { 0x4F8E,0x5F40,  "EFccch" },  // 51.011
    { 0x4F8F,0x5F40,  "EFldcc" },  // 51.011
    { 0x4F90,0x5F40,  "EFgsm-recon" }, // 51.011
    { 0x4F91,0x5F40,  "EFamps-2-gsm" },// 51.011
    { 0x4F93,0x5F40,  "EFamps-ui" },   // 51.011

    { 0x5F60,0x7F20,  "DFcts" },

    { 0x5F70,0x7F20,  "DFsolsa" },
    { 0x4F30,0x5F70,  "EFsai" },
    { 0x4F31,0x5F70,  "EFsll" },

    { 0x5F3C,0x7F20,  "DFmexe" },
    { 0x4F40,0x5F3C,  "EFmexe-st" },
    { 0x4F41,0x5F3C,  "EForpk" },
    { 0x4F42,0x5F3C,  "EFarpk" },
    { 0x4F43,0x5F3C,  "EFtprpk" },

    { 0x7F22,0x3F00,  "DFis41" },

    { 0x7F23,0x3F00,  "DFfp-cts" }
};

void ipc_sec_pin_status_set_setup(struct ipc_sec_pin_status_set *message,
                                  unsigned char pin_type, char *pin1, char *pin2)
{
    assert(message != NULL);

     memset(message, 0, sizeof(struct ipc_sec_pin_status_set));

    message->type = pin_type;

    if (pin1 != NULL)
    {
        strncpy((char*)message->pin1, pin1, 8);
        message->length1 = strlen(pin1);
    }

    if (pin2 != NULL)
    {
        strncpy((char*)message->pin2, pin2, 8);
        message->length2 = strlen(pin2);
    }
}

unsigned short ipc_sec_sim_filesystem_entry_name_to_code(char *entry_name)
{
    int i;
    int table_size;

    table_size = (int) (sizeof(ipc_sec_sim_file_system) / sizeof(struct ipc_sec_sim_filesystem_entry));

    for(i=0 ; i < table_size ; i++)
    {
        if(strcmp(ipc_sec_sim_file_system[i].name, entry_name) == 0)
            return ipc_sec_sim_file_system[i].id;
    }

    return 0;
}

/*
 * ISO/IEC 7816-4 tells:
 * P1-P2 indicates controls and options for processing the command. 
 * A parameter byte set to '00' generally provides no further qualification. 
 * There is no other general convention for encoding the parameter bytes.
 */

void ipc_sec_rsim_access_request_setup(struct ipc_sec_rsim_access_request *request, 
                                       unsigned char command, char *entry_name, 
                                       unsigned char p1, unsigned char p2, unsigned char p3)
{
    request->command = command;
    request->fileid = ipc_sec_sim_filesystem_entry_name_to_code(entry_name);
    request->p1 = p1;
    request->p2 = p2;
    request->p3 = p3;
}

/*
 * ISO/IEC 7816-4 tells:
 * SWT bytes are status bytes (the first byte is the most significant byte)
 * 
 * See section 5.1.3 Status bytes
 * IPC_SEC_RSIM_ACCESS_COMP_NORMAL: Request completed normally
 * IPC_SEC_RSIM_ACCESS_COMP_WARNING: Request completed with warning(s)
 * IPC_SEC_RSIM_ACCESS_ABORT_EXEC: Request aborted with execution error(s)
 * IPC_SEC_RSIM_ACCESS_ABORT_CHECK: Request aborted with check error(s) on
 *                                  provided data
 */

int ipc_sec_rsim_access_response_get_status(struct ipc_message_info *response)
{
    int status_bytes;
    int status;

    struct ipc_sec_rsim_access_response *rsimresp;

    rsimresp = (struct ipc_sec_rsim_access_response*) response->data;
    status_bytes = (rsimresp->sw1 << 8) + rsimresp->sw2;

    if(status_bytes == 0x9000)
        return IPC_SEC_RSIM_ACCESS_COMP_NORMAL;

    /* SIM PIN required */
    if(status_bytes == 0x9404)
        return IPC_SEC_RSIM_ACCESS_ABORT_CHECK;

    switch (rsimresp->sw1)
    {
        case 0x61:
            return IPC_SEC_RSIM_ACCESS_COMP_NORMAL;
        break;

        case 0x62:
        case 0x63:
            return IPC_SEC_RSIM_ACCESS_COMP_WARNING;
        break;

        case 0x64:
        case 0x65:
        case 0x66:
            return IPC_SEC_RSIM_ACCESS_ABORT_EXEC;
        break;

        case 0x67:
        case 0x68:
        case 0x69:
        case 0x6a:
        case 0x6b:
        case 0x6c:
        case 0x6d:
        case 0x6e:
        case 0x6f:
            return IPC_SEC_RSIM_ACCESS_ABORT_CHECK;
        break;

        default:
            return IPC_SEC_RSIM_ACCESS_UNKNOWN;
        break;
    }
}

char* ipc_sec_rsim_access_response_get_file_data(struct ipc_message_info *response)
{
    int n = 0;
    int offset = (int) sizeof(struct ipc_sec_rsim_access_response);
    int size = 0;

    if (response == NULL)
        return NULL;

    struct ipc_sec_rsim_access_response *rsimresp = (struct ipc_sec_rsim_access_response*) response->data;
    char *file_data = (char*) malloc(sizeof(char) * rsimresp->len);

    for (n = 0; n < rsimresp->len; n++)
    {
        if (response->data[offset + n] == 0x0)
            continue;
        else if (response->data[offset + n] == 0xff)
            break;
        else {
            file_data[size] = response->data[offset + n];
            size++;
        }
    }

    if (size < rsimresp->len)
        file_data = (char*) realloc(file_data, sizeof(char) * size);

    return file_data;
}

// vim:ts=4:sw=4:expandtab
