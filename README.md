# I2C Functions Library <sup>V1.4</sup>

![GitHub release (latest by date)](https://img.shields.io/github/v/release/akkoyun/I2C_Functions) ![arduino-library-badge](https://www.ardu-badge.com/badge/I2C_Functions.svg?) ![Visits Badge](https://badges.pufler.dev/visits/akkoyun/I2C_Functions) ![GitHub stars](https://img.shields.io/github/stars/akkoyun/I2C_Functions?style=flat&logo=github) ![Updated Badge](https://badges.pufler.dev/updated/akkoyun/I2C_Functions) ![PlatformIO Registry](https://badges.registry.platformio.org/packages/akkoyun/library/I2C_Functions.svg) 
[![Check Arduino](https://github.com/akkoyun/I2C_Functions/actions/workflows/check-arduino.yml/badge.svg)](https://github.com/akkoyun/I2C_Functions/actions/workflows/check-arduino.yml) [![Compile Examples](https://github.com/akkoyun/I2C_Functions/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/akkoyun/I2C_Functions/actions/workflows/compile-examples.yml) [![Spell Check](https://github.com/akkoyun/I2C_Functions/actions/workflows/spell-check.yml/badge.svg)](https://github.com/akkoyun/I2C_Functions/actions/workflows/spell-check.yml)

	Build - 01.04.04

---

**Abstract**

This is a helper library to abstract away I2C transactions and registers.

Library includes some helper I2C functions and a generic I2C multiplexer function.

    * Control_Device
    * Read_Register
    * Read_Multiple_Register
    * Write_Register
    * Write_Multiple_Register
    * Write_Command
    * Set_Register_Bit
    * Clear_Register_Bit
    * Read_Register_Bit
    * Set_Multiplexer

---

**I2C Device Control**

Library can control the I2C device and if connected function returns ```true```

```C++
bool Sensor_Connected = I2C.Control_Device(0x40);
```

**I2C Read Single Register**

Library can read a single register on I2C device and function returns readded register from device in ```uint8_t``` format

```C++
uint8_t Register = I2C.Read_Register(0x40, 0x01);
```

**I2C Write Single Register**

Library can write a single byte of data to specified register on the selected I2C device. Function also allows the end connection parameter. Function returns success response if command is success.

```C++
uint8_t I2C_Address = 0x40;
uint8_t Register = 0x01;
uint8_t Data = 0x00;

bool Success = Write_Register(I2C_Address, Register, Data, false);
```

**I2C Write Command**

Library can write a single command to the selected I2C device. Function also allows the end connection parameter. Function returns success response if command is success.

```C++
uint8_t I2C_Address = 0x40;
uint8_t Command = 0x01;

bool Success = Write_Command(I2C_Address, Command, false);
```

**I2C Read Multiple Register Command**

Library can read multiple register from the selected I2C device. Readded data stores in the out function array. Function also allows the end connection parameter. Function returns success response if command is success.

```C++
uint8_t I2C_Address = 0x40;
uint8_t Register = 0x01;
uint8_t Data[2];
uint8_t Length = 2;

bool Success = Read_Multiple_Register(I2C_Address, Register, Data, Length, false);
```

**I2C Write Multiple Register Command**

Library can write multiple register to the selected I2C device. Sended data stores in the out function array. Function also allows the end connection parameter. Function returns success response if command is success.

```C++
uint8_t I2C_Address = 0x40;
uint8_t Register = 0x01;
uint8_t Data[2] = {0x01, 0x04};
uint8_t Length = 2;

bool Success = Write_Multiple_Register(I2C_Address, Register, Data, Length);
```

**I2C Set Register Bit Command**

In some conditions we need to change a bit on register and write again to device. This library can do it on single function. You can specify address, register and selected bit. Function also allows the end connection parameter. Function returns success response if command is success.

```C++
uint8_t I2C_Address = 0x40;
uint8_t Register = 0x01;
uint8_t Bit_Number = 2;

bool Success = Set_Register_Bit(I2C_Address, Register, Bit_Number, false);
```

**I2C Clear Register Bit Command**

In some conditions we need to change a bit on register and write again to device. This library can do it on single function. You can specify address, register and selected bit. Function also allows the end connection parameter. Function returns success response if command is success.

```C++
uint8_t I2C_Address = 0x40;
uint8_t Register = 0x01;
uint8_t Bit_Number = 2;

bool Success = Clear_Register_Bit(I2C_Address, Register, Bit_Number, false);
```

**I2C Read Register Bit Command**

In some conditions we need to read a bit on register. This library can do it on single function. You can specify address, register and selected bit. Function also allows the end connection parameter. Function returns success response if command is success.

```C++
uint8_t I2C_Address = 0x40;
uint8_t Register = 0x01;
uint8_t Bit_Number = 2;

bool Success = Read_Register_Bit(I2C_Address, Register, Bit_Number, false);
```

**I2C Generic Multiplexer Command**

If your I2C structure contains a I2C Multiplexer, you need to use a additional library (or command set). In this library you can also use a generic multiplexer channel set command. Function returns success response if command is success.

```C++
uint8_t I2C_Address = 0x40;
uint8_t Channel = 0x01;

bool Success = Set_Multiplexer(I2C_Address, Channel);
```

---

[![Support me](https://img.shields.io/badge/Support-PATREON-GREEN.svg)](https://www.patreon.com/bePatron?u=62967889) ![Twitter Follow](https://img.shields.io/twitter/follow/gunceakkoyun?style=social) ![YouTube Channel Views](https://img.shields.io/youtube/channel/views/UCIguQGdaBT1GnnVMz5qAZ2Q?style=social) ![Repos Badge](https://badges.pufler.dev/repos/akkoyun) [![E-Mail](https://img.shields.io/badge/E_Mail-Mehmet_Gunce_Akkoyun-blue.svg)](mailto:akkoyun@me.com) ![GitHub](https://img.shields.io/github/license/akkoyun/Statistical) 