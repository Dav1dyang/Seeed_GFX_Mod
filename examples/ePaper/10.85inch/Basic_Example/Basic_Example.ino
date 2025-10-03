/*
 * Waveshare 10.85" e-Paper Display - Basic Example
 *
 * This example demonstrates the Waveshare 10.85" (1360×480) dual-IC e-paper display
 * with the Seeed XIAO ESP32S3 and Seeed XIAO ePaper Driver Board.
 *
 * ============================================================================
 * HARDWARE REQUIREMENTS
 * ============================================================================
 * - Seeed XIAO ESP32S3
 * - Seeed XIAO ePaper Driver Board V2
 * - Waveshare 10.85" e-Paper display
 *
 * ============================================================================
 * HARDWARE MODIFICATION REQUIRED
 * ============================================================================
 * The 10.85" display uses TWO driver ICs (JD79686AB) that require separate
 * chip select lines:
 *
 * Standard connections via Seeed Driver Board:
 *   XIAO Pin → Driver Board → Display Pin | Function
 *   ------------------------------------------------
 *   D8       → SCLK         → Pin 13     | SPI Clock (shared)
 *   D10      → MOSI         → Pin 14     | SPI Data (shared)
 *   D3       → DC           → Pin 11     | Data/Command (shared)
 *   D0       → RST          → Pin 10     | Reset (shared)
 *   D2       → BUSY         → Pin 9      | Busy signal (shared)
 *   D1       → CS           → Pin 12     | Primary IC CS (CSB_M)
 *
 * ** REQUIRED MODIFICATION **:
 *   D7 (XIAO) ──wire──> Display Pin 1 (CSB_S)
 *
 * Solder a wire from D7 on the XIAO ESP32S3 directly to pin 1 on the
 * display FPC connector. This provides the chip select for the secondary IC.
 *
 * ============================================================================
 * DISPLAY ARCHITECTURE
 * ============================================================================
 * Resolution: 1360×480 pixels (horizontal orientation)
 *
 * ┌─────────────────────────────────────┐
 * │  LEFT 680px      │  RIGHT 680px     │
 * │  Primary IC      │  Secondary IC    │
 * │  (CSB_M, pin 12) │  (CSB_S, pin 1)  │
 * │  via D1          │  via D7          │
 * └─────────────────────────────────────┘
 *
 * ============================================================================
 * SOFTWARE CONFIGURATION
 * ============================================================================
 * Create a file named "driver.h" in your sketch folder with:
 *
 *    #define BOARD_SCREEN_COMBO 511
 *
 * This selects the Waveshare 10.85" display configuration.
 *
 * ============================================================================
 */

#include "TFT_eSPI.h"

#ifdef EPAPER_ENABLE
EPaper epaper;
#endif

void setup()
{
#ifdef EPAPER_ENABLE
    // Initialize display
    epaper.begin();

    // Clear to white
    epaper.fillScreen(TFT_WHITE);

    // Draw on LEFT side (Primary IC, 0-680px)
    epaper.setTextSize(3);
    epaper.setTextColor(TFT_BLACK, TFT_WHITE);
    epaper.drawString("LEFT IC", 50, 50);
    epaper.drawString("Primary", 50, 100);
    epaper.drawString("(D1)", 50, 150);
    epaper.fillCircle(300, 300, 80, TFT_BLACK);

    // Draw on RIGHT side (Secondary IC, 680-1360px)
    epaper.drawString("RIGHT IC", 800, 50);
    epaper.drawString("Secondary", 800, 100);
    epaper.drawString("(D7)", 800, 150);
    epaper.fillRect(900, 220, 160, 160, TFT_BLACK);

    // Draw across center (crosses both ICs at 680px)
    epaper.drawFastVLine(680, 0, epaper.height(), TFT_BLACK);
    epaper.drawRect(600, 380, 160, 60, TFT_BLACK);
    epaper.setTextSize(2);
    epaper.drawString("Boundary at 680px", 540, 395);

    // Border frame
    epaper.drawRect(0, 0, epaper.width(), epaper.height(), TFT_BLACK);

    // Update display (will take ~4 seconds)
    epaper.update();

    // Display will remain showing this image until next update
    // E-paper is bistable - no power needed to maintain image

#endif
}

void loop()
{
    // Nothing to do - image persists on e-paper
    delay(10000);
}
