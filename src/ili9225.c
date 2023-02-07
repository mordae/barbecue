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

#include "tft.h"

#include <pico/stdlib.h>
#include <hardware/spi.h>
#include <hardware/dma.h>

#include <stdio.h>
#include <string.h>


uint16_t tft_palette[16] = {
	0b0000000000000000, /* black */
	0b0001100001100011, /* dark gray */
	0b1000110001010001, /* light gray */
	0b1111111111111111, /* white */

	0b1111100000000000, /* red */
	0b0000011111100000, /* green */
	0b0000000000011111, /* blue */

	0b1111101001001001, /* light red */
	0b0100111111101001, /* light green */
	0b0100101001011111, /* light blue */

	0b1111111111100000, /* yellow */
	0b0000011111111111, /* cyan */
	0b1111100000011111, /* purple */

	0b1000110001000000, /* dark yellow */
	0b0000010001010001, /* dark cyan */
	0b1000100000010001, /* dark purple */
};

#if TFT_SWAP_XY
# define WIDTH 220
# define HEIGHT 176
#else
# define WIDTH 176
# define HEIGHT 220
#endif

const unsigned tft_width = WIDTH;
const unsigned tft_height = HEIGHT;

/*
 * We are using double buffering.
 *
 * One buffer is being written to by the client.
 * The other buffer is being transmitted.
 *
 * After every cycle the buffers are rotated.
 */
static uint8_t buffer[2][HEIGHT * WIDTH >> 1];
static uint8_t *committed;

uint8_t *tft_input;

extern uint8_t tft_font[256][16];

/* DMA channel to use for transmit. */
static int dma_ch;
static dma_channel_config dma_conf;

/* Transfer buffers. */
static uint8_t txbuf[2][WIDTH * 2];


inline static void select_register(void)
{
	gpio_put(TFT_RS_PIN, 0);
}

inline static void select_data(void)
{
	gpio_put(TFT_RS_PIN, 1);
}


static void transmit_blocking(const void *buf, size_t len)
{
	dma_channel_wait_for_finish_blocking(dma_ch);
	size_t wr = spi_write_blocking(TFT_SPI_DEV, buf, len);
	assert (len == wr);
}


static void transmit_dma(const void *buf, size_t len)
{
	dma_channel_wait_for_finish_blocking(dma_ch);
	dma_channel_configure(dma_ch, &dma_conf,
			&spi_get_hw(TFT_SPI_DEV)->dr,
			buf, len, true);
}


/*
 * Change register ID.
 */
static void write_register(uint8_t reg)
{
	uint8_t buf[] = {reg};

	select_register();
	transmit_blocking(buf, 1);
}


/*
 * Write a word to the current register.
 */
static void write_word(uint16_t word)
{
	uint8_t buf[] = {word >> 8, word};

	select_data();
	transmit_blocking(buf, 2);
}


static void write_buffer(uint8_t *bstr, size_t len)
{
	select_data();
	transmit_blocking(bstr, len);
}


static void write_buffer_dma(uint8_t *bstr, size_t len)
{
	select_data();
	transmit_dma(bstr, len);
}


/*
 * Shortcut to change the register and then write a word to it.
 * Useful for preflight().
 */
static void set_register(uint8_t reg, uint16_t word)
{
	write_register(reg);
	write_word(word);
}


/*
 * Prepare the display for operation.
 */
static void preflight()
{
	/* Reset power options. */
	set_register(0x10, 0x0000);	// Set SAP, DSTB, STB
	set_register(0x11, 0x0000);	// Set APON, PON, AON, VCI1EN, VC
	set_register(0x12, 0x0000);	// Set BT, DC1, DC2, DC3
	set_register(0x13, 0x0000);	// Set GVDD
	set_register(0x14, 0x0000);	// Set VCOMH/VCOML voltage
	sleep_ms(40);

	/* Set power options. */
	set_register(0x11, 0x0018);	// Set APON, PON, AON, VCI1EN, VC
	set_register(0x12, 0x6121);	// Set BT, DC1, DC2, DC3
	set_register(0x13, 0x006f);	// Set GVDD
	set_register(0x14, 0x495f);	// Set VCOMH/VCOML voltage
	set_register(0x10, 0x0800);	// Set SAP, DSTB, STB
	sleep_ms(10);

	set_register(0x11, 0x103b);	// Set APON, PON, AON, VCI1EN, VC
	sleep_ms(50);

	/* Configure most of the display. */
	set_register(0x01, 0x001c);     // 220 lines
	set_register(0x02, 0x0100);	// INV0=1 (3 field interlace)

	uint16_t orient = (TFT_SWAP_XY << 3)
	                | (TFT_FLIP_Y << 4)
	                | ((!TFT_FLIP_X) << 5);
	set_register(0x03, 0x1000 | orient);	// BGR=1 + orient

	set_register(0x07, 0x0000);	// Display off
	set_register(0x08, 0x0808);	// Back and front porch
	set_register(0x0b, 0x1100);	// NO=1, STD=1, RTN=0 (16 clocks per line)
	set_register(0x0c, 0x0000);	// RIM=0 (18b), DM=0, RM=0
	set_register(0x0f, 0xe001);	// FOSC=1110 (500KHz), OSC_EN=1
	set_register(0x15, 0x0020);	// VCIR=010 (2 clocks)
	set_register(0x20, 0x0000);	// AD_LO=0 (position GRAM AC=0)
	set_register(0x21, 0x0000);	// AD_HI=0

	/* Scrolling and update area setup. */
	set_register(0x30, 0x0000);
	set_register(0x31, 0x00db);
	set_register(0x32, 0x0000);
	set_register(0x33, 0x0000);
	set_register(0x34, 0x00db);
	set_register(0x35, 0x0000);
	set_register(0x36, 0x00af);
	set_register(0x37, 0x0000);
	set_register(0x38, 0x00db);
	set_register(0x39, 0x0000);

	/* Adjust gamma curve. */
	set_register(0x50, 0x0000);
	set_register(0x51, 0x0808);
	set_register(0x52, 0x080a);
	set_register(0x53, 0x000a);
	set_register(0x54, 0x0a08);
	set_register(0x55, 0x0808);
	set_register(0x56, 0x0000);
	set_register(0x57, 0x0a00);
	set_register(0x58, 0x0710);
	set_register(0x59, 0x0710);

	set_register(0x07, 0x0012);
	sleep_ms(50);

	set_register(0x07, 0x1017);     // TEMON=1, GON=1, CL=1, REV=1, D=11
}


