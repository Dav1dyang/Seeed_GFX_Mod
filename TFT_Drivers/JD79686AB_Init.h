/*
 * JD79686AB_Init.h
 * Initialization sequence for Waveshare 10.85" e-Paper
 *
 * Dual IC Architecture:
 * - Primary IC (left 680px):   CSB_M (pin 12) controlled via TFT_CS_PRIMARY
 * - Secondary IC (right 680px): CSB_S (pin 1) controlled via TFT_CS_SECONDARY
 *
 * Reference: Waveshare EPD_10in85_Init() function
 * Uses bit-bang SPI for reliable dual-IC communication
 */

{
#ifdef TFT_BUSY
    pinMode(TFT_BUSY, INPUT);
#endif

    // Initialize all GPIO pins
    pinMode(TFT_CS_PRIMARY, OUTPUT);
    pinMode(TFT_CS_SECONDARY, OUTPUT);
    pinMode(TFT_DC, OUTPUT);
    pinMode(TFT_RST, OUTPUT);
    pinMode(TFT_MOSI, OUTPUT);
    pinMode(TFT_SCLK, OUTPUT);

    digitalWrite(TFT_CS_PRIMARY, HIGH);
    digitalWrite(TFT_CS_SECONDARY, HIGH);
    digitalWrite(TFT_DC, HIGH);
    digitalWrite(TFT_RST, HIGH);
    digitalWrite(TFT_SCLK, LOW);

    // Hardware reset
    digitalWrite(TFT_RST, HIGH);
    delay(20);
    digitalWrite(TFT_RST, LOW);
    delay(10);
    digitalWrite(TFT_RST, HIGH);
    delay(20);

    // Helper macros for cleaner code
    #define CMD_M(c) digitalWrite(TFT_DC,LOW); digitalWrite(TFT_CS_PRIMARY,LOW); SPI_BITBANG_WRITE(c); digitalWrite(TFT_CS_PRIMARY,HIGH)
    #define DATA_M(d) digitalWrite(TFT_DC,HIGH); digitalWrite(TFT_CS_PRIMARY,LOW); SPI_BITBANG_WRITE(d); digitalWrite(TFT_CS_PRIMARY,HIGH)
    #define CMD_S(c) digitalWrite(TFT_DC,LOW); digitalWrite(TFT_CS_SECONDARY,LOW); SPI_BITBANG_WRITE(c); digitalWrite(TFT_CS_SECONDARY,HIGH)
    #define DATA_S(d) digitalWrite(TFT_DC,HIGH); digitalWrite(TFT_CS_SECONDARY,LOW); SPI_BITBANG_WRITE(d); digitalWrite(TFT_CS_SECONDARY,HIGH)

    // Initialize Master IC (Waveshare lines 163-189)
    CMD_M(0x4D); DATA_M(0x55);
    CMD_M(0xA6); DATA_M(0x38);
    CMD_M(0xB4); DATA_M(0x5D);
    CMD_M(0xB6); DATA_M(0x80);
    CMD_M(0xB7); DATA_M(0x00);
    CMD_M(0xF7); DATA_M(0x02);

    // Initialize Slave IC (same sequence)
    CMD_S(0x4D); DATA_S(0x55);
    CMD_S(0xA6); DATA_S(0x38);
    CMD_S(0xB4); DATA_S(0x5D);
    CMD_S(0xB6); DATA_S(0x80);
    CMD_S(0xB7); DATA_S(0x00);
    CMD_S(0xF7); DATA_S(0x02);

    // CRITICAL: Slave-specific command (Waveshare lines 181-182)
    CMD_S(0xAE); DATA_S(0xA0);

    // Panel settings to both ICs (Waveshare lines 184-218)
    CMD_M(0xE0); DATA_M(0x01);
    CMD_M(0x00); DATA_M(0x9F); DATA_M(0x0D);  // Panel setting
    CMD_M(0x06); DATA_M(0x57); DATA_M(0x24); DATA_M(0x28); DATA_M(0x32); DATA_M(0x08); DATA_M(0x48);  // Boost (6 bytes!)
    CMD_M(0x61); DATA_M(0x02); DATA_M(0xA8); DATA_M(0x01); DATA_M(0xE0);  // Resolution 680×480
    CMD_M(0x62); DATA_M(0x00); DATA_M(0x00); DATA_M(0x00); DATA_M(0x00);  // Source & gate start
    CMD_M(0x60); DATA_M(0x31);  // TCON
    CMD_M(0x50); DATA_M(0x97);  // VCOM
    CMD_M(0xE8); DATA_M(0x01);

    CMD_S(0xE0); DATA_S(0x01);
    CMD_S(0x00); DATA_S(0x9F); DATA_S(0x0D);
    CMD_S(0x06); DATA_S(0x57); DATA_S(0x24); DATA_S(0x28); DATA_S(0x32); DATA_S(0x08); DATA_S(0x48);
    CMD_S(0x61); DATA_S(0x02); DATA_S(0xA8); DATA_S(0x01); DATA_S(0xE0);
    CMD_S(0x62); DATA_S(0x00); DATA_S(0x00); DATA_S(0x00); DATA_S(0x00);
    CMD_S(0x60); DATA_S(0x31);
    CMD_S(0x50); DATA_S(0x97);
    CMD_S(0xE8); DATA_S(0x01);

    // Power ON both ICs (Waveshare lines 220-222)
    CMD_M(0x04);
    CMD_S(0x04);

    delay(200);  // CRITICAL: 200ms delay before BUSY check

#ifdef TFT_BUSY
    {
        unsigned long _busy_start = millis();
        while (!digitalRead(TFT_BUSY)) {
            if (millis() - _busy_start > 25000)
                break;
            delay(10);
        }
        delay(10);
    }
#endif

    #undef CMD_M
    #undef DATA_M
    #undef CMD_S
    #undef DATA_S
}
