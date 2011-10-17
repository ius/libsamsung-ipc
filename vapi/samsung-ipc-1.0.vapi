
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
        PWR_PHONE_STATE,
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
        DISP_ICON_INFO,
        DISP_HOMEZONE_INFO,
        DISP_RSSI_INFO,
        SEC_PIN_STATUS,
        SEC_PHONE_LOCK,
        SEC_CHANGE_LOCKING_PW,
        SEC_SIM_LANG,
        SEC_RSIM_ACCESS,
        SEC_GSIM_ACCESS,
        SEC_SIM_ICC_TYPE,
        SEC_LOCK_INFO,
        SEC_ISIM_AUTH,
        NET_PREF_PLMN,
        NET_PLMN_SEL,
        NET_CURRENT_PLMN,
        NET_PLMN_LIST,
        NET_REGIST,
        NET_SUBSCRIBER_NUM,
        NET_BAND_SEL,
        NET_SERVICE_DOMAIN_CONFIG,
        NET_POWERON_ATTACH,
        NET_MODE_SEL,
        NET_ACQ_ORDER,
        NET_IDENTITY,
        NET_CURRENT_RRC_STATUS,
        GEN_PHONE_RES,
        MISC_ME_VERSION,
        MISC_ME_IMSI,
        MISC_ME_SN,
        MISC_TIME_INFO,
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
            case MessageType.PWR_PHONE_STATE:
                result = "PWR_PHONE_STATE";
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
                result = "GPRS_PDP_CONTEXT";
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
            case MessageType.DISP_ICON_INFO:
                result = "DISP_ICON_INFO";
                break;
            case MessageType.DISP_HOMEZONE_INFO:
                result = "DISP_HOMEZONE_INFO";
                break;
            case MessageType.DISP_RSSI_INFO:
                result = "DISP_RSSI_INFO";
                break;
            case MessageType.SEC_PIN_STATUS:
                result = "SEC_PIN_STATUS";
                break;
            case MessageType.SEC_PHONE_LOCK:
                result = "SEC_PHONE_LOCK";
                break;
            case MessageType.SEC_CHANGE_LOCKING_PW:
                result = "SEC_CHANGE_LOCKING_PW";
                break;
            case MessageType.SEC_SIM_LANG:
                result = "SEC_SIM_LANG";
                break;
            case MessageType.SEC_RSIM_ACCESS:
                result = "SEC_RSIM_ACCESS";
                break;
            case MessageType.SEC_GSIM_ACCESS:
                result = "SEC_GSIM_ACCESS";
                break;
            case MessageType.SEC_SIM_ICC_TYPE:
                result = "SEC_SIM_ICC_TYPE";
                break;
            case MessageType.SEC_LOCK_INFO:
                result = "SEC_LOCK_INFO";
                break;
            case MessageType.SEC_ISIM_AUTH:
                result = "SEC_ISIM_AUTH";
                break;
            case MessageType.NET_PREF_PLMN:
                result = "NET_PREF_PLMN";
                break;
            case MessageType.NET_PLMN_SEL:
                result = "NET_PLMN_SEL";
                break;
            case MessageType.NET_CURRENT_PLMN:
                result = "NET_CURRENT_PLMN";
                break;
            case MessageType.NET_PLMN_LIST:
                result = "NET_PLMN_LIST";
                break;
            case MessageType.NET_REGIST:
                result = "NET_REGIST";
                break;
            case MessageType.NET_SUBSCRIBER_NUM:
                result = "NET_SUBSCRIBER_NUM";
                break;
            case MessageType.NET_BAND_SEL:
                result = "NET_BAND_SEL";
                break;
            case MessageType.NET_SERVICE_DOMAIN_CONFIG:
                result = "NET_SERVICE_DOMAIN_CONFIG";
                break;
            case MessageType.NET_POWERON_ATTACH:
                result = "NET_POWERON_ATTACH";
                break;
            case MessageType.NET_MODE_SEL:
                result = "NET_MODE_SEL";
                break;
            case MessageType.NET_ACQ_ORDER:
                result = "NET_ACQ_ORDER";
                break;
            case MessageType.NET_IDENTITY:
                result = "NET_IDENTITY";
                break;
            case MessageType.NET_CURRENT_RRC_STATUS:
                result = "NET_CURRENT_RRC_STATUS";
                break;
            case MessageType.GEN_PHONE_RES:
                result = "GEN_PHONE_RES";
                break;
            case MessageType.MISC_ME_VERSION:
                result = "MISC_ME_VERSION";
                break;
            case MessageType.MISC_ME_IMSI:
                result = "MISC_ME_IMSI";
                break;
            case MessageType.MISC_ME_SN:
                result = "MISC_ME_SN";
                break;
            case MessageType.MISC_TIME_INFO:
                result = "MISC_TIME_INFO";
                break;
        }

        return result;
    }

    /* ******************************************************************************** */

    namespace Security
    {
        [CCode (cname = "uint8", cprefix = "IPC_SEC_PIN_SIM_", has_type_id = false)]
        public enum SimStatus
        {
            INITIALIZING,
            SIM_LOCK_REQUIRED,
            INSIDE_PF_ERROR,
            LOCK_SC,
            LOCK_FD,
            LOCK_PN,
            LOCK_PU,
            LOCK_PP,
            LOCK_PC,
            CARD_NOT_PRESENT,
            CARD_ERROR,
            INIT_COMPLETE,
            PB_INIT_COMPLETE,
        }

        [CCode (cname = "uint8", cprefix = "IPC_SEC_PIN_SIM_LOCK_SC_", has_type_id = false)]
        public enum SimLockStatus
        {
            PIN1_REQ,
            PUK_REQ,
            CARD_BLOCKED,
        }

        [CCode (cname = "uint8", cprefix = "IPC_SEC_PIN_TYPE_", has_type_id = false)]
        public enum PinType
        {
            PIN1,
            PIN2,
        }

        [CCode (cname = "uint8", cprefix = "IPC_SEC_SIM_CARD_TYPE_", has_type_id = false)]
        public enum SimCardType
        {
            UNKNOWN,
            SIM,
            USIM,
        }

        [CCode (cname = "struct ipc_sec_pin_status_noti")]
        public struct SimStatusMessage
        {
            public SimStatus status;
            public uint8 key;
        }

        [CCode (cname = "struct ipc_sec_pin_status_set")]
        public struct PinStatusSetMessage
        {
            public PinType type;
            public uint8 length1;
            public uint8 length2;
            [CCode (array_length_cname = "length1")]
            public uint8[] pin1; // size = 8
            [CCode (array_length_cname = "length2")]
            public uint8[] pin2; // size = 8
        }

        [CCode (cname = "struct ipc_sec_phone_lock_request")]
        public struct PhoneLockRequestMessage
        {
            public SimStatus lock_type; // FIXME refactor log type from SimStatus in own enum
        }

        [CCode (cname = "struct ipc_sec_phone_lock_response")]
        public struct PhoneLockResponseMessage
        {
            public uint8 type;
            public SimLockStatus status;
        }

        [CCode (cname = "struct ipc_sec_rsim_access_request")]
        public struct RSimAccessRequestMessage
        {
            public uint8 command;
            public uint16 fileid;
            public uint8 p1;
            public uint8 p2;
            public uint8 p3;
        }

        [CCode (cname = "struct ipc_sec_rsim_access_response")]
        public struct RSimAccessResponse
        {
            public uint8 sw1;
            public uint8 sw2;
            public uint8 len;
        }

        [CCode (cname = "struct ipc_sec_lock_info_request")]
        public struct LockInfoRequestMessage
        {
            public uint8 unk0;
            public PinType pin_type;
        }

        [CCode (cname = "struct ipc_sec_lock_info_response")]
        public struct LockInfoResponseMessage
        {
            public uint8 num;
            public uint8 type;
            public uint8 key;
            public uint8 attempts;
        }
    }

    /* ******************************************************************************** */

    namespace Display
    {
        [CCode (cname = "ipc_disp_icon_info")]
        public struct IconInfoMessage
        {
            public uint8 unk;
            public uint8 rssi;
            public uint8 battery;
            public uint8 act;
            public uint8 reg;
        }

        [CCode (cname = "struct ipc_disp_rssi_info")]
        public struct RssiInfo
        {
            public uint8 rssi;
        }
    }

    /* ******************************************************************************** */

    namespace Network
    {
        [CCode (cname = "uint8", cprefix = "IPC_NET_SERVICE_TYPE_", has_type_id = false)]
        public enum ServiceType
        {
            GSM,
            GSM2,
            GPRS,
            EDGE,
            UMTS,
        }

        [CCode (cname = "uint8", cprefix = "IPC_NET_SERVICE_LEVEL_", has_type_id = false)]
        public enum ServiceLevel
        {
            NONE,
            HOME,
            SEARCHING,
            EMERGENCY,
            NONE2,
            ROAMING,
        }

        [CCode (cname = "uint8", cprefix = "IPC_NET_PLMN_STATUS_", has_type_id = false)]
        public enum PlmnStatus
        {
            AVAILABLE,
            CURRENT,
            FORBIDDEN,
        }

        [CCode (cname = "uint8", cprefix = "IPC_NET_PLMN_SEL_", has_type_id = false)]
        public enum PlmnSelection
        {
            MANUAL,
            AUTO,
        }

        [CCode (cname = "struct ipc_net_regist")]
        public struct RegistrationMessage
        {
            public uint8 act;
            public uint8 domain;
            public uint8 status;
            public uint8 edge;
            public uint16 lac;
            public uint32 cid;
            public uint8 rej_cause;
        }

        [CCode (cname = "struct ipc_net_regist_set")]
        public struct RegistrationSetMessage
        {
            public uint8 net;
            public uint8 domain;
        }

        [CCode (cname = "struct ipc_net_current_plmn")]
        public struct CurrentPlmnMessage
        {
            public uint8 unk;
            public uint8 slevel;
            public uint8[] plmn;
            public uint8 type;
            public uint16 lac;
        }

        [CCode (cname = "struct ipc_net_plmn_entry")]
        public struct PlmnEntryMessage
        {
            public PlmnStatus status;
            public uint8[] plmn;
            public uint8 type;
            public uint8[] unk;
        }

        [CCode (cname = "struct ipc_net_plmn_entries")]
        public struct PlmnEntriesMessage
        {
            public uint8 num;
            [CCode (cname = "data", array_length_cname = "num")]
            public PlmnEntriesMessage[] entries;
        }
    }

    /* ******************************************************************************** */

    namespace Call
    {
        [CCode (cname = "int", cprefix = "IPC_CALL_TYPE_", has_type_id = false, cheader_filename = "radio.h")]
        public enum Type
        {
            VOICE,
            DATA,
        }

        public string call_type_to_string( Type type )
        {
            string result = "unknown";

            switch ( type )
            {
                case Type.VOICE:
                    result = "VOICE";
                    break;
                case Type.DATA:
                    result = "DATA";
                    break;
            }

            return result;
        }

        [CCode (cname = "uint8", cprefix = "IPC_CALL_IDENTITY_", has_type_id = false, cheader_filename = "radio.h")]
        public enum Identity
        {
            DEFAULT,
            HIDE,
            SHOW,
        }

        [CCode (cname = "uint8", cprefix = "IPC_CALL_PREFIX_", has_type_id = false, cheader_filename = "radio.h")]
        public enum Prefix
        {
            NONE,
            INTL,
        }

        [CCode (cname = "uint8", cprefix = "IPC_CALL_STATE_", has_type_id = false, cheader_filename = "radio.h")]
        public enum State
        {
            DIALING,
            IGNORING_INCOMING_STATUS,
            CONNECTED,
            RELEASED,
            CONNECTING,
        }

        [CCode (cname = "int", cprefix = "IPC_CALL_TERM_", has_type_id = false, cheader_filename = "radio.h")]
        public enum Termination
        {
            MO,
            MT,
        }

        [CCode (cname = "struct ipc_call_outgoing", cheader_filename = "radio.h")]
        public struct OutgoingMessage
        {
            public uint8 type;
            public Identity identity;
            public uint8 length;
            public Prefix prefix;
            public uint8[] number;
        }

        [CCode (cname = "struct ipc_call_incoming", cheader_filename = "radio.h")]
        public struct IncomingMessage
        {
            public uint8 type;
            public uint8 id;
            public uint8 line;
        }

        [CCode (cname = "struct ipc_call_list_entry", cheader_filename = "radio.h")]
        public struct ListEntryMessage
        {
            public uint8 type;
            public uint8 idx;
            public Termination term;
            public State state;
            public uint8 mpty;
            public uint8 number_len;
            public uint8 unk4;
        }

        [CCode (cname = "struct ipc_call_status", cheader_filename = "radio.h")]
        public struct StatusMessage
        {
            public uint8 type;
            public uint8 id;
            public State state;
            public uint8 reason;
            public uint8 end_cause;
        }
    }

    /* ******************************************************************************** */

    namespace Generic
    {
        [CCode (cname = "struct ipc_gen_phone_res")]
        public struct PhoneResponseMessage
        {
            public uint8 group;
            public uint8 type;
            public uint16 code;
            public uint8 unk;
        }
    }

    /* ******************************************************************************** */

    namespace Misc
    {
        [CCode (cname = "struct ipc_misc_me_version")]
        public struct VersionMessage
        {
            public uint8[] sw_version;
            public uint8[] hw_version;
            public uint8[] cal_data;
            public uint8[] misc;
        }

        [CCode (cname = "struct ipc_misc_time_info")]
        public struct TimeInfoMessage
        {
            public uint8 tz_valid;
            public uint8 daylight_valid;
            public uint8 year;
            public uint8 mon;
            public uint8 day;
            public uint8 hour;
            public uint8 min;
            public uint8 sec;
            public uint8 tz;
            public uint8 dl;
            public uint8 dv;
            public uint8[] plmn;
        }
    }

    /* ******************************************************************************** */

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
