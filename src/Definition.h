// Library Version
#define __I2C_Functions_Version__ "01.11.00"

// I2C Address Definitions
#ifndef __I2C_Addr_TCA9548__
	#define __I2C_Addr_TCA9548__	(uint8_t)0x70
#endif
#ifndef __I2C_Addr_RV3028C7__
	#define __I2C_Addr_RV3028C7__	(uint8_t)0x52
#endif
#ifndef __I2C_Addr_DS28C__
	#define __I2C_Addr_DS28C__		(uint8_t)0x50
#endif
#ifndef __I2C_Addr_HDC2010__
	#define __I2C_Addr_HDC2010__	(uint8_t)0x40
#endif
#ifndef __I2C_Addr_MPL3115A2__
	#define __I2C_Addr_MPL3115A2__	(uint8_t)0x60
#endif
#ifndef __I2C_Addr_TSL2561__
	#define __I2C_Addr_TSL2561__	(uint8_t)0x39
#endif
#ifndef __I2C_Addr_SI1145__
	#define __I2C_Addr_SI1145__		(uint8_t)0x60
#endif
#ifndef __I2C_Addr_MAX17055__
	#define __I2C_Addr_MAX17055__	(uint8_t)0x36
#endif
#ifndef __I2C_Addr_BQ24298__
	#define __I2C_Addr_BQ24298__	(uint8_t)0x6B
#endif
#ifndef __I2C_Addr_SHT21__
	#define __I2C_Addr_SHT21__		(uint8_t)0x40
#endif
#ifndef __I2C_Addr_SDP810__
	#define __I2C_Addr_SDP810__		(uint8_t)0x25
#endif
#ifndef __I2C_Addr_PCF8574_A__
	#define __I2C_Addr_PCF8574_A__	(uint8_t)0x3F
#endif
#ifndef __I2C_Addr_PCF8574_B__
	#define __I2C_Addr_PCF8574_B__	(uint8_t)0x3B
#endif
#ifndef __I2C_Addr_PCF8574_C__
	#define __I2C_Addr_PCF8574_C__	(uint8_t)0x39
#endif
#ifndef __I2C_Addr_PCF8574_D__
	#define __I2C_Addr_PCF8574_D__	(uint8_t)0x3E
#endif
#ifndef __I2C_Addr_NA2302__
	#define __I2C_Addr_NA2302__		(uint8_t)0x3A	
#endif

// Set Default Address
#ifndef __Mux_Address__
	#define __Mux_Address__			(uint8_t)0x70
#endif

// Multiplexer Channel Definirions
#ifndef __Mux_Channel_Off__
	#define __Mux_Channel_Off__		(uint8_t)0x00
#endif
#ifndef __Mux_Channel_1__
	#define __Mux_Channel_1__		(uint8_t)0x01
#endif
#ifndef __Mux_Channel_2__
	#define __Mux_Channel_2__		(uint8_t)0x02
#endif
#ifndef __Mux_Channel_3__
	#define __Mux_Channel_3__		(uint8_t)0x04
#endif
#ifndef __Mux_Channel_4__
	#define __Mux_Channel_4__		(uint8_t)0x08
#endif
#ifndef __Mux_Channel_5__
	#define __Mux_Channel_5__		(uint8_t)0x10
#endif
#ifndef __Mux_Channel_6__
	#define __Mux_Channel_6__		(uint8_t)0x20
#endif
#ifndef __Mux_Channel_7__
	#define __Mux_Channel_7__		(uint8_t)0x40
#endif
#ifndef __Mux_Channel_8__
	#define __Mux_Channel_8__		(uint8_t)0x80
#endif
