/*
 * JD79686AB_Defines.h
 * Driver for Waveshare 10.85" e-Paper Display (1360×480)
 *
 * Hardware: Dual JD79686AB driver ICs (left 680px + right 680px)
 * Communication: Bit-bang SPI (hardware SPI incompatible with dual-IC timing)
 * Based on: Waveshare reference implementation
 */

#ifndef EPD_WIDTH
#define EPD_WIDTH 1360  // Full display width (680 per IC)
#endif

#ifndef EPD_HEIGHT
#define EPD_HEIGHT 480
#endif

#ifndef TFT_WIDTH
#define TFT_WIDTH EPD_WIDTH
#endif

#ifndef TFT_HEIGHT
#define TFT_HEIGHT EPD_HEIGHT
#endif

#define EPD_COLOR_DEPTH 1

// Dual IC constants
#define EPD_BYTES_PER_ROW 170   // 1360 / 8
#define EPD_BYTES_PER_HALF 85   // 680 / 8

// Dual CS pins (must be defined in setup file)
#ifndef TFT_CS_PRIMARY
#define TFT_CS_PRIMARY TFT_CS  // Master IC CS
#endif

#ifndef TFT_CS_SECONDARY
#define TFT_CS_SECONDARY -1      // Slave IC CS (must be defined)
#endif

// Bit-bang SPI macro - EXACT Waveshare implementation
// Matches DEV_SPI_WriteByte() from Waveshare code
#define SPI_BITBANG_WRITE(data)           \
    do                                    \
    {                                     \
        uint8_t _d = (data);              \
        for (int _i = 0; _i < 8; _i++)    \
        {                                 \
            if (_d & 0x80)                \
                digitalWrite(TFT_MOSI, HIGH); \
            else                          \
                digitalWrite(TFT_MOSI, LOW);  \
            _d <<= 1;                     \
            digitalWrite(TFT_SCLK, HIGH); \
            digitalWrite(TFT_SCLK, LOW);  \
        }                                 \
    } while (0)

// BUSY check with timeout (matches Waveshare ReadBusy)
#ifdef TFT_BUSY
#define CHECK_BUSY()                              \
    do                                            \
    {                                             \
        unsigned long _busy_start = millis();     \
        while (!digitalRead(TFT_BUSY)) {          \
            if (millis() - _busy_start > 25000)   \
                break;                            \
            delay(10);                            \
        }                                         \
        delay(10);                                \
    } while (0)
#else
#define CHECK_BUSY()
#endif

// EPD_UPDATE - Refresh both ICs (Waveshare TurnOnDisplay)
#define EPD_UPDATE()                        \
    do                                      \
    {                                       \
        digitalWrite(TFT_DC, LOW);          \
        digitalWrite(TFT_CS_PRIMARY, LOW);        \
        SPI_BITBANG_WRITE(0x12);            \
        digitalWrite(TFT_CS_PRIMARY, HIGH);       \
        digitalWrite(TFT_CS_SECONDARY, LOW);        \
        SPI_BITBANG_WRITE(0x12);            \
        digitalWrite(TFT_CS_SECONDARY, HIGH);       \
        CHECK_BUSY();                       \
    } while (0)

// EPD_SLEEP - Sleep both ICs (Waveshare EPD_10in85_Sleep)
#define EPD_SLEEP()                         \
    do                                      \
    {                                       \
        digitalWrite(TFT_DC, LOW);          \
        digitalWrite(TFT_CS_PRIMARY, LOW);        \
        SPI_BITBANG_WRITE(0x02);            \
        digitalWrite(TFT_CS_PRIMARY, HIGH);       \
        digitalWrite(TFT_CS_SECONDARY, LOW);        \
        SPI_BITBANG_WRITE(0x02);            \
        digitalWrite(TFT_CS_SECONDARY, HIGH);       \
        delay(100);                         \
        CHECK_BUSY();                       \
        digitalWrite(TFT_DC, LOW);          \
        digitalWrite(TFT_CS_PRIMARY, LOW);        \
        SPI_BITBANG_WRITE(0x07);            \
        digitalWrite(TFT_CS_PRIMARY, HIGH);       \
        digitalWrite(TFT_DC, HIGH);         \
        digitalWrite(TFT_CS_PRIMARY, LOW);        \
        SPI_BITBANG_WRITE(0xA5);            \
        digitalWrite(TFT_CS_PRIMARY, HIGH);       \
        digitalWrite(TFT_DC, LOW);          \
        digitalWrite(TFT_CS_SECONDARY, LOW);        \
        SPI_BITBANG_WRITE(0x07);            \
        digitalWrite(TFT_CS_SECONDARY, HIGH);       \
        digitalWrite(TFT_DC, HIGH);         \
        digitalWrite(TFT_CS_SECONDARY, LOW);        \
        SPI_BITBANG_WRITE(0xA5);            \
        digitalWrite(TFT_CS_SECONDARY, HIGH);       \
        delay(100);                         \
    } while (0)

