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


/*
 * Ways the screen can be oriented.
 *
 * We can compensate when drawing and properly transform the virtual xy
 * coordinates to the real coordinates so that users don't have to.
 */
enum tft_orientation {
	TFT_ROTATE_0 = 0,
	TFT_ROTATE_90,
	TFT_ROTATE_180,
	TFT_ROTATE_270,
	TFT_MIRROR_X,
	TFT_MIRROR_Y,
};

/*
 * Defaults to TFT_ROTATE_90, because everyone likes it wider.
 */
extern enum tft_orientation tft_orientation;


/*
 * Color palette. We save only 4 bits per pixel instead of full 16.
 *
 * Default colors are:
 *
 *   0 - black
 *   1 - dark gray
 *   2 - light gray
 *   3 - white,
 *   4 - red
 *   5 - green
 *   6 - blue
 *   7 - light red
 *   8 - light green
 *   9 - light blue
 *  10 - yellow
 *  11 - cyan
 *  12 - purple
 *  13 - dark yellow
 *  14 - dark cyan
 *  15 - dark purple
 *
 * You should define some aliases and perhaps change the colors to
 * your liking. You can use tft_rgb() to generate the colors.
 */
extern uint16_t tft_palette[16];

/*
 * Generate 16bit color from the customary 3x 8bit RGB.
 */
inline static uint16_t tft_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	r = (r >> 3) & 0b00011111;
	g = (g >> 2) & 0b00111111;
	b = (b >> 3) & 0b00011111;
	return (r << 11) | (g << 5) | b;
}


/*
 * Modified latin 16x8 bitmap font.
 * Populate it with tft_load_font().
 */
extern uint8_t tft_font[256][16];


/*
 * Initialize the screen.
 *
 * You must provide the Register Select GPIO pin number.
 * You can provide a RST pin number or leave it at -1.
 */
void tft_init(void);


/*
 * Start display synchronization cycle.
 *
 * Blocks until the last cycle finishes so the you do not clobber
 * the input buffer it reads from.
 *
 * Changes tft_input to a new buffer and copies the last one to it.
 */
void tft_sync(void);


/*
 * Here goes whatever should be on the screen.
 * First come the Y rows, then the X columns.
 */
extern uint8_t (*tft_input)[TFT_HEIGHT][TFT_WIDTH / 2];


/*
 * Color a single pixel.
 */
void tft_draw_pixel(uint8_t x, uint8_t y, uint8_t color);


/*
 * Color a whole rect of pixels.
 */
void tft_draw_rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);


/*
 * Paint the whole screen with a single color.
 */
void tft_fill(uint8_t color);


/*
 * Draw given glyph at specified coordinates.
 * The coordinates indicate bottom left of the glyph.
 */
void tft_draw_glyph(uint8_t x, uint8_t y, uint8_t color, char c);


/*
 * Draw given string at specified coordinates.
 * The coordinates indicate bottom left of the string.
 */
void tft_draw_string(uint8_t x, uint8_t y, uint8_t color, const char *str);
