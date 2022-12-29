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


#include <pico/stdlib.h>
#include <hardware/adc.h>
#include <tusb.h>

#include "ili9225.h"


static void pwm123_init(void)
{
	/* Push = High-Z (external pull-up) = Disabled */
	gpio_init(PWM3_P_PIN);
	gpio_disable_pulls(PWM3_P_PIN);
	gpio_set_dir(PWM3_P_PIN, GPIO_IN);
	gpio_set_drive_strength(PWM3_P_PIN, GPIO_DRIVE_STRENGTH_2MA);
	gpio_put(PWM3_P_PIN, 0);

	/* Pull = Disabled */
	gpio_init(PWM3_N_PIN);
	gpio_disable_pulls(PWM3_N_PIN);
	gpio_set_dir(PWM3_N_PIN, GPIO_OUT);
	gpio_set_drive_strength(PWM3_N_PIN, GPIO_DRIVE_STRENGTH_2MA);
	gpio_put(PWM3_N_PIN, 0);

	/* Push = High-Z (external pull-up) = Disabled */
	gpio_init(PWM2_P_PIN);
	gpio_disable_pulls(PWM2_P_PIN);
	gpio_set_dir(PWM2_P_PIN, GPIO_IN);
	gpio_set_drive_strength(PWM2_P_PIN, GPIO_DRIVE_STRENGTH_2MA);
	gpio_put(PWM2_P_PIN, 0);

	/* Pull = Disabled */
	gpio_init(PWM2_N_PIN);
	gpio_disable_pulls(PWM2_N_PIN);
	gpio_set_dir(PWM2_N_PIN, GPIO_OUT);
	gpio_set_drive_strength(PWM2_N_PIN, GPIO_DRIVE_STRENGTH_2MA);
	gpio_put(PWM2_N_PIN, 0);

	/* Push = High-Z (external pull-up) = Disabled */
	gpio_init(PWM1_P_PIN);
	gpio_disable_pulls(PWM1_P_PIN);
	gpio_set_dir(PWM1_P_PIN, GPIO_IN);
	gpio_set_drive_strength(PWM1_P_PIN, GPIO_DRIVE_STRENGTH_2MA);
	gpio_put(PWM1_P_PIN, 0);

	/* Pull = Disabled */
	gpio_init(PWM1_N_PIN);
	gpio_disable_pulls(PWM1_N_PIN);
	gpio_set_dir(PWM1_N_PIN, GPIO_OUT);
	gpio_set_drive_strength(PWM1_N_PIN, GPIO_DRIVE_STRENGTH_2MA);
	gpio_put(PWM1_N_PIN, 0);
}


static void tsense_init(void)
{
	adc_init();
	adc_gpio_init(TSENSE_PIN);
}


static void tsense_select(void)
{
#if TSENSE_PIN == 26
	adc_select_input(0);
#elif TSENSE_PIN == 27
	adc_select_input(1);
#elif TSENSE_PIN == 28
	adc_select_input(2);
#elif TSENSE_PIN == 29
	adc_select_input(3);
#else
# error "Selected TSENSE_PIN is not an ADC input!"
#endif
}


static double voltage_to_temp(double v)
{
	return 278.642 - 244.739 * v + 108.529 * v * v - 18.5223 * v * v * v;
}


int main()
{
	/* Initialize stdio over USB. */
	stdio_init_all();

#if 0
	while (!stdio_usb_connected())
		sleep_ms(10);
#endif

	/* Turn off all 3 PWM outputs. */
	pwm123_init();

	/* Initialize the TFT screen. */
	tft_init();

	/* Initialize the temperature probe. */
	tsense_init();
	tsense_select();

	/* Incremental thermistor ADC measurements average. */
	double raw_temp_avg = 0;

	while (true) {
		unsigned raw_temp = 0;

		// 8 + 12 bits = 20 bits
		for (int i = 0; i < 256; i++)
			raw_temp += adc_read();

		// 20 bits to 16 bits
		raw_temp >>= 4;

		raw_temp_avg = (31.0 * raw_temp_avg + raw_temp) / 32.0;

		double v_temp = raw_temp_avg * 3.3 / (1 << 16);
		double temp = voltage_to_temp(v_temp);

		tft_fill(0);

		char buf[20];
		sprintf(buf, "%7.2f mV", v_temp * 1000.0);
		tft_draw_string(70, 90, 3, buf);

		sprintf(buf, "%7.2f \260C", temp);
		tft_draw_string(70, 70, 3, buf);

		sleep_ms(15);

		tft_sync();
	}
}
