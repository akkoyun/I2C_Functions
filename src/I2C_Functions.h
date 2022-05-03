/* *******************************************************************************
 *  Copyright (C) 2014-2022 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: Generic I2C Functions
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *********************************************************************************/

#ifndef __I2C_Functions__
#define __I2C_Functions__

// Include Arduino Library
#ifndef __Arduino__
#include <Arduino.h>
#endif

// Include Wire Library
#ifndef __Wire__
#include <Wire.h>
#endif

// Include Sensor Database
#ifndef __I2C_Address__
#include "I2C_Definitions.h"
#endif

// I2C Control Functions
class I2C_Functions {

	public:

		// Class Constractor
		I2C_Functions(uint8_t _Address, uint8_t _Mux_Channel = 0x00);
		~I2C_Functions();
		bool Begin(void);

		// Register Functions
		uint8_t Read_Register(uint8_t _Register);
		bool Write_Register(uint8_t _Register, uint8_t _Data, bool _Stop);
		bool Read_Multiple_Register(uint8_t _Register, uint8_t * _Data, uint8_t _Length, bool _Stop);
		bool Write_Multiple_Register(uint8_t _Register, uint8_t * _Data, uint8_t _Length);

		// Command Functions
		bool Write_Command(uint8_t _Command, bool _Stop);

		// Bit Functions
		bool Set_Register_Bit(uint8_t _Register, uint8_t _Bit_Number, bool _Stop);
		bool Clear_Register_Bit(uint8_t _Register, uint8_t _Bit_Number, bool _Stop);
		bool Read_Register_Bit(uint8_t _Register, uint8_t _Bit_Number);

		// Converter Functions
		uint8_t BCDtoDEC(uint8_t _Value);
		uint8_t DECtoBCD(byte _Value);

		// Detect Functions
		bool Control_Device(void);

		// Multiplexer Functions
		bool Set_Multiplexer(uint8_t _Channel);

		// Control Functions
		bool Detect(void);
		uint8_t Address(void);

	private:

		// Device Definations
		uint8_t TWI_Address;
		bool TWI_Device;
		uint8_t TWI_Device_Mux_Channel;

		// Multiplexer Variables
		uint8_t _Multiplexer_Current_Channel = 9;

};

#endif /* defined(__I2C_Functions__) */