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

[CCode (cheader_filename = "radio.h")]
namespace SamsungIpc
{
    [CCode (cname = "int", cprefix = "IPC_CLIENT_TYPE_", has_type_id = false)]
    public enum ClientType
    {
        CRESPO_FMT,
        CRESPO_RFS,
        H1,
    }

    [CCode (cname = "int", cprefix = "IPC_TYPE_", has_type_id = false)]
    public enum RequestType
    {
        EXEC,
        GET,
        SET,
        CFRM,
        EVENT,
    }

    [CCode (cname = "unsigned char", cprefix = "IPC_TYPE_", has_type_id = false)]
    public enum ResponseType
    {
        INDICATION,
        RESPONSE,
        NOTIFICATION,
    }

    [CCode (cname = "int", cprefix = "IPC_GROUP_", has_type_id = false)]
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

    [CCode (cname = "int", cprefix = "IPC_PWR_", has_type_id = false)]
    public enum GenericMessageType
    {
        PHONE_RESPONSE,
    }

    [CCode (cname = "struct ipc_get_phone_res")]
    public struct GenericPhoneResponseMessage
    {
        public uint8 group;
        public uint8 type;
        public uint8 unk;
        public uint16 code;
    }

    [CCode (cname = "unsigned short", cprefix = "IPC_", has_type_id = false)]
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
        SMS_SEND_MSG,
        SMS_INCOMING_MSG,
        SMS_READ_MSG,
        SMS_SAVE_MSG,
        SMS_DEL_MSG,
        SMS_DELIVER_REPORT,
        SMS_DEVICE_READY,
        SMS_SEL_MEM,
        SMS_STORED_MSG_COUNT,
        SMS_SVC_CENTER_ADDR,
        SMS_SVC_OPTION,
        SMS_MEM_STATUS,
        SMS_CBS_MSG,
        SMS_CBS_CONFIG,
        SMS_STORED_MSG_STATUS,
        SMS_PARAM_COUNT,
        SMS_PARAM,
    }

    /* ******************************************************************************** */

    namespace Power
    {
        [CCode (cname = "gint8", cprefix = "IPC_PWR_PHONE_STATE_", has_type_id = false)]
        public enum PhoneState
        {
            LPM,
            NORMAL,
        }
    }

    /* ******************************************************************************** */

    namespace Security
    {
        [CCode (cname = "gint8", cprefix = "IPC_SEC_PIN_SIM_", has_type_id = false)]
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

        [CCode (cname = "gint8", cprefix = "IPC_SEC_PIN_SIM_LOCK_SC_", has_type_id = false)]
        public enum SimLockStatus
        {
            PIN1_REQ,
            PUK_REQ,
            CARD_BLOCKED,
        }

        [CCode (cname = "gint8", cprefix = "IPC_SEC_PIN_TYPE_", has_type_id = false)]
        public enum PinType
        {
            PIN1,
            PIN2,
        }

        [CCode (cname = "gint8", cprefix = "IPC_SEC_SIM_CARD_TYPE_", has_type_id = false)]
        public enum SimCardType
        {
            UNKNOWN,
            SIM,
            USIM,
        }

        [CCode (cname = "struct ipc_sec_pin_status_noti", destroy_function = "")]
        public struct SimStatusMessage
        {
            [CCode (cname = "type")]
            public SimStatus status;
            [CCode (cname = "key")]
            public SimLockStatus lock_status;
        }

        [CCode (cname = "struct ipc_sec_pin_status_set", destroy_function = "")]
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

        [CCode (cname = "struct ipc_sec_phone_lock_request", destroy_function = "")]
        public struct PhoneLockRequestMessage
        {
            public SimStatus lock_type; // FIXME refactor log type from SimStatus in own enum
        }

        [CCode (cname = "struct ipc_sec_phone_lock_response", destroy_function = "")]
        public struct PhoneLockResponseMessage
        {
            public uint8 type;
            public SimLockStatus status;
        }

        [CCode (cname = "struct ipc_sec_rsim_access_request", destroy_function = "")]
        public struct RSimAccessRequestMessage
        {
            public uint8 command;
            public uint16 fileid;
            public uint8 p1;
            public uint8 p2;
            public uint8 p3;
        }

        [CCode (cname = "struct ipc_sec_rsim_access_response", destroy_function = "")]
        public struct RSimAccessResponse
        {
            public uint8 sw1;
            public uint8 sw2;
            public uint8 len;
        }

        [CCode (cname = "struct ipc_sec_lock_info_request", destroy_function = "")]
        public struct LockInfoRequestMessage
        {
            public uint8 unk0;
            public PinType pin_type;
        }

        [CCode (cname = "struct ipc_sec_lock_info_response", destroy_function = "")]
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
        [CCode (cname = "ipc_disp_icon_info", destroy_function = "")]
        public struct IconInfoMessage
        {
            public uint8 unk;
            public uint8 rssi;
            public uint8 battery;
            public uint8 act;
            public uint8 reg;
        }

        [CCode (cname = "struct ipc_disp_rssi_info", destroy_function = "")]
        public struct RssiInfo
        {
            public uint8 rssi;
        }
    }

    /* ******************************************************************************** */

    namespace Network
    {
        [CCode (cname = "gint8", cprefix = "IPC_NET_ACCESS_TECHNOLOGY_", has_type_id = false)]
        public enum AccessTechnology
        {
            UNKNOWN,
            GSM,
            GSM2,
            GPRS,
            EDGE,
            UMTS,
        }

        [CCode (cname = "gint8", cprefix = "IPC_NET_REGISTRATION_STATE_", has_type_id = false)]
        public enum RegistrationState
        {
            NONE,
            HOME,
            SEARCHING,
            EMERGENCY,
            UNKNOWN,
            ROAMING,
        }

        [CCode (cname = "gint8", cprefix = "IPC_NET_PLMN_STATUS_", has_type_id = false)]
        public enum PlmnStatus
        {
            AVAILABLE,
            CURRENT,
            FORBIDDEN,
        }

        [CCode (cname = "gint8", cprefix = "IPC_NET_PLMN_SEL_", has_type_id = false)]
        public enum PlmnSelection
        {
            MANUAL,
            AUTO,
        }

        [CCode (cname = "struct ipc_net_regist", destroy_function = "")]
        public struct RegistrationMessage
        {
            public uint8 act;
            public uint8 reg_state;
            public uint8 unk;
            public uint8 edge;
            public uint16 lac;
            public uint32 cid;
            public uint8 rej_cause;
        }

        [CCode (cname = "struct ipc_net_regist_set", destroy_function = "")]
        public struct RegistrationSetMessage
        {
            public uint8 net;
            public uint8 domain;
        }

        [CCode (cname = "struct ipc_net_current_plmn", destroy_function = "")]
        public struct CurrentPlmnMessage
        {
            public uint8 unk;
            public uint8 slevel;
            public uint8[] plmn;
            public uint8 type;
            public uint16 lac;
        }

        [CCode (cname = "struct ipc_net_plmn_entry", destroy_function = "")]
        public struct PlmnEntryMessage
        {
            public PlmnStatus status;
            public uint8[] plmn;
            public uint8 type;
            public uint8[] unk;
        }

        [CCode (cname = "struct ipc_net_plmn_entries", destroy_function = "")]
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
        [CCode (cname = "int", cprefix = "IPC_CALL_TYPE_", has_type_id = false)]
        public enum Type
        {
            VOICE,
            DATA,
        }

        [CCode (cname = "gint8", cprefix = "IPC_CALL_IDENTITY_", has_type_id = false)]
        public enum Identity
        {
            DEFAULT,
            HIDE,
            SHOW,
        }

        [CCode (cname = "gint8", cprefix = "IPC_CALL_PREFIX_", has_type_id = false)]
        public enum Prefix
        {
            NONE,
            INTL,
        }

        [CCode (cname = "gint8", cprefix = "IPC_CALL_STATE_", has_type_id = false)]
        public enum State
        {
            DIALING,
            IGNORING_INCOMING_STATUS,
            CONNECTED,
            RELEASED,
            CONNECTING,
        }

        [CCode (cname = "int", cprefix = "IPC_CALL_TERM_", has_type_id = false)]
        public enum Termination
        {
            MO,
            MT,
        }

        [CCode (cname = "struct ipc_call_outgoing", destroy_function = "")]
        public struct OutgoingMessage
        {
            public uint8 type;
            public Identity identity;
            public uint8 length;
            public Prefix prefix;
            public uint8[] number;
        }

        [CCode (cname = "struct ipc_call_incoming", destroy_function = "")]
        public struct IncomingMessage
        {
            public uint8 type;
            public uint8 id;
            public uint8 line;
        }

        [CCode (cname = "struct ipc_call_list_entry", destroy_function = "")]
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

        [CCode (cname = "struct ipc_call_status", destroy_function = "")]
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
        [CCode (cname = "struct ipc_gen_phone_res", destroy_function = "")]
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
        [CCode (cname = "ipc_parse_misc_me_imsi")]
        public string parse_imsi(uint8[] data);

        [CCode (cname = "struct ipc_misc_me_version", destroy_function = "", free_function = "")]
        public struct VersionMessage
        {
            public uint8[] sw_version;
            public uint8[] hw_version;
            public uint8[] cal_date;
            public uint8[] misc;
        }

        [CCode (cname = "struct ipc_misc_time_info", destroy_function = "")]
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

    [CCode (cname = "struct ipc_header", destroy_function = "")]
    public struct Header
    {
        public uint16 length;
        public uint8 mseq;
        public uint8 aseq;
        public uint8 group;
        public uint8 index;
        public uint8 type;
    }

    [CCode (cname = "struct ipc_request", destroy_function = "", free_function = "")]
    public struct Request
    {
        public uint8 mseq;
        public uint8 aseq;
        public uint8 group;
        public uint8 index;
        public RequestType type;
        public uint32 length;
        public uint8[] data;
    }

    [CCode (cname = "struct ipc_response", destroy_function = "", free_function = "", copy_function = "")]
    public struct Response
    {
        public uint8 mseq;
        public uint8 aseq;
        public MessageType command;
        public ResponseType type;
        public uint32 data_length;
        [CCode (array_length_cname = "data_length")]
        public uint8[] data;
    }

    public delegate int TransportCb(uint8[] data);
    public delegate void LogHandlerCb(string message);

    [Compact]
    [CCode (cname = "struct ipc_client", cprefix = "ipc_client_")]
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
        public void send(MessageType command, RequestType type, uint8[] data, uint8 mseq);
        public void send_get(MessageType command, uint8 aseq);
        public void send_exec(MessageType command, uint8 aseq);
    }
}
