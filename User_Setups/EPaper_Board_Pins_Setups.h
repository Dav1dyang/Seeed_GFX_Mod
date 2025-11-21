
#if defined(USE_XIAO_EPAPER_DRIVER_BOARD)
// Standard single-IC e-paper displays
#define TFT_SCLK D8
#define TFT_MISO D9
#define TFT_MOSI D10
#define TFT_CS D1
#define TFT_DC D3
#define TFT_BUSY D2
#define TFT_RST D0

#elif defined(USE_XIAO_EPAPER_DRIVER_BOARD_DUAL_CS_D7)
// Dual-IC e-paper displays (e.g. Waveshare 10.85")
// Requires hardware modification: Connect display CSB_S (pin 1) to D7 on XIAO
#define TFT_SCLK D8              // Shared SPI clock
#define TFT_MISO D9              // Shared SPI MISO
#define TFT_MOSI D10             // Shared SPI MOSI
#define TFT_DC D3                // Shared Data/Command
#define TFT_BUSY D2              // Shared BUSY signal
#define TFT_RST D0               // Shared Reset
#define TFT_CS D1                // Default CS
#define TFT_CS_PRIMARY D1        // Primary/Left IC → CSB_M (display pin 12)
#define TFT_CS_SECONDARY D7      // Secondary/Right IC → CSB_S (display pin 1)

#elif defined(USE_XIAO_EPAPER_BREAKOUT_BOARD_DUAL_CS_D7)
// Dual-IC e-paper displays on breakout board (e.g. Waveshare 10.85")
// Requires hardware modification: Connect display CSB_S (pin 1) to D7 on XIAO
#define TFT_SCLK D8              // Shared SPI clock
#define TFT_MISO D9              // Shared SPI MISO
#define TFT_MOSI D10             // Shared SPI MOSI
#define TFT_DC D3                // Shared Data/Command
#define TFT_BUSY D5              // Shared BUSY signal (BREAKOUT BOARD USES D5)
#define TFT_RST D0               // Shared Reset
#define TFT_CS D1                // Default CS
#define TFT_CS_PRIMARY D1        // Primary/Left IC → CSB_M (display pin 12)
#define TFT_CS_SECONDARY D7      // Secondary/Right IC → CSB_S (display pin 1)

#elif defined(USE_XIAO_EPAPER_BREAKOUT_BOARD)
#define TFT_SCLK D8
#define TFT_MISO D9
#define TFT_MOSI D10
#define TFT_CS D1
#define TFT_DC D3
#define TFT_BUSY D5
#define TFT_RST D0
#elif defined(USE_XIAO_EPAPER_DISPLAY_BOARD_EE04)
#define TFT_SCLK D8
#define TFT_MISO -1
#define TFT_MOSI D10
#define TFT_CS 44  // D7
#define TFT_DC 10  // D16
#define TFT_BUSY 4 // D3
#define TFT_RST 38 // D11
#endif