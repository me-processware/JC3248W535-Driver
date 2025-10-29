/**
 * JC3248W535 Complete Driver
 * Single include file for display and touch
 * 
 * Author: Processware
 * License: MIT
 * 
 * Usage:
 *   #include <JC3248W535.h>
 *   
 *   JC3248W535_Display display;
 *   JC3248W535_Touch touch;
 *   
 *   void setup() {
 *     display.begin();
 *     touch.begin();
 *   }
 */

#ifndef JC3248W535_H
#define JC3248W535_H

#include "JC3248W535_Display.h"
#include "JC3248W535_Touch.h"

// Hardware pin definitions (for reference)
// Display QSPI:
//   CS: GPIO 45, CLK: GPIO 47
//   Data: GPIO 21, 48, 40, 39
//   Backlight: GPIO 1
//
// Touch I2C:
//   SDA: GPIO 4, SCL: GPIO 8
//   INT: GPIO 3, Address: 0x3B

#endif // JC3248W535_H
