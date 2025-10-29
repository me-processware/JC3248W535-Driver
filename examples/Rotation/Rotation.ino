/**
 * Rotation Example for JC3248W535 Driver
 * 
 * This example demonstrates how to use different display orientations:
 * - Portrait (320x480) - Default
 * - Landscape (480x320) - 90° rotation
 * - Portrait Inverted (320x480) - 180° rotation
 * - Landscape Inverted (480x320) - 270° rotation
 * 
 * Author: Processware
 * License: MIT
 */

#include <JC3248W535.h>

// Choose your rotation mode:
// ROTATION_0   = Portrait (320x480)
// ROTATION_90  = Landscape (480x320)
// ROTATION_180 = Portrait inverted (320x480)
// ROTATION_270 = Landscape inverted (480x320)

JC3248W535_Display display;
JC3248W535_Touch touch;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("JC3248W535 Rotation Example");
  Serial.println("===========================");
  
  // Initialize display with rotation
  if (!display.begin()) {
    Serial.println("Display init failed!");
    while(1) delay(1000);
  }
  
  // Initialize touch
  touch.begin();
  
  // Set display rotation
  display.setRotation(ROTATION_90); // Landscape mode
  
  // Pass display rotation to touch driver for coordinate mapping
  display.setTouchRotation(&touch);
  
  // Print display info
  Serial.print("Rotation: ");
  Serial.println(display.getRotation());
  Serial.print("Display size: ");
  Serial.print(display.width());
  Serial.print(" x ");
  Serial.println(display.height());
  
  // Draw test pattern
  drawTestPattern();
  
  Serial.println("\nTouch the corners to verify orientation");
}

void drawTestPattern() {
  auto gfx = display.getCanvas();
  
  // Clear screen
  gfx->fillScreen(WHITE);
  
  // Title
  gfx->setTextColor(BLACK);
  gfx->setTextSize(3);
  gfx->setCursor(10, 10);
  gfx->print("Rotation Test");
  
  // Display dimensions
  gfx->setTextSize(2);
  gfx->setCursor(10, 50);
  gfx->print(display.width());
  gfx->print(" x ");
  gfx->print(display.height());
  
  // Draw corner markers
  int w = display.width();
  int h = display.height();
  
  // Top-left (RED)
  gfx->fillCircle(20, 100, 15, RED);
  gfx->setTextColor(BLACK);
  gfx->setTextSize(1);
  gfx->setCursor(40, 95);
  gfx->print("TOP-LEFT");
  
  // Top-right (GREEN)
  gfx->fillCircle(w - 20, 100, 15, GREEN);
  gfx->setCursor(w - 100, 95);
  gfx->print("TOP-RIGHT");
  
  // Bottom-left (BLUE)
  gfx->fillCircle(20, h - 20, 15, BLUE);
  gfx->setCursor(40, h - 25);
  gfx->print("BOTTOM-LEFT");
  
  // Bottom-right (YELLOW)
  gfx->fillCircle(w - 20, h - 20, 15, YELLOW);
  gfx->setCursor(w - 120, h - 25);
  gfx->print("BOTTOM-RIGHT");
  
  // Center crosshair
  gfx->drawLine(w/2 - 20, h/2, w/2 + 20, h/2, BLACK);
  gfx->drawLine(w/2, h/2 - 20, w/2, h/2 + 20, BLACK);
  gfx->setCursor(w/2 - 30, h/2 + 30);
  gfx->print("CENTER");
  
  // Instructions
  gfx->setTextSize(1);
  gfx->setCursor(10, h - 50);
  gfx->print("Touch corners to verify");
  gfx->setCursor(10, h - 35);
  gfx->print("orientation is correct");
  
  display.flush();
}

void loop() {
  TouchPoint point;
  
  if (touch.read(point)) {
    Serial.print("Touch: X=");
    Serial.print(point.x);
    Serial.print(" Y=");
    Serial.println(point.y);
    
    // Draw touch point
    auto gfx = display.getCanvas();
    gfx->fillCircle(point.x, point.y, 3, MAGENTA);
    display.flush();
  }
  
  // Fast polling for smooth drawing
  delay(1);
}
