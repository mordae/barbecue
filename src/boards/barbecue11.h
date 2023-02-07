#pragma once

/* Delay to stabilize the oscillator. */
#if !defined(PICO_XOSC_STARTUP_DELAY_MULTIPLIER)
# define PICO_XOSC_STARTUP_DELAY_MULTIPLIER 64
#endif

/* QSPI flash access protocol selection. */
#define PICO_BOOT_STAGE2_CHOOSE_W25Q080 1
//#define PICO_BOOT_STAGE2_CHOOSE_GENERIC_03H 1

/* Flash access clock divider. */
#if !defined(PICO_FLASH_SPI_CLKDIV)
# define PICO_FLASH_SPI_CLKDIV 2
#endif

/* Total flash size in bytes. */
#if !defined(PICO_FLASH_SIZE_BYTES)
# define PICO_FLASH_SIZE_BYTES (16 * 1024 * 1024)
#endif

/* SD-Card */
#define SD_CS_PIN 1
#define SD_SCK_PIN 2
#define SD_MOSI_PIN 3
#define SD_MISO_PIN 4

/* Rotary encoder */
#define NUM_RENC 1
#define RENC_CW_PIN 9
#define RENC_CCW_PIN 10
#define RENC_SW_PIN 11
#define RENC_SENS 10

/* TFT Screen */
#define TFT_CS_PIN 21
#define TFT_SCK_PIN 22
#define TFT_MOSI_PIN 23
#define TFT_RS_PIN 24
#define TFT_RST_PIN 25

#define TFT_SWAP_XY 1
#define TFT_FLIP_X 0
#define TFT_FLIP_Y 0
#define TFT_SPI_DEV spi0

/* Other TFT parameters. */
#if !defined(TFT_BAUDRATE)
# define TFT_BAUDRATE (64 * 1000 * 1000)
#endif

/* Fan and heater control */
#define FAN1_PIN 27
#define FAN2_PIN 26
#define HEAT_PIN 29

/* NTC thermistor */
#define TSENSE_PIN 28
