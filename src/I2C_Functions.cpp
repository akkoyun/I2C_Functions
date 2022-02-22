/* *******************************************************************************
 *  Copyright (C) 2014-2022 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: Generic I2C Functions
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *********************************************************************************/

#include <I2C_Functions.h>

// Global Functions
bool _I2C_Functions::Control_Device(uint8_t _Address) {

	// Connect to Device
	Wire.beginTransmission(_Address);

	// Close I2C Connection
	uint8_t _Result = Wire.endTransmission();

	// Control For Result
	if (_Result != 0) return(false);

	// End Function
	return(true);

}

uint8_t _I2C_Functions::Read_Register(uint8_t _Address, uint8_t _Register) {

	// Declare Response Variable
	uint8_t _Response = 0x00;

	// Connect to Device
	Wire.beginTransmission(_Address);

	// Send Command
	Wire.write(_Register);

	// Close I2C Connection
	Wire.endTransmission();

	// Read Register
	Wire.requestFrom(_Address, (uint8_t)1);

	// Control for Response
	if (Wire.available()) {
		
		// Read Response
		_Response = Wire.read();

	} else {

		// Set Error Variable
		_Response = 0xFF;

	}
	
	// End Function
	return(_Response);

}
bool _I2C_Functions::Write_Register(uint8_t _Address, uint8_t _Register, uint8_t _Data, bool _Stop) {

	// Connect to Device
	Wire.beginTransmission(_Address);

	// Send Register Address
	Wire.write(_Register);

	// Send Data
	Wire.write(_Data);

	// Close I2C Connection
	uint8_t _Result = Wire.endTransmission(_Stop);

	// Control For Result
	//if (_Result != 0) return(false);

	// End Function
	return(true);

}
bool _I2C_Functions::Write_Command(uint8_t _Address, uint8_t _Command, bool _Stop) {

	// Connect to Device
	Wire.beginTransmission(_Address);

	// Send Register Address
	Wire.write(_Command);

	// Close I2C Connection
	uint8_t _Result = Wire.endTransmission(_Stop);

	// Control For Result
	if (_Result != 0) return(false);

	// End Function
	return(true);

}
bool _I2C_Functions::Read_Multiple_Register(uint8_t _Address, uint8_t _Register, uint8_t * _Data, uint8_t _Length, bool _Stop) {

	// Connect to Device
	Wire.beginTransmission(_Address);

	// Send Register Address
	Wire.write(_Register);

	// Close I2C Connection
	uint8_t _Result = Wire.endTransmission(_Stop);

	// Control For Result
	if (_Result != 0) return(false);

	// Send Read Request
	Wire.requestFrom(_Address, _Length);

	// Read Registers
	for (size_t i = 0; i < _Length; i++) {

		// Get Response
		_Data[i] = Wire.read();

	}

	// End Function
	return(true);

}
bool _I2C_Functions::Write_Multiple_Register(uint8_t _Address, uint8_t _Register, uint8_t * _Data, uint8_t _Length) {

	// Connect to Device
	Wire.beginTransmission(_Address);

	// Send Register Address
	Wire.write(_Register);

	// Write Registers Loop
	for (size_t i = 0; i < _Length; i++) {

		// Write Register
		Wire.write(_Data[i]);

	}

	// Close I2C Connection
	uint8_t _Result = Wire.endTransmission();

	// Control For Result
	if (_Result != 0) return(false);

	// End Function
	return(true);

}

bool _I2C_Functions::Set_Register_Bit(uint8_t _Address, uint8_t _Register, uint8_t _Bit_Number, bool _Stop) {

	// Declare Response Variable
	uint8_t _Response = 0x00;

	// Declare Variable
	bool _Write_Response = false;

	// Read Register
	_Response = Read_Register(_Address, _Register);

	// Set Bit
	_Response = bitSet(_Response, _Bit_Number);

	// Write Register
	_Write_Response = Write_Register(_Address, _Register, _Response, _Stop);

	// End Function
	return(_Write_Response);

}
bool _I2C_Functions::Clear_Register_Bit(uint8_t _Address, uint8_t _Register, uint8_t _Bit_Number, bool _Stop) {
	
	// Declare Response Variable
	uint8_t _Response = 0x00;

	// Declare Variable
	bool _Write_Response = false;

	// Read Register
	_Response = Read_Register(_Address, _Register);

	// Set Bit
	_Response = bitClear(_Response, _Bit_Number);

	// Write Register
	_Write_Response = Write_Register(_Address, _Register, _Response, _Stop);

	// End Function
	return(_Write_Response);

}
bool _I2C_Functions::Read_Register_Bit(uint8_t _Address, uint8_t _Register, uint8_t _Bit_Number) {
	
	// Declare Response Variable
	uint8_t _Response = 0x00;

	// Declare Bit Variable
	bool _Bit_Value = false;

	// Read Register
	_Response = Read_Register(_Address, _Register);

	// Read Bit
	_Bit_Value = bitRead(_Response, _Bit_Number);

	// End Function
	return(_Bit_Value);

}

bool _I2C_Functions::Set_Multiplexer(uint8_t _Address, uint8_t _Channel) {

	// Control for Channel
	if (_Channel > 8 or _Channel < 0) return(false);

	// Control for Current Channel
	if (_Channel != _Multiplexer_Current_Channel) {
		
		// Connect I2C Multiplexer
		Wire.beginTransmission(_Address);

		// Change Channel
		if (_Channel == 0) 	Wire.write(0x00);	// Turn Multiplexer OFF
		if (_Channel == 1) 	Wire.write(0x01);	// Turn Multiplexer to CH1
		if (_Channel == 2) 	Wire.write(0x02);	// Turn Multiplexer to CH2
		if (_Channel == 3) 	Wire.write(0x04);	// Turn Multiplexer to CH3
		if (_Channel == 4) 	Wire.write(0x08);	// Turn Multiplexer to CH4
		if (_Channel == 5) 	Wire.write(0x10);	// Turn Multiplexer to CH5
		if (_Channel == 6) 	Wire.write(0x20);	// Turn Multiplexer to CH6
		if (_Channel == 7) 	Wire.write(0x40);	// Turn Multiplexer to CH7
		if (_Channel == 8) 	Wire.write(0x80);	// Turn Multiplexer to CH8

		// Close I2C Connection
		uint8_t _Result = Wire.endTransmission();

		// Control For Result
		if (_Result != 0) return(false);

		// Set Variable
		_Multiplexer_Current_Channel = _Channel;

		// Delay
		delay(20);

		// End Function
		return(true);

	} 

}

// Define Library Class
_I2C_Functions I2C;

// 1903