
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

    public string request_type_to_string( int type )
    {
        string result = "unknown";

        switch ( (RequestType) type )
        {
            case RequestType.EXEC:
                result = "EXEC";
                break;
            case RequestType.GET:
                result = "GET";
                break;
            case RequestType.SET:
                result = "SET";
                break;
            case RequestType.CFRM:
                result = "CFRM";
                break;
            case RequestType.EVENT:
                result = "EVENT";
                break;
        }

        return result;
    }

    [CCode (cname = "int", cprefix = "IPC_TYPE_", has_type_id = false, cheader_filename = "radio.h")]
    public enum ResponseType
    {
        INDICATION,
        RESPONSE,
        NOTIFICATION,
    }

    public string response_type_to_string( ResponseType type )
    {
        string result = "unknown";

        switch ( type )
        {
            case ResponseType.INDICATION:
                result = "INDICATION";
                break;
            case ResponseType.RESPONSE:
                result = "RESPONSE";
                break;
            case ResponseType.NOTIFICATION:
                result = "NOTIFICATION";
                break;
        }

        return result;
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
        GEN,
    }

    public string message_group_to_string( int group )
    {
        string result = "unknown";

        switch ( (MessageGroup) group )
        {
            case MessageGroup.PWR:
                result = "PWR";
                break;
            case MessageGroup.CALL:
                result = "CALL";
                break;
            case MessageGroup.SMS:
                result = "SMS";
                break;
            case MessageGroup.SEC:
                result = "SEC";
                break;
            case MessageGroup.PB:
                result = "PB";
                break;
            case MessageGroup.DISP:
                result = "DISP";
                break;
            case MessageGroup.NET:
                result = "NET";
                break;
            case MessageGroup.SND:
                result = "SND";
                break;
            case MessageGroup.MISC:
                result = "MISC";
                break;
            case MessageGroup.SVC:
                result = "SVC";
                break;
            case MessageGroup.SS:
                result = "SS";
                break;
            case MessageGroup.GPRS:
                result = "GPRS";
                break;
            case MessageGroup.SAT:
                result = "SAT";
                break;
            case MessageGroup.CFG:
                result = "CFG";
                break;
            case MessageGroup.IMEI:
                result = "IMEI";
                break;
            case MessageGroup.GPS:
                result = "GPS";
                break;
            case MessageGroup.SAP:
                result = "SAP";
                break;
            case MessageGroup.GEN:
                result = "GEN";
                break;
        }

        return result;
    }

    [CCode (cname = "int", cprefix = "IPC_PWR_", has_type_id = false, cheader_filename = "radio.h")]
    public enum GenericMessageType
    {
        PHONE_RESPONSE,
    }

    [CCode (cname = "struct ipc_get_phone_res", cheader_filename = "radio.h")]
    public struct GenericPhoneResponseMessage
    {
        public uint8 group;
        public uint8 type;
        public uint16 code;
        public uint8 unk;
    }

    [CCode (cname = "int", cprefix = "IPC_", has_type_id = false, cheader_filename = "radio.h")]
    public enum MessageType
    {
        PWR_PHONE_PWR_OFF,
        PWR_PHONE_PWR_UP,
        PWR_PHONE_RESET,
        PWR_BATT_STATUS,
        PWR_BATT_TYPE,
        PWR_BATT_COMP,
        PWR_PHONE_ONLINE,
        PB_ACCESS,
        PB_STORAGE,
        PB_STORAGE_LIST,
        PB_ENTRY_INFO,
        PB_CAPABILITY_INFO,
        SS_WAITING,
        SS_CLI,
        SS_BARRING,
        SS_BARRING_PW,
        SS_FORWARDING,
        SS_INFO,
        SS_MANAGE_CALL,
        SS_USSD,
        SS_AOC,
        SS_RELEASE_COMPLETE,
        GPRS_DEFINE_PDP_CONTEXT,
        GPRS_QOS,
        GPRS_PS,
        GPRS_PDP_CONTEXT,
        GPRS_SHOW_PDP_ADDR,
        GPRS_3G_QUAL_SERVICE_PROFILE,
        GPRS_IP_CONFIGURATION,
        GPRS_DEFINE_SEC_PDP_CONTEXT,
        GPRS_TFT,
        GPRS_HSDPA_STATUS,
        GPRS_CURRENT_SESSION_DATA_COUNT,
        GPRS_DATA_DORMANT,
        GPRS_DUN_PIN_CTRL,
        GPRS_CALL_STATUS,
        SAT_PROFILE_DOWNLOAD,
        SAT_ENVELOPE_CMD,
        SAT_PROACTIVE_CMD,
        SAT_TERMINATE_USAT_SESSION,
        SAT_EVENT_DOWNLOAD,
        SAT_PROVIDE_LOCAL_INFO,
        SAT_POLLING,
        SAT_REFRESH,
        SAT_SETUP_EVENT_LIST,
        SAT_CALL_CONTROL_RESULT,
        SAT_IMAGE_CLUT,
        SAT_CALL_PROCESSING,
        IMEI_START,
        IMEI_CHECK_DEVICE_INFO,
        CALL_OUTGOING,
        CALL_INCOMING,
        CALL_RELEASE,
        CALL_ANSWER,
        CALL_STATUS,
        CALL_LIST,
        CALL_BURST_DTMF,
        CALL_CONT_DTMF,
        CALL_WAITING,
        CALL_LINE_ID,
    }

    public string message_type_to_string( MessageType type )
    {
        string result = "unknown";

        switch ( type )
        {
            case MessageType.PWR_PHONE_PWR_OFF:
                result = "PWR_PHONE_PWR_OFF";
                break;
            case MessageType.PWR_PHONE_PWR_UP:
                result = "PWR_PHONE_PWR_UP";
                break;
            case MessageType.PWR_PHONE_RESET:
                result = "PWR_PHONE_RESET";
                break;
            case MessageType.PWR_BATT_STATUS:
                result = "PWR_BATT_STATUS";
                break;
            case MessageType.PWR_BATT_TYPE:
                result = "PWR_BATT_TYPE";
                break;
            case MessageType.PWR_BATT_COMP:
                result = "PWR_BATT_COMP";
                break;
            case MessageType.PWR_PHONE_ONLINE:
                result = "WR_PHONE_ONLINE";
                break;
            case MessageType.PB_ACCESS:
                result = "PB_ACCESS";
                break;
            case MessageType.PB_STORAGE:
                result = "PB_STORAGE";
                break;
            case MessageType.PB_STORAGE_LIST:
                result = "PB_STORAGE_LIST";
                break;
            case MessageType.PB_ENTRY_INFO:
                result = "PB_ENTRY_INFO";
                break;
            case MessageType.PB_CAPABILITY_INFO:
                result = "PB_CAPABILITY_INFO";
                break;
            case MessageType.SS_WAITING:
                result = "SS_WAITING";
                break;
            case MessageType.SS_CLI:
                result = "SS_CLI";
                break;
            case MessageType.SS_BARRING:
                result = "SS_BARRING";
                break;
            case MessageType.SS_BARRING_PW:
                result = "SS_BARRING_PW";
                break;
            case MessageType.SS_FORWARDING:
                result = "SS_FORWARDING";
                break;
            case MessageType.SS_INFO:
                result = "SS_INFO";
                break;
            case MessageType.SS_MANAGE_CALL:
                result = "SS_MANAGE_CALL";
                break;
            case MessageType.SS_USSD:
                result = "SS_USSD";
                break;
            case MessageType.SS_AOC:
                result = "SS_AOC";
                break;
            case MessageType.SS_RELEASE_COMPLETE:
                result = "SS_RELEASE_COMPLETE";
                break;
            case MessageType.GPRS_DEFINE_PDP_CONTEXT:
                result = "GPRS_DEFINE_PDP_CONTEXT";
                break;
            case MessageType.GPRS_QOS:
                result = "GPRS_QOS";
                break;
            case MessageType.GPRS_PS:
                result = "GPRS_PS";
                break;
            case MessageType.GPRS_PDP_CONTEXT:
                result = "gPRS_PDP_CONTEXT";
                break;
            case MessageType.GPRS_SHOW_PDP_ADDR:
                result = "GPRS_SHOW_PDP_ADDR";
                break;
            case MessageType.GPRS_3G_QUAL_SERVICE_PROFILE:
                result = "GPRS_3G_QUAL_SERVICE_PROFILE";
                break;
            case MessageType.GPRS_IP_CONFIGURATION:
                result = "GPRS_IP_CONFIGURATION";
                break;
            case MessageType.GPRS_DEFINE_SEC_PDP_CONTEXT:
                result = "GPRS_DEFINE_SEC_PDP_CONTEXT";
                break;
            case MessageType.GPRS_TFT:
                result = "GPRS_TFT";
                break;
            case MessageType.GPRS_HSDPA_STATUS:
                result = "GPRS_HSDPA_STATUS";
                break;
            case MessageType.GPRS_CURRENT_SESSION_DATA_COUNT:
                result = "GPRS_CURRENT_SESSION_DATA_COUNT";
                break;
            case MessageType.GPRS_DATA_DORMANT:
                result = "GPRRS_DATA_DORMANT";
                break;
            case MessageType.GPRS_DUN_PIN_CTRL:
                result = "GPRS_DUN_PIN_CTRL";
                break;
            case MessageType.GPRS_CALL_STATUS:
                result = "GPRS_CALL_STATUS";
                break;
            case MessageType.SAT_PROFILE_DOWNLOAD:
                result = "SAT_PROFILE_DOWNLOAD";
                break;
            case MessageType.SAT_ENVELOPE_CMD:
                result = "SAT_ENVELOPE_CMD";
                break;
            case MessageType.SAT_PROACTIVE_CMD:
                result = "SAT_PROACTIVE_CMD";
                break;
            case MessageType.SAT_TERMINATE_USAT_SESSION:
                result = "SAT_TERMINATE_USAT_SESSION";
                break;
            case MessageType.SAT_EVENT_DOWNLOAD:
                result = "SAT_EVENT_DOWNLOAD";
                break;
            case MessageType.SAT_PROVIDE_LOCAL_INFO:
                result = "SAT_PROVIDE_LOCAL_INFO";
                break;
            case MessageType.SAT_POLLING:
                result = "SAT_POLLING";
                break;
            case MessageType.SAT_REFRESH:
                result = "SAT_REFRESH";
                break;
            case MessageType.SAT_SETUP_EVENT_LIST:
                result = "SAT_SETUP_EVENT_LIST";
                break;
            case MessageType.SAT_CALL_CONTROL_RESULT:
                result = "SAT_CALL_CONTROL_RESULT";
                break;
            case MessageType.SAT_IMAGE_CLUT:
                result = "SAT_IMAGE_CLUT";
                break;
            case MessageType.SAT_CALL_PROCESSING:
                result = "SAT_CALL_PROCESSING";
                break;
            case MessageType.IMEI_START:
                result = "IMEI_START";
                break;
            case MessageType.IMEI_CHECK_DEVICE_INFO:
                result = "IMEI_CHECK_DEVICE_INFO";
                break;
            case MessageType.CALL_OUTGOING:
                result = "CALL_OUTGOING";
                break;
            case MessageType.CALL_INCOMING:
                result = "CALL_INCOMING";
                break;
            case MessageType.CALL_RELEASE:
                result = "CALL_RELEASE";
                break;
            case MessageType.CALL_ANSWER:
                result = "CALL_ANSWER";
                break;
            case MessageType.CALL_STATUS:
                result = "CALL_STATUS";
                break;
            case MessageType.CALL_LIST:
                result = "CALL_LIST";
                break;
            case MessageType.CALL_BURST_DTMF:
                result = "CALL_BURST_DTMF";
                break;
            case MessageType.CALL_CONT_DTMF:
                result = "CALL_CONT_DTMF";
                break;
            case MessageType.CALL_WAITING:
                result = "CALL_WAITING";
                break;
            case MessageType.CALL_LINE_ID:
                result = "CALL_LINE_ID";
                break;
        }

        return result;
    }

    [CCode (cname = "int", cprefix = "IPC_CALL_TYPE_", has_type_id = false, cheader_filename = "radio.h")]
    public enum CallType
    {
        VOICE,
        DATA,
    }

    public string call_type_to_string( int type )
    {
        string result = "unknown";

        switch ( (CallType) type )
        {
            case CallType.VOICE:
                result = "VOICE";
                break;
            case CallType.DATA:
                result = "DATA";
                break;
        }

        return result;
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

    [CCode (cname = "struct ipc_request", cheader_filename = "radio.h", destroy_function = "", free_function = "")]
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

    [CCode (cname = "struct ipc_response", cheader_filename = "radio.h", destroy_function = "", free_function = "", copy_function = "")]
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
    public delegate void LogHandlerCb(string message);

    [Compact]
    [CCode (cname = "struct ipc_client", cprefix = "ipc_client_", cheader_filename = "radio.h")]
    public class Client
    {
        public Client(ClientType type);
        [CCode (delagate_target_pos = 0.9)]
        public int set_log_handler(LogHandlerCb log_cb);
        public int set_delegates(TransportCb write_cb, TransportCb read_cb);
        public int bootstrap_modem();
        public void open();
        public void close();
        public int recv(out Response response);
        public void send(int command, int type, uint8[] data, uint8 mseq);
        public void send_get(int command, uint8 aseq);
        public void send_exec(int command, uint8 aseq);
    }
}
