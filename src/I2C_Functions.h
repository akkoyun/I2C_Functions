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

// Define Sensor Libraries
#ifndef __I2C_SENSOR_LIBRARY__
#include <I2C_Sensor_Library.h>
#endif

class _I2C_Functions {

	public:

		// Register Functions
		uint8_t Read_Register(uint8_t _Address, uint8_t _Register);
		bool Read_Multiple_Register(uint8_t _Address, uint8_t _Register, uint8_t * _Data, uint8_t _Length, bool _Stop);
		bool Write_Register(uint8_t _Address, uint8_t _Register, uint8_t _Data, bool _Stop);
		bool Write_Multiple_Register(uint8_t _Address, uint8_t _Register, uint8_t * _Data, uint8_t _Length);
		bool Write_Command(uint8_t _Address, uint8_t _Command, bool _Stop);

		// Bit Functions
		bool Set_Register_Bit(uint8_t _Address, uint8_t _Register, uint8_t _Bit_Number, bool _Stop);
		bool Clear_Register_Bit(uint8_t _Address, uint8_t _Register, uint8_t _Bit_Number, bool _Stop);
		bool Read_Register_Bit(uint8_t _Address, uint8_t _Register, uint8_t _Bit_Number);

		// Converter Functions
		uint8_t BCDtoDEC(uint8_t _Value);
		uint8_t DECtoBCD(byte _Value);

		// Generic I2C Functions
		bool Control_Device(uint8_t _Address);
		bool Set_Multiplexer(uint8_t _Address, uint8_t _Channel);

	private:

		// Private Variables
		uint8_t _Multiplexer_Current_Channel = 0;

};

extern _I2C_Functions I2C;

#endif /* defined(__I2C_Functions__) */