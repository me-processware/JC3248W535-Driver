/**
 * JC3248W535 Display Driver
 * Minimal driver for AXS15231B QSPI display controller
 * 
 * Author: Processware
 * License: MIT
 */

#ifndef JC3248W535_DISPLAY_H
#define JC3248W535_DISPLAY_H

#include <Arduino.h>
#include <Arduino_GFX_Library.h>

// Forward declaration to resolve circular dependency with JC3248W535_Touch
class JC3248W535_Touch;

// Display hardware configuration
#define JC3248_LCD_CS      45
#define JC3248_LCD_SCLK    47
#define JC3248_LCD_SDIO0   21
#define JC3248_LCD_SDIO1   48
#define JC3248_LCD_SDIO2   40
#define JC3248_LCD_SDIO3   39
#define JC3248_LCD_RST     -1
#define JC3248_TFT_BL      1

#define JC3248_LCD_WIDTH   320
#define JC3248_LCD_HEIGHT  480

// Display rotation modes
enum DisplayRotation {
    ROTATION_0   = 0,  // Portrait (320x480)
    ROTATION_90  = 1,  // Landscape (480x320)
    ROTATION_180 = 2,  // Portrait inverted (320x480)
    ROTATION_270 = 3   // Landscape inverted (480x320)
};

class JC3248W535_Display {
public:
    JC3248W535_Display();
    ~JC3248W535_Display();
    
    // Initialize display
    bool begin();
    
    // Get display object for drawing
    Arduino_Canvas* getCanvas() { return canvas; }
    
    // Backlight control
    void backlightOn();
    void backlightOff();
    void setBacklight(uint8_t brightness); // 0-255
    
    // Display dimensions (adjusted for rotation)
    int16_t width() { return canvas ? canvas->width() : JC3248_LCD_WIDTH; }
    int16_t height() { return canvas ? canvas->height() : JC3248_LCD_HEIGHT; }
    
    // Get rotation
    uint8_t getRotation() { return canvas ? canvas->getRotation() : ROTATION_0; }
    
    // Set touch rotation
    void setTouchRotation(JC3248W535_Touch *touchDriver);
    
    // Set display rotation
    void setRotation(uint8_t rotation);
    
    // Flush canvas to display (REQUIRED after drawing!)
    void flush() { if (canvas) canvas->flush(); }
    
private:
    Arduino_DataBus *bus;
    Arduino_GFX *output_display;
    Arduino_Canvas *canvas;
};

#endif // JC3248W535_DISPLAY_H
