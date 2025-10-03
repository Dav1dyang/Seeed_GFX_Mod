# Waveshare 10.85" e-Paper Support - Changes Summary

## Overview
Added support for Waveshare 10.85" (1360×480) dual-IC e-Paper display to Seeed_GFX library.

## New Files Added

### Driver Files
- `TFT_Drivers/JD79686AB_Defines.h` - Driver definitions with bit-bang SPI
- `TFT_Drivers/JD79686AB_Init.h` - Initialization sequence for dual ICs
- `TFT_Drivers/JD79686AB_Rotation.h` - Rotation handling (minimal for e-paper)

### Configuration Files
- `User_Setups/Setup511_Waveshare_10_85.h` - Display configuration
- Updated `User_Setups/EPaper_Board_Pins_Setups.h` - Added USE_XIAO_EPAPER_DRIVER_BOARD_DUAL_CS_D7
- Updated `User_Setups/Dynamic_Setup.h` - Registered BOARD_SCREEN_COMBO 511

### Example
- `examples/ePaper/10.85inch/Basic_Example/Basic_Example.ino` - Working example
- `examples/ePaper/10.85inch/Basic_Example/driver.h` - Configuration

## Modified Files

### Core Library Files
- `User_Setup_Select.h` - Added JD79686AB_DRIVER registration
- `TFT_eSPI.cpp` - Added JD79686AB init/rotation includes, disabled hardware SPI for this driver
- `TFT_eSPI.h` - No changes needed

## Technical Implementation

### Why Bit-Bang SPI?
Hardware SPI timing is incompatible with JD79686AB dual-IC architecture. Bit-bang SPI (matching Waveshare's reference implementation) provides reliable communication with both ICs.

### Dual IC Architecture
- Display uses TWO JD79686AB driver ICs
- Primary IC (left 680px): Controlled via CSB_M (pin 12) → D1
- Secondary IC (right 680px): Controlled via CSB_S (pin 1) → D7
- Requires hardware modification: D7 wire to display pin 1

### Key Features
- Full 1360×480 resolution support
- Automatic image splitting between ICs (170 bytes per row: 85+85)
- Compatible with EPaper class and all drawing functions
- Proper sleep/wake power management

## Hardware Requirements

**Requires hardware modification**: Connect display CSB_S (pin 1) to D7 on XIAO

## Testing

Tested and verified working on:
- Seeed XIAO ESP32S3
- Seeed XIAO ePaper Driver Board V2
- Waveshare 10.85" e-Paper display

Both ICs display correctly with clean output, no corruption or misalignment.

## Usage

```cpp
// driver.h
#define BOARD_SCREEN_COMBO 511

// sketch.ino
#include "TFT_eSPI.h"

EPaper epaper;

void setup() {
    epaper.begin();
    epaper.fillScreen(TFT_WHITE);
    epaper.drawString("Hello 10.85\"!", 100, 100);
    epaper.update();
}
```

## Limitations

- Requires D7 hardware modification (not plug-and-play)
- Bit-bang SPI is slower than hardware SPI
- Specific to Waveshare 10.85" dual-IC architecture

## Reference

Implementation based on Waveshare's official ESP32 example code for 10.85" display.
