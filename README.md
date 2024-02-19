# I2C Functions Library ^V1.12^

![GitHub release (latest by date)](https://img.shields.io/github/v/release/akkoyun/I2C_Functions) ![arduino-library-badge](https://www.ardu-badge.com/badge/I2C_Functions.svg?) ![GitHub stars](https://img.shields.io/github/stars/akkoyun/I2C_Functions?style=flat&logo=github) ![PlatformIO Registry](https://badges.registry.platformio.org/packages/akkoyun/library/I2C_Functions.svg)

---

## Abstract

You can use this library with any I2C device and I2C multiplexer. If you are using an I2C multiplexer, you can specify the I2C multiplexer channel in the object creation. If you are not using an I2C multiplexer, you can create the object without specifying the I2C multiplexer channel.

You don't worry about the I2C multiplexer channel. The library automatically sets the I2C multiplexer channel when you call the I2C functions.

---

## Object Creation

```C++
// Declare Object (With I2C Mux)
I2C_Functions HDC2010(0x40, true, 3); // Connect 0x40 adres with I2C mux channel 3

// Declare Object (Without I2C Mux)
I2C_Functions HDC2010(0x40); // Connect 0x40 adres without I2C mux

// Write Register
HDC2010.Write_Register(0x10, 0x22, true); // Write 0x22 data to 0x10 register

// Read Register
uint8_t Result = HDC2010.Read_Register(0x01); // Read register 0x01
```

---

## Pre-Defined Values

You can use the pre-defined I2C devices in the library. You don't need to specify the I2C device address. You can also add your own I2C device address to the library.

```C++
// Library Version
#define __I2C_Functions_Version__ "01.11.00"

// I2C Address Definitions
#define __I2C_Addr_TCA9548__    (uint8_t)0x70
#define __I2C_Addr_RV3028C7__   (uint8_t)0x52
#define __I2C_Addr_DS28C__      (uint8_t)0x50
#define __I2C_Addr_HDC2010__    (uint8_t)0x40
#define __I2C_Addr_MPL3115A2__  (uint8_t)0x60
#define __I2C_Addr_TSL2561__    (uint8_t)0x39
#define __I2C_Addr_SI1145__     (uint8_t)0x60
#define __I2C_Addr_MAX17055__   (uint8_t)0x36
#define __I2C_Addr_BQ24298__    (uint8_t)0x6B
#define __I2C_Addr_SHT21__      (uint8_t)0x40
#define __I2C_Addr_SDP810__     (uint8_t)0x25
#define __I2C_Addr_PCF8574_A__  (uint8_t)0x3F
#define __I2C_Addr_PCF8574_B__  (uint8_t)0x3B
#define __I2C_Addr_PCF8574_C__  (uint8_t)0x39
#define __I2C_Addr_PCF8574_D__  (uint8_t)0x3E
#define __I2C_Addr_NA2302__     (uint8_t)0x3A

// Set Default Address
#define __Mux_Address__         (uint8_t)0x70

// Multiplexer Channel Definirions
#define __Mux_Channel_Off__     (uint8_t)0x00
#define __Mux_Channel_1__       (uint8_t)0x01
#define __Mux_Channel_2__       (uint8_t)0x02
#define __Mux_Channel_3__       (uint8_t)0x04
#define __Mux_Channel_4__       (uint8_t)0x08
#define __Mux_Channel_5__       (uint8_t)0x10
#define __Mux_Channel_6__       (uint8_t)0x20
#define __Mux_Channel_7__       (uint8_t)0x40
#define __Mux_Channel_8__       (uint8_t)0x80
```

---

## Functions

Library includes some helper I2C functions and a generic I2C multiplexer function.

### Read_Register

This function reads a single byte from the I2C device.

```C++
// Read Register Usage
uint8_t Read_Register(uint8_t Register);

// Read Register Example
uint8_t Result = HDC2010.Read_Register(0x01); // Read register 0x01

```

### Write_Register

This function writes a single byte to the I2C device.

```C++
// Write Register Usage
void Write_Register(uint8_t Register, uint8_t Data, bool Debug = false);

// Write Register Example
HDC2010.Write_Register(0x10, 0x22, true); // Write 0x22 data to 0x10 register
```

### Read_Multiple_Register

This function reads multiple bytes from the I2C device.

```C++
// Read Multiple Register Usage
void Read_Multiple_Register(uint8_t Register, uint8_t *Data, uint8_t Length);

// Read Multiple Register Example
uint8_t Data[4];
HDC2010.Read_Multiple_Register(0x00, Data, 4); // Read 4 bytes from 0x00 register
```

### Read_Multiple_Register_u16

This function reads multiple bytes from the I2C device and converts to 16-bit register.

```C++
// Read Multiple Register Usage
Read_Multiple_Register_u16(const uint16_t _Register, uint8_t * _Data, const uint8_t _Length, const bool _Stop);

// Read Multiple Register Example
uint8_t Data[4];
HDC2010.Read_Multiple_Register_u16(0x0001, Data, 4, true); // Read 4 bytes from 0x0001 register
```

### Write_Multiple_Register

This function writes multiple bytes to the I2C device.

```C++
// Write Multiple Register Usage
void Write_Multiple_Register(uint8_t Register, uint8_t *Data, uint8_t Length);

// Write Multiple Register Example
uint8_t Data[4] = {0x22, 0x33, 0x44, 0x55};
HDC2010.Write_Multiple_Register(0x10, Data, 4); // Write 4 bytes to 0x10 register
```

### Write_Command

This function writes a single byte to the I2C device as a command.

```C++
// Write Command Usage
void Write_Command(uint8_t Command);

// Write Command Example
HDC2010.Write_Command(0x22); // Write 0x22 command
```

### Write_Multiple_Command

This function writes multiple bytes to the I2C device as a command.

```C++
// Write Multiple Command Usage
void Write_Multiple_Command(uint8_t *Command, uint8_t Length);

// Write Multiple Command Example
uint8_t Command[4] = {0x22, 0x33, 0x44, 0x55};
HDC2010.Write_Multiple_Command(Command, 4); // Write 4 bytes command
```

### Set_Register_Bit

This function sets a single bit in a register.

```C++
// Set Register Bit Usage
void Set_Register_Bit(uint8_t Register, uint8_t Bit);

// Set Register Bit Example
HDC2010.Set_Register_Bit(0x10, 0x02); // Set 0x02 bit in 0x10 register
```

### Clear_Register_Bit

This function clears a single bit in a register.

```C++
// Clear Register Bit Usage
void Clear_Register_Bit(uint8_t Register, uint8_t Bit);

// Clear Register Bit Example
HDC2010.Clear_Register_Bit(0x10, 0x02); // Clear 0x02 bit in 0x10 register
```

### Read_Register_Bit

This function reads a single bit from a register.

```C++
// Read Register Bit Usage
bool Read_Register_Bit(uint8_t Register, uint8_t Bit);

// Read Register Bit Example
bool Result = HDC2010.Read_Register_Bit(0x10, 0x02); // Read 0x02 bit in 0x10 register
```

### Set_Mux_Channel

This function sets the I2C multiplexer channel. (If I2C multiplexer is used)

```C++
// Set Mux Channel Usage
void Set_Mux_Channel(void);

// Set Mux Channel Example
HDC2010.Set_Mux_Channel(); // Set I2C mux to channel (Specified in object creation)
```

### Detect

This function detects the I2C device.

```C++
// Detect Usage
bool Detect(void);

// Detect Example
bool Result = HDC2010.Detect(); // Detect I2C device
```

### Address

This function gets the I2C device address.

```C++
// Address Usage
uint8_t Address(void);

// Address Example
uint8_t Address = HDC2010.Address(); // Get I2C device address
```

### Mux_Channel

This function gets the I2C multiplexer channel. (If I2C multiplexer is used)

```C++
// Mux Channel Usage
uint8_t Mux_Channel(void);

// Mux Channel Example
uint8_t Channel = HDC2010.Mux_Channel(); // Get I2C mux channel
```

---

[![Support me](https://img.shields.io/badge/Support-PATREON-GREEN.svg)](https://www.patreon.com/bePatron?u=62967889) ![Twitter Follow](https://img.shields.io/twitter/follow/gunceakkoyun?style=social) ![YouTube Channel Views](https://img.shields.io/youtube/channel/views/UCIguQGdaBT1GnnVMz5qAZ2Q?style=social) [![E-Mail](https://img.shields.io/badge/E_Mail-Mehmet_Gunce_Akkoyun-blue.svg)](mailto:akkoyun@me.com) ![GitHub](https://img.shields.io/github/license/akkoyun/Statistical)
