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
#include <pico/multicore.h>
#include <hardware/adc.h>
#include <hardware/timer.h>
#include <tusb.h>
#include <math.h>

//#include "ili9225.h"
#include "st7735.h"

#include "renc.h"
#include "task.h"


static task_t screen_task_id;
static task_t tsense_task_id;
static task_t input_task_id;
static task_t control_task_id;
static task_t stats_task_id;


static double target_temp = 0;
static double internal_temp = 25;


static void pwm123_init(void)
{
	gpio_init(FAN1_PIN);
	gpio_init(FAN2_PIN);
	gpio_init(HEAT_PIN);

	gpio_put(FAN1_PIN, 0);
	gpio_put(FAN2_PIN, 0);
	gpio_put(HEAT_PIN, 0);

	gpio_set_dir(FAN1_PIN, GPIO_OUT);
	gpio_set_dir(FAN2_PIN, GPIO_OUT);
	gpio_set_dir(HEAT_PIN, GPIO_OUT);

	gpio_disable_pulls(FAN1_PIN);
	gpio_disable_pulls(FAN2_PIN);
	gpio_disable_pulls(HEAT_PIN);
}


static void tsense_init(void)
{
	adc_init();
	adc_gpio_init(TSENSE_PIN);
}


#if (TSENSE_PIN < 26) || (TSENSE_PIN > 29)
# error "TSENSE_PIN must be a valid ADC pin"
#endif

static void select_tsense(void)
{
	adc_select_input(TSENSE_PIN - 26);
}


static void select_internal(void)
{
	adc_select_input(4);
}


inline static int wrap(int x, int limit)
{
	return (limit + x) % limit;
}


/* History of temperatures. */
static double history[TFT_WIDTH] = {0.0};
static unsigned history_offset = 0;


static void update_sparkline(double temp)
{
	static double temp_min_avg = 1000;
	static double temp_max_avg = 0;
	static double temp_avg = 21;

	temp_avg = 0.99 * temp_avg + 0.01 * temp;

	history_offset = wrap(history_offset + 1, TFT_WIDTH);
	history[history_offset] = temp;

	double temp_min = 1000, temp_max = 0;

	for (int i = 0; i < TFT_WIDTH; i++) {
		temp_min = fmin(temp_min, history[i]);
		temp_max = fmax(temp_max, history[i]);
	}

	temp_min_avg = 0.99 * temp_min_avg + 0.01 * temp_min;
	temp_max_avg = 0.99 * temp_max_avg + 0.01 * temp_max;

	temp_min = fmin(fmin(temp_min_avg, temp_min), temp_avg - 0.5);
	temp_max = fmax(fmax(temp_max_avg, temp_max), temp_avg + 0.5);

	for (int i = 0; i < TFT_WIDTH; i++) {
		int h = wrap(history_offset + 1 + i, TFT_WIDTH);
		double temp_adj = (history[h] - temp_min) / (temp_max - temp_min);
		int y = (TFT_HEIGHT - 1) * temp_adj;
		tft_draw_pixel(i, y, 7);
	}

	double avg = (temp_avg - temp_min) / (temp_max - temp_min);
	int y = (TFT_HEIGHT - 1) * avg;
	tft_draw_rect(0, y, TFT_WIDTH - 1, y, 5);

	if (y < TFT_HEIGHT - 20)
		y += 17;

	char buf[20];
	sprintf(buf, "%7.1f\260C", temp);
	tft_draw_string(TFT_WIDTH - 1 - strlen(buf) * 8, y - 16, 5, buf);

	sprintf(buf, "%2.1f\260C", internal_temp);
	tft_draw_string(0, 0, 2, buf);

	sprintf(buf, "%3.0f\260C", target_temp);
	tft_draw_string(TFT_WIDTH - 1 - 8 * strlen(buf), 0, 4, buf);
}


static void screen_task(void)
{
	while (true) {
		/* Commit the screen buffer. */
		tft_swap_buffers();

		/* Unblock the data gathering task. */
		task_set_ready(tsense_task_id);

		/* Output the buffer. */
		tft_sync();

		/* Limit ourselves to about 60 FPS. */
		task_sleep_us(9780);

		/* Wait for more data. */
		task_yield_until_ready();
	}
}


inline static double tsense_to_temp(double v)
{
	double a = -20.960;
	double b = 115.584;
	double c = -234.160;
	double d = 244.833;
	return (v * v * v * a) + (v * v * b) + (v * c) + d;
}


inline static double internal_to_temp(double v)
{
	return 27.0 - (v - 0.598) / 0.001721;
}


