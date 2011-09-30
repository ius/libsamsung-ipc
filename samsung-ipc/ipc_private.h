/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2011 Simon Busch <morphis@gravedo.de>
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

#ifndef __IPC_PRIVATE_H__
#define __IPC_PRIVATE_H__

struct ipc_ops {
	int (*bootstrap)(void);
	int (*open)(void);
	void (*fd_set)(int);
	int (*close)(void);
	void (*power_on)(void);
	void (*power_off)(void);
	int (*send)(struct ipc_request*);
	int (*recv)(struct ipc_response*);
	int (*fd_get)(void);
};

#endif
