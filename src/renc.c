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

#include "renc.h"

#include <stdint.h>
#include <stdio.h>


#define DEBOUNCE_US 1000


enum {
	DIR_CW	= 0x08,
	DIR_CCW	= 0x10,
};

enum {
	R_START = 0,
	R_ERROR,
	R_CCW_1,
	R_CCW_2,
	R_CCW_3,
	R_CW_1,
	R_CW_2,
	R_CW_3,
};

static const uint8_t state_table[8][4] = {
	{R_START,         R_CCW_1, R_CW_1,  R_ERROR}, // 0 R_START
	{R_START,         R_ERROR, R_ERROR, R_ERROR}, // 1 R_ERROR

	{R_START,         R_CCW_1, R_CW_1,  R_CCW_2}, // 2 R_CCW_1
	{R_START,         R_CCW_1, R_CCW_3, R_CCW_2}, // 3 R_CCW_2
	{R_START|DIR_CCW, R_CCW_1, R_CCW_3, R_CCW_2}, // 4 R_CCW_3

	{R_START,         R_CCW_1, R_CW_1,  R_CW_2},  // 5 R_CW_1
	{R_START,         R_CW_3,  R_CW_1,  R_CW_2},  // 6 R_CW_2
	{R_START|DIR_CW,  R_CW_3,  R_CW_1,  R_CW_2},  // 7 R_CW_3
};

struct state {
	uint8_t cw_pin, ccw_pin, sw_pin, sens;
	uint8_t state : 5;
	bool sw : 1;
	bool cw : 1;
	bool ccw : 1;
	uint32_t sw_mtime;
	uint32_t re_mtime;
};


/* Encoder state machines. */
static struct state state[NUM_RENC];

/* Output queue. */
queue_t renc_queue;

/* Alarm for switch debouncing. */
static alarm_id_t alarm_id;


static void intr_handler(unsigned gpio, uint32_t events);


inline static int clamp(int x, int min, int max)
{
	if (x < min)
		return min;

	if (x > max)
		return max;

	return x;
}


inline static unsigned bit(unsigned n)
{
	return 1 << n;
}


static void update_state(struct state *st)
{
	uint8_t pin_state = (st->cw << 1) | st->ccw;

	//printf("re: ccw=%i cw=%i inp=%i st %i->%i\n", st->ccw, st->cw, pin_state, st->state & 0x7, state_table[st->state & 0x7][pin_state]);

	st->state = state_table[st->state & 0x7][pin_state];

	if (st->state & (DIR_CW | DIR_CCW)) {
		uint32_t now = time_us_32() >> 10;

		if (now <= st->re_mtime) {
			st->re_mtime = now - 1;
		} else if (now - st->re_mtime > st->sens) {
			st->re_mtime = now - st->sens;
		}

		int speed = st->sens / (now - st->re_mtime);
		st->re_mtime = now;

		speed = speed * speed;

		struct renc_event event = {
			.num = st - &state[0],
		};

		if (st->state & DIR_CW) {
			st->state &= 0xf;
			event.steps = speed;
		} else if (st->state & DIR_CCW) {
			st->state &= 0xf;
			event.steps = -speed;
		}

		(void)queue_try_add(&renc_queue, &event);
	}
}


inline static bool update_cw(struct state *st, unsigned events)
{
	bool cw;

	if (events == GPIO_IRQ_EDGE_FALL) {
		cw = true;
	} else if (events == GPIO_IRQ_EDGE_RISE) {
		cw = false;
	} else {
		return false;
	}

	if (cw == st->cw)
		return false;

	st->cw = cw;
	return true;
}


inline static bool update_ccw(struct state *st, unsigned events)
{
	bool ccw;

	if (events == GPIO_IRQ_EDGE_FALL) {
		ccw = true;
	} else if (events == GPIO_IRQ_EDGE_RISE) {
		ccw = false;
	} else {
		return false;
	}

	if (ccw == st->ccw)
		return false;

	st->ccw = ccw;
	return true;
}


