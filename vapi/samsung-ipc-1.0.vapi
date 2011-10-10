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
        public uint32 length;
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
