#ifndef __I2C_Functions__
#define __I2C_Functions__

	// Include Arduino Library
	#ifndef Arduino_h
		#include <Arduino.h>
	#endif

	// Include Wire Library
	#ifndef WIRE_H
		#include <Wire.h>
	#endif

	// Include Definitions
	#include "Definition.h"

	// I2C Control Functions
	class I2C_Functions {

		// Private Context
		private:

			// Library Variable Structure
			struct Library_Variable_Structure {

				// Declare TWI Object
				TwoWire * TWI = nullptr;

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

			bool TWI_Ready(void) {

				// End Function
				return(this->Variables.TWI_Start && this->Variables.TWI != nullptr);

			}

			uint8_t Resolve_Mux_Channel(const uint8_t _Mux_Channel) {

				// Control for Mux Channel
				switch (_Mux_Channel) {
					case 1: return(__Mux_Channel_1__);
					case 2: return(__Mux_Channel_2__);
					case 3: return(__Mux_Channel_3__);
					case 4: return(__Mux_Channel_4__);
					case 5: return(__Mux_Channel_5__);
					case 6: return(__Mux_Channel_6__);
					case 7: return(__Mux_Channel_7__);
					case 8: return(__Mux_Channel_8__);
					default: return(__Mux_Channel_Off__);
				}

			}

			bool Device_Ready(void) {

				// Control for TWI Start
				if (!this->TWI_Ready()) return(false);

				// Control for Device Detect
				if (!this->Variables.Device.Detect) return(false);

				// Set Multiplexer
				if (this->Variables.Multiplexer.Enable && !this->Set_Mux_Channel()) return(false);

				// End Function
				return(true);

			}

			bool Begin_Device_Transmission(void) {

				// Control for Device Status
				if (!this->Device_Ready()) return(false);

				// Connect to Device
				this->Variables.TWI->beginTransmission(this->Variables.Device.Address);

				// End Function
				return(true);

			}

			bool End_Device_Transmission(const bool _Stop = true) {

				// End Function
				return(this->Variables.TWI->endTransmission(_Stop) == 0);

			}

			bool Write_Buffer(const uint8_t * _Data, const uint8_t _Length) {

				// Control for Data Pointer
				if (_Length > 0 && _Data == nullptr) return(false);

				// Write Registers Loop
				for (uint8_t i = 0; i < _Length; i++) this->Variables.TWI->write(_Data[i]);

				// End Function
				return(true);

			}

			bool Read_Buffer(uint8_t * _Data, const uint8_t _Length) {

				// Control for Data Pointer
				if (_Length > 0 && _Data == nullptr) return(false);

				// Control for Length
				if (_Length == 0) return(true);

				// Read Request
				uint8_t _Received_Length = this->Variables.TWI->requestFrom(this->Variables.Device.Address, _Length);

				// Control for Response Length
				if (_Received_Length != _Length) {

					// Flush Incomplete Response
					while (this->Variables.TWI->available()) this->Variables.TWI->read();

					// End Function
					return(false);

				}

				// Read Registers
				for (uint8_t i = 0; i < _Length; i++) {

					// Control for Response
					if (!this->Variables.TWI->available()) return(false);

					// Get Response
					_Data[i] = this->Variables.TWI->read();

				}

				// End Function
				return(true);

			}

		// Public Context
		public:

			// Object constructor of I2C library.
			explicit I2C_Functions(uint8_t _Address, bool _Mux_Enable = false, uint8_t _Mux_Channel = 0) {

				// Set Variables
				this->Variables.Device.Detect = false;
				this->Variables.Device.Address = _Address;
				this->Variables.Multiplexer.Enable = _Mux_Enable;
				this->Variables.Multiplexer.Channel = this->Resolve_Mux_Channel(_Mux_Channel);

				// Set Mux Channel
				if (!_Mux_Enable) this->Variables.Multiplexer.Channel = __Mux_Channel_Off__;

				// Set TWI Start Variable
				this->Variables.TWI_Start = false;

			}

			// Start TWI Connection
			void Begin(TwoWire *_TWI = &Wire) {

				// Set TWI Object
				this->Variables.TWI = (_TWI != nullptr) ? _TWI : &Wire;

				// Start TWI
				this->Variables.TWI->begin();

				// Set TWI Start Variable
				this->Variables.TWI_Start = true;

				// Detect Device
				this->Detect_Device();

			}

			// End TWI Connection
			void End(void) {

				// Control for TWI Start
				if (!this->TWI_Ready()) return;

				// End TWI
				this->Variables.TWI->end();

				// Set TWI Start Variable
				this->Variables.TWI_Start = false;

			}

			// I2C device controller.
			void Detect_Device(void) {

				// Control for TWI Start
				if (!this->TWI_Ready()) {

					// Set Device
					this->Variables.Device.Detect = false;

					// End Function
					return;

				}

				// Set Multiplexer
				if (this->Variables.Multiplexer.Enable && !this->Set_Mux_Channel()) {

					// Set Device
					this->Variables.Device.Detect = false;

					// End Function
					return;

				}

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

			// Try to read a single byte from specified register on I2C device.
			bool Try_Read_Register(const uint8_t _Register, uint8_t * _Data) {

				// Control for Data Pointer
				if (_Data == nullptr) return(false);

				// Connect to Device
				if (!this->Begin_Device_Transmission()) return(false);

				// Send Command
				this->Variables.TWI->write(_Register);

				// Close I2C Connection
				if (!this->End_Device_Transmission()) return(false);

				// Read Register
				if (!this->Read_Buffer(_Data, 1)) return(false);

				// End Function
				return(true);

			}

			// Try to read a single word from specified register on I2C device.
			bool Try_Read_Register_Word(const uint8_t _Register, uint16_t * _Data) {

				// Control for Data Pointer
				if (_Data == nullptr) return(false);

				// Declare Data Variable
				uint8_t _Buffer[2] = {0x00, 0x00};

				// Connect to Device
				if (!this->Begin_Device_Transmission()) return(false);

				// Send Command
				this->Variables.TWI->write(_Register);

				// Close I2C Connection
				if (!this->End_Device_Transmission()) return(false);

				// Read Register
				if (!this->Read_Buffer(_Buffer, 2)) return(false);

				// Combine Read Bytes
				*_Data = ((uint16_t)(_Buffer[1]) << 8 | (uint16_t)_Buffer[0]);

				// End Function
				return(true);

			}

			// Try to read multiple data on specified register.
			bool Try_Read_Multiple_Register(const uint8_t _Register, uint8_t * _Data, const uint8_t _Length, const bool _Stop = true) {

				// Control for Data Pointer
				if (_Length > 0 && _Data == nullptr) return(false);

				// Connect to Device
				if (!this->Begin_Device_Transmission()) return(false);

				// Send Register Address
				this->Variables.TWI->write(_Register);

				// Close I2C Connection
				if (!this->End_Device_Transmission(_Stop)) return(false);

				// Read Registers
				if (!this->Read_Buffer(_Data, _Length)) return(false);

				// End Function
				return(true);

			}

			// Try to read multiple data on specified 16-bit register.
			bool Try_Read_Multiple_Register_u16(const uint16_t _Register, uint8_t * _Data, const uint8_t _Length, const bool _Stop = true) {

				// Control for Data Pointer
				if (_Length > 0 && _Data == nullptr) return(false);

				// Connect to Device
				if (!this->Begin_Device_Transmission()) return(false);

				// Declare Register Low and High address
				uint8_t _Register_Low = (uint8_t)(0x00FF & (uint16_t)_Register);
				uint8_t _Register_High = (uint8_t)((0xFF00 & (uint16_t)_Register) >> 8);

				// Send Register Address
				this->Variables.TWI->write(_Register_High);
				this->Variables.TWI->write(_Register_Low);

				// Close I2C Connection
				if (!this->End_Device_Transmission(_Stop)) return(false);

				// Read Registers
				if (!this->Read_Buffer(_Data, _Length)) return(false);

				// End Function
				return(true);

			}

			// Try to read multiple data without writing a register command.
			bool Try_Read_Multiple_Register_u16_NoCMD(uint8_t * _Data, const uint8_t _Length) {

				// Control for Data Pointer
				if (_Length > 0 && _Data == nullptr) return(false);

				// Control for Device Status
				if (!this->Device_Ready()) return(false);

				// Read Registers
				if (!this->Read_Buffer(_Data, _Length)) return(false);

				// End Function
				return(true);

			}

			// Try to read a single bit from specified register on I2C device.
			bool Try_Read_Register_Bit(const uint8_t _Register, const uint8_t _Bit_Number, bool * _Bit_Value) {

				// Control for Data Pointer
				if (_Bit_Value == nullptr) return(false);

				// Control for Bit Number
				if (_Bit_Number > 7) return(false);

				// Declare Response Variable
				uint8_t _Response = 0x00;

				// Read Register
				if (!this->Try_Read_Register(_Register, &_Response)) return(false);

				// Read Bit
				*_Bit_Value = bitRead(_Response, _Bit_Number);

				// End Function
				return(true);

			}

			// Read specified register on I2C device.
			uint8_t Read_Register(const uint8_t _Register) {

				// Declare Response Variable
				uint8_t _Response = 0x00;

				// Read Register
				if (!this->Try_Read_Register(_Register, &_Response)) _Response = 0x00;
				
				// End Function
				return(_Response);

			}

			// Read specified register on I2C device.
			uint16_t Read_Register_Word(const uint8_t _Register) {

				// Declare Response Variable
				uint16_t _Response = 0x0000;

				// Read Register
				if (!this->Try_Read_Register_Word(_Register, &_Response)) _Response = 0x0000;

				// End Function
				return(_Response);

			}

			// Read multiple data on specified register.
			bool Read_Multiple_Register(const uint8_t _Register, uint8_t * _Data, const uint8_t _Length, const bool _Stop = true) {

				// End Function
				return(this->Try_Read_Multiple_Register(_Register, _Data, _Length, _Stop));

			}

			// Read multiple data on specified register.
			bool Read_Multiple_Register_u16(const uint16_t _Register, uint8_t * _Data, const uint8_t _Length, const bool _Stop = true) {

				// End Function
				return(this->Try_Read_Multiple_Register_u16(_Register, _Data, _Length, _Stop));

			}

			// Read multiple data on specified register.
			bool Read_Multiple_Register_u16_NoCMD(uint8_t * _Data, const uint8_t _Length) {

				// End Function
				return(this->Try_Read_Multiple_Register_u16_NoCMD(_Data, _Length));

			}

			// Try to write data to specified register on I2C device.
			bool Try_Write_Register(const uint8_t _Register, const uint8_t _Data, const bool _Stop = true) {

				// Connect to Device
				if (!this->Begin_Device_Transmission()) return(false);

				// Send Register Address
				this->Variables.TWI->write(_Register);

				// Send Data
				this->Variables.TWI->write(_Data);

				// Close I2C Connection
				if (!this->End_Device_Transmission(_Stop)) return(false);

				// End Function
				return(true);

			}

			// Try to write multiple data to specified register on I2C device.
			bool Try_Write_Multiple_Register(const uint8_t _Register, const uint8_t * _Data, const uint8_t _Length) {

				// Control for Data Pointer
				if (_Length > 0 && _Data == nullptr) return(false);

				// Connect to Device
				if (!this->Begin_Device_Transmission()) return(false);

				// Send Register Address
				this->Variables.TWI->write(_Register);

				// Write Data Buffer
				if (!this->Write_Buffer(_Data, _Length)) return(false);

				// Close I2C Connection
				if (!this->End_Device_Transmission()) return(false);

				// End Function
				return(true);

			}

			// Try to write command to I2C device.
			bool Try_Write_Command(const uint8_t _Command, const bool _Stop = true) {

				// Connect to Device
				if (!this->Begin_Device_Transmission()) return(false);

				// Send Command
				this->Variables.TWI->write(_Command);

				// Close I2C Connection
				if (!this->End_Device_Transmission(_Stop)) return(false);

				// End Function
				return(true);

			}

			// Try to write multiple command to I2C device.
			bool Try_Write_Multiple_Command(const uint8_t * _Command, const uint8_t _Length) {

				// Control for Data Pointer
				if (_Length > 0 && _Command == nullptr) return(false);

				// Connect to Device
				if (!this->Begin_Device_Transmission()) return(false);

				// Write Command Buffer
				if (!this->Write_Buffer(_Command, _Length)) return(false);

				// Close I2C Connection
				if (!this->End_Device_Transmission()) return(false);

				// End Function
				return(true);

			}

			// Write data to specified register on I2C device.
			bool Write_Register(const uint8_t _Register, const uint8_t _Data, const bool _Stop = true) {

				// End Function
				return(this->Try_Write_Register(_Register, _Data, _Stop));

			}

			// Write multiple data to specified register.
			bool Write_Multiple_Register(const uint8_t _Register, const uint8_t * _Data, const uint8_t _Length) {

				// End Function
				return(this->Try_Write_Multiple_Register(_Register, _Data, _Length));

			}

			// Write command to I2C device.
			bool Write_Command(const uint8_t _Command, const bool _Stop = true) {

				// End Function
				return(this->Try_Write_Command(_Command, _Stop));

			}

			// Write multiple command to I2C device.
			bool Write_Multiple_Command(const uint8_t * _Command, const uint8_t _Length) {

				// End Function
				return(this->Try_Write_Multiple_Command(_Command, _Length));

			}

			// Set specified register bit on I2C device.
			bool Set_Register_Bit(const uint8_t _Register, const uint8_t _Bit_Number, const bool _Stop = true) {

				// Control for TWI Start
				if (!this->TWI_Ready()) return(false);

				// Control for Bit Number
				if (_Bit_Number > 7) return(false);

				// Control for Device
				if (this->Variables.Device.Detect) {

					// Declare Response Variable
					uint8_t _Response = 0x00;

					// Read Register
					if (!this->Try_Read_Register(_Register, &_Response)) return(false);

					// Control Bit value
					if (bitRead(_Response, _Bit_Number) == false) {

						// Set Bit
						bitSet(_Response, _Bit_Number);

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
			bool Clear_Register_Bit(const uint8_t _Register, const uint8_t _Bit_Number, const bool _Stop = true) {

				// Control for TWI Start
				if (!this->TWI_Ready()) return(false);

				// Control for Bit Number
				if (_Bit_Number > 7) return(false);

				// Control for Device
				if (this->Variables.Device.Detect) {

					// Declare Response Variable
					uint8_t _Response = 0x00;

					// Read Register
					if (!this->Try_Read_Register(_Register, &_Response)) return(false);

					// Control Bit value
					if (bitRead(_Response, _Bit_Number) == true) {

						// Set Bit
						bitClear(_Response, _Bit_Number);

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
			bool Read_Register_Bit(const uint8_t _Register, const uint8_t _Bit_Number) {

				// Read Bit
				bool _Bit_Value = false;

				// Read Register Bit
				if (!this->Try_Read_Register_Bit(_Register, _Bit_Number, &_Bit_Value)) _Bit_Value = false;

				// End Function
				return(_Bit_Value);

			}

			// Set multiplexer channel.
			bool Set_Mux_Channel(void) {

				// Declare Result Variable
				bool _Result = true;

				// Control for TWI Start
				if (!this->TWI_Ready()) return(false);

				// Control for Multiplexer
				if (this->Variables.Multiplexer.Enable) {

					// Read Current Channel
					if (this->Variables.TWI->requestFrom((uint8_t)__Mux_Address__, (uint8_t)1) != 1) return(false);
					if (!this->Variables.TWI->available()) return(false);
					uint8_t _Current_Channel = this->Variables.TWI->read();
					this->Variables.Multiplexer.Current_Channel = _Current_Channel;

					// Coltrol for Current Mux Channel
					if (_Current_Channel != this->Variables.Multiplexer.Channel) {

						// Connect I2C Multiplexer
						this->Variables.TWI->beginTransmission((uint8_t)__Mux_Address__);

						// Change Channel
						this->Variables.TWI->write((uint8_t)this->Variables.Multiplexer.Channel);

						// Control For Result
						if (this->Variables.TWI->endTransmission() != 0) _Result = false;
						else this->Variables.Multiplexer.Current_Channel = this->Variables.Multiplexer.Channel;

					} 

				}

				// End Function
				return(_Result);

			}

			// Get I2C Address
			uint8_t Address(void) {

				// End Function
				return(this->Variables.Device.Address);

			}

			// Get I2C Detect
			bool Detect(void) {

				// End Function
				return(this->Variables.Device.Detect);

			}

			// Get I2C Multiplexer Enable
			bool Mux_Enable(void) {

				// End Function
				return(this->Variables.Multiplexer.Enable);

			}

			// Get I2C Multiplexer Channel
			uint8_t Mux_Channel(void) {

				// End Function
				return(this->Variables.Multiplexer.Channel);

			}

	};

#endif /* defined(__I2C_Functions__) */