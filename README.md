# I2C Functions Library ^V02.00.01^

![GitHub release (latest by date)](https://img.shields.io/github/v/release/akkoyun/I2C_Functions) ![arduino-library-badge](https://www.ardu-badge.com/badge/I2C_Functions.svg?) ![GitHub stars](https://img.shields.io/github/stars/akkoyun/I2C_Functions?style=flat&logo=github) ![PlatformIO Registry](https://badges.registry.platformio.org/packages/akkoyun/library/I2C_Functions.svg)

I2C Functions is a lightweight Arduino helper library for register-based I2C devices. It wraps common read, write, bit-control, and optional multiplexer operations behind a compact single-header API.

The library is designed for projects that need:

- small footprint
- no dynamic memory allocation
- explicit transaction helpers for byte, word, and buffer access
- optional TCA9548-style mux channel control
- safer status-returning APIs for production use

## Table of Contents

1. Overview
2. Features
3. Installation
4. Quick Start
5. Working with an I2C Mux
6. API Design
7. Full API Reference
8. Predefined Constants
9. Example Sketch
10. Project Structure
11. Version Management
12. Local Validation and CI
13. Notes and Limitations

## Overview

This library provides a reusable object for a single I2C device address. Each object stores:

- device address
- optional mux usage state
- optional mux channel
- current detection result
- active TwoWire bus pointer

Once started with Begin, the object can:

- probe the target device
- read registers
- write registers
- read and modify individual bits
- switch the mux channel automatically before transactions when mux support is enabled

The library does not allocate heap memory and does not own hardware resources beyond the TwoWire instance you pass to it.

## Features

- Single-header implementation in src/I2C_Functions.h
- Works with the default Wire bus or a custom TwoWire instance
- Supports direct read/write operations for 8-bit and 16-bit register addressing patterns
- Supports raw reads without sending a register command first
- Supports bit-level register updates
- Supports optional multiplexer channel switching through the default mux address
- Includes compatibility wrappers and safer status-returning APIs
- Includes Arduino Library Manager metadata and PlatformIO metadata

## Installation

### Arduino IDE

1. Open Library Manager.
2. Search for I2C_Functions.
3. Install the library.

### PlatformIO

Add the library to platformio.ini:

```ini
lib_deps =
    akkoyun/I2C_Functions
```

### Manual Installation

1. Download or clone this repository.
2. Place it inside your Arduino libraries folder.
3. Restart the IDE.

## Quick Start

### Include and Create an Object

```cpp
// Include the library header.
#include <I2C_Functions.h>

// Create an object for a device at address 0x40.
I2C_Functions sensor(0x40);
```

### Start the Bus and Check the Device

```cpp
// Start Serial and the I2C device helper.
void setup() {

    Serial.begin(115200);
    sensor.Begin();

    if (sensor.Detect()) {
        Serial.println(F("Device detected"));
    } else {
        Serial.println(F("Device not detected"));
    }
}
```

### Read a Single Register

```cpp
// Read one register with explicit status handling.
uint8_t value = 0x00;
bool ok = sensor.Try_Read_Register(0x00, &value);

if (ok) {
    Serial.print(F("Value: 0x"));
    Serial.println(value, HEX);
}
```

### Write a Single Register

```cpp
// Write one register only when the target register is documented as writable.
bool ok = sensor.Try_Write_Register(0x10, 0x22, true);
```

## Working with an I2C Mux

The constructor supports optional mux usage.

```cpp
// Create an object behind mux channel 3.
I2C_Functions muxed_sensor(0x40, true, 3);
```

Constructor parameters:

- address: target device I2C address
- mux_enable: set to true when the device is behind the mux
- mux_channel: channel number from 1 to 8; invalid values are treated as mux off

When mux support is enabled:

- the library resolves channel numbers 1..8 to mux bit masks
- the mux channel is selected automatically before device transactions
- the default mux address is __Mux_Address__ and can be overridden from Definition.h

If mux support is disabled, the object uses __Mux_Channel_Off__ internally.

## API Design

The library exposes two API families.

### 1. Status-returning APIs

These methods return success or failure explicitly and are the recommended interface for robust applications.

Examples:

- Try_Read_Register
- Try_Read_Register_Word
- Try_Read_Multiple_Register
- Try_Write_Register
- Try_Write_Command
- Try_Read_Register_Bit

### 2. Compatibility APIs

These methods preserve the older interface style.

- Some compatibility methods return the read value directly.
- On failure, direct-value read methods fall back to zero or false.
- Compatibility methods are useful when updating older sketches with minimal changes.

For production code, prefer the status-returning APIs because they keep transfer status separate from returned data.

### About the Stop Parameter

Several write and read methods expose a stop parameter.

- true sends a STOP condition at the end of the write phase
- false keeps the bus active for devices that expect repeated-start style access

Use the value required by the target device datasheet.

## Full API Reference

### Constructor and Lifecycle

### I2C_Functions

Creates a device helper object.

```cpp
I2C_Functions(uint8_t address, bool mux_enable = false, uint8_t mux_channel = 0)
```

Parameters:

- address: I2C device address
- mux_enable: enable automatic mux handling
- mux_channel: channel number from 1 to 8 when mux is enabled

### Begin

Starts the selected TwoWire bus and runs an initial device detection.

```cpp
void Begin(TwoWire *twi = &Wire)
```

Example:

```cpp
// Start the default Wire bus.
sensor.Begin();
```

### End

Stops the active TwoWire bus used by the object.

```cpp
void End(void)
```

### Detect_Device

Re-runs device detection and updates the internal detect state.

```cpp
void Detect_Device(void)
```

Use this when the device may appear after startup or after a bus reset.

### Detect

Returns the cached device detection state.

```cpp
bool Detect(void)
```

### Address

Returns the configured device address.

```cpp
uint8_t Address(void)
```

### Mux_Enable

Returns whether mux support is enabled for this object.

```cpp
bool Mux_Enable(void)
```

### Mux_Channel

Returns the resolved mux channel mask currently assigned to this object.

```cpp
uint8_t Mux_Channel(void)
```

### Set_Mux_Channel

Applies the configured mux channel manually.

```cpp
bool Set_Mux_Channel(void)
```

Most users do not need to call this directly because normal transactions already do it automatically.

## Read Operations

### Try_Read_Register

Reads one byte from an 8-bit register address.

```cpp
bool Try_Read_Register(uint8_t reg, uint8_t *data)
```

### Read_Register

Compatibility wrapper for single-byte register reads.

```cpp
uint8_t Read_Register(uint8_t reg)
```

Behavior:

- returns the register value on success
- returns 0x00 on failure

### Try_Read_Register_Word

Reads two bytes from an 8-bit register address and combines them into a 16-bit value.

```cpp
bool Try_Read_Register_Word(uint8_t reg, uint16_t *data)
```

Byte order used by the library:

- low byte is read first
- high byte is read second
- final value is composed as high << 8 | low

### Read_Register_Word

Compatibility wrapper for 16-bit register reads.

```cpp
uint16_t Read_Register_Word(uint8_t reg)
```

Behavior:

- returns the word value on success
- returns 0x0000 on failure

### Try_Read_Multiple_Register

Reads a byte buffer from an 8-bit register address.

```cpp
bool Try_Read_Multiple_Register(uint8_t reg, uint8_t *data, uint8_t length, bool stop = true)
```

### Read_Multiple_Register

Compatibility wrapper for buffered reads using an 8-bit register address.

```cpp
bool Read_Multiple_Register(uint8_t reg, uint8_t *data, uint8_t length, bool stop = true)
```

### Try_Read_Multiple_Register_u16

Reads a byte buffer from a 16-bit register address.

```cpp
bool Try_Read_Multiple_Register_u16(uint16_t reg, uint8_t *data, uint8_t length, bool stop = true)
```

The library sends the register address as:

- high byte first
- low byte second

### Read_Multiple_Register_u16

Compatibility wrapper for buffered reads using a 16-bit register address.

```cpp
bool Read_Multiple_Register_u16(uint16_t reg, uint8_t *data, uint8_t length, bool stop = true)
```

### Try_Read_Multiple_Register_u16_NoCMD

Reads bytes from the device without writing any register address first.

```cpp
bool Try_Read_Multiple_Register_u16_NoCMD(uint8_t *data, uint8_t length)
```

Use this for devices that stream data immediately after a read request.

### Read_Multiple_Register_u16_NoCMD

Compatibility wrapper for raw reads without a command phase.

```cpp
bool Read_Multiple_Register_u16_NoCMD(uint8_t *data, uint8_t length)
```

## Write Operations

### Try_Write_Register

Writes one byte to an 8-bit register address.

```cpp
bool Try_Write_Register(uint8_t reg, uint8_t data, bool stop = true)
```

### Write_Register

Compatibility wrapper for single-byte register writes.

```cpp
bool Write_Register(uint8_t reg, uint8_t data, bool stop = true)
```

### Try_Write_Multiple_Register

Writes a byte buffer to an 8-bit register address.

```cpp
bool Try_Write_Multiple_Register(uint8_t reg, const uint8_t *data, uint8_t length)
```

### Write_Multiple_Register

Compatibility wrapper for buffered register writes.

```cpp
bool Write_Multiple_Register(uint8_t reg, const uint8_t *data, uint8_t length)
```

### Try_Write_Command

Sends one command byte to the target device without a register field.

```cpp
bool Try_Write_Command(uint8_t command, bool stop = true)
```

### Write_Command

Compatibility wrapper for one-byte command writes.

```cpp
bool Write_Command(uint8_t command, bool stop = true)
```

### Try_Write_Multiple_Command

Sends a command buffer without a register field.

```cpp
bool Try_Write_Multiple_Command(const uint8_t *command, uint8_t length)
```

### Write_Multiple_Command

Compatibility wrapper for command buffer writes.

```cpp
bool Write_Multiple_Command(const uint8_t *command, uint8_t length)
```

## Bit Operations

### Set_Register_Bit

Sets one bit inside a register.

```cpp
bool Set_Register_Bit(uint8_t reg, uint8_t bit_number, bool stop = true)
```

Behavior:

- validates that bit_number is in the 0..7 range
- reads the current register value
- sets the requested bit only when needed
- writes the updated register back

### Clear_Register_Bit

Clears one bit inside a register.

```cpp
bool Clear_Register_Bit(uint8_t reg, uint8_t bit_number, bool stop = true)
```

Behavior:

- validates that bit_number is in the 0..7 range
- reads the current register value
- clears the requested bit only when needed
- writes the updated register back

### Try_Read_Register_Bit

Reads one bit and returns the result through an output pointer.

```cpp
bool Try_Read_Register_Bit(uint8_t reg, uint8_t bit_number, bool *bit_value)
```

### Read_Register_Bit

Compatibility wrapper for single-bit reads.

```cpp
bool Read_Register_Bit(uint8_t reg, uint8_t bit_number)
```

Behavior:

- returns the bit value on success
- returns false on failure

## Predefined Constants

The library includes commonly used address and mux definitions in src/Definition.h.

### Version Macros

```cpp
#define __I2C_Functions_Version_Major__ 2
#define __I2C_Functions_Version_Minor__ 0
#define __I2C_Functions_Version_Patch__ 1
#define __I2C_Functions_Version__ "02.00.01"
```

### Device Address Macros

```cpp
#define __I2C_Addr_TCA9548__   (uint8_t)0x70
#define __I2C_Addr_RV3028C7__  (uint8_t)0x52
#define __I2C_Addr_DS28C__     (uint8_t)0x50
#define __I2C_Addr_HDC2010__   (uint8_t)0x40
#define __I2C_Addr_MPL3115A2__ (uint8_t)0x60
#define __I2C_Addr_TSL2561__   (uint8_t)0x39
#define __I2C_Addr_SI1145__    (uint8_t)0x60
#define __I2C_Addr_MAX17055__  (uint8_t)0x36
#define __I2C_Addr_BQ24298__   (uint8_t)0x6B
#define __I2C_Addr_SHT21__     (uint8_t)0x40
#define __I2C_Addr_SDP810__    (uint8_t)0x25
#define __I2C_Addr_PCF8574_A__ (uint8_t)0x3F
#define __I2C_Addr_PCF8574_B__ (uint8_t)0x3B
#define __I2C_Addr_PCF8574_C__ (uint8_t)0x39
#define __I2C_Addr_PCF8574_D__ (uint8_t)0x3E
#define __I2C_Addr_NA2302__    (uint8_t)0x3A
```

### Mux Definitions

```cpp
#define __Mux_Address__     (uint8_t)0x70
#define __Mux_Channel_Off__ (uint8_t)0x00
#define __Mux_Channel_1__   (uint8_t)0x01
#define __Mux_Channel_2__   (uint8_t)0x02
#define __Mux_Channel_3__   (uint8_t)0x04
#define __Mux_Channel_4__   (uint8_t)0x08
#define __Mux_Channel_5__   (uint8_t)0x10
#define __Mux_Channel_6__   (uint8_t)0x20
#define __Mux_Channel_7__   (uint8_t)0x40
#define __Mux_Channel_8__   (uint8_t)0x80
```

## Example Sketch

The repository includes an example at examples/Device_Control/Device_Control.ino.

What it demonstrates:

- creating an object with a predefined address macro
- starting the library with Begin
- checking Detect
- reading one register with Try_Read_Register
- optionally writing one register with Try_Write_Register

The write example is intentionally disabled by default. Enable it only when:

- the connected device is correct
- the selected register is documented as writable
- the value is known to be safe for that device

Example snippet:

```cpp
// Include I2C library.
#include <I2C_Functions.h>

// Create an object for the HDC2010 device.
I2C_Functions HDC2010(__I2C_Addr_HDC2010__);

void setup() {
    Serial.begin(115200);
    HDC2010.Begin();

    if (HDC2010.Detect()) {
        uint8_t value = 0x00;
        if (HDC2010.Try_Read_Register(0x00, &value)) {
            Serial.println(value, HEX);
        }
    }
}

void loop() {
}
```

## Project Structure

```text
src/
  Definition.h          Version, address, and mux macros
  I2C_Functions.h       Full library implementation
examples/
  Device_Control/
    Device_Control.ino  Basic read and optional write demo
scripts/
  sync-version.sh       Synchronizes VERSION into metadata files
.github/workflows/
  version-sync.yml      Checks synchronized version data
  build-example.yml     Builds the example with PlatformIO
platformio.ini          Local build configuration
VERSION                 Single source of truth for the release version
```

## Version Management

The repository keeps the display version in the root VERSION file.

Release flow:

1. Update VERSION.
2. Run sh scripts/sync-version.sh.
3. Commit the synchronized files.
4. Push the branch or open a pull request.
5. Verify that Version Sync and Build Example are green.

## Local Validation and CI

### Local Validation

1. Open the repository as a PlatformIO project.
2. Install the recommended VS Code extensions for PlatformIO and C/C++.
3. Use the default uno or esp32dev environments from platformio.ini.
4. Build examples/Device_Control.

The PlatformIO configuration links the checked-out repository into the example build as a local library dependency, so validation runs against the current working tree rather than an installed copy.

This setup also helps VS Code resolve Arduino.h and Wire.h correctly through the Arduino framework provided by PlatformIO.

### Continuous Integration

The repository includes two CI checks.

- Version Sync verifies that VERSION, src/Definition.h, library.properties, library.json, and README.md stay aligned.
- Build Example compiles the example for both uno and esp32dev.

## Notes and Limitations

- The library depends on Arduino.h and Wire.h.
- It is a transport helper, not a full device-specific driver.
- Register safety is the caller's responsibility.
- Write operations should only target registers marked writable in the device datasheet.
- Compatibility read methods can hide transfer failures because they return fallback values.
- For error-aware applications, use the Try_* methods.

---

[![Support me](https://img.shields.io/badge/Support-PATREON-GREEN.svg)](https://www.patreon.com/bePatron?u=62967889) ![Twitter Follow](https://img.shields.io/twitter/follow/gunceakkoyun?style=social) ![YouTube Channel Views](https://img.shields.io/youtube/channel/views/UCIguQGdaBT1GnnVMz5qAZ2Q?style=social) [![E-Mail](https://img.shields.io/badge/E_Mail-Mehmet_Gunce_Akkoyun-blue.svg)](mailto:akkoyun@me.com) ![GitHub](https://img.shields.io/github/license/akkoyun/Statistical)
