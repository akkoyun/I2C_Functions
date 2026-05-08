#ifndef __I2C_Functions_Definition__
#define __I2C_Functions_Definition__

	#include <stdint.h>

	// I2C Device Address Constants
	constexpr uint8_t __I2C_Addr_TCA9548__		= 0x70;
	constexpr uint8_t __I2C_Addr_RV3028C7__		= 0x52;
	constexpr uint8_t __I2C_Addr_DS28C__		= 0x50;
	constexpr uint8_t __I2C_Addr_HDC2010__		= 0x40;
	constexpr uint8_t __I2C_Addr_MPL3115A2__	= 0x60;
	constexpr uint8_t __I2C_Addr_TSL2561__		= 0x39;
	constexpr uint8_t __I2C_Addr_SI1145__		= 0x60;
	constexpr uint8_t __I2C_Addr_MAX17055__		= 0x36;
	constexpr uint8_t __I2C_Addr_BQ24298__		= 0x6B;
	constexpr uint8_t __I2C_Addr_SHT21__		= 0x40;
	constexpr uint8_t __I2C_Addr_SDP810__		= 0x25;
	constexpr uint8_t __I2C_Addr_PCF8574_A__	= 0x3F;
	constexpr uint8_t __I2C_Addr_PCF8574_B__	= 0x3B;
	constexpr uint8_t __I2C_Addr_PCF8574_C__	= 0x39;
	constexpr uint8_t __I2C_Addr_PCF8574_D__	= 0x3E;
	constexpr uint8_t __I2C_Addr_NA2302__		= 0x3A;

	// Multiplexer Default I2C Address (TCA9548)
	constexpr uint8_t __Mux_Address__			= 0x70;

	// Multiplexer Channel Bitmasks
	constexpr uint8_t __Mux_Channel_Off__		= 0x00;
	constexpr uint8_t __Mux_Channel_1__			= 0x01;
	constexpr uint8_t __Mux_Channel_2__			= 0x02;
	constexpr uint8_t __Mux_Channel_3__			= 0x04;
	constexpr uint8_t __Mux_Channel_4__			= 0x08;
	constexpr uint8_t __Mux_Channel_5__			= 0x10;
	constexpr uint8_t __Mux_Channel_6__			= 0x20;
	constexpr uint8_t __Mux_Channel_7__			= 0x40;
	constexpr uint8_t __Mux_Channel_8__			= 0x80;

#endif /* defined(__I2C_Functions_Definition__) */
