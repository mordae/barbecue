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

#pragma once

#include <pico/stdlib.h>
#include <pico/util/queue.h>

#include <stdbool.h>
#include <stdint.h>


/* Queue to read events from. */
extern queue_t renc_queue;


/* Number of rotary encoders. */
#if !defined(NUM_RENC)
# define NUM_RENC 4
#endif


/*
 * Rotary encoder event.
 *
 * Switch changes and deltas are never produced simultaneously.
 * Switch state is only valid when delta is 0.
 */
struct renc_event {
	/* Rotary encoder number. */
	uint8_t num : 5;

	/* State of the switch button. */
	bool sw : 1;

	/* Steps in clockwise (positive) or counterclockwise (negative)
	 * direction of rotation.
	 */
	int32_t steps : 26;
};


/*
 * Initialize rotary encoders.
 *
 * Registers interrupt handlers that control the state machines and
 * initialize the `renc_queue` to hold `q_size` events.
 */
void renc_init(unsigned q_size);


/* Configure given rotary encoder. */
void renc_config(unsigned num, uint8_t cw_pin, uint8_t ccw_pin, uint8_t sw_pin, uint8_t sens);
