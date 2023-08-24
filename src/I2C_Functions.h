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

	// Include Definitions
	#include "Definition.h"

	// I2C Control Functions
	class I2C_Functions {

		// Public Context
		public:

			// Library Variable Structure
			struct Library_Variable_Structure {

				// Declare TWI Object
				TwoWire * TWI;

				// Declare Object Start Variable
				bool TWI_Start = false;

				// Device Structure
				struct Device_Structure {

					// Object I2C address variable.
					uint8_t Address = 0x00;

					// Object detect variable.
					bool Detect = false;

				} Device;

				// Multiplexer Structure
				struct Multiplexer_Structure {

					// Object multiplexer enable variable.
					bool Enable = false;

					// Object multiplexer channel variable.
					uint8_t Channel = __Mux_Channel_Off__;

					// Object multiplexer current channel variable.
					uint8_t Current_Channel = __Mux_Channel_Off__;

				} Multiplexer;

			} Variables;

			// Object constructor of I2C library.
			I2C_Functions(uint8_t _Address, bool _Mux_Enable = false, uint8_t _Mux_Channel = 0) {

				// Set Variables
				this->Variables.Device.Detect = false;
				this->Variables.Device.Address = _Address;
				this->Variables.Multiplexer.Enable = _Mux_Enable;

				// Set Mux Channel
				if (_Mux_Enable) {

					// Set Mux Channel
					if (_Mux_Channel == 0) this->Variables.Multiplexer.Channel = __Mux_Channel_Off__;
					else if (_Mux_Channel == 1) this->Variables.Multiplexer.Channel = __Mux_Channel_1__;
					else if (_Mux_Channel == 2) this->Variables.Multiplexer.Channel = __Mux_Channel_2__;
					else if (_Mux_Channel == 3) this->Variables.Multiplexer.Channel = __Mux_Channel_3__;
					else if (_Mux_Channel == 4) this->Variables.Multiplexer.Channel = __Mux_Channel_4__;
					else if (_Mux_Channel == 5) this->Variables.Multiplexer.Channel = __Mux_Channel_5__;
					else if (_Mux_Channel == 6) this->Variables.Multiplexer.Channel = __Mux_Channel_6__;
					else if (_Mux_Channel == 7) this->Variables.Multiplexer.Channel = __Mux_Channel_7__;
					else if (_Mux_Channel == 8) this->Variables.Multiplexer.Channel = __Mux_Channel_8__;

				}

				// Set TWI Start Variable
				this->Variables.TWI_Start = false;

			}

			// Start TWI Connection
			void Begin(TwoWire *_TWI = &Wire) {

				// Set TWI Object
				this->Variables.TWI = _TWI;

				// Start TWI
				this->Variables.TWI->begin();

				// Set TWI Start Variable
				this->Variables.TWI_Start = true;

				// Detect Device
				this->Detect_Device();

			}

			// End TWI Connection
			void End(void) {

				// End TWI
				this->Variables.TWI->end();

				// Set TWI Start Variable
				this->Variables.TWI_Start = false;

			}

			// I2C device controller.
			void Detect_Device(void) {

				// Set Multiplexer
				this->Set_Mux_Channel();
				
				// Connect to Device
				this->Variables.TWI->beginTransmission(this->Variables.Device.Address);

				// Close I2C Connection
				if (this->Variables.TWI->endTransmission() != 0) {

					// Set Device
					this->Variables.Device.Detect = false;

				} else {

					// Set Device
					this->Variables.Device.Detect = true;

				}

			}

			// Read specified register on I2C device.
			uint8_t Read_Register(uint8_t _Register) {

				// Control for TWI Start
				if (!this->Variables.TWI_Start) return(false);

				// Declare Response Variable
				uint8_t _Response = 0x00;

				// Control for Device
				if (this->Variables.Device.Detect) {

					// Set Multiplexer
					if (this->Variables.Multiplexer.Enable)	this->Set_Mux_Channel();

					// Connect to Device
					this->Variables.TWI->beginTransmission(this->Variables.Device.Address);

					// Send Command
					this->Variables.TWI->write(_Register);

					// Close I2C Connection
					this->Variables.TWI->endTransmission();

					// Read Register
					this->Variables.TWI->requestFrom(this->Variables.Device.Address, (uint8_t)1);

					// Control for Response
					if (this->Variables.TWI->available()) {
						
						// Read Response
						_Response = this->Variables.TWI->read();

					} else {

						// Set Error Variable
						_Response = 0x00;

					}

				} else {

					// Set Error Variable
					_Response = 0x00;

				}
				
				// End Function
				return(_Response);

			}

			// Read specified register on I2C device.
			uint16_t Read_Register_Word(uint8_t _Register) {

				// Control for TWI Start
				if (!this->Variables.TWI_Start) return(false);

				// Declare Response Variable
				uint16_t _Response = 0x0000;

				// Declare Data Variable
				uint8_t _Data[2] = {0x00, 0x00};

				// Control for Device
				if (this->Variables.Device.Detect) {

					// Set Multiplexer
					if (this->Variables.Multiplexer.Enable)	this->Set_Mux_Channel();

					// Connect to Device
					this->Variables.TWI->beginTransmission(this->Variables.Device.Address);

					// Send Command
					this->Variables.TWI->write(_Register);

					// Close I2C Connection
					this->Variables.TWI->endTransmission();

					// Read Register
					this->Variables.TWI->requestFrom(this->Variables.Device.Address, (uint8_t)2);

					// Control for Response
					if (this->Variables.TWI->available()) {

						// Get Response
						_Data[0] = this->Variables.TWI->read();
						_Data[1] = this->Variables.TWI->read();

					} else {

						// Set Error Variable
						_Response = 0x00;

					}

				} else {

					// Set Error Variable
					_Response = 0x00;

				}

				// Combine Read Bytes
				_Response = ((uint16_t)(_Data[1]) << 8 | (uint16_t)_Data[0]);

				// End Function
				return(_Response);

			}

			// Read multiple data on specified register.
			bool Read_Multiple_Register(uint8_t _Register, uint8_t * _Data, uint8_t _Length, bool _Stop) {

				// Control for TWI Start
				if (!this->Variables.TWI_Start) return(false);

				// Control for Device
				if (this->Variables.Device.Detect) {

					// Set Multiplexer
					if (this->Variables.Multiplexer.Enable)	this->Set_Mux_Channel();

					// Connect to Device
					this->Variables.TWI->beginTransmission(this->Variables.Device.Address);

					// Send Register Address
					this->Variables.TWI->write(_Register);

					// Close I2C Connection
					uint8_t _Result = this->Variables.TWI->endTransmission(_Stop);

					// Control For Result
					if (_Result != 0) return(false);

					// Send Read Request
					this->Variables.TWI->requestFrom(this->Variables.Device.Address, _Length);

					// Read Registers
					for (size_t i = 0; i < _Length; i++) {

						// Get Response
						_Data[i] = this->Variables.TWI->read();

					}

				} else {

					// End Function
					return(false);

				}

				// End Function
				return(true);

			}

			// Read multiple data on specified register.
			bool Read_Multiple_Register_u16(uint16_t _Register, uint8_t * _Data, uint8_t _Length, bool _Stop) {

				// Control for TWI Start
				if (!this->Variables.TWI_Start) return(false);

				// Control for Device
				if (this->Variables.Device.Detect) {

					// Set Multiplexer
					if (this->Variables.Multiplexer.Enable)	this->Set_Mux_Channel();

					// Connect to Device
					this->Variables.TWI->beginTransmission(this->Variables.Device.Address);

					// Declare Register Low and High address
					uint8_t _Register_Low = (uint8_t)(0x00FF & (uint16_t)_Register);
					uint8_t _Register_High = (uint8_t)((0xFF00 & (uint16_t)_Register) >> 8);

					// Send Register Address
					this->Variables.TWI->write(_Register_High);
					this->Variables.TWI->write(_Register_Low);

					// Close I2C Connection
					uint8_t _Result = this->Variables.TWI->endTransmission(_Stop);

					// Control For Result
					if (_Result != 0) return(false);

					// Send Read Request
					this->Variables.TWI->requestFrom(this->Variables.Device.Address, _Length);

					// Read Registers
					for (size_t i = 0; i < _Length; i++) {

						// Get Response
						_Data[i] = this->Variables.TWI->read();

					}

				} else {

					// End Function
					return(false);

				}

				// End Function
				return(true);

			}

			// Write data to specified register on I2C device.
			bool Write_Register(uint8_t _Register, uint8_t _Data, bool _Stop) {

				// Control for TWI Start
				if (!this->Variables.TWI_Start) return(false);

				// Control for Device
				if (this->Variables.Device.Detect) {

					// Set Multiplexer
					if (this->Variables.Multiplexer.Enable)	this->Set_Mux_Channel();

					// Connect to Device
					this->Variables.TWI->beginTransmission(this->Variables.Device.Address);

					// Send Register Address
					this->Variables.TWI->write(_Register);

					// Send Data
					this->Variables.TWI->write(_Data);

					// Close I2C Connection
					uint8_t _Result = this->Variables.TWI->endTransmission(_Stop);

					// Control For Result
					if (_Result != 0) return(false);

				} else {

					// End Function
					return(false);

				}

				// End Function
				return(true);

			}

			// Write multiple data to specified register.
			bool Write_Multiple_Register(uint8_t _Register, uint8_t * _Data, uint8_t _Length) {

				// Control for TWI Start
				if (!this->Variables.TWI_Start) return(false);

				// Control for Device
				if (this->Variables.Device.Detect) {

					// Set Multiplexer
					if (this->Variables.Multiplexer.Enable)	this->Set_Mux_Channel();

					// Connect to Device
					this->Variables.TWI->beginTransmission(this->Variables.Device.Address);

					// Send Register Address
					this->Variables.TWI->write(_Register);

					// Write Registers Loop
					for (size_t i = 0; i < _Length; i++) this->Variables.TWI->write(_Data[i]);

					// Close I2C Connection
					uint8_t _Result = this->Variables.TWI->endTransmission();

					// Control For Result
					if (_Result != 0) return(false);

				} else {

					// End Function
					return(false);

				}

				// End Function
				return(true);

			}

			// Write command to I2C device.
			bool Write_Command(uint8_t _Command, bool _Stop) {

				// Control for TWI Start
				if (!this->Variables.TWI_Start) return(false);

				// Control for Device
				if (this->Variables.Device.Detect) {

					// Set Multiplexer
					if (this->Variables.Multiplexer.Enable)	this->Set_Mux_Channel();

					// Connect to Device
					this->Variables.TWI->beginTransmission(this->Variables.Device.Address);

					// Send Register Address
					this->Variables.TWI->write(_Command);

					// Close I2C Connection
					uint8_t _Result = this->Variables.TWI->endTransmission(_Stop);

					// Control For Result
					if (_Result != 0) return(false);

				} else {

					// End Function
					return(false);

				}

				// End Function
				return(true);

			}

			// Write multiple command to I2C device.
			bool Write_Multiple_Command(uint8_t * _Command, uint8_t _Length) {

				// Control for TWI Start
				if (!this->Variables.TWI_Start) return(false);

				// Control for Device
				if (this->Variables.Device.Detect) {

					// Set Multiplexer
					if (this->Variables.Multiplexer.Enable)	this->Set_Mux_Channel();

					// Connect to Device
					this->Variables.TWI->beginTransmission(this->Variables.Device.Address);

					// Write Registers Loop
					for (size_t i = 0; i < _Length; i++) this->Variables.TWI->write(_Command[i]);

					// Close I2C Connection
					uint8_t _Result = this->Variables.TWI->endTransmission();

					// Control For Result
					if (_Result != 0) return(false);

				} else {

					// End Function
					return(false);

				}

				// End Function
				return(true);

			}

			// Set specified register bit on I2C device.
			bool Set_Register_Bit(uint8_t _Register, uint8_t _Bit_Number, bool _Stop) {

				// Control for TWI Start
				if (!this->Variables.TWI_Start) return(false);

				// Control for Device
				if (this->Variables.Device.Detect) {

					// Set Multiplexer
					if (this->Variables.Multiplexer.Enable)	this->Set_Mux_Channel();

					// Read Register
					uint8_t _Response = this->Read_Register(_Register);

					// Control Bit value
					if (bitRead(_Response, _Bit_Number) == false) {

						// Set Bit
						_Response = bitSet(_Response, _Bit_Number);

						// Write Register
						bool _Write_Response = this->Write_Register(_Register, _Response, _Stop);

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

			// Clear specified register bit on I2C device.
			bool Clear_Register_Bit(uint8_t _Register, uint8_t _Bit_Number, bool _Stop) {

				// Control for TWI Start
				if (!this->Variables.TWI_Start) return(false);

				// Control for Device
				if (this->Variables.Device.Detect) {

					// Set Multiplexer
					if (this->Variables.Multiplexer.Enable)	this->Set_Mux_Channel();

					// Read Register
					uint8_t _Response = this->Read_Register(_Register);

					// Control Bit value
					if (bitRead(_Response, _Bit_Number) == true) {

						// Set Bit
						_Response = bitClear(_Response, _Bit_Number);

						// Write Register
						bool _Write_Response = this->Write_Register(_Register, _Response, _Stop);

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

			// Read specified register bit on I2C device.
			bool Read_Register_Bit(uint8_t _Register, uint8_t _Bit_Number) {

				// Control for TWI Start
				if (!this->Variables.TWI_Start) return(false);

				// Set Multiplexer
				if (this->Variables.Multiplexer.Enable)	this->Set_Mux_Channel();

				// Read Register
				uint8_t _Response = this->Read_Register(_Register);

				// Read Bit
				bool _Bit_Value = bitRead(_Response, _Bit_Number);

				// End Function
				return(_Bit_Value);

			}

			// Set multiplexer channel.
			bool Set_Mux_Channel(void) {

				// Declare Result Variable
				bool _Result = true;

				// Control for Multiplexer
				if (this->Variables.Multiplexer.Enable) {

					// Read Current Channel
					this->Variables.TWI->requestFrom((uint8_t)__Mux_Address__, (uint8_t)1);
					uint8_t _Current_Channel = this->Variables.TWI->read();

					// Coltrol for Current Mux Channel
					if (_Current_Channel != this->Variables.Multiplexer.Channel) {

						// Connect I2C Multiplexer
						this->Variables.TWI->beginTransmission((uint8_t)__Mux_Address__);

						// Change Channel
						this->Variables.TWI->write((uint8_t)this->Variables.Multiplexer.Channel);

						// Control For Result
						if (this->Variables.TWI->endTransmission() != 0) _Result = false;

					} 

				}

				// End Function
				return(_Result);

			}



	};

#endif /* defined(__I2C_Functions__) */