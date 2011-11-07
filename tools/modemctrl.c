/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2010-2011 Joerie de Gram <j.de.gram@gmail.com>
 *               2011 Simon Busch <morphis@gravedo.de>
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
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <getopt.h>

#include <radio.h>

#define MODEM_STATE_LPM     0
#define MODEM_STATE_NORMAL  2
#define MODEM_STATE_SIM_OK  4

#define DEF_CALL_NUMBER "950"
#define DEF_SIM_PIN     "1234"

int client_fd = -1;
int state = MODEM_STATE_LPM;
int seq = 0;
int in_call = 0;
int out_call = 0;
int call_done = 0;

char sim_pin[8];

int seq_get(void)
{
    if(seq == 0xff)
        seq = 0x00;

    seq++;

    return seq;
}

void modem_snd_no_mic_mute(struct ipc_client *client)
{
    uint8_t data = 0;
    ipc_client_send(client, IPC_SND_MIC_MUTE_CTRL, IPC_TYPE_SET, (void *) &data, 1, seq_get());
}

void modem_snd_clock_ctrl(struct ipc_client *client)
{
    uint8_t data = 0x01;
    ipc_client_send(client, IPC_SND_CLOCK_CTRL, IPC_TYPE_EXEC, (void *) &data, 1, seq_get());
}

void modem_snd_spkr_volume_ctrl(struct ipc_client *client)
{
    uint16_t data = 0x0411;
    ipc_client_send(client, IPC_SND_SPKR_VOLUME_CTRL, IPC_TYPE_SET, (void *) &data, 2, seq_get());
}

void modem_snd_audio_path_ctrl(struct ipc_client *client)
{
    uint8_t data = 0x01;
    ipc_client_send(client, IPC_SND_AUDIO_PATH_CTRL, IPC_TYPE_SET, (void *) &data, 1, seq_get());
}


void modem_exec_call_out(struct ipc_client *client, char *num)
{
    struct ipc_call_outgoing call_out;

    modem_snd_no_mic_mute(client);

    memset(&call_out, 0, sizeof(struct ipc_call_outgoing));

    call_out.type = IPC_CALL_TYPE_VOICE;
    call_out.identity = IPC_CALL_IDENTITY_DEFAULT;
    call_out.length=strlen(num);
    /* 0x21 = +33 */
    call_out.prefix=IPC_CALL_PREFIX_NONE; //0x21;//IPC_CALL_PREFIX_NONE;
    memcpy(call_out.number, num, call_out.length);

    ipc_client_send(client, IPC_CALL_OUTGOING, IPC_TYPE_EXEC, (void *) &call_out, sizeof(struct ipc_call_outgoing), seq_get());

    out_call = 1;

    modem_snd_no_mic_mute(client);
    modem_snd_spkr_volume_ctrl(client);
    modem_snd_audio_path_ctrl(client);
}

void modem_exec_call_answer(struct ipc_client *client)
{
    modem_snd_clock_ctrl(client);

    ipc_client_send(client, IPC_CALL_ANSWER, IPC_TYPE_EXEC, NULL, 0, seq_get());

    modem_snd_no_mic_mute(client);
}

void modem_get_call_list(struct ipc_client *client)
{
    ipc_client_send(client, IPC_CALL_LIST, IPC_TYPE_GET, NULL, 0, seq_get());

    modem_snd_no_mic_mute(client);
}

void modem_exec_power_normal(struct ipc_client *client)
{
    uint16_t data = 0x0202;
    ipc_client_send(client, IPC_PWR_PHONE_STATE, IPC_TYPE_EXEC, (void *) &data, sizeof(data), seq_get());
}

void modem_set_sms_device_ready(struct ipc_client *client)
{
    ipc_client_send(client, IPC_SMS_DEVICE_READY, IPC_TYPE_SET, NULL, 0, seq_get());
}