void tft_init(void)
{
	printf("ili9225: Arrange buffers...\n");
	tft_input = buffer[0];
	committed = buffer[1];

	printf("ili9225: Configure SPI...\n");

	uint rate = spi_init(TFT_SPI_DEV, TFT_BAUDRATE);
	printf("ili9225: Baudrate: %u\n", rate);

	gpio_set_function(TFT_CS_PIN, GPIO_FUNC_SPI);
	gpio_set_function(TFT_SCK_PIN, GPIO_FUNC_SPI);
	gpio_set_function(TFT_MOSI_PIN, GPIO_FUNC_SPI);

	printf("ili9225: Configure aux pins...\n");

	gpio_init(TFT_RST_PIN);
	gpio_set_dir(TFT_RST_PIN, GPIO_OUT);

	gpio_init(TFT_RS_PIN);
	gpio_set_dir(TFT_RS_PIN, GPIO_OUT);

	printf("ili9225: Configure DMA channel...\n");
	dma_ch = dma_claim_unused_channel(true);
	dma_conf = dma_channel_get_default_config(dma_ch);
	channel_config_set_transfer_data_size(&dma_conf, DMA_SIZE_8);
	channel_config_set_dreq(&dma_conf, spi_get_dreq(TFT_SPI_DEV, true));

	printf("ili9225: Reset screen...\n");

	gpio_put(TFT_RST_PIN, 0);
	sleep_ms(50);

	gpio_put(TFT_RST_PIN, 1);
	sleep_ms(50);

	printf("ili9225: Begin preflight...\n");
	preflight();

	printf("ili9225: Fill screen with gray...\n");
	tft_fill(1);
	tft_sync();

	printf("ili9225: Fill screen with black...\n");
	tft_fill(0);
	tft_sync();
}


inline static uint8_t high(uint8_t x)
{
	return (x >> 4) & 0b1111;
}


inline static uint8_t low(uint8_t x)
{
	return x & 0b1111;
}


void tft_swap_buffers(void)
{
	uint8_t *tmp;

	tmp       = committed;
	committed = tft_input;
	tft_input = tmp;
}


void tft_sync(void)
{
	/* Home the GRAM Address Counter. */
	set_register(0x20, 0);
	set_register(0x21, 0);

	/* Activate GRAM write register. */
	write_register(0x22);

	for (int y = 0; y < HEIGHT; y++) {
		uint8_t *buf = txbuf[y & 1];

		for (int x = 0; x < WIDTH >> 1; x++) {
			uint8_t twopix = committed[y * (WIDTH >> 1) + x];

			uint16_t left  = tft_palette[(twopix >> 4) & 0b1111];
			uint16_t right = tft_palette[twopix & 0b1111];

			size_t base = x << 2;

			buf[base + 0] = left >> 8;
			buf[base + 1] = left;
			buf[base + 2] = right >> 8;
			buf[base + 3] = right;
		}

		/* Send the buffer out while we prepare the next one. */
		write_buffer_dma(buf, WIDTH << 1);
	}
}


void tft_swap_sync(void)
{
	tft_swap_buffers();
	tft_sync();
}


inline static int clamp(int x, int min, int max)
{
	if (x < min)
		return min;

	if (x > max)
		return max;

	return x;
}


void tft_draw_rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color)
{
	x0 = tft_clamp(x0, 0, WIDTH - 1);
	x1 = tft_clamp(x1, 0, WIDTH - 1);
	y0 = tft_clamp(y0, 0, HEIGHT - 1);
	y1 = tft_clamp(y1, 0, HEIGHT - 1);
	color = tft_clamp(color, 0, 0x0f);

	if (x0 > x1) {
		x0 ^= x1;
		x1 ^= x0;
		x0 ^= x1;
	}

	if (y0 > y1) {
		y0 ^= y1;
		y1 ^= y0;
		y0 ^= y1;
	}

	for (int y = y0; y <= y1; y++) {
		for (int x = x0; x <= x1; x++) {
			tft_draw_pixel(x, y, color);
		}
	}
}


void tft_fill(uint8_t color)
{
	uint8_t twopix = ((color & 0b1111) << 4) | (color & 0b1111);
	memset(tft_input, twopix, sizeof(buffer[0]));
}


void tft_draw_glyph(uint8_t x, uint8_t y, uint8_t color, char c)
{
	uint8_t *glyph = tft_font[(uint8_t)c];

	for (int gx = 0; gx < 8; gx++) {
		for (int gy = 0; gy < 16; gy++) {
			if ((glyph[15 - gy] >> (7 - gx)) & 1) {
				tft_draw_pixel(x + gx, y + gy, color);
			}
		}
	}
}


void tft_draw_string(uint8_t x, uint8_t y, uint8_t color, const char *str)
{
	int len = strlen(str);

	for (int i = 0; i < len; i++)
		tft_draw_glyph(x + i * 8, y, color, str[i]);
}
