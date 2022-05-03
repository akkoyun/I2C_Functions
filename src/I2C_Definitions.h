/* *******************************************************************************
 * 	Copyright (C) 2014-2022 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: I2C Address DataBase
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *********************************************************************************/

#ifndef __I2C_Address__
#define __I2C_Address__

// I2C Library Definitions
#define __I2C_Functions_Version__	"01.05.03"

// Sensor Address Definitions
#define __I2C_Addr_TCA9548__		(uint8_t)0x70
#define __I2C_Addr_RV3028C7__		(uint8_t)0x52
#define __I2C_Addr_DS28C__			(uint8_t)0x50
#define __I2C_Addr_HDC2010__		(uint8_t)0x40
#define __I2C_Addr_MAX17055__		(uint8_t)0x36
#define __I2C_Addr_BQ24298__		(uint8_t)0x6B
#define __I2C_Addr_SHT21__			(uint8_t)0x40
#define __I2C_Addr_SDP810__			(uint8_t)0x25

// Set Default Address
#define __Mux_Address__             (uint8_t)0x70

// Multiplexer Channel Definirions
#define __Mux_Channel_Off__			(uint8_t)0x00
#define __Mux_Channel_1__			(uint8_t)0x01
#define __Mux_Channel_2__			(uint8_t)0x02
#define __Mux_Channel_3__			(uint8_t)0x04
#define __Mux_Channel_4__			(uint8_t)0x08
#define __Mux_Channel_5__			(uint8_t)0x10
#define __Mux_Channel_6__			(uint8_t)0x20
#define __Mux_Channel_7__			(uint8_t)0x40
#define __Mux_Channel_8__			(uint8_t)0x80

#endif