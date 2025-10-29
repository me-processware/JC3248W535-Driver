/**
 * Drawing Demo for JC3248W535 Driver
 * 
 * Interactive drawing application with:
 * - Color palette selection
 * - Drawing canvas
 * - Clear button
 * - Brush size control
 * 
 * Author: Processware
 * License: MIT
 */

#include <JC3248W535.h>

JC3248W535_Display display;
JC3248W535_Touch touch;

// Color palette
const uint16_t colors[] = {RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, BLACK, WHITE};
const int numColors = 8;
const int colorBoxSize = 35;
const int colorBoxY = 10;

// Current drawing color and brush size
uint16_t currentColor = RED;
int brushSize = 3;

// Clear button
const int clearBtnX = 250;
const int clearBtnY = 420;
const int clearBtnW = 60;
const int clearBtnH = 50;

void drawUI() {
  auto gfx = display.getCanvas();
  
  // Background
  gfx->fillScreen(WHITE);
  
  // Color palette
  for (int i = 0; i < numColors; i++) {
    int x = 10 + i * (colorBoxSize + 5);
    gfx->fillRect(x, colorBoxY, colorBoxSize, colorBoxSize, colors[i]);
    gfx->drawRect(x, colorBoxY, colorBoxSize, colorBoxSize, BLACK);
    
    // Highlight selected color
    if (colors[i] == currentColor) {
      gfx->drawRect(x - 2, colorBoxY - 2, colorBoxSize + 4, colorBoxSize + 4, GREEN);
      gfx->drawRect(x - 3, colorBoxY - 3, colorBoxSize + 6, colorBoxSize + 6, GREEN);
    }
  }
  
  // Drawing area border
  gfx->drawRect(5, 60, 310, 350, BLACK);
  
  // Clear button
  gfx->fillRect(clearBtnX, clearBtnY, clearBtnW, clearBtnH, RED);
  gfx->setTextColor(WHITE);
  gfx->setTextSize(2);
  gfx->setCursor(clearBtnX + 8, clearBtnY + 17);
  gfx->print("Clear");
  
  // Instructions
  gfx->setTextColor(BLACK);
  gfx->setTextSize(1);
  gfx->setCursor(10, 425);
  gfx->print("Touch colors to");
  gfx->setCursor(10, 440);
  gfx->print("change brush");
  
  display.flush();
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("JC3248W535 Drawing Demo");
  Serial.println("=======================");
  
  // Initialize display
  if (!display.begin()) {
    Serial.println("Display init failed!");
    while(1) delay(1000);
  }
  
  // Initialize touch
  if (!touch.begin()) {
    Serial.println("Touch init failed!");
  } else {
    // Pass display rotation to touch driver for coordinate mapping
    display.setTouchRotation(&touch);
  }
  
  // Draw UI
  drawUI();
  
  Serial.println("Ready to draw!");
  Serial.println("- Touch color boxes to change color");
  Serial.println("- Draw in the canvas area");
  Serial.println("- Touch Clear to reset");
}

void loop() {
  TouchPoint point;
  
  if (touch.read(point)) {
    auto gfx = display.getCanvas();
    bool needsRedraw = false;
    
    // Check color palette
    if (point.y >= colorBoxY && point.y <= colorBoxY + colorBoxSize) {
      for (int i = 0; i < numColors; i++) {
        int x = 10 + i * (colorBoxSize + 5);
        if (point.x >= x && point.x <= x + colorBoxSize) {
          currentColor = colors[i];
          Serial.print("Color changed to: ");
          Serial.println(i);
          needsRedraw = true;
          delay(150);
          break;
        }
      }
    }
    
    // Check clear button
    else if (point.x >= clearBtnX && point.x <= clearBtnX + clearBtnW &&
             point.y >= clearBtnY && point.y <= clearBtnY + clearBtnH) {
      Serial.println("Canvas cleared");
      needsRedraw = true;
      delay(150);
    }
    
    // Drawing area
    else if (point.x >= 5 && point.x <= 315 &&
             point.y >= 60 && point.y <= 410) {
      // Draw with current color and brush size
      gfx->fillCircle(point.x, point.y, brushSize, currentColor);
      display.flush();
    }
    
    // Redraw UI if needed
    if (needsRedraw) {
      drawUI();
    }
  }
  
  // Fast polling for smooth drawing
  delay(1);
}
