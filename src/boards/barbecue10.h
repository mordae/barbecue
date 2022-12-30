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

/* J5 */
#define PWM3_P_PIN 5
#define PWM3_N_PIN 4

/* J7 */
#define PWM2_P_PIN 3
#define PWM2_N_PIN 2

/* J8 */
#define PWM1_P_PIN 1
#define PWM1_N_PIN 0

/* J6 */
#define TSENSE_PIN 29

/* 4-pin OLED header. */
#define OLED_SDA_PIN 6
#define OLED_SCL_PIN 7

/* 11-pin TFT header. */
#define TFT_SPI_DEV   spi1
#define TFT_RST_PIN   8
#define TFT_CS_PIN    9
#define TFT_SCK_PIN  10
#define TFT_MOSI_PIN 11
#define TFT_RS_PIN   14

/* Other TFT parameters. */
#if !defined(TFT_WIDTH)
# define TFT_WIDTH 176
#endif

#if !defined(TFT_HEIGHT)
# define TFT_HEIGHT 220
#endif

#if !defined(TFT_BAUDRATE)
# define TFT_BAUDRATE (64 * 1000 * 1000)
#endif

/* Rotary Encoder */
#define RE_SW_PIN 23
#define RE_B_PIN 24
#define RE_A_PIN 25