void modem_set_sec_pin_status(struct ipc_client *client, char *pin1, char *pin2)
{
    struct ipc_sec_pin_status_set pin_status;
    struct ipc_sec_lock_info_request lock_info_req;

    printf("[I] Sending PIN1 unlock request\n");

    ipc_sec_pin_status_set_setup(&pin_status, IPC_SEC_PIN_TYPE_PIN1, pin1, pin2);
    ipc_client_send(client, IPC_SEC_PIN_STATUS, IPC_TYPE_SET, (void *) &pin_status, sizeof(pin_status), seq_get());
}

void modem_response_sec(struct ipc_client *client, struct ipc_message_info *resp)
{
    struct ipc_sec_pin_status_noti *pin_status;
    unsigned char type;
    int status;
    char *data;

    switch(IPC_COMMAND(resp))
    {
        case IPC_SEC_PIN_STATUS :
            pin_status = (struct ipc_sec_pin_status_noti *)resp->data;

            switch(pin_status->type)
            {
                case IPC_SEC_PIN_SIM_INITIALIZING:
                    printf("[I] SIM is initializing\n");
                break;
                case IPC_SEC_PIN_SIM_CARD_NOT_PRESENT:
                    printf("[I] SIM card is definitely absent\n");
                break;
                case IPC_SEC_PIN_SIM_LOCK_SC:
                    switch(pin_status->key)
                    {
                        case IPC_SEC_PIN_SIM_LOCK_SC_PIN1_REQ:
                            printf("[I] We need the PIN1 to unlock the card!\n");
                            if(strlen(sim_pin) > 0) {
                                modem_set_sec_pin_status(client, sim_pin, NULL);
                            } else {
                                printf("[E] No SIM Pin, use --pin\n");
                            }
                        break;
                        case IPC_SEC_PIN_SIM_LOCK_SC_PUK_REQ:
                            printf("[I] Please provide the SIM card PUK!\n");
                        break;
                        case IPC_SEC_PIN_SIM_LOCK_SC_CARD_BLOCKED:
                            printf("[I] Ouch, the SIM Card is blocked.\n");
                        break;
                    }
                break;
                case IPC_SEC_PIN_SIM_INIT_COMPLETE:
                    printf("[3] SIM init complete\n");
                    if(state == MODEM_STATE_NORMAL)
                        state = MODEM_STATE_SIM_OK;
                        
                break;
                case IPC_SEC_PIN_SIM_PB_INIT_COMPLETE:
                    printf("[I] SIM Phone Book init complete\n");
                break;
            }
        break;
        case IPC_SEC_SIM_ICC_TYPE:
            type = *((char *) resp->data);
            switch(type)
            {
                case IPC_SEC_SIM_CARD_TYPE_UNKNOWN:
                    printf("[I] No SIM card type: unknown (absent?)\n");
                break;
                case IPC_SEC_SIM_CARD_TYPE_SIM:
                case IPC_SEC_SIM_CARD_TYPE_USIM:
                    printf("[I] SIM card found\n");
                break;
            }
        break;
    }
}

void modem_response_sms(struct ipc_client *client, struct ipc_message_info *resp)
{
    switch(IPC_COMMAND(resp))
    {
        case IPC_SMS_DEVICE_READY:
            if(state ==  MODEM_STATE_LPM)
            {
                printf("[4] Modem is ready, requesting normal power mode\n");
                modem_exec_power_normal(client);
            }
            else if(state == MODEM_STATE_SIM_OK)
            {
                printf("[5] Modem is fully ready\n");
                modem_set_sms_device_ready(client);
            }
        break;
    }
}

