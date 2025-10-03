# Seeed_GFX with Waveshare 10.85" e-Paper Support

This is a fork of [Seeed-Studio/Seeed_GFX](https://github.com/Seeed-Studio/Seeed_GFX) with added support for the **Waveshare 10.85" dual-IC e-Paper display**.

## What's New

✅ Full support for Waveshare 10.85" (1360×480) e-Paper display
✅ Dual JD79686AB driver IC handling
✅ Bit-bang SPI implementation for reliable dual-IC communication
✅ Working example with hardware setup documentation

## Hardware Setup

### Required Components
- Seeed XIAO ESP32S3
- Seeed XIAO ePaper Driver Board V2
- Waveshare 10.85" e-Paper Display

### Hardware Modification
**Required**: Connect display pin 1 (CSB_S) to D7 on XIAO ESP32S3

## Quick Start

1. **Install this library** in your Arduino libraries folder

2. **Create sketch with driver.h**:
```cpp
#define BOARD_SCREEN_COMBO 511
```

3. **Use the example**:
```cpp
#include "TFT_eSPI.h"

EPaper epaper;

void setup() {
    epaper.begin();
    epaper.fillScreen(TFT_WHITE);

    // Draw on left side (Primary IC)
    epaper.drawString("LEFT IC", 50, 50);
    epaper.fillCircle(300, 240, 80, TFT_BLACK);

    // Draw on right side (Secondary IC)
    epaper.drawString("RIGHT IC", 800, 50);
    epaper.fillRect(900, 160, 200, 200, TFT_BLACK);

    epaper.update();
}

void loop() {}
```

4. **See example**: `examples/ePaper/10.85inch/Basic_Example/`

## Implementation Details

- **Driver**: JD79686AB with bit-bang SPI
- **Pin Setup**: USE_XIAO_EPAPER_DRIVER_BOARD_DUAL_CS_D7
- **Resolution**: 1360×480 (680×480 per IC)
- **IC Control**: TFT_CS_PRIMARY (D1), TFT_CS_SECONDARY (D7)

See `CHANGES_10_85.md` for detailed technical information.

## Upstream Status

This is a personal fork. Consider opening an issue with Seeed Studio if you'd like to see this integrated into the main repository.

## Credits

Implementation based on Waveshare's reference code for the 10.85" display, adapted for Seeed XIAO ecosystem.
