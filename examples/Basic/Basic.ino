/**
 * Basic Example for JC3248W535 Driver
 * 
 * This example demonstrates the minimal code needed to:
 * - Initialize the display
 * - Draw text and shapes
 * - Read touch input
 * 
 * Author: Processware
 * License: MIT
 */

#include <JC3248W535.h>

JC3248W535_Display display;
JC3248W535_Touch touch;
Arduino_Canvas *gfx; // Global pointer to the canvas

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("JC3248W535 Basic Example");
  Serial.println("========================");
  
  // Initialize display
  Serial.print("Initializing display... ");
  if (!display.begin()) {
    Serial.println("FAILED!");
    while(1) delay(1000);
  }
  Serial.println("OK");
  
  // Initialize touch
  Serial.print("Initializing touch... ");
  if (!touch.begin()) {
    Serial.println("FAILED!");
  } else {
    Serial.println("OK");
    // Pass display rotation to touch driver for coordinate mapping
    display.setTouchRotation(&touch);
  }
  
  // Get canvas for drawing
  gfx = display.getCanvas();
  
  // Draw welcome screen
  gfx->fillScreen(WHITE);
  
  // Title
  gfx->setTextColor(BLACK);
  gfx->setTextSize(3);
  gfx->setCursor(40, 100);
  gfx->print("JC3248W535");
  
  // Subtitle
  gfx->setTextSize(2);
  gfx->setCursor(80, 150);
  gfx->print("Touch Demo");
  
  // Draw a rectangle
  gfx->drawRect(50, 200, 220, 100, RED);
  
  // Instructions
  gfx->setTextSize(1);
  gfx->setTextColor(BLUE);
  gfx->setCursor(60, 230);
  gfx->print("Touch anywhere on screen");
  gfx->setCursor(80, 250);
  gfx->print("to draw a circle");
  
  // Flush to display
  display.flush();
  
  Serial.println("\nReady! Touch the screen.");
  Serial.println("========================\n");
}

void loop() {
  TouchPoint point;
  
  // Check for touch
  if (touch.read(point)) {
    Serial.print("Touch detected at X: ");
    Serial.print(point.x);
    Serial.print(", Y: ");
    Serial.println(point.y);
    
    // Draw a circle where touched
    gfx->fillCircle(point.x, point.y, 5, RED);
    display.flush();
    
    // Small delay to debounce
    delay(10);
  }
  
  // No delay needed - touch polling is fast enough
  delay(1);
}