void modem_response_call(struct ipc_client *client, struct ipc_message_info *resp)
{
    struct ipc_call_status *stat;

    switch(IPC_COMMAND(resp))
    {
        case IPC_CALL_LIST:
/*
            if(in_call)
                modem_exec_call_answer(client);
            if(out_call)
                modem_snd_no_mic_mute(client);
*/
        break;
        case IPC_CALL_INCOMING:
            printf("[I] Got an incoming call!\n");
            in_call = 1;
            modem_get_call_list(client);
        break;
        case IPC_CALL_STATUS:
            stat = (struct ipc_call_status *)resp->data;

            if(stat->state == IPC_CALL_STATE_DIALING)
            {
                printf("[I] Sending clock ctrl and restore alsa\n");
                modem_snd_clock_ctrl(client);
//        system("alsa_ctl -f /data/alsa_state_modem restore");

                printf("[I] CALL STATE DIALING!!!\n");

                modem_snd_spkr_volume_ctrl(client);
                modem_snd_audio_path_ctrl(client);

                modem_get_call_list(client);
            }
            if(stat->state == IPC_CALL_STATE_CONNECTED)
            {
                printf("[I] CALL STATE CONNECTED!!!\n");
                modem_snd_no_mic_mute(client);
            }
            if(stat->state == IPC_CALL_STATE_RELEASED)
            {
                printf("[I] CALL STATE RELEASED!!!\n");
                modem_snd_no_mic_mute(client);
            }
        break;
    }    
}

void modem_response_pwr(struct ipc_client *client, struct ipc_message_info *resp)
{
    int state_n;

    switch(IPC_COMMAND(resp))
    {
        case IPC_PWR_PHONE_PWR_UP:
            printf("[2] Phone is powered up (LPM)!\n");
            state = MODEM_STATE_LPM;
        break;

        case IPC_PWR_PHONE_STATE:
            state_n = *((int *)resp->data);
#if 0
            switch(state_n)
            {
                /* FIXME: Broken */
                case IPC_PWR_PHONE_STATE_NORMAL:
                    printf("Power state is now: NORMAL\n");
                break;
                case IPC_PWR_PHONE_STATE_LPM:
                    printf("Power state is now: LPM (Low Power Mode)?\n");
                break;
            }
#endif
            state = state_n;
        break;

    }
}

void modem_response_net(struct ipc_client *client, struct ipc_message_info *resp)
{
    struct ipc_net_regist *regi;
    struct ipc_net_plmn_entry *plmn;
    char mnc[6];

    switch(IPC_COMMAND(resp))
    {
        case IPC_NET_REGIST:
            regi = (struct ipc_net_regist *)resp->data;
            if(regi->reg_state == IPC_NET_REGISTRATION_STATE_HOME)
            {
                printf("[I] Registered with network successfully!\n");

            }
        break;
        case IPC_NET_CURRENT_PLMN:

            memcpy(mnc, (char *)(resp->data + 3), 5);
            mnc[5]=0;
            printf("[6] Registered with network! Got PLMN (Mobile Network Code): '%s'\n", mnc);
/*
            if(call_done == 0)
            {
                printf("Requesting outgoing call to %s!\n", DEF_CALL_NUMBER);
                modem_exec_call_out(client, DEF_CALL_NUMBER);
            }
            call_done = 1;
*/
        break;
    }
}

void modem_response_handle(struct ipc_client *client, struct ipc_message_info *resp)
{
    switch(resp->group)
    {
        case IPC_GROUP_NET:
            modem_response_net(client, resp);
        break;
        case IPC_GROUP_PWR:
            modem_response_pwr(client, resp);
        break;
        case IPC_GROUP_SEC:
            modem_response_sec(client, resp);
        break;
        case IPC_GROUP_SMS:
            modem_response_sms(client, resp);
        break;
        case IPC_GROUP_CALL:
            modem_response_call(client, resp);
        break;
        case IPC_GROUP_DISP:
            if(in_call)
                modem_snd_no_mic_mute(client);
        break;
    }
}

int modem_read_loop(struct ipc_client *client)
{
    struct ipc_message_info resp;
    int fd = client_fd;
    int rc;
    fd_set fds;

    if(fd < 0) {
        return -1;
    }

    memset(&resp, 0, sizeof(resp));

    FD_ZERO(&fds);
    FD_SET(fd, &fds);

    while(1) {
        usleep(3000);

        select(fd + 1, &fds, NULL, NULL, NULL);

        if(FD_ISSET(fd, &fds))
        {
            rc = ipc_client_recv(client, &resp);

            if(rc > 0) {
                printf("[E] Can't RECV from modem: please run this again\n");
                break;
            }

            modem_response_handle(client, &resp);

            if(resp.data != NULL)
                free(resp.data);
        }
    }

    return 0;
}

