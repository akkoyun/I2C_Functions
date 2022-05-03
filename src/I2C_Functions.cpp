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
I2C_Functions::I2C_Functions(uint8_t _Address, bool _Mux_Enable, uint8_t _Mux_Channel) : TWI_Address(_Address), TWI_Device(false), Multiplexer_Enable(_Mux_Enable), TWI_Device_Mux_Channel(_Mux_Channel) {

	// Start TWI
	Wire.begin();

	// Set Mux Off
	if (this->Multiplexer_Enable) {

		// Set Mux Channel
		if (_Mux_Channel == 0) this->TWI_Device_Mux_Channel = __Mux_Channel_Off__;
		if (_Mux_Channel == 1) this->TWI_Device_Mux_Channel = __Mux_Channel_1__;
		if (_Mux_Channel == 2) this->TWI_Device_Mux_Channel = __Mux_Channel_2__;
		if (_Mux_Channel == 3) this->TWI_Device_Mux_Channel = __Mux_Channel_3__;
		if (_Mux_Channel == 4) this->TWI_Device_Mux_Channel = __Mux_Channel_4__;
		if (_Mux_Channel == 5) this->TWI_Device_Mux_Channel = __Mux_Channel_5__;
		if (_Mux_Channel == 6) this->TWI_Device_Mux_Channel = __Mux_Channel_6__;
		if (_Mux_Channel == 7) this->TWI_Device_Mux_Channel = __Mux_Channel_7__;
		if (_Mux_Channel == 8) this->TWI_Device_Mux_Channel = __Mux_Channel_8__;

		// Connect I2C Multiplexer
		Wire.beginTransmission(__Mux_Address__);

		// Change Channel
		Wire.write((uint8_t)0x00);

		// Control For Result
		Wire.endTransmission();

	}

	// Control for Device
	this->Control_Device();

}
uint8_t I2C_Functions::Read_Register(uint8_t _Register) {

	// Declare Response Variable
	uint8_t _Response = 0x00;

	// Control for Multiplexer
	this->Set_Multiplexer();

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
	this->Set_Multiplexer();

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
	this->Set_Multiplexer();

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
	this->Set_Multiplexer();

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
	this->Set_Multiplexer();

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
	this->Set_Multiplexer();

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
	this->Set_Multiplexer();

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
	this->Set_Multiplexer();

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

	// Set Mux Channel
	this->Set_Multiplexer();

	// Connect to Device
	Wire.beginTransmission(this->TWI_Address);

	// Close I2C Connection
	if (Wire.endTransmission() != 0) {

		// Set Device
		this->TWI_Device = false;

	} else {

		// Set Device
		this->TWI_Device = true;

	}

	// End Function
	return(this->TWI_Device);

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
uint8_t I2C_Functions::Mux(void) {

	// End Functions
	return(this->TWI_Device_Mux_Channel);

}

// Multiplexer Functions
bool I2C_Functions::Set_Multiplexer(void) {

	// Declare Result Variable
	bool Result = true;

	// Control for Multiplexer
	if (this->Multiplexer_Enable) {

		// Coltrol for Current Mux Channel
		if (this->_Multiplexer_Current_Channel != this->TWI_Device_Mux_Channel) {

			// Connect I2C Multiplexer
			Wire.beginTransmission(__Mux_Address__);

			// Change Channel
			Wire.write((uint8_t)this->TWI_Device_Mux_Channel);

			// Control For Result
			if (Wire.endTransmission() != 0) Result = false;

			// Set Variable
			this->_Multiplexer_Current_Channel = this->TWI_Device_Mux_Channel;

		} 

	}

	// End Function
	return(Result);

}

// 1903