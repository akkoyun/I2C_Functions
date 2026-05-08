# I2C Functions Library

![GitHub release (latest by date)](https://img.shields.io/github/v/release/akkoyun/I2C_Functions) ![arduino-library-badge](https://www.ardu-badge.com/badge/I2C_Functions.svg?) ![GitHub stars](https://img.shields.io/github/stars/akkoyun/I2C_Functions?style=flat&logo=github) ![PlatformIO Registry](https://badges.registry.platformio.org/packages/akkoyun/library/I2C_Functions.svg)

**Version 03.00.01** — Lightweight, zero-allocation Arduino helper library for register-based I2C devices.

`I2C_Functions` wraps every common I2C transaction — byte, word, buffer, bit, and command — behind a clean single-header API. It works with the standard `Wire` bus or any custom `TwoWire` instance and optionally manages a TCA9548-style I2C multiplexer channel automatically before each transaction.

---

## Table of Contents

1. [Features](#features)
2. [Installation](#installation)
3. [Quick Start](#quick-start)
4. [API Families](#api-families)
5. [Constructor and Lifecycle](#constructor-and-lifecycle)
6. [Read Operations](#read-operations)
7. [Write Operations](#write-operations)
8. [Bit Operations](#bit-operations)
9. [Multiplexer Support](#multiplexer-support)
10. [Predefined Constants](#predefined-constants)
11. [Project Structure](#project-structure)
12. [Notes and Limitations](#notes-and-limitations)

---

## Features

| Feature | Details |
| --- | --- |
| **Zero heap allocation** | No `new`, `malloc`, or `String` — safe for constrained MCUs |
| **Single-header** | Drop in `src/I2C_Functions.h`, done |
| **Dual API** | Status-returning `Try_*` variants for production + simple wrappers for prototyping |
| **Byte operations** | Read / write single byte registers |
| **Word operations** | Read / write 16-bit registers with configurable endianness (LSB-first or MSB-first) |
| **Buffer operations** | Read / write multi-byte payloads with 8-bit or 16-bit register addressing |
| **Command operations** | Send raw command bytes without a register address |
| **Bit operations** | Set, clear, toggle, read, and write individual register bits (read-modify-write) |
| **Mux support** | Automatic TCA9548 channel switching before each transaction |
| **Bus flexibility** | Accepts any `TwoWire*` pointer — Wire, Wire1, or a software I2C instance |
| **Platform agnostic** | Arduino AVR, megaAVR, ESP32, and any Arduino-compatible target |

---

## Installation

### Arduino Library Manager

1. Open **Sketch → Include Library → Manage Libraries**
2. Search for `I2C_Functions`
3. Click Install

### PlatformIO

Add to your `platformio.ini`:

```ini
lib_deps =
    akkoyun/I2C_Functions
```

### Manual

1. Download or clone this repository
2. Copy the folder into your Arduino `libraries/` directory
3. Restart the IDE

---

## Quick Start

### Basic sensor read

```cpp
#include <I2C_Functions.h>

// Create an object for a device at 0x40 (e.g. HDC2010)
I2C_Functions sensor(__I2C_Addr_HDC2010__);

void setup() {
    Serial.begin(115200);

    // Start Wire and probe the device
    sensor.Begin();

    if (!sensor.Detect()) {
        Serial.println(F("Device not found"));
        return;
    }

    // Read register 0x00 — explicit status (recommended)
    uint8_t value = 0x00;
    if (sensor.Try_Read_Register(0x00, &value)) {
        Serial.print(F("Register 0x00 = 0x"));
        Serial.println(value, HEX);
    }
}

void loop() {}
```

### Read a 16-bit register (big-endian sensor)

```cpp
uint16_t raw = 0x0000;

// Pass true for MSB-first (big-endian) — common for most sensors
if (sensor.Try_Read_Register_Word(0x02, &raw, true)) {
    Serial.println(raw);
}
```

### Modify a single bit

```cpp
// Set bit 3 of register 0x0F
sensor.Set_Register_Bit(0x0F, 3);

// Clear bit 3 of register 0x0F
sensor.Clear_Register_Bit(0x0F, 3);

// Toggle bit 3 of register 0x0F
sensor.Toggle_Register_Bit(0x0F, 3);

// Write a specific value to bit 3 (set or clear depending on bool)
sensor.Write_Register_Bit(0x0F, 3, true);
```

### Device behind a multiplexer

```cpp
// Channel 3 on a TCA9548 at the default address (0x70)
I2C_Functions mux_sensor(__I2C_Addr_HDC2010__, true, 3);

void setup() {
    // The library switches the mux to channel 3 automatically
    // before every read or write transaction
    mux_sensor.Begin();
}
```

---

## API Families

The library exposes two parallel families for every operation.

### `Try_*` — Status-returning (recommended)

These functions return `bool`:  `true` on success, `false` on any failure (device absent, NACK, buffer overflow, bad pointer). Use these in production code.

```cpp
uint8_t val = 0x00;
if (sensor.Try_Read_Register(0x00, &val)) {
    // val is valid
}
```

### Simple wrappers — Quick prototyping

These functions return the value directly and silently fall back to `0` / `false` on failure. Useful when you don't need error handling, but hiding failures can mask bus issues.

```cpp
uint8_t val = sensor.Read_Register(0x00);
// val is 0x00 on failure — indistinguishable from a real 0x00 read
// Use Try_Read_Register for error-aware code
```

### The `_Stop` parameter

Several write and multi-byte read functions expose a `stop` parameter:

| Value | Effect |
| --- | --- |
| `true` (default) | Sends a STOP condition — ends the transaction normally |
| `false` | Sends a repeated START — keeps the bus active for devices that require it |

Consult your device's datasheet to know which is needed.

### The `_MSB_First` parameter

Word (16-bit) read and write functions support configurable byte order:

| Value | Byte order | Use when |
| --- | --- | --- |
| `false` (default) | Little-endian — LSB first | Device sends/expects LSB at lower address |
| `true` | Big-endian — MSB first | Most I2C sensors (MPU, BMP, HDC, etc.) |

---

## Constructor and Lifecycle

### `I2C_Functions` — Constructor

```cpp
explicit I2C_Functions(uint8_t address, bool mux_enable = false, uint8_t mux_channel = 0)
```

| Parameter | Type | Description |
| --- | --- | --- |
| `address` | `uint8_t` | I2C address of the target device |
| `mux_enable` | `bool` | `true` to enable automatic mux channel switching |
| `mux_channel` | `uint8_t` | Channel number 1–8; values outside that range disable the mux |

```cpp
I2C_Functions sensor(0x40);                   // Direct device
I2C_Functions muxed(0x40, true, 3);           // Behind mux channel 3
I2C_Functions wire1_dev(0x52, false, 0);      // Will use Wire1 via Begin(&Wire1)
```

---

### `Begin`

Starts the TwoWire bus and runs an initial device detection.

```cpp
void Begin(TwoWire *twi = &Wire)
```

```cpp
sensor.Begin();          // Uses Wire (default)
sensor.Begin(&Wire1);    // Uses Wire1
```

---

### `End`

Stops the active TwoWire bus.

```cpp
void End(void)
```

---

### `Detect_Device`

Re-runs device detection and updates the internal state. Call this if the device may appear after startup or following a bus reset.

```cpp
void Detect_Device(void)
```

---

### `Detect`

Returns the cached detection result (updated by `Begin` and `Detect_Device`).

```cpp
bool Detect(void)
// Returns: true if the device acknowledged its address, false otherwise
```

---

### `Address`

Returns the configured device address.

```cpp
uint8_t Address(void)
```

---

### `Mux_Enable` / `Mux_Channel`

Query multiplexer configuration.

```cpp
bool    Mux_Enable(void)    // true if mux is active for this object
uint8_t Mux_Channel(void)  // resolved bitmask (0x01–0x80), or 0x00 if disabled
```

---

## Read Operations

### Read Single Byte

```cpp
// Status-returning — recommended
bool Try_Read_Register(uint8_t reg, uint8_t *data)

// Simple wrapper — returns 0x00 on failure
uint8_t Read_Register(uint8_t reg)
```

```cpp
uint8_t val = 0x00;
if (sensor.Try_Read_Register(0x00, &val)) {
    // val holds the register content
}
```

---

### Read Single Word (16-bit)

```cpp
// Status-returning
bool Try_Read_Register_Word(uint8_t reg, uint16_t *data, bool msb_first = false)

// Simple wrapper — returns 0x0000 on failure
uint16_t Read_Register_Word(uint8_t reg, bool msb_first = false)
```

```cpp
uint16_t raw = 0x0000;

// Little-endian device (LSB first) — default
sensor.Try_Read_Register_Word(0x04, &raw);

// Big-endian device (MSB first) — most sensors
sensor.Try_Read_Register_Word(0x04, &raw, true);
```

---

### Multiple Bytes — 8-bit register address

```cpp
bool Read_Multiple_Register(uint8_t reg, uint8_t *data, uint8_t length, bool stop = true)
```

```cpp
uint8_t buf[6];
if (sensor.Read_Multiple_Register(0x3B, buf, 6)) {
    // buf contains 6 bytes starting from register 0x3B
}
```

---

### Multiple Bytes — 16-bit register address

For devices that use a two-byte register pointer (EEPROMs, some image sensors).

```cpp
bool Read_Multiple_Register_u16(uint16_t reg, uint8_t *data, uint8_t length, bool stop = true)
```

The register address is sent MSB-first (high byte then low byte) as required by most devices with 16-bit addressing.

```cpp
uint8_t page[16];
sensor.Read_Multiple_Register_u16(0x0100, page, 16);
```

---

### Multiple Bytes — No register address

For devices that stream data immediately after a read request, without needing a register address first.

```cpp
bool Read_Multiple_Register_NoCMD(uint8_t *data, uint8_t length)
```

```cpp
uint8_t frame[4];
sensor.Read_Multiple_Register_NoCMD(frame, 4);
```

---

### Single Bit

```cpp
// Status-returning — bit value written to output pointer
bool Try_Read_Register_Bit(uint8_t reg, uint8_t bit_number, bool *bit_value)

// Simple wrapper — returns false on failure
bool Read_Register_Bit(uint8_t reg, uint8_t bit_number)
```

```cpp
bool data_ready = false;
if (sensor.Try_Read_Register_Bit(0x00, 7, &data_ready)) {
    if (data_ready) { /* process */ }
}
```

---

## Write Operations

### Write Single Byte

```cpp
bool Write_Register(uint8_t reg, uint8_t data, bool stop = true)
```

```cpp
sensor.Write_Register(0x0F, 0x22);
```

---

### Write Single Word (16-bit)

```cpp
bool Write_Register_Word(uint8_t reg, uint16_t data, bool stop = true, bool msb_first = false)
```

```cpp
// Little-endian write (default)
sensor.Write_Register_Word(0x10, 0x1234);

// Big-endian write — sends 0x12 then 0x34
sensor.Write_Register_Word(0x10, 0x1234, true, true);
```

---

### Multiple Bytes

```cpp
bool Write_Multiple_Register(uint8_t reg, const uint8_t *data, uint8_t length)
```

```cpp
uint8_t config[] = {0x01, 0x80, 0x00};
sensor.Write_Multiple_Register(0x10, config, 3);
```

The Wire internal buffer is 32 bytes on AVR. Writing more bytes than the buffer holds will abort the transaction and return `false`.

---

### Command (no register address)

For devices that accept command bytes directly without a preceding register field.

```cpp
bool Write_Command(uint8_t command, bool stop = true)
```

```cpp
sensor.Write_Command(0xFE);          // soft reset command, for example
```

---

### Multiple Commands

```cpp
bool Write_Multiple_Command(const uint8_t *command, uint8_t length)
```

```cpp
uint8_t seq[] = {0xAC, 0x33, 0x00};
sensor.Write_Multiple_Command(seq, 3);
```

---

## Bit Operations

All bit operations perform a **read-modify-write** cycle. The bit number must be in the range 0–7 (bit 0 = LSB).

### Set a bit

Reads the register, sets the target bit if it is not already set, and writes back. Skips the write if the bit is already `1`.

```cpp
bool Set_Register_Bit(uint8_t reg, uint8_t bit_number, bool stop = true)
```

```cpp
sensor.Set_Register_Bit(0x0F, 3);   // set bit 3
```

---

### Clear a bit

Reads the register, clears the target bit if it is not already clear, and writes back. Skips the write if the bit is already `0`.

```cpp
bool Clear_Register_Bit(uint8_t reg, uint8_t bit_number, bool stop = true)
```

```cpp
sensor.Clear_Register_Bit(0x0F, 3);  // clear bit 3
```

---

### Toggle a bit

Reads the register, inverts the target bit, and writes back unconditionally.

```cpp
bool Toggle_Register_Bit(uint8_t reg, uint8_t bit_number, bool stop = true)
```

```cpp
sensor.Toggle_Register_Bit(0x0F, 3);  // flip bit 3
```

---

### Write a bit (set or clear by value)

Convenience wrapper that calls `Set_Register_Bit` or `Clear_Register_Bit` based on the boolean value.

```cpp
bool Write_Register_Bit(uint8_t reg, uint8_t bit_number, bool bit_value, bool stop = true)
```

```cpp
bool enable = true;
sensor.Write_Register_Bit(0x0F, 3, enable);   // sets bit 3
sensor.Write_Register_Bit(0x0F, 3, !enable);  // clears bit 3
```

---

## Multiplexer Support

The library integrates directly with a TCA9548A (or compatible) I2C multiplexer at the default address `0x70`.

### How it works

When mux support is enabled, every read and write transaction automatically:

1. Reads the current mux channel register
2. Switches to the configured channel only if it has changed
3. Runs the actual I2C transaction with the target device

This makes it transparent — you call `Try_Read_Register` and the mux is handled for you.

### Setup

```cpp
// Channel numbers 1–8 map to TCA9548 bitmasks 0x01–0x80
I2C_Functions temp_sensor(__I2C_Addr_SHT21__, true, 2);   // channel 2
I2C_Functions pres_sensor(__I2C_Addr_MPL3115A2__, true, 5); // channel 5

void setup() {
    temp_sensor.Begin();
    pres_sensor.Begin();
}

void loop() {
    uint8_t t_raw;
    temp_sensor.Try_Read_Register(0x00, &t_raw);   // auto-switches to channel 2

    uint16_t p_raw;
    pres_sensor.Try_Read_Register_Word(0x01, &p_raw, true);  // auto-switches to channel 5
}
```

---

## Predefined Constants

`src/Definition.h` provides typed `constexpr uint8_t` constants for commonly used devices and mux configuration.

### Device Addresses

```cpp
constexpr uint8_t __I2C_Addr_TCA9548__    = 0x70;  // I2C Multiplexer
constexpr uint8_t __I2C_Addr_RV3028C7__   = 0x52;  // RTC
constexpr uint8_t __I2C_Addr_DS28C__      = 0x50;  // EEPROM
constexpr uint8_t __I2C_Addr_HDC2010__    = 0x40;  // Temp / Humidity
constexpr uint8_t __I2C_Addr_MPL3115A2__  = 0x60;  // Pressure / Altitude
constexpr uint8_t __I2C_Addr_TSL2561__    = 0x39;  // Light
constexpr uint8_t __I2C_Addr_SI1145__     = 0x60;  // UV / IR / Visible
constexpr uint8_t __I2C_Addr_MAX17055__   = 0x36;  // Fuel Gauge
constexpr uint8_t __I2C_Addr_BQ24298__    = 0x6B;  // Battery Charger
constexpr uint8_t __I2C_Addr_SHT21__      = 0x40;  // Temp / Humidity
constexpr uint8_t __I2C_Addr_SDP810__     = 0x25;  // Differential Pressure
constexpr uint8_t __I2C_Addr_PCF8574_A__  = 0x3F;  // I/O Expander
constexpr uint8_t __I2C_Addr_PCF8574_B__  = 0x3B;  // I/O Expander
constexpr uint8_t __I2C_Addr_PCF8574_C__  = 0x39;  // I/O Expander
constexpr uint8_t __I2C_Addr_PCF8574_D__  = 0x3E;  // I/O Expander
constexpr uint8_t __I2C_Addr_NA2302__     = 0x3A;  // Humidity
```

### Multiplexer

```cpp
constexpr uint8_t __Mux_Address__         = 0x70;  // TCA9548 default address

constexpr uint8_t __Mux_Channel_Off__     = 0x00;
constexpr uint8_t __Mux_Channel_1__       = 0x01;
constexpr uint8_t __Mux_Channel_2__       = 0x02;
constexpr uint8_t __Mux_Channel_3__       = 0x04;
constexpr uint8_t __Mux_Channel_4__       = 0x08;
constexpr uint8_t __Mux_Channel_5__       = 0x10;
constexpr uint8_t __Mux_Channel_6__       = 0x20;
constexpr uint8_t __Mux_Channel_7__       = 0x40;
constexpr uint8_t __Mux_Channel_8__       = 0x80;
```

Using `constexpr` instead of `#define` gives you full type safety — the compiler checks that you are passing `uint8_t` values, and debuggers can display the constant by name.

---

## Project Structure

```text
src/
  Definition.h          constexpr address and mux constants
  I2C_Functions.h       Full single-header library implementation
examples/
  Device_Control/
    Device_Control.ino  Basic read and optional write demonstration
library.properties      Arduino Library Manager metadata
library.json            PlatformIO registry metadata
VERSION                 Single source of truth for the release version
platformio.ini          Local build and validation configuration
```

---

## Notes and Limitations

- **Transport only** — This library handles the I2C framing. It does not interpret sensor data, apply calibration, or implement device-specific protocols.
- **Register safety** — Writing to a register that is not documented as writable can lock or damage a device. Always consult the datasheet.
- **Wire buffer limit** — The Arduino Wire library buffers up to 32 bytes per transaction on AVR. `Write_Multiple_Register` and `Write_Multiple_Command` detect a buffer overflow (Wire's `write()` returns 0) and abort cleanly, always sending a STOP before returning `false`.
- **Mux address** — The mux address defaults to `0x70`. If your TCA9548 is at a different address, override `__Mux_Address__` before including the library.
- **Simple wrappers hide errors** — `Read_Register`, `Read_Register_Word`, and `Read_Register_Bit` return `0` / `false` on failure. Use the `Try_*` variants when error handling matters.
- **Endianness is your responsibility** — Pass `msb_first = true` for big-endian sensors (the majority) and `msb_first = false` for little-endian ones. The library does not auto-detect byte order.

---

[![Support me](https://img.shields.io/badge/Support-PATREON-GREEN.svg)](https://www.patreon.com/bePatron?u=62967889) ![Twitter Follow](https://img.shields.io/twitter/follow/gunceakkoyun?style=social) ![YouTube Channel Views](https://img.shields.io/youtube/channel/views/UCIguQGdaBT1GnnVMz5qAZ2Q?style=social) [![E-Mail](https://img.shields.io/badge/E_Mail-Mehmet_Gunce_Akkoyun-blue.svg)](mailto:akkoyun@me.com) ![GitHub](https://img.shields.io/github/license/akkoyun/Statistical)