static int64_t debounce(alarm_id_t id, void *arg)
{
	/* Bounce alarm timed out. */
	alarm_id = -1;

	struct state *st = arg;
	const bool sw = !gpio_get(st->sw_pin);

	if (sw == st->sw) {
		/* No change. No need to do anything. */
		return 0;
	}

	st->sw = sw;

	struct renc_event event = {
		.num = st - &state[0],
		.sw = sw,
	};

	(void)queue_try_add(&renc_queue, &event);

	return 0;
}


static void update_sw(struct state *st, unsigned events)
{
	bool sw;

	if (events & GPIO_IRQ_EDGE_FALL) {
		sw = true;
	} else if (events & GPIO_IRQ_EDGE_RISE) {
		sw = false;
	} else {
		/* This should not happen. */
		return;
	}

	if (sw == st->sw) {
		/* No change. */
		return;
	}

	const uint32_t prev = st->sw_mtime;
	const uint32_t now = time_us_32();

	if (alarm_id >= 0) {
		/* Cancel bounce timer, this happened earlier. */
		cancel_alarm(alarm_id);
		alarm_id = -1;
	}

	if (now - prev < DEBOUNCE_US) {
		/* Possible switch bounce.
		 * Start alarm and read the actual value then. */
		alarm_id = add_alarm_in_us(DEBOUNCE_US, debounce, st, true);
		return;
	}

	/* There was long enough delay since the last event,
	 * consider this event final. */
	st->sw_mtime = now;
	st->sw = sw;

	struct renc_event event = {
		.num = st - &state[0],
		.sw = sw,
	};

	(void)queue_try_add(&renc_queue, &event);
}


static void irq_handler(void)
{
	unsigned event_mask = GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL;

	for (int i = 0; i < NUM_RENC; i++) {
		struct state *st = &state[i];
		unsigned events;
		bool changed = false;

		/* Skip unconfigured encoders. */
		if (st->cw_pin == st->ccw_pin)
			continue;

		events = gpio_get_irq_event_mask(st->cw_pin);
		if (events & event_mask) {
			gpio_acknowledge_irq(st->cw_pin, event_mask);
			changed |= update_cw(&state[i], events);
		}

		events = gpio_get_irq_event_mask(st->ccw_pin);
		if (events & event_mask) {
			gpio_acknowledge_irq(st->ccw_pin, event_mask);
			changed |= update_ccw(&state[i], events);
		}

		events = gpio_get_irq_event_mask(st->sw_pin);
		if (events & event_mask) {
			gpio_acknowledge_irq(st->sw_pin, event_mask);
			update_sw(&state[i], events);
		}

		if (changed)
			update_state(&state[i]);
	}
}


void renc_init(unsigned q_size)
{
	queue_init(&renc_queue, sizeof(struct renc_event), q_size);
	alarm_pool_init_default();
	irq_set_enabled(IO_IRQ_BANK0, true);
}


void renc_config(unsigned num, uint8_t cw_pin, uint8_t ccw_pin, uint8_t sw_pin, uint8_t sens)
{
	state[num].cw_pin = cw_pin;
	state[num].ccw_pin = ccw_pin;
	state[num].sw_pin = sw_pin;
	state[num].sens = sens;

	gpio_init(cw_pin);
	gpio_set_dir(cw_pin, false);
	gpio_pull_up(cw_pin);

	gpio_init(ccw_pin);
	gpio_set_dir(ccw_pin, false);
	gpio_pull_up(ccw_pin);

	gpio_init(sw_pin);
	gpio_set_dir(sw_pin, false);
	gpio_pull_up(sw_pin);

	gpio_add_raw_irq_handler(cw_pin, irq_handler);
	gpio_add_raw_irq_handler(ccw_pin, irq_handler);
	gpio_add_raw_irq_handler(sw_pin, irq_handler);

	unsigned event_mask = GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL;
	gpio_set_irq_enabled(cw_pin, event_mask, true);
	gpio_set_irq_enabled(ccw_pin, event_mask, true);
	gpio_set_irq_enabled(sw_pin, event_mask, true);
}
