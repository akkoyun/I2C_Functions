/* *******************************************************************************
 *  Copyright (C) 2014-2022 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: Generic I2C Functions
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *********************************************************************************/

#ifndef __I2C_Functions__
#define __I2C_Functions__

// Define Arduino Library
#ifndef __Arduino__
#include <Arduino.h>
#endif

// Define Wire Library
#ifndef __Wire__
#include <Wire.h>
#endif

// Define Multiplexer Variables
#define		__OFF__				0
#define		__CH1__				1
#define		__CH2__				2
#define		__CH3__				3
#define		__CH4__				4
#define		__CH5__				5
#define		__CH6__				6
#define		__CH7__				7
#define		__CH8__				8

// Define I2C Addresses
#define		__ADDR_TCA9548__	0x70
#define		__ADDR_RV3028C7__	0x52
#define		__ADDR_DS28C__		0x50
#define		__ADDR_HDC201__		0x40
#define		__ADDR_MAX17055__	0x36
#define		__ADDR_BQ24298__	0x6B

class _I2C_Functions {

	public:

		bool Control_Device(uint8_t _Address);

		uint8_t Read_Register(uint8_t _Address, uint8_t _Register);
		bool Read_Multiple_Register(uint8_t _Address, uint8_t _Register, uint8_t * _Data, uint8_t _Length, bool _Stop);
		bool Write_Register(uint8_t _Address, uint8_t _Register, uint8_t _Data, bool _Stop);
		bool Write_Multiple_Register(uint8_t _Address, uint8_t _Register, uint8_t * _Data, uint8_t _Length);
		bool Write_Command(uint8_t _Address, uint8_t _Command, bool _Stop);

		void Set_Register_Bit(uint8_t _Address, uint8_t _Register, uint8_t _Bit_Number);
		void Clear_Register_Bit(uint8_t _Address, uint8_t _Register, uint8_t _Bit_Number);
		bool Read_Register_Bit(uint8_t _Address, uint8_t _Register, uint8_t _Bit_Number);

		bool Set_Multiplexer(uint8_t _Address, uint8_t _Channel);

	private:

		uint8_t _Multiplexer_Current_Channel = 0;


};

extern _I2C_Functions I2C;

#endif /* defined(__I2C_Functions__) */