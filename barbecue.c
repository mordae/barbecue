/*
 * Copyright (C) 2022 Jan Hamal Dvořák <mordae@anilinux.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


#include "pico/stdlib.h"

#define FAN_P_PIN 5
#define FAN_N_PIN 4


int main()
{
	/* Push = High-Z (external pull-up) = Disabled */
	gpio_init(FAN_P_PIN);
	gpio_disable_pulls(FAN_P_PIN);
	gpio_set_dir(FAN_P_PIN, GPIO_IN);
	gpio_set_drive_strength(FAN_P_PIN, GPIO_DRIVE_STRENGTH_2MA);
	gpio_put(FAN_P_PIN, 0);

	/* Pull = Disabled */
	gpio_init(FAN_N_PIN);
	gpio_disable_pulls(FAN_N_PIN);
	gpio_set_dir(FAN_N_PIN, GPIO_OUT);
	gpio_set_drive_strength(FAN_N_PIN, GPIO_DRIVE_STRENGTH_2MA);
	gpio_put(FAN_N_PIN, 0);

	while (true) {
		/* Push = High-Z (external pull-up) = Disabled */
		gpio_set_dir(FAN_P_PIN, GPIO_IN);

		sleep_ms(1200);

		/* Push = Enabled */
		gpio_set_dir(FAN_P_PIN, GPIO_OUT);

		sleep_ms(800);
	}
}