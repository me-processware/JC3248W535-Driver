/**
 * Touch Test Example for JC3248W535 Driver
 * 
 * This example helps test and calibrate touch functionality:
 * - Displays touch coordinates in real-time
 * - Shows touch trail for accuracy testing
 * - Clear button to reset screen
 * 
 * Author: Processware
 * License: MIT
 */

#include <JC3248W535.h>

JC3248W535_Display display;
JC3248W535_Touch touch;

// Clear button area
const int CLEAR_BTN_X = 220;
const int CLEAR_BTN_Y = 10;
const int CLEAR_BTN_W = 90;
const int CLEAR_BTN_H = 40;

void drawUI() {
  auto gfx = display.getCanvas();
  
  // Clear screen
  gfx->fillScreen(WHITE);
  
  // Title bar
  gfx->fillRect(0, 0, 320, 60, BLUE);
  gfx->setTextColor(WHITE);
  gfx->setTextSize(2);
  gfx->setCursor(10, 20);
  gfx->print("Touch Test");
  
  // Clear button
  gfx->fillRect(CLEAR_BTN_X, CLEAR_BTN_Y, CLEAR_BTN_W, CLEAR_BTN_H, RED);
  gfx->setTextColor(WHITE);
  gfx->setTextSize(2);
  gfx->setCursor(CLEAR_BTN_X + 15, CLEAR_BTN_Y + 12);
  gfx->print("Clear");
  
  // Instructions
  gfx->setTextColor(BLACK);
  gfx->setTextSize(1);
  gfx->setCursor(10, 70);
  gfx->print("Touch anywhere to draw");
  gfx->setCursor(10, 85);
  gfx->print("Coordinates shown in serial monitor");
  
  // Test area border
  gfx->drawRect(5, 100, 310, 375, BLACK);
  
  display.flush();
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n========================================");
  Serial.println("JC3248W535 Touch Test");
  Serial.println("========================================");
  
  // Initialize display
  if (!display.begin()) {
    Serial.println("ERROR: Display init failed!");
    while(1) delay(1000);
  }
  Serial.println("Display: OK");
  
  // Initialize touch
  if (!touch.begin()) {
    Serial.println("ERROR: Touch init failed!");
  } else {
    Serial.println("Touch: OK");
    // Pass display rotation to touch driver for coordinate mapping
    display.setTouchRotation(&touch);
  }
  
  // Draw UI
  drawUI();
  
  Serial.println("\nTouch the screen to test");
  Serial.println("Format: X, Y");
  Serial.println("========================================\n");
}

void loop() {
  TouchPoint point;
  
  if (touch.read(point)) {
    // Print coordinates to serial
    Serial.print(point.x);
    Serial.print(", ");
    Serial.println(point.y);
    
    auto gfx = display.getCanvas();
    
    // Check if clear button was pressed
    if (point.x >= CLEAR_BTN_X && point.x <= CLEAR_BTN_X + CLEAR_BTN_W &&
        point.y >= CLEAR_BTN_Y && point.y <= CLEAR_BTN_Y + CLEAR_BTN_H) {
      
      Serial.println("--- Screen Cleared ---");
      drawUI();
      delay(150);
      
    } else {
      // Draw touch point
      gfx->fillCircle(point.x, point.y, 3, BLUE);
      
      // Draw crosshair for precision
      gfx->drawLine(point.x - 10, point.y, point.x + 10, point.y, RED);
      gfx->drawLine(point.x, point.y - 10, point.x, point.y + 10, RED);
      
      display.flush();
    }
  }
  
  // Fast polling for smooth drawing
  delay(1);
}
