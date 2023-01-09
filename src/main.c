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

#include "ili9225.h"
#include "renc.h"
#include "task.h"


/* Because the screen is rotated. */
#define WIDTH TFT_HEIGHT
#define HEIGHT TFT_WIDTH


static task_t screen_task_id;
static task_t tsense_task_id;
static task_t input_task_id;
static task_t stats_task_id;


static void pwm123_init(void)
{
	/* Push = High-Z (external pull-up) = Disabled */
	gpio_init(FAN1_P_PIN);
	gpio_disable_pulls(FAN1_P_PIN);
	gpio_put(FAN1_P_PIN, 0);
	gpio_set_drive_strength(FAN1_P_PIN, GPIO_DRIVE_STRENGTH_2MA);
	gpio_set_dir(FAN1_P_PIN, GPIO_IN);

	/* Pull = Disabled */
	gpio_init(FAN1_N_PIN);
	gpio_disable_pulls(FAN1_N_PIN);
	gpio_set_dir(FAN1_N_PIN, GPIO_OUT);
	gpio_set_drive_strength(FAN1_N_PIN, GPIO_DRIVE_STRENGTH_2MA);
	gpio_put(FAN1_N_PIN, 0);

	/* Push = High-Z (external pull-up) = Disabled */
	gpio_init(FAN2_P_PIN);
	gpio_disable_pulls(FAN2_P_PIN);
	gpio_put(FAN2_P_PIN, 0);
	gpio_set_drive_strength(FAN2_P_PIN, GPIO_DRIVE_STRENGTH_2MA);
	gpio_set_dir(FAN2_P_PIN, GPIO_IN);

	/* Pull = Disabled */
	gpio_init(FAN2_N_PIN);
	gpio_disable_pulls(FAN2_N_PIN);
	gpio_set_dir(FAN2_N_PIN, GPIO_OUT);
	gpio_set_drive_strength(FAN2_N_PIN, GPIO_DRIVE_STRENGTH_2MA);
	gpio_put(FAN2_N_PIN, 0);

	/* Push = High-Z (external pull-up) = Disabled */
	gpio_init(PLATE_P_PIN);
	gpio_disable_pulls(PLATE_P_PIN);
	gpio_put(PLATE_P_PIN, 0);
	gpio_set_drive_strength(PLATE_P_PIN, GPIO_DRIVE_STRENGTH_2MA);
	gpio_set_dir(PLATE_P_PIN, GPIO_IN);

	/* Pull = Disabled */
	gpio_init(PLATE_N_PIN);
	gpio_disable_pulls(PLATE_N_PIN);
	gpio_set_dir(PLATE_N_PIN, GPIO_OUT);
	gpio_set_drive_strength(PLATE_N_PIN, GPIO_DRIVE_STRENGTH_2MA);
	gpio_put(PLATE_N_PIN, 0);
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


inline static int wrap(int x, int limit)
{
	return (limit + x) % limit;
}


/* History of temperatures. */
static double history[WIDTH] = {0.0};
static unsigned history_offset = 0;


#define SPARKLINE_HEIGHT 88


static void update_sparkline(double temp)
{
	static double temp_min_avg = 1000;
	static double temp_max_avg = 0;
	static double temp_avg = 21;

	temp_avg = 0.99 * temp_avg + 0.01 * temp;

	history_offset = wrap(history_offset + 1, WIDTH);
	history[history_offset] = temp;

	/* Draw slightly lighter sparkline background. */
	tft_draw_rect(0, HEIGHT - SPARKLINE_HEIGHT - 1, WIDTH - 1, HEIGHT - 1, 1);

	double temp_min = 1000, temp_max = 0;

	for (int i = 0; i < WIDTH; i++) {
		temp_min = fmin(temp_min, history[i]);
		temp_max = fmax(temp_max, history[i]);
	}

	temp_min_avg = 0.99 * temp_min_avg + 0.01 * temp_min;
	temp_max_avg = 0.99 * temp_max_avg + 0.01 * temp_max;

	temp_min = fmin(fmin(temp_min_avg, temp_min), temp_avg - 0.5);
	temp_max = fmax(fmax(temp_max_avg, temp_max), temp_avg + 0.5);

	for (int i = 0; i < WIDTH; i++) {
		int h = wrap(history_offset + 1 + i, WIDTH);
		double temp_adj = (history[h] - temp_min) / (temp_max - temp_min);
		int y = wrap((SPARKLINE_HEIGHT - 1) * temp_adj, SPARKLINE_HEIGHT);

		tft_draw_pixel(i, HEIGHT - SPARKLINE_HEIGHT - 1 + y, 7);
	}

	double avg = (temp_avg - temp_min) / (temp_max - temp_min);
	int y = HEIGHT - SPARKLINE_HEIGHT - 1 + wrap((SPARKLINE_HEIGHT - 1) * avg, SPARKLINE_HEIGHT);

	tft_draw_rect(0, y, WIDTH - 1, y, 5);

	if (y < HEIGHT - 20)
		y += 17;

	char buf[20];
	sprintf(buf, "%7.1f \260C", temp);
	tft_draw_string(WIDTH - 1 - strlen(buf) * 8, y - 16, 5, buf);
}


static void screen_task(void)
{
	uint64_t last_frame = 0;
	uint64_t diff_time = 0;
	unsigned frame_no = 0;
	unsigned fps = 60;

	const unsigned target_fps = 30;
	int sleep = 20000;

	while (true) {
		uint64_t now = time_us_64();
		diff_time += now - last_frame;
		last_frame = now;
		frame_no++;

		if (diff_time >= 500000) {
			fps = frame_no * 2;
			diff_time = 0;
			frame_no = 0;

			if (fps != target_fps) {
				int delta = fps - target_fps;
				sleep += 100 * delta;
			}
		}

		char buf[20];
		sprintf(buf, "%u fps", fps);
		tft_draw_string(0, 0, 3, buf);

		/* Commit the screen buffer. */
		tft_swap_buffers();

		/* Unblock the data gathering task. */
		task_set_ready(tsense_task_id);

		/* Output the buffer. */
		tft_sync();

		/* Insert delay to control FPS. */
		if (sleep > 0)
			task_sleep_us(sleep);

		/* Wait for more data. */
		task_yield_until_ready();
	}
}


inline static double voltage_to_temp(double v)
{
	double a = -37.722;
	double b = 245.275;
	double c = -567.286;
	double d = 530.194;
	return (v * v * v * a) + (v * v * b) + (v * c) + d;
}


static void tsense_task(void)
{
	/* Incremental thermistor ADC measurements average. */
	unsigned raw_temp_avg = (256 * 4096) >> 4;

	while (true) {
		unsigned raw_temp = 0;

		// 8 + 12 bits = 20 bits
		for (int i = 0; i < 256; i++)
			raw_temp += adc_read();

		// 20 bits to 16 bits
		raw_temp >>= 4;

		// 16 bits to 20 bits to 16 bits
		raw_temp_avg = (15 * raw_temp_avg + raw_temp) >> 4;

		// 16 bits to 32 bits to 16 bits
		unsigned mv_temp = raw_temp_avg * 33000 >> 16;

		double temp = voltage_to_temp(mv_temp / 10000.0);

		tft_fill(0);
		update_sparkline(temp);

		char buf[20];
		sprintf(buf, "%4u.%u mV", mv_temp / 10, mv_temp % 10);
		tft_draw_string(70, 16 * 4, 3, buf);

		sprintf(buf, "%6.1f \260C", temp);
		tft_draw_string(70, 16 * 3, 3, buf);

		/* Unblock the display output task. */
		task_set_ready(screen_task_id);

		/* Wait for the buffers to get flipped so that we can
		 * begin drawing next frame. */
		task_yield_until_ready();
	}
}

static void input_task(void)
{
	while (true) {
		struct renc_event event;

		queue_remove_blocking(&renc_queue, &event);
		printf("RE: num=%u sw=%u steps=%i\n",
		       event.num, event.sw, event.steps);
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

	/* Initialize the rotary encoder. */
	renc_init(16);
	renc_config(0, RENC_CW_PIN, RENC_CCW_PIN, RENC_SW_PIN, RENC_SENS);

	/* Initialize the temperature probe. */
	tsense_init();
	tsense_select();

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

	/* Run tasks on the second core. */
	multicore_reset_core1();
	multicore_launch_core1(task_run_loop);

	/* Run tasks on this core. */
	task_run_loop();
}
