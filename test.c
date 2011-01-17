/**
 * This file is part of libmsm-h1.
 *
 * Copyright (C) 2010-2011 Joerie de Gram <j.de.gram@gmail.com>
 *
 * libmsm-h1 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libmsm-h1 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libmsm-h1.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <radio.h>

static void on_receive(struct msm_request_info *info)
{
}

static struct msm_info msm = {
	.tty		= "/dev/dpram0",
	.on_receive	= on_receive,
};

int main(int argc, char *argv[])
{
	msm_register(&msm);
	msm_open();
	msm_power_on();

	msm_loop();

	msm_close();

	return 0;
}
