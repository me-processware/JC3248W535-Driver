/**
 * JC3248W535 Touch Driver
 * Minimal driver for AXS15231B I2C touch controller
 * 
 * Author: Processware
 * License: MIT
 */

#ifndef JC3248W535_TOUCH_H
#define JC3248W535_TOUCH_H

#include <Arduino.h>
#include <Wire.h>

// Touch hardware configuration
#define JC3248_TOUCH_SDA   4
#define JC3248_TOUCH_SCL   8
#define JC3248_TOUCH_INT   3
#define JC3248_TOUCH_ADDR  0x3B

// Touch point structure
struct TouchPoint {
    uint16_t x;
    uint16_t y;
    bool touched;
};

class JC3248W535_Touch {
public:
    JC3248W535_Touch();
    
    // Initialize touch controller
    bool begin();
    
    // Set display rotation and logical dimensions for touch coordinate mapping
    void setRotation(uint8_t rotation, int16_t logicalWidth, int16_t logicalHeight);
    
    // Read touch state
    // Returns true if touch detected, fills point with coordinates
    bool read(TouchPoint &point);
    
    // Check if currently touched (non-blocking)
    bool isTouched();
    
    // Get last touch point
    TouchPoint getLastTouch() { return lastTouch; }
    
private:
    TouchPoint lastTouch;
    uint8_t currentRotation = 0;
    int16_t logicalWidth = 320;
    int16_t logicalHeight = 480;
    
    // AXS15231B touch read command
    static const uint8_t AXS_READ_TOUCHPAD[11];
};

#endif // JC3248W535_TOUCH_H
