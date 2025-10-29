/**
 * JC3248W535 Display Driver Implementation
 * 
 * Author: Processware
 * License: MIT
 */

#include "JC3248W535_Display.h"
#include "JC3248W535_Touch.h" // Required for setTouchRotation implementation

JC3248W535_Display::JC3248W535_Display() 
    : bus(nullptr), output_display(nullptr), canvas(nullptr) {
}

JC3248W535_Display::~JC3248W535_Display() {
    if (canvas) delete canvas;
    if (output_display) delete output_display;
    if (bus) delete bus;
}

bool JC3248W535_Display::begin() {
    // Check for PSRAM (REQUIRED for canvas buffer!)
    if (!psramFound()) {
        Serial.println("ERROR: PSRAM not found!");
        Serial.println("PSRAM is required for the display canvas buffer.");
        Serial.println("Add to platformio.ini:");
        Serial.println("  board_build.arduino.memory_type = qio_opi");
        Serial.println("  build_flags = -DBOARD_HAS_PSRAM");
        return false;
    }
    
    // Initialize backlight pin
    pinMode(JC3248_TFT_BL, OUTPUT);
    digitalWrite(JC3248_TFT_BL, HIGH);
    
    // Create QSPI bus
    bus = new Arduino_ESP32QSPI(
        JC3248_LCD_CS,
        JC3248_LCD_SCLK,
        JC3248_LCD_SDIO0,
        JC3248_LCD_SDIO1,
        JC3248_LCD_SDIO2,
        JC3248_LCD_SDIO3
    );
    
    if (!bus) return false;
    
    // Create display driver (AXS15231B)
    output_display = new Arduino_AXS15231B(
        bus,
        JC3248_LCD_RST,
        ROTATION_0,  // Always initialize to default rotation
        false,  // IPS
        JC3248_LCD_WIDTH,
        JC3248_LCD_HEIGHT,
        0, 0, 0, 0  // Offsets
    );
    
    if (!output_display) return false;
    
    // Create canvas buffer (REQUIRED for QSPI!)
    // Always create canvas with physical dimensions (320x480)
    canvas = new Arduino_Canvas(
        JC3248_LCD_WIDTH,
        JC3248_LCD_HEIGHT,
        output_display
    );
    
    if (!canvas) return false;
    
    // Initialize display
    if (!canvas->begin()) {
        return false;
    }
    
    return true;
}

// Function to set touch rotation after touch driver is initialized
void JC3248W535_Display::setTouchRotation(JC3248W535_Touch *touchDriver) {
    if (touchDriver && canvas) {
        touchDriver->setRotation(canvas->getRotation(), canvas->width(), canvas->height());
    }
}

// Function to set display rotation
void JC3248W535_Display::setRotation(uint8_t rotation) {
    if (canvas) {
        canvas->setRotation(rotation);
    }
}

void JC3248W535_Display::backlightOn() {
    digitalWrite(JC3248_TFT_BL, HIGH);
}

void JC3248W535_Display::backlightOff() {
    digitalWrite(JC3248_TFT_BL, LOW);
}

void JC3248W535_Display::setBacklight(uint8_t brightness) {
    // Simple on/off for now (PWM could be added if needed)
    if (brightness > 127) {
        backlightOn();
    } else {
        backlightOff();
    }
}