static void tsense_task(void)
{
	/* Incremental thermistor ADC measurements average. */
	unsigned raw_temp_avg = (256 * 4096) >> 4;

	while (true) {
		unsigned raw_temp = 0;

		select_internal();

		/* Get rid of residual charge. */
		for (int i = 0; i < 32; i++)
			(void)adc_read();

		for (int i = 0; i < 256; i++)
			raw_temp += adc_read();

		double itemp = internal_to_temp(raw_temp * 3.3 / 256.0 / 4096.0);
		internal_temp = internal_temp * 0.975 + itemp * 0.025;

		raw_temp = 0;
		select_tsense();

		/* Get rid of residual charge. */
		for (int i = 0; i < 32; i++)
			(void)adc_read();

		// 8 + 12 bits = 20 bits
		for (int i = 0; i < 256; i++)
			raw_temp += adc_read();

		// 20 bits to 16 bits
		raw_temp >>= 4;

		// 16 bits to 20 bits to 16 bits
		raw_temp_avg = (15 * raw_temp_avg + raw_temp) >> 4;

		// 16 bits to 32 bits to 16 bits
		unsigned mv_temp = raw_temp_avg * 33000 >> 16;
		double temp = tsense_to_temp(mv_temp / 10000.0);

		tft_fill(0);
		update_sparkline(temp);

		/* Unblock the display output task. */
		task_set_ready(screen_task_id);

		/* Wait for the buffers to get flipped so that we can
		 * begin drawing next frame. */
		task_yield_until_ready();
	}
}

static void input_task(void)
{
	/* Initialize the rotary encoder. */
	renc_init();
	renc_config(0, RENC_CW_PIN, RENC_CCW_PIN, RENC_SW_PIN, RENC_SENS);

	while (true) {
		struct renc_event event;
		renc_read_blocking(&event);

		if (event.steps) {
			target_temp += event.steps;

			if (target_temp > 230)
				target_temp = 230;
			else if (target_temp < 0)
				target_temp = 0;

			if (target_temp < internal_temp)
				target_temp = ceil(internal_temp);
		}
	}
}


static void control_task(void)
{
	while (true) {
		double temp = history[history_offset];

		if (target_temp < internal_temp)
			target_temp = ceil(internal_temp);

		if (temp < target_temp) {
			gpio_put(HEAT_PIN, 1);
		} else {
			gpio_put(HEAT_PIN, 0);
		}

		if (temp > target_temp + 5) {
			gpio_put(FAN1_PIN, 1);
			gpio_put(FAN2_PIN, 1);
		} else {
			gpio_put(FAN1_PIN, 0);
			gpio_put(FAN2_PIN, 0);
		}

		/* Run at approximately 200 Hz.
		 * AC mains relay can't switch faster than 60 Hz anyway. */
		task_sleep_ms(5);
	}
}


static void stats_task(void)
{
	while (true) {
		task_sleep_ms(10 * 1000);
		for (int i = 0; i < NUM_CORES; i++)
			task_stats_report_reset(i);

		printf("\n");
	}
}


int main()
{
	/* Initialize stdio over USB. */
	stdio_init_all();

	/* Initialize task scheduler. */
	task_init();

	/* Wait up to 1s in case the console is attached. */
	for (int i = 0; i < 100; i++) {
		if (stdio_usb_connected())
			break;

		sleep_ms(10);
	}

	printf("Welcome! Have a safe and productive day!\n");

	/* Turn off all 3 PWM outputs. */
	pwm123_init();

	/* Initialize the TFT screen. */
	tft_init();

	/* Initialize the temperature probe. */
	tsense_init();
	select_tsense();

	/* Draws user interface on the screen.
	 * Starts not-ready, woken up by tsense_task.
	 */
	screen_task_id = task_create_on_core(1, screen_task, 1024);
	task_set_name(screen_task_id, "screen");

	/* Periodically measures temperature. */
	tsense_task_id = task_create(tsense_task, 1536);
	task_set_name(tsense_task_id, "tsense");
	task_set_ready(tsense_task_id);

	/* Interprets input events. */
	input_task_id = task_create(input_task, 1536);
	task_set_name(input_task_id, "input");
	task_set_ready(input_task_id);
	task_set_priority(input_task_id, 3);

	/* Prints task statistics. */
	stats_task_id = task_create(stats_task, 1536);
	task_set_name(stats_task_id, "stats");
	task_set_ready(stats_task_id);
	task_set_priority(stats_task_id, 1);

	/* Controls heating element and fans. */
	control_task_id = task_create(control_task, 1024);
	task_set_name(control_task_id, "control");
	task_set_ready(control_task_id);
	task_set_priority(control_task_id, 2);

	/* Run tasks on the second core. */
	multicore_reset_core1();
	multicore_launch_core1(task_run_loop);

	/* Run tasks on this core. */
	task_run_loop();
}
