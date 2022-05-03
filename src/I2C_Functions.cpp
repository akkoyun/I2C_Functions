/* *******************************************************************************
 *  Copyright (C) 2014-2022 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: Generic I2C Functions
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *********************************************************************************/

// Include Header
#include <I2C_Functions.h>

// Register Functions
I2C_Functions::I2C_Functions(uint8_t _Address, uint8_t _Mux_Channel) {

	// Start TWI
	Wire.begin();

	// Set I2C Device Address
	this->TWI_Address = _Address;

	// Set I2C Device State
	this->TWI_Device = false;

	// Set Variable
	this->TWI_Device_Mux_Channel = _Mux_Channel;

}
I2C_Functions::~I2C_Functions() {

	// Set I2C Device Address
	this->TWI_Address = 0;

	// Set I2C Device State
	this->TWI_Device = false;

	// Set Mux
	this->Set_Multiplexer(__Mux_Channel_Off__);

	// Delay
	delay(10);

}
bool I2C_Functions::Begin(void) {

	// Set Multiplexer Channel
	if (this->TWI_Device_Mux_Channel == 0) this->Set_Multiplexer(__Mux_Channel_Off__);

	// Control for Device
	this->Control_Device();

	// End Function
	return(this->TWI_Device);

}
uint8_t I2C_Functions::Read_Register(uint8_t _Register) {

	// Declare Response Variable
	uint8_t _Response = 0x00;

	// Control for Multiplexer
	if (this->TWI_Device_Mux_Channel != 0 and this->_Multiplexer_Current_Channel != this->TWI_Device_Mux_Channel) this->Set_Multiplexer(this->TWI_Device_Mux_Channel);

	// Control for Device
	if (this->TWI_Device) {

		// Connect to Device
		Wire.beginTransmission(this->TWI_Address);

		// Send Command
		Wire.write(_Register);

		// Close I2C Connection
		Wire.endTransmission();

		// Read Register
		Wire.requestFrom(this->TWI_Address, (uint8_t)1);

		// Control for Response
		if (Wire.available()) {
			
			// Read Response
			_Response = Wire.read();

		} else {

			// Set Error Variable
			_Response = NAN;

		}

	} else {

		// Set Error Variable
		_Response = NAN;

	}
	
	// End Function
	return(_Response);

}
bool I2C_Functions::Write_Register(uint8_t _Register, uint8_t _Data, bool _Stop) {

	// Control for Multiplexer
	if (this->TWI_Device_Mux_Channel != 0 and this->_Multiplexer_Current_Channel != this->TWI_Device_Mux_Channel) this->Set_Multiplexer(this->TWI_Device_Mux_Channel);

	// Control for Device
	if (this->TWI_Device) {

		// Declare Variable
		uint8_t _Result;

		// Connect to Device
		Wire.beginTransmission(this->TWI_Address);

		// Send Register Address
		Wire.write(_Register);

		// Send Data
		Wire.write(_Data);

		// Close I2C Connection
		_Result = Wire.endTransmission(_Stop);

		// Control For Result
		if (_Result != 0) return(false);

	} else {

		// End Function
		return(false);

	}

	// End Function
	return(true);

}
bool I2C_Functions::Read_Multiple_Register(uint8_t _Register, uint8_t * _Data, uint8_t _Length, bool _Stop) {

	// Control for Multiplexer
	if (this->TWI_Device_Mux_Channel != 0 and this->_Multiplexer_Current_Channel != this->TWI_Device_Mux_Channel) this->Set_Multiplexer(this->TWI_Device_Mux_Channel);

	// Control for Device
	if (this->TWI_Device) {

		// Connect to Device
		Wire.beginTransmission(this->TWI_Address);

		// Send Register Address
		Wire.write(_Register);

		// Close I2C Connection
		uint8_t _Result = Wire.endTransmission(_Stop);

		// Control For Result
		if (_Result != 0) return(false);

		// Send Read Request
		Wire.requestFrom(this->TWI_Address, _Length);

		// Read Registers
		for (size_t i = 0; i < _Length; i++) {

			// Get Response
			_Data[i] = Wire.read();

		}

	} else {

		// End Function
		return(false);

	}

	// End Function
	return(true);

}
bool I2C_Functions::Write_Multiple_Register(uint8_t _Register, uint8_t * _Data, uint8_t _Length) {

	// Control for Multiplexer
	if (this->TWI_Device_Mux_Channel != 0 and this->_Multiplexer_Current_Channel != this->TWI_Device_Mux_Channel) this->Set_Multiplexer(this->TWI_Device_Mux_Channel);

	// Control for Device
	if (this->TWI_Device) {

		// Connect to Device
		Wire.beginTransmission(this->TWI_Address);

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

	} else {

		// End Function
		return(false);

	}

	// End Function
	return(true);

}

// Command Functions
bool I2C_Functions::Write_Command(uint8_t _Command, bool _Stop) {

	// Control for Multiplexer
	if (this->TWI_Device_Mux_Channel != 0 and this->_Multiplexer_Current_Channel != this->TWI_Device_Mux_Channel) this->Set_Multiplexer(this->TWI_Device_Mux_Channel);

	// Control for Device
	if (this->TWI_Device) {

		// Connect to Device
		Wire.beginTransmission(this->TWI_Address);

		// Send Register Address
		Wire.write(_Command);

		// Close I2C Connection
		uint8_t _Result = Wire.endTransmission(_Stop);

		// Control For Result
		if (_Result != 0) return(false);

	} else {

		// End Function
		return(false);

	}

	// End Function
	return(true);

}

