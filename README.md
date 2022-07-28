# I2C Functions Library <sup>V1.8</sup>

![GitHub release (latest by date)](https://img.shields.io/github/v/release/akkoyun/I2C_Functions) ![arduino-library-badge](https://www.ardu-badge.com/badge/I2C_Functions.svg?) ![GitHub stars](https://img.shields.io/github/stars/akkoyun/I2C_Functions?style=flat&logo=github) ![PlatformIO Registry](https://badges.registry.platformio.org/packages/akkoyun/library/I2C_Functions.svg)

---

**Abstract**

This is a helper library to abstract away I2C transactions and registers.

```C++
// Declare Object
I2C_Functions HDC2010(0x40, true, 3);
```

Library includes some helper I2C functions and a generic I2C multiplexer function.

    * Read_Register
    * Write_Register
    * Read_Multiple_Register
    * Write_Multiple_Register
    * Write_Command
    * Set_Register_Bit
    * Clear_Register_Bit
    * Read_Register_Bit
    * BCDtoDEC
    * DECtoBCD
    * Control_Device
    * Detect
    * Address
    * Mux
    * Set_Multiplexer

**Scanner**

This very simple sketch scans the I2C-bus for devices. If a device is found, it is reported to the Arduino serial monitor.

This sketch is the first step to get the I2C communication working.

The sketch shows the 7-bit addresses of the found devices as hexadecimal values. That value can be used for the "Wire.begin" function which uses the 7-bit address. Some datasheets use the 8-bit address and some example sketches use decimal addresses.

This scanner supports I2C multiplexer and can be used for channel selection.

![I2C Scanner](https://github.com/akkoyun/I2C_Functions/blob/main/Documents/ScreenShot.png)

---

[![Support me](https://img.shields.io/badge/Support-PATREON-GREEN.svg)](https://www.patreon.com/bePatron?u=62967889) ![Twitter Follow](https://img.shields.io/twitter/follow/gunceakkoyun?style=social) ![YouTube Channel Views](https://img.shields.io/youtube/channel/views/UCIguQGdaBT1GnnVMz5qAZ2Q?style=social) [![E-Mail](https://img.shields.io/badge/E_Mail-Mehmet_Gunce_Akkoyun-blue.svg)](mailto:akkoyun@me.com) ![GitHub](https://img.shields.io/github/license/akkoyun/Statistical) 