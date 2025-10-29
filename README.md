# JC3248W535 Driver

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform](https://img.shields.io/badge/platform-ESP32--S3-blue.svg)](https://www.espressif.com/en/products/socs/esp32-s3)

Clean, minimal driver for the **JC3248W535** 3.5" IPS touchscreen display module with ESP32-S3.

![JC3248W535](https://via.placeholder.com/800x400/1a1a1a/ffffff?text=JC3248W535+3.5%22+Touch+Display)

## Features

- ✅ **Simple API** - Easy to use, minimal code required
- ✅ **QSPI Display** - Fast 40MHz quad SPI interface
- ✅ **Capacitive Touch** - I2C touch controller with coordinate mapping
- ✅ **Arduino_GFX** - Full graphics library support
- ✅ **Well Documented** - Complete API reference and examples
- ✅ **Tested** - Working on real hardware

## Hardware Specifications

| Specification | Value |
|--------------|-------|
| Display Size | 3.5 inches |
| Resolution | 320 × 480 pixels |
| Display Type | IPS LCD |
| Touch Type | Capacitive (5-point) |
| Controller | AXS15231B |
| MCU | ESP32-S3-WROOM-1 |
| Flash | 16MB |
| PSRAM | 8MB |
| Interface | QSPI (display), I2C (touch) |

## Quick Start

### Installation

#### PlatformIO

Add to your `platformio.ini`:

```ini
lib_deps = 
    moononournation/GFX Library for Arduino@^1.4.9
    https://github.com/yourusername/JC3248W535-Driver
```

#### Arduino IDE

1. Download this repository as ZIP
2. In Arduino IDE: Sketch → Include Library → Add .ZIP Library
3. Select the downloaded ZIP file

### Minimal Example

```cpp
#include <JC3248W535.h>

// Default: Portrait mode (320x480)
JC3248W535_Display display;
JC3248W535_Touch touch;

void setup() {
  Serial.begin(115200);
  
  // Initialize display
  if (!display.begin()) {
    Serial.println("Display init failed!");
    while(1);
  }
  
  // Initialize touch
  touch.begin();
  
  // Get canvas for drawing
  auto gfx = display.getCanvas();
  
  // Draw something
  gfx->fillScreen(WHITE);
  gfx->setTextColor(BLACK);
  gfx->setTextSize(3);
  gfx->setCursor(50, 200);
  gfx->print("Hello World!");
  
  // Flush to display
  display.flush();
}

void loop() {
  TouchPoint point;
  
  if (touch.read(point)) {
    Serial.print("Touch: ");
    Serial.print(point.x);
    Serial.print(", ");
    Serial.println(point.y);
  }
  
  delay(10);
}
```

## API Reference

### Display Class

```cpp
// Constructor with optional rotation
JC3248W535_Display display(rotation);  // rotation: 0-3 (default: 0)

display.begin()              // Initialize display
display.getCanvas()          // Get Arduino_Canvas for drawing
display.flush()              // Update display (required after drawing!)
display.backlightOn()        // Turn backlight on
display.backlightOff()       // Turn backlight off
display.width()              // Get width (depends on rotation)
display.height()             // Get height (depends on rotation)
display.getRotation()        // Get current rotation (0-3)
```

### Touch Class

```cpp
JC3248W535_Touch touch;

touch.begin()                // Initialize touch controller
touch.read(point)            // Read touch, returns true if touched
touch.isTouched()            // Check if currently touched
touch.getLastTouch()         // Get last touch coordinates
```

### TouchPoint Structure

```cpp
struct TouchPoint {
    uint16_t x;        // X coordinate (0-319)
    uint16_t y;        // Y coordinate (0-479)
    bool touched;      // True if touch detected
};
```

## Display Rotation

The driver supports 4 rotation modes:

```cpp
// Portrait mode (default)
JC3248W535_Display display(ROTATION_0);    // 320x480

// Landscape mode (90° clockwise)
JC3248W535_Display display(ROTATION_90);   // 480x320

// Portrait inverted (180°)
JC3248W535_Display display(ROTATION_180);  // 320x480

// Landscape inverted (270° clockwise)
JC3248W535_Display display(ROTATION_270);  // 480x320
```

**Note**: The `width()` and `height()` functions automatically return the correct dimensions based on rotation.

## Drawing Functions

This driver uses Arduino_GFX for drawing. Common functions:

```cpp
auto gfx = display.getCanvas();

// Basic shapes
gfx->fillScreen(color);
gfx->drawPixel(x, y, color);
gfx->drawLine(x0, y0, x1, y1, color);
gfx->drawRect(x, y, w, h, color);
gfx->fillRect(x, y, w, h, color);
gfx->drawCircle(x, y, r, color);
gfx->fillCircle(x, y, r, color);

// Text
gfx->setTextColor(color);
gfx->setTextSize(size);
gfx->setCursor(x, y);
gfx->print("text");

// Always flush after drawing!
display.flush();
```

### Color Constants (RGB565)

```cpp
BLACK       0x0000
WHITE       0xFFFF
RED         0xF800
GREEN       0x07E0
BLUE        0x001F
YELLOW      0xFFE0
CYAN        0x07FF
MAGENTA     0xF81F
```

## Pin Configuration

### Display (QSPI)
- **CS**: GPIO 45
- **CLK**: GPIO 47
- **Data 0-3**: GPIO 21, 48, 40, 39
- **Backlight**: GPIO 1

### Touch (I2C)
- **SDA**: GPIO 4
- **SCL**: GPIO 8
- **INT**: GPIO 3
- **Address**: 0x3B

## PlatformIO Configuration

Required settings in `platformio.ini`:

```ini
[env:jc3248w535]
platform = espressif32
board = esp32-s3-devkitc-1
framework = arduino

board_build.arduino.memory_type = qio_opi
board_build.flash_mode = dio
board_build.f_flash = 80000000L
board_build.f_cpu = 240000000L

build_flags = 
    -DARDUINO_USB_CDC_ON_BOOT=1
    -DBOARD_HAS_PSRAM
    -mfix-esp32-psram-cache-issue
    -DARDUINO_USB_MODE=1

upload_speed = 921600
monitor_speed = 115200

lib_deps = 
    moononournation/GFX Library for Arduino@^1.4.9
```

## Examples

### Basic Example
Simple "Hello World" with touch detection.

See: [`examples/Basic/Basic.ino`](examples/Basic/Basic.ino)

### Touch Test
Visualize touch coordinates and test touch accuracy.

See: [`examples/TouchTest/TouchTest.ino`](examples/TouchTest/TouchTest.ino)

### Drawing Demo
Interactive drawing application with color selection.

See: [`examples/DrawingDemo/DrawingDemo.ino`](examples/DrawingDemo/DrawingDemo.ino)

### Rotation
Demonstrates all 4 rotation modes with visual test pattern.

See: [`examples/Rotation/Rotation.ino`](examples/Rotation/Rotation.ino)

## Important Notes

### PSRAM is REQUIRED

The display **will not work** without PSRAM enabled. The 320×480 canvas buffer requires ~300KB of RAM which must be allocated in PSRAM.

**Symptoms without PSRAM:**
- Display shows only backlight (blank white screen)
- `display.begin()` returns false
- Serial monitor shows PSRAM error message

**Solution:** Ensure these settings in `platformio.ini`:
```ini
board_build.arduino.memory_type = qio_opi
build_flags = -DBOARD_HAS_PSRAM
```

### Touch Performance

The AXS15231B touch controller is **single-touch only** and has a polling-based interface:

- **Single touch**: Only one finger detected at a time
- **Polling rate**: ~100-200Hz depending on I2C speed
- **For smooth drawing**: Use `delay(1)` in your loop, not `delay(10)` or higher
- **I2C speed**: Driver uses 400kHz (fast mode) for better response

**Example for smooth drawing:**
```cpp
void loop() {
  TouchPoint point;
  if (touch.read(point)) {
    // Draw immediately
    gfx->fillCircle(point.x, point.y, 3, RED);
    display.flush();
  }
  delay(1);  // Fast polling for smooth lines
}
```

## Troubleshooting

### Display shows nothing (blank/white screen)
- **PSRAM not enabled** - See "PSRAM is REQUIRED" section above
- Ensure you call `display.flush()` after drawing
- Check backlight is on: `display.backlightOn()`

### Touch not working
- Run I2C scanner to verify device at 0x3B
- Check SDA=GPIO4, SCL=GPIO8 (not reversed)
- Ensure `touch.begin()` returns true

### Touch is slow/choppy when drawing
- Reduce `delay()` in your loop to `delay(1)`
- Remove extra delays after drawing
- Touch is single-point only, not multi-touch
- Polling rate is limited by I2C speed (~100-200Hz)

### Compilation errors
- Update Arduino_GFX to latest version (1.4.9+)
- Verify ESP32 Arduino core is up to date
- Check all required build flags are set

### Out of memory
- Enable PSRAM: `-DBOARD_HAS_PSRAM`
- The canvas buffer requires ~300KB RAM

## Technical Details

### Memory Requirements
- **Flash**: ~120KB (driver + Arduino_GFX)
- **RAM**: ~301KB (canvas buffer in PSRAM)

### Performance
- **QSPI Clock**: 40MHz
- **Bandwidth**: ~160Mbps
- **Frame Rate**: Limited by flush() speed

### Touch Protocol
- **Controller**: AXS15231B
- **Command**: `{0xb5, 0xab, 0xa5, 0x5a, 0x0, 0x0, 0x0, 0x8}`
- **Response**: 8 bytes with 12-bit coordinates

## Contributing

Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request

## License

MIT License - see [LICENSE](LICENSE) file for details.

## Credits

- **Author**: Processware
- **Display Controller**: AXS15231B by Shenzhen Jingcai Intelligent
- **Graphics Library**: [Arduino_GFX](https://github.com/moononournation/Arduino_GFX) by moononournation

## Support

- **Issues**: [GitHub Issues](https://github.com/yourusername/JC3248W535-Driver/issues)
- **Discussions**: [GitHub Discussions](https://github.com/yourusername/JC3248W535-Driver/discussions)

## Changelog

### v1.0.0 (2025-10-29)
- Initial release
- Display driver with QSPI support
- Touch driver with I2C support
- Complete documentation
- Example sketches

---

**Made with ❤️ by Processware**