void modem_log_handler(char *message, void *user_data)
{
    int i, l;
    l = strlen(message);

    if(l > 1) {
        for(i=l ; i > 0 ; i--)
        {
            if(message[i] == '\n') {
                message[i] = 0;
            } else if(message[i] != 0) {
                break;
            }
        }

        printf("[D] %s\n", message);
    }
}

void modem_log_handler_quiet(const char *message, void *user_data)
{
    return;
}

int modem_start(struct ipc_client *client)
{
    int rc = -1;

//    ipc_client_set_handlers(client, &ipc_default_handlers);
    ipc_client_set_all_handlers_data(client, &client_fd);

    ipc_client_bootstrap_modem(client);

    usleep(300);

    rc = ipc_client_open(client);
    if(rc < 0)
        return -1;

    rc = ipc_client_power_on(client);
    if(rc < 0)
        return -1;

    return 0;
}

int modem_stop(struct ipc_client *client)
{
    ipc_client_power_off(client);
    ipc_client_close(client);

    return 0;
}

void print_help()
{
    printf("usage: modemctrl <command>\n");
    printf("commands:\n");
    printf("\tstart                 bootstrap modem and start read loop\n");
    printf("\tpower-on              power on the modem\n");
    printf("\tpower-off             power off the modem\n");
    printf("arguments:\n");
    printf("\t--debug               enable debug messages\n");
    printf("\t--pin=[PIN]           provide SIM card PIN\n");
}

int main(int argc, char *argv[])
{
    struct ipc_client *client_fmt;
    int c = 0;
	int opt_i = 0;
    int rc = -1;

    struct option opt_l[] = {
        {"debug",   no_argument,        0,  0 },
        {"pin",     required_argument,  0,  0 },
        {0,         0,                  0,  0 }
    };

    if (argc < 2) {
        print_help();
        exit(1);
    }

    client_fmt = ipc_client_new(IPC_CLIENT_TYPE_FMT);
    ipc_client_set_log_handler(client_fmt, modem_log_handler_quiet, NULL);

    while(c >= 0) {
        c = getopt_long(argc, argv, "", opt_l, &opt_i);
        if(c < 0)
            break;

        switch(c) {
            case 0:
                if(strcmp(opt_l[opt_i].name, "debug") == 0) {
                    ipc_client_set_log_handler(client_fmt, modem_log_handler, NULL);
                    printf("[I] Debug enabled\n");
                } else if(strcmp(opt_l[opt_i].name, "pin") == 0) {
                    if(optarg) {
                        if(strlen(optarg) < 8) {
                            printf("[I] Got SIM PIN!\n");
                            memcpy(sim_pin, optarg, 8);
                        } else {
                            printf("[E] SIM PIN is too long!\n");
                            return 1;
                        }
                    }
                }
            break;
        }
    }

        while(opt_i < argc) {
            if(strncmp(argv[optind], "power-on", 8) == 0) {
                ipc_client_power_on(client_fmt);
                goto modem_quit;
            } else if(strncmp(argv[optind], "power-off", 9) == 0) {
                ipc_client_power_off(client_fmt);
                goto modem_quit;
            } else if(strncmp(argv[optind], "start", 5) == 0) {
                printf("[0] Starting modem on FMT client\n");
                rc = modem_start(client_fmt);
                if(rc > 0) {
                    printf("[E] Something went wrong\n");
                    modem_stop(client_fmt);
                    return 1;
                }

                printf("[1] Starting modem_read_loop on FMT client\n");
                modem_read_loop(client_fmt);

                modem_stop(client_fmt);
            } else {
                printf("[E] Unknown argument: '%s'\n", argv[optind]);
                print_help();
                return 1;
            }

            optind++;
        }

modem_quit:
    ipc_client_free(client_fmt);

    return 0;
}

// vim:ts=4:sw=4:expandtab
