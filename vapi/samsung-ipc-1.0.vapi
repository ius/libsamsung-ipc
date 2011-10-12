/*
 * samsung-ipc-1.0.vapi
 *
 * Copyright (C) 2011 Simon Busch <morphis@gravedo.de>
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

namespace SamsungIpc
{
    [CCode (cname = "int", cprefix = "IPC_CLIENT_TYPE_", has_type_id = false, cheader_filename = "radio.h")]
    public enum ClientType
    {
        CRESPO_FMT,
        CRESPO_RFS,
        H1,
    }

    [CCode (cname = "int", cprefix = "IPC_TYPE_", has_type_id = false, cheader_filename = "radio.h")]
    public enum RequestType
    {
        EXEC,
        GET,
        SET,
        CFRM,
        EVENT,
    }

    [CCode (cname = "int", cprefix = "IPC_TYPE_", has_type_id = false, cheader_filename = "radio.h")]
    public enum ResponseType
    {
        INDICATION,
        RESPONSE,
        NOTIFICATION,
    }

    [CCode (cname = "int", cprefix = "IPC_GROUP_", has_type_id = false, cheader_filename = "radio.h")]
    public enum MessageGroup
    {
        PWR,
        CALL,
        SMS,
        SEC,
        PB,
        DISP,
        NET,
        SND,
        MISC,
        SVC,
        SS,
        GPRS,
        SAT,
        CFG,
        IMEI,
        GPS,
        SAP,
        GEN
    }

    [CCode (cname = "int", cprefix = "IPC_PWR_", has_type_id = false, cheader_filename = "radio.h")]
    public enum PowerMessageType
    {
        PHONE_PWR_OFF,
        PHONE_PWR_UP,
        PHONE_RESET,
        BATT_STATUS,
        BATT_TYPE,
        BATT_COMP,
        PHONE_ONLINE,
    }

    [CCode (cname = "int", cprefix = "IPC_PB_", has_type_id = false, cheader_filename = "radio.h")]
    public enum PhonebookMessageType
    {
        ACCESS,
        STORAGE,
        STORAGE_LIST,
        ENTRY_INFO,
        CAPABILITY_INFO,
    }

    [CCode (cname = "int", cprefix = "IPC_SS_", has_type_id = false, cheader_filename = "radio.h")]
    public enum SupplementarySevicesMessageType
    {
        WAITING,
        CLI,
        BARRING,
        BARRING_PW,
        FORWARDING,
        INFO,
        MANAGE_CALL,
        USSD,
        AOC,
        RELASE_COMPLETE,
    }

    [CCode (cname = "int", cprefix = "IPC_GPRS_", has_type_id = false, cheader_filename = "radio.h")]
    public enum GprsMessageType
    {
        DEFINE_PDP_CONTEXT,
        QOS,
        PS,
        PDP_CONTEXT,
        SHOW_PDP_ADDR,
        /* 3G_QUAL_SERVICE_PROFILE, */
        IP_CONFIGURATION,
        DEFINE_SEC_PDP_CONTEXT,
        TFT,
        HSDPA_STATUS,
        CURRENT_SESSION_DATA_COUNT,
        DATA_DORMANT,
        DUN_PIN_CTRL,
        CALL_STATUS,
    }

    [CCode (cname = "int", cprefix = "IPC_SAT_", has_type_id = false, cheader_filename = "radio.h")]
    public enum SatMessageType
    {
        PROFILE_DOWNLOAD,
        ENVELOPE_CMD,
        PROACTIVE_CMD,
        TERMINATE_USAT_SESSION,
        EVENT_DOWNLOAD,
        PROVIDE_LOCAL_INFO,
        POLLING,
        REFRESH,
        SETUP_EVENT_LIST,
        CALL_CONTROL_RESULT,
        IMAGE_CLUT,
        CALL_PROCESSING,
    }

    [CCode (cname = "int", cprefix = "IPC_IMEI_", has_type_id = false, cheader_filename = "radio.h")]
    public enum ImeiMessageType
    {
        START,
        CHECK_DEVICE_INFO,
    }

    [CCode (cname = "int", cprefix = "IPC_CALL_", has_type_id = false, cheader_filename = "radio.h")]
    public enum CallMessageType
    {
        OUTGOING,
        INCOMING,
        RELEASE,
        ANSWER,
        STATUS,
        LIST,
        BURST_DTMF,
        CONT_DTMF,
        WAITING,
        LINE_ID,
    }

    [CCode (cname = "int", cprefix = "IPC_CALL_TYPE_", has_type_id = false, cheader_filename = "radio.h")]
    public enum CallType
    {
        VOICE,
        DATA,
    }

    [CCode (cname = "int", cprefix = "IPC_CALL_IDENTITY_", has_type_id = false, cheader_filename = "radio.h")]
    public enum CallIdentity
    {
        DEFAULT,
        HIDE,
        SHOW,
    }

    [CCode (cname = "int", cprefix = "IPC_CALL_PREFIX_", has_type_id = false, cheader_filename = "radio.h")]
    public enum CallPrefix
    {
        NONE,
        INTL,
    }

    [CCode (cname = "int", cprefix = "IPC_CALL_STATE_", has_type_id = false, cheader_filename = "radio.h")]
    public enum CallState
    {
        DIALING,
        IGNORING_INCOMING_STATUS,
        CONNECTED,
        RELEASED,
        CONNECTING,
    }

    [CCode (cname = "int", cprefix = "IPC_CALL_TERM_", has_type_id = false, cheader_filename = "radio.h")]
    public enum CallTermination
    {
        MO,
        MT,
    }

    [CCode (cname = "struct ipc_call_outgoing", cheader_filename = "radio.h")]
    public struct CallOutgoingMessage
    {
        public uint8 type;
        public uint8 identity;
        public uint8 length;
        public uint8 prefix;
        public uint8[] number;
    }

    [CCode (cname = "struct ipc_call_incoming", cheader_filename = "radio.h")]
    public struct CallIncomingMessage
    {
        public uint8 type;
        public uint8 id;
        public uint8 line;
    }

    [CCode (cname = "struct ipc_call_list_entry", cheader_filename = "radio.h")]
    public struct CallListEntryMessage
    {
        public uint8 type;
        public uint8 idx;
        public uint8 term;
        public uint8 state;
        public uint8 mpty;
        public uint8 number_len;
        public uint8 unk4;
    }

    [CCode (cname = "struct ipc_call_status", cheader_filename = "radio.h")]
    public struct CallStatusMessage
    {
        public uint8 type;
        public uint8 id;
        public uint8 state;
        public uint8 reason;
        public uint8 end_cause;
    }

    [CCode (cname = "struct ipc_header", cheader_filename = "radio.h")]
    public struct Header
    {
        public uint16 length;
        public uint8 mseq;
        public uint8 aseq;
        public uint8 group;
        public uint8 index;
        public uint8 type;
    }

    [CCode (cname = "struct ipc_request", cheader_filename = "radio.h", destroy_function = "")]
    public struct Request
    {
        public uint8 mseq;
        public uint8 aseq;
        public uint8 group;
        public uint8 index;
        public uint8 type;
        public uint32 length;
        public uint8[] data;
    }

    [Compact]
    [CCode (cname = "struct ipc_response", cheader_filename = "radio.h", destroy_function = "")]
    public struct Response
    {
        public uint8 mseq;
        public uint8 aseq;
        public uint16 command;
        public uint8 type;
        public uint32 data_length;
        [CCode (array_length_cname = "data_length")]
        public uint8[] data;
    }

    public delegate int TransportCb(uint8[] data);

    [Compact]
    [CCode (cname = "struct ipc_client", cprefix = "ipc_client_", cheader_filename = "radio.h")]
    public class Client
    {
        public Client(ClientType type);
        [CCode (delagate_target_pos = 0.9)]
        public int set_delegates(TransportCb write_cb, TransportCb read_cb);
        public int bootstrap_modem();
        public void open();
        public void close();
        public int recv(out Response response);
        public void send(int command, int type, uint8 data, int length, uint8 mseq);
        public void send_get(int command, uint8 aseq);
        public void send_exec(int command, uint8 aseq);
    }
}