// EPD_WAKEUP - Re-initialize display after sleep (matches Waveshare Init)
#define EPD_WAKEUP()                                                                    \
    do                                                                                  \
    {                                                                                   \
        /* Hardware reset */                                                            \
        digitalWrite(TFT_RST, HIGH);                                                    \
        delay(20);                                                                      \
        digitalWrite(TFT_RST, LOW);                                                     \
        delay(10);                                                                      \
        digitalWrite(TFT_RST, HIGH);                                                    \
        delay(20);                                                                      \
        /* Master IC register configuration */                                          \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_PRIMARY, LOW);                   \
        SPI_BITBANG_WRITE(0x4D); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_PRIMARY, LOW);                  \
        SPI_BITBANG_WRITE(0x55); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_PRIMARY, LOW);                   \
        SPI_BITBANG_WRITE(0xA6); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_PRIMARY, LOW);                  \
        SPI_BITBANG_WRITE(0x38); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_PRIMARY, LOW);                   \
        SPI_BITBANG_WRITE(0xB4); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_PRIMARY, LOW);                  \
        SPI_BITBANG_WRITE(0x5D); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_PRIMARY, LOW);                   \
        SPI_BITBANG_WRITE(0xB6); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_PRIMARY, LOW);                  \
        SPI_BITBANG_WRITE(0x80); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_PRIMARY, LOW);                   \
        SPI_BITBANG_WRITE(0xB7); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_PRIMARY, LOW);                  \
        SPI_BITBANG_WRITE(0x00); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_PRIMARY, LOW);                   \
        SPI_BITBANG_WRITE(0xF7); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_PRIMARY, LOW);                  \
        SPI_BITBANG_WRITE(0x02); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        /* Slave IC register configuration */                                           \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_SECONDARY, LOW);                 \
        SPI_BITBANG_WRITE(0x4D); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_SECONDARY, LOW);                \
        SPI_BITBANG_WRITE(0x55); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_SECONDARY, LOW);                 \
        SPI_BITBANG_WRITE(0xA6); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_SECONDARY, LOW);                \
        SPI_BITBANG_WRITE(0x38); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_SECONDARY, LOW);                 \
        SPI_BITBANG_WRITE(0xB4); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_SECONDARY, LOW);                \
        SPI_BITBANG_WRITE(0x5D); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_SECONDARY, LOW);                 \
        SPI_BITBANG_WRITE(0xB6); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_SECONDARY, LOW);                \
        SPI_BITBANG_WRITE(0x80); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_SECONDARY, LOW);                 \
        SPI_BITBANG_WRITE(0xB7); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_SECONDARY, LOW);                \
        SPI_BITBANG_WRITE(0x00); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_SECONDARY, LOW);                 \
        SPI_BITBANG_WRITE(0xF7); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_SECONDARY, LOW);                \
        SPI_BITBANG_WRITE(0x02); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        /* Slave-specific command */                                                    \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_SECONDARY, LOW);                 \
        SPI_BITBANG_WRITE(0xAE); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_SECONDARY, LOW);                \
        SPI_BITBANG_WRITE(0xA0); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        /* Master panel settings */                                                     \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_PRIMARY, LOW);                   \
        SPI_BITBANG_WRITE(0xE0); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_PRIMARY, LOW);                  \
        SPI_BITBANG_WRITE(0x01); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_PRIMARY, LOW);                   \
        SPI_BITBANG_WRITE(0x00); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_PRIMARY, LOW);                  \
        SPI_BITBANG_WRITE(0x9F); SPI_BITBANG_WRITE(0x0D);                               \
        digitalWrite(TFT_CS_PRIMARY, HIGH);                                             \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_PRIMARY, LOW);                   \
        SPI_BITBANG_WRITE(0x06); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_PRIMARY, LOW);                  \
        SPI_BITBANG_WRITE(0x57); SPI_BITBANG_WRITE(0x24);                               \
        SPI_BITBANG_WRITE(0x28); SPI_BITBANG_WRITE(0x32);                               \
        SPI_BITBANG_WRITE(0x08); SPI_BITBANG_WRITE(0x48);                               \
        digitalWrite(TFT_CS_PRIMARY, HIGH);                                             \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_PRIMARY, LOW);                   \
        SPI_BITBANG_WRITE(0x61); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_PRIMARY, LOW);                  \
        SPI_BITBANG_WRITE(0x02); SPI_BITBANG_WRITE(0xA8);                               \
        SPI_BITBANG_WRITE(0x01); SPI_BITBANG_WRITE(0xE0);                               \
        digitalWrite(TFT_CS_PRIMARY, HIGH);                                             \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_PRIMARY, LOW);                   \
        SPI_BITBANG_WRITE(0x62); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_PRIMARY, LOW);                  \
        SPI_BITBANG_WRITE(0x00); SPI_BITBANG_WRITE(0x00);                               \
        SPI_BITBANG_WRITE(0x00); SPI_BITBANG_WRITE(0x00);                               \
        digitalWrite(TFT_CS_PRIMARY, HIGH);                                             \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_PRIMARY, LOW);                   \
        SPI_BITBANG_WRITE(0x60); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_PRIMARY, LOW);                  \
        SPI_BITBANG_WRITE(0x31); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_PRIMARY, LOW);                   \
        SPI_BITBANG_WRITE(0x50); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_PRIMARY, LOW);                  \
        SPI_BITBANG_WRITE(0x97); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_PRIMARY, LOW);                   \
        SPI_BITBANG_WRITE(0xE8); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_PRIMARY, LOW);                  \
        SPI_BITBANG_WRITE(0x01); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        /* Slave panel settings */                                                      \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_SECONDARY, LOW);                 \
        SPI_BITBANG_WRITE(0xE0); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_SECONDARY, LOW);                \
        SPI_BITBANG_WRITE(0x01); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_SECONDARY, LOW);                 \
        SPI_BITBANG_WRITE(0x00); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_SECONDARY, LOW);                \
        SPI_BITBANG_WRITE(0x9F); SPI_BITBANG_WRITE(0x0D);                               \
        digitalWrite(TFT_CS_SECONDARY, HIGH);                                           \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_SECONDARY, LOW);                 \
        SPI_BITBANG_WRITE(0x06); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_SECONDARY, LOW);                \
        SPI_BITBANG_WRITE(0x57); SPI_BITBANG_WRITE(0x24);                               \
        SPI_BITBANG_WRITE(0x28); SPI_BITBANG_WRITE(0x32);                               \
        SPI_BITBANG_WRITE(0x08); SPI_BITBANG_WRITE(0x48);                               \
        digitalWrite(TFT_CS_SECONDARY, HIGH);                                           \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_SECONDARY, LOW);                 \
        SPI_BITBANG_WRITE(0x61); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_SECONDARY, LOW);                \
        SPI_BITBANG_WRITE(0x02); SPI_BITBANG_WRITE(0xA8);                               \
        SPI_BITBANG_WRITE(0x01); SPI_BITBANG_WRITE(0xE0);                               \
        digitalWrite(TFT_CS_SECONDARY, HIGH);                                           \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_SECONDARY, LOW);                 \
        SPI_BITBANG_WRITE(0x62); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_SECONDARY, LOW);                \
        SPI_BITBANG_WRITE(0x00); SPI_BITBANG_WRITE(0x00);                               \
        SPI_BITBANG_WRITE(0x00); SPI_BITBANG_WRITE(0x00);                               \
        digitalWrite(TFT_CS_SECONDARY, HIGH);                                           \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_SECONDARY, LOW);                 \
        SPI_BITBANG_WRITE(0x60); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_SECONDARY, LOW);                \
        SPI_BITBANG_WRITE(0x31); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_SECONDARY, LOW);                 \
        SPI_BITBANG_WRITE(0x50); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_SECONDARY, LOW);                \
        SPI_BITBANG_WRITE(0x97); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_SECONDARY, LOW);                 \
        SPI_BITBANG_WRITE(0xE8); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS_SECONDARY, LOW);                \
        SPI_BITBANG_WRITE(0x01); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        /* Power ON both ICs */                                                         \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_PRIMARY, LOW);                   \
        SPI_BITBANG_WRITE(0x04); digitalWrite(TFT_CS_PRIMARY, HIGH);                    \
        digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS_SECONDARY, LOW);                 \
        SPI_BITBANG_WRITE(0x04); digitalWrite(TFT_CS_SECONDARY, HIGH);                  \
        delay(200);                                                                     \
        CHECK_BUSY();                                                                   \
    } while (0)

