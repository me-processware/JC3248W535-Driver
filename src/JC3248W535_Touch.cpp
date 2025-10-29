/**
 * JC3248W535 Touch Driver Implementation
 * 
 * Author: Processware
 * License: MIT
 */

#include "JC3248W535_Touch.h"

// AXS15231B touch read command sequence
const uint8_t JC3248W535_Touch::AXS_READ_TOUCHPAD[11] = {
    0xb5, 0xab, 0xa5, 0x5a, 0x0, 0x0, 0x0, 0x8
};

JC3248W535_Touch::JC3248W535_Touch() {
    lastTouch.x = 0;
    lastTouch.y = 0;
    lastTouch.touched = false;
}

bool JC3248W535_Touch::begin() {
    // Initialize I2C with fast mode (400kHz) for better touch response
    Wire.begin(JC3248_TOUCH_SDA, JC3248_TOUCH_SCL);
    Wire.setClock(400000);  // 400kHz I2C speed
    
    // Initialize interrupt pin (optional)
    pinMode(JC3248_TOUCH_INT, INPUT);
    
    // Test I2C connection
    Wire.beginTransmission(JC3248_TOUCH_ADDR);
    uint8_t error = Wire.endTransmission();
    
    return (error == 0);
}

bool JC3248W535_Touch::read(TouchPoint &point) {
    uint8_t data[8] = {0};
    
    // Send touch read command
    Wire.beginTransmission(JC3248_TOUCH_ADDR);
    Wire.write(AXS_READ_TOUCHPAD, sizeof(AXS_READ_TOUCHPAD));
    if (Wire.endTransmission() != 0) {
        point.touched = false;
        return false;
    }
    
    // Small delay for controller to process (reduced for faster response)
    delayMicroseconds(50);
    
    // Read 8 bytes response
    Wire.requestFrom(JC3248_TOUCH_ADDR, (uint8_t)8);
    int i = 0;
    while (Wire.available() && i < 8) {
        data[i++] = Wire.read();
    }
    
    if (i < 8) {
        point.touched = false;
        return false;
    }
    
    // Check if touch detected
    // Touch detected when: data[0] == 0 AND data[1] != 0
    if (data[0] != 0 || data[1] == 0) {
        point.touched = false;
        lastTouch.touched = false;
        return false;
    }
    
    // Decode coordinates (12-bit values)
    uint16_t raw_x = ((data[2] & 0x0F) << 8) | data[3];
    uint16_t raw_y = ((data[4] & 0x0F) << 8) | data[5];
    
    // The raw coordinates are 0-4095, but the controller seems to return
    // values already scaled to the panel's physical resolution (320x480).
    uint16_t x = raw_x;
    uint16_t y = raw_y;
    
    // Apply rotation to touch coordinates
    // The touch controller's physical axes are fixed. We need to map them
    // to the display's current logical orientation.
    switch (currentRotation) {
        case 1: // ROTATION_90 (Landscape)
            point.x = y;
            point.y = 320 - x;
            break;
        case 2: // ROTATION_180 (Portrait Inverted)
            point.x = 320 - x;
            point.y = 480 - y;
            break;
        case 3: // ROTATION_270 (Landscape Inverted)
            point.x = 480 - y;
            point.y = x;
            break;
        case 0: // ROTATION_0 (Portrait)
        default:
            point.x = x;
            point.y = y;
            break;
    }
    
// Clamp to display bounds (using logical dimensions)
if (point.x >= logicalWidth) point.x = logicalWidth - 1;
if (point.y >= logicalHeight) point.y = logicalHeight - 1;
    
    point.touched = true;
    lastTouch = point;
    
    return true;
}

bool JC3248W535_Touch::isTouched() {
    TouchPoint point;
    return read(point);
}

// Function to set display rotation and logical dimensions
void JC3248W535_Touch::setRotation(uint8_t rotation, int16_t logicalWidth, int16_t logicalHeight) {
    currentRotation = rotation;
    this->logicalWidth = logicalWidth;
    this->logicalHeight = logicalHeight;
}