// Bit Functions
bool I2C_Functions::Set_Register_Bit(uint8_t _Register, uint8_t _Bit_Number, bool _Stop) {

	// Control for Multiplexer
	if (this->TWI_Device_Mux_Channel != 0 and this->_Multiplexer_Current_Channel != this->TWI_Device_Mux_Channel) this->Set_Multiplexer(this->TWI_Device_Mux_Channel);

	// Control for Device
	if (this->TWI_Device) {

		// Declare Response Variable
		uint8_t _Response = 0x00;

		// Declare Variable
		bool _Write_Response = false;

		// Read Register
		_Response = Read_Register(_Register);

		// Control Bit value
		if (bitRead(_Response, _Bit_Number) == false) {

			// Set Bit
			_Response = bitSet(_Response, _Bit_Number);

			// Write Register
			_Write_Response = Write_Register(_Register, _Response, _Stop);

			// End Function
			return(_Write_Response);

		}

	} else {

		// End Function
		return(false);

	}

	// End Function
	return(true);

}
bool I2C_Functions::Clear_Register_Bit(uint8_t _Register, uint8_t _Bit_Number, bool _Stop) {

	// Control for Multiplexer
	if (this->TWI_Device_Mux_Channel != 0 and this->_Multiplexer_Current_Channel != this->TWI_Device_Mux_Channel) this->Set_Multiplexer(this->TWI_Device_Mux_Channel);

	// Control for Device
	if (this->TWI_Device) {

		// Declare Response Variable
		uint8_t _Response = 0x00;

		// Declare Variable
		bool _Write_Response = false;

		// Read Register
		_Response = Read_Register(_Register);

		// Control Bit value
		if (bitRead(_Response, _Bit_Number) == true) {

			// Set Bit
			_Response = bitClear(_Response, _Bit_Number);

			// Write Register
			_Write_Response = Write_Register(_Register, _Response, _Stop);

			// End Function
			return(_Write_Response);

		}

	} else {

		// End Function
		return(false);

	}

	// End Function
	return(true);

}
bool I2C_Functions::Read_Register_Bit(uint8_t _Register, uint8_t _Bit_Number) {

	// Control for Multiplexer
	if (this->TWI_Device_Mux_Channel != 0 and this->_Multiplexer_Current_Channel != this->TWI_Device_Mux_Channel) this->Set_Multiplexer(this->TWI_Device_Mux_Channel);

	// Declare Response Variable
	uint8_t _Response = 0x00;

	// Declare Bit Variable
	bool _Bit_Value = false;

	// Read Register
	_Response = Read_Register(_Register);

	// Read Bit
	_Bit_Value = bitRead(_Response, _Bit_Number);

	// End Function
	return(_Bit_Value);

}

// Converter Functions
uint8_t I2C_Functions::BCDtoDEC(uint8_t _Value) {

	// Define Variable
	uint8_t _OutPut;

	// Calculate Value
	_OutPut = ((_Value / 16 * 10) + (_Value % 16));

	// End Function
	return(_OutPut);

}
uint8_t I2C_Functions::DECtoBCD(byte _Value) {

	// Define Variable
	uint8_t _OutPut;

	// Calculate Value
	_OutPut = ((_Value / 10 * 16) + (_Value % 10));

	// End Function
	return(_OutPut);

}

// Generic I2C Functions
bool I2C_Functions::Control_Device(void) {

	// Control for Multiplexer
	if (this->TWI_Device_Mux_Channel != 0 and this->_Multiplexer_Current_Channel != this->TWI_Device_Mux_Channel) this->Set_Multiplexer(this->TWI_Device_Mux_Channel);

	// Connect to Device
	Wire.beginTransmission(this->TWI_Address);

	// Close I2C Connection
	uint8_t _Result = Wire.endTransmission();

	// Control For Result
	if (_Result != 0) {

		// Set Device
		this->TWI_Device = false;

		// End Function
		return(false);

	} else {

		// Set Device
		this->TWI_Device = true;

		// End Function
		return(true);

	}

}

// Multiplexer Functions
bool I2C_Functions::Set_Multiplexer(uint8_t _Channel) {

	// Control for Channel
	if (_Channel > 8) return(false);

	// Control for Current Channel
	if (_Channel != this->_Multiplexer_Current_Channel) {
		
		// Connect I2C Multiplexer
		Wire.beginTransmission(__Mux_Address__);

		// Change Channel
		Wire.write((uint8_t)_Channel);

		// Close I2C Connection
		uint8_t _Result = Wire.endTransmission();

		// Control For Result
		if (_Result != 0) return(false);

		// Set Variable
		this->_Multiplexer_Current_Channel = _Channel;

	}

	// End Function
	return(true);

}

// Control Functions
bool I2C_Functions::Detect(void) {

	// End Functions
	return(this->TWI_Device);

}
uint8_t I2C_Functions::Address(void) {

	// End Functions
	return(this->TWI_Address);

}

// 1903