// EPD_SET_WINDOW - Not used for full refresh
#define EPD_SET_WINDOW(x1, y1, x2, y2)  do { } while (0)

// EPD_PUSH_NEW_COLORS - Dual IC data transmission
// EXACT match to Waveshare EPD_10in85_Display() function
#define EPD_PUSH_NEW_COLORS(w, h, colors)                                           \
    do                                                                              \
    {                                                                               \
        /* Master IC - OLD data (0x10) white buffer */                              \
        digitalWrite(TFT_DC, LOW);                                                  \
        digitalWrite(TFT_CS_PRIMARY, LOW);                                                \
        SPI_BITBANG_WRITE(0x10);                                                    \
        digitalWrite(TFT_CS_PRIMARY, HIGH);                                               \
        digitalWrite(TFT_DC, HIGH);                                                 \
        digitalWrite(TFT_CS_PRIMARY, LOW);                                                \
        for (uint16_t j = 0; j < (h); j++)                                          \
        {                                                                           \
            for (uint16_t i = 0; i < EPD_BYTES_PER_HALF; i++)                       \
            {                                                                       \
                SPI_BITBANG_WRITE(0xFF);                                            \
            }                                                                       \
        }                                                                           \
        digitalWrite(TFT_CS_PRIMARY, HIGH);                                               \
        /* Master IC - NEW data (0x13) left half */                                 \
        digitalWrite(TFT_DC, LOW);                                                  \
        digitalWrite(TFT_CS_PRIMARY, LOW);                                                \
        SPI_BITBANG_WRITE(0x13);                                                    \
        digitalWrite(TFT_CS_PRIMARY, HIGH);                                               \
        digitalWrite(TFT_DC, HIGH);                                                 \
        digitalWrite(TFT_CS_PRIMARY, LOW);                                                \
        for (uint16_t j = 0; j < (h); j++)                                          \
        {                                                                           \
            for (uint16_t i = 0; i < EPD_BYTES_PER_HALF; i++)                       \
            {                                                                       \
                SPI_BITBANG_WRITE(colors[j * EPD_BYTES_PER_ROW + i]);               \
            }                                                                       \
        }                                                                           \
        digitalWrite(TFT_CS_PRIMARY, HIGH);                                               \
        /* Slave IC - OLD data (0x10) white buffer */                               \
        digitalWrite(TFT_DC, LOW);                                                  \
        digitalWrite(TFT_CS_SECONDARY, LOW);                                                \
        SPI_BITBANG_WRITE(0x10);                                                    \
        digitalWrite(TFT_CS_SECONDARY, HIGH);                                               \
        digitalWrite(TFT_DC, HIGH);                                                 \
        digitalWrite(TFT_CS_SECONDARY, LOW);                                                \
        for (uint16_t j = 0; j < (h); j++)                                          \
        {                                                                           \
            for (uint16_t i = 0; i < EPD_BYTES_PER_HALF; i++)                       \
            {                                                                       \
                SPI_BITBANG_WRITE(0xFF);                                            \
            }                                                                       \
        }                                                                           \
        digitalWrite(TFT_CS_SECONDARY, HIGH);                                               \
        /* Slave IC - NEW data (0x13) right half */                                 \
        digitalWrite(TFT_DC, LOW);                                                  \
        digitalWrite(TFT_CS_SECONDARY, LOW);                                                \
        SPI_BITBANG_WRITE(0x13);                                                    \
        digitalWrite(TFT_CS_SECONDARY, HIGH);                                               \
        digitalWrite(TFT_DC, HIGH);                                                 \
        digitalWrite(TFT_CS_SECONDARY, LOW);                                                \
        for (uint16_t j = 0; j < (h); j++)                                          \
        {                                                                           \
            for (uint16_t i = 0; i < EPD_BYTES_PER_HALF; i++)                       \
            {                                                                       \
                SPI_BITBANG_WRITE(colors[j * EPD_BYTES_PER_ROW + EPD_BYTES_PER_HALF + i]); \
            }                                                                       \
        }                                                                           \
        digitalWrite(TFT_CS_SECONDARY, HIGH);                                               \
    } while (0)

// No FLIP version needed for this display
#define EPD_PUSH_NEW_COLORS_FLIP EPD_PUSH_NEW_COLORS
#define EPD_PUSH_OLD_COLORS(w, h, colors)  do { } while (0)
#define EPD_PUSH_OLD_COLORS_FLIP(w, h, colors)  do { } while (0)

// Standard command defines (not used but needed for compatibility)
#define EPD_NOP 0xFF
#define EPD_PNLSET 0x00
#define EPD_DISPON 0x04
#define EPD_DISPOFF 0x02
#define EPD_SLPIN 0x07
#define EPD_SLPOUT 0xFF

#define TFT_SWRST 0xFF
#define TFT_CASET 0xFF
#define TFT_PASET 0xFF
#define TFT_RAMWR 0x13
#define TFT_RAMRD 0xFF
#define TFT_INVON 0xFF
#define TFT_INVOFF 0xFF
#define TFT_INIT_DELAY 0
