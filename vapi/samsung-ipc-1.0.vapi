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
        CRESPO,
        H1,
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

    [CCode (cname = "struct ipc_request", cheader_filename = "radio.h")]
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

    [CCode (cname = "struct ipc_response", cheader_filename = "radio.h")]
    public struct Response
    {
        public uint8 mseq;
        public uint8 aseq;
        public uint16 command;
        public uint8 type;
        public uint32 length;
        public uint8[] data;
    }

    [CCode (cname = "ipc_init", cheader_filename = "radio.h")]
    public int init(ClientType type);
    [CCode (cname = "ipc_bootstrap", cheader_filename = "radio.h")]
    public int bootstrap();
    [CCode (cname = "ipc_open", cheader_filename = "radio.h")]
    public void open();
    [CCode (cname = "ipc_close", cheader_filename = "radio.h")]
    public void close();
    [CCode (cname = "ipc_fd_set", cheader_filename = "radio.h")]
    public void fd_set(int fd);
    [CCode (cname = "ipc_fd_get", cheader_filename = "radio.h")]
    public int fd_get();
    [CCode (cname = "ipc_power_on", cheader_filename = "radio.h")]
    public void power_on();
    [CCode (cname = "ipc_power_off", cheader_filename = "radio.h")]
    public void power_off();
    [CCode (cname = "ipc_send", cheader_filename = "radio.h")]
    public void send(Request request);
    [CCode (cname = "ipc_recv", cheader_filename = "radio.h")]
    public int recv(Response response);
    [CCode (cname = "ipc_msg_send", cheader_filename = "radio.h")]
    public void message_send(int command, int type, uint8 data, int length, uint8 mseq);
    [CCode (cname = "ipc_msg_send_get", cheader_filename = "radio.h")]
    public void message_send_get(int command, uint8 aseq);
    [CCode (cname = "ipc_msg_send_exec", cheader_filename = "radio.h")]
    public void message_send_exec(int command, uint8 aseq);
}
