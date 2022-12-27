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
#include "hardware/adc.h"
#include "tusb.h"


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


static float voltage_to_temp(float V)
{
	return 240.201 - 195.011 * V + 88.4434 * V * V - 15.8647 * V * V * V;
}


int main()
{
	/* Initialize stdio over USB. */
	stdio_init_all();

	/* Turn off all 3 PWM outputs. */
	pwm123_init();

	/* Initialize the temperature probe. */
	tsense_init();
	tsense_select();

	while (true) {
		float Vconv = 3.3 / ((1 << 12) * 256);
		float Vtemp = 0;

		for (int i = 0; i < 256; i++)
			Vtemp += adc_read();

		Vtemp *= Vconv;

		printf("V: %.2f mV\n", Vtemp * 1000.0);
		printf("T: %.2f °C\n", voltage_to_temp(Vtemp));
		printf("\n");

		sleep_ms(1000);
	}
}
