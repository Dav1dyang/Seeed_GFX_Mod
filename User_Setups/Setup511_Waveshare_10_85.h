/*
 * Setup511: Waveshare 10.85" e-Paper Display
 *
 * Display: Waveshare 10.85" (1360×480) with dual JD79686AB ICs
 * Board: Seeed XIAO ESP32S3/ESP32C6 + Seeed XIAO ePaper Driver Board
 *
 * HARDWARE MODIFICATION REQUIRED:
 * Connect display pin 1 (CSB_S) directly to D7 on XIAO
 *
 * Schematic Pin Reference:
 * - Primary IC CS:   CSB_M (display pin 12) → D1 via driver board
 * - Secondary IC CS: CSB_S (display pin 1)  → D7 direct wire **MOD REQUIRED**
 */

#include <Wire.h>

#define USER_SETUP_ID 511

#define JD79686AB_DRIVER
#define EPAPER_ENABLE

// Display resolution: Full 1360×480 (680×480 per IC)
#define TFT_WIDTH 1360
#define TFT_HEIGHT 480
#define EPD_WIDTH TFT_WIDTH
#define EPD_HEIGHT TFT_HEIGHT

// Use dual CS pin configuration (loads from EPaper_Board_Pins_Setups.h)
#define USE_XIAO_EPAPER_DRIVER_BOARD_DUAL_CS_D7
#include "EPaper_Board_Pins_Setups.h"

// Font configuration
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

#define SMOOTH_FONT

// ESP32S3 SPI configuration (not used - we use bit-bang)
#ifdef CONFIG_IDF_TARGET_ESP32S3
#define USE_HSPI_PORT
#endif

// SPI Frequency (not used for bit-bang, but required by library)
#if defined(ARDUINO_XIAO_ESP32S3) || defined(ARDUINO_XIAO_ESP32S3_PLUS)
#define SPI_FREQUENCY 10000000
#define SPI_READ_FREQUENCY 4000000
#elif defined(ARDUINO_XIAO_ESP32C6)
#define SPI_FREQUENCY 10000000
#define SPI_READ_FREQUENCY 4000000
#else
#define SPI_FREQUENCY 10000000
#define SPI_READ_FREQUENCY 4000000
#endif
