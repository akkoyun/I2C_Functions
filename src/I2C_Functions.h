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

				// Active TwoWire bus pointer (nullptr = bus not started)
				TwoWire * TWI = nullptr;

				// Device Structure
				struct Device_Structure {
					uint8_t Address = 0x00;
					bool    Detect  = false;
				} Device;

				// Multiplexer Structure
				// Channel == 0x00 (__Mux_Channel_Off__) means mux is disabled.
				// Valid channels 1-8 resolve to bitmasks 0x01-0x80.
				struct Multiplexer_Structure {
					uint8_t Channel         = __Mux_Channel_Off__;
					uint8_t Current_Channel = __Mux_Channel_Off__;
				} Multiplexer;

			} Variables;

			bool TWI_Ready(void) {
				return(this->Variables.TWI != nullptr);
			}

			uint8_t Resolve_Mux_Channel(const uint8_t _Mux_Channel) {
				if (_Mux_Channel >= 1 && _Mux_Channel <= 8) return (uint8_t)(1 << (_Mux_Channel - 1));
				return(__Mux_Channel_Off__);
			}

			bool Device_Ready(void) {
				if (!this->TWI_Ready()) return(false);
				if (!this->Variables.Device.Detect) return(false);
				if (this->Variables.Multiplexer.Channel != __Mux_Channel_Off__ && !this->Set_Mux_Channel()) return(false);
				return(true);
			}

			bool Begin_Device_Transmission(void) {
				if (!this->Device_Ready()) return(false);
				this->Variables.TWI->beginTransmission(this->Variables.Device.Address);
				return(true);
			}

			bool End_Device_Transmission(const bool _Stop = true) {
				return(this->Variables.TWI->endTransmission(_Stop) == 0);
			}

			bool Write_Buffer(const uint8_t * _Data, const uint8_t _Length) {
				if (_Length > 0 && _Data == nullptr) return(false);
				for (uint8_t i = 0; i < _Length; i++) {
					// Abort if Wire internal buffer is full
					if (this->Variables.TWI->write(_Data[i]) == 0) return(false);
				}
				return(true);
			}

			bool Read_Buffer(uint8_t * _Data, const uint8_t _Length) {
				if (_Length > 0 && _Data == nullptr) return(false);
				if (_Length == 0) return(true);

				uint8_t _Received = this->Variables.TWI->requestFrom(this->Variables.Device.Address, _Length);

				if (_Received != _Length) {
					while (this->Variables.TWI->available()) this->Variables.TWI->read();
					return(false);
				}

				for (uint8_t i = 0; i < _Length; i++) {
					if (!this->Variables.TWI->available()) {
						while (this->Variables.TWI->available()) this->Variables.TWI->read();
						return(false);
					}
					_Data[i] = this->Variables.TWI->read();
				}

				return(true);
			}

			// Apply the configured mux channel. Called automatically before every transaction.
			bool Set_Mux_Channel(void) {
				if (!this->TWI_Ready()) return(false);
				if (this->Variables.Multiplexer.Channel == __Mux_Channel_Off__) return(true);

				if (this->Variables.TWI->requestFrom((uint8_t)__Mux_Address__, (uint8_t)1) != 1) return(false);
				if (!this->Variables.TWI->available()) return(false);

				uint8_t _Current = this->Variables.TWI->read();
				this->Variables.Multiplexer.Current_Channel = _Current;

				if (_Current == this->Variables.Multiplexer.Channel) return(true);

				this->Variables.TWI->beginTransmission((uint8_t)__Mux_Address__);
				this->Variables.TWI->write((uint8_t)this->Variables.Multiplexer.Channel);

				if (this->Variables.TWI->endTransmission() != 0) return(false);

				this->Variables.Multiplexer.Current_Channel = this->Variables.Multiplexer.Channel;
				return(true);
			}

		// Public Context
		public:

			// Object constructor.
			explicit I2C_Functions(uint8_t _Address, bool _Mux_Enable = false, uint8_t _Mux_Channel = 0) {
				this->Variables.Device.Address       = _Address;
				this->Variables.Multiplexer.Channel  = _Mux_Enable ? this->Resolve_Mux_Channel(_Mux_Channel) : __Mux_Channel_Off__;
			}

			// Start TWI bus and run initial device detection.
			void Begin(TwoWire * _TWI = &Wire) {
				this->Variables.TWI = (_TWI != nullptr) ? _TWI : &Wire;
				this->Variables.TWI->begin();
				this->Detect_Device();
			}

			// Stop TWI bus.
			void End(void) {
				if (!this->TWI_Ready()) return;
				this->Variables.TWI->end();
				this->Variables.TWI = nullptr;
			}

			// Probe device address and update detection state.
			void Detect_Device(void) {
				if (!this->TWI_Ready()) { this->Variables.Device.Detect = false; return; }
				if (this->Variables.Multiplexer.Channel != __Mux_Channel_Off__ && !this->Set_Mux_Channel()) { this->Variables.Device.Detect = false; return; }
				this->Variables.TWI->beginTransmission(this->Variables.Device.Address);
				this->Variables.Device.Detect = (this->Variables.TWI->endTransmission() == 0);
			}

			// Return configured device address.
			uint8_t Address(void) { return(this->Variables.Device.Address); }

			// Return cached device detection state.
			bool Detect(void) { return(this->Variables.Device.Detect); }

			// Return true if mux channel is assigned to this object.
			bool Mux_Enable(void) { return(this->Variables.Multiplexer.Channel != __Mux_Channel_Off__); }

			// Return the resolved mux channel bitmask (0x00 = disabled).
			uint8_t Mux_Channel(void) { return(this->Variables.Multiplexer.Channel); }

			// ---------------------------------------------------------------
			// Read Operations
			// ---------------------------------------------------------------

			// Read one byte from an 8-bit register address. Returns false on bus error.
			bool Try_Read_Register(const uint8_t _Register, uint8_t * _Data) {
				if (_Data == nullptr) return(false);
				if (!this->Begin_Device_Transmission()) return(false);
				this->Variables.TWI->write(_Register);
				if (!this->End_Device_Transmission()) return(false);
				return(this->Read_Buffer(_Data, 1));
			}

			// Read one byte from an 8-bit register address. Returns 0x00 on failure; use Try_Read_Register for explicit status.
			uint8_t Read_Register(const uint8_t _Register) {
				uint8_t _Response = 0x00;
				this->Try_Read_Register(_Register, &_Response);
				return(_Response);
			}

			// Read two bytes from an 8-bit register address into a 16-bit value. Pass msb_first=true for big-endian devices.
			bool Try_Read_Register_Word(const uint8_t _Register, uint16_t * _Data, const bool _MSB_First = false) {
				if (_Data == nullptr) return(false);
				uint8_t _Buffer[2] = {0x00, 0x00};
				if (!this->Begin_Device_Transmission()) return(false);
				this->Variables.TWI->write(_Register);
				if (!this->End_Device_Transmission()) return(false);
				if (!this->Read_Buffer(_Buffer, 2)) return(false);
				*_Data = _MSB_First ? ((uint16_t)_Buffer[0] << 8) | (uint16_t)_Buffer[1]
				                    : ((uint16_t)_Buffer[1] << 8) | (uint16_t)_Buffer[0];
				return(true);
			}

			// Read two bytes from an 8-bit register address. Returns 0x0000 on failure; use Try_Read_Register_Word for explicit status.
			uint16_t Read_Register_Word(const uint8_t _Register, const bool _MSB_First = false) {
				uint16_t _Response = 0x0000;
				this->Try_Read_Register_Word(_Register, &_Response, _MSB_First);
				return(_Response);
			}

			// Read one bit from an 8-bit register address. Returns false on bus error.
			bool Try_Read_Register_Bit(const uint8_t _Register, const uint8_t _Bit_Number, bool * _Bit_Value) {
				if (_Bit_Value == nullptr || _Bit_Number > 7) return(false);
				uint8_t _Response = 0x00;
				if (!this->Try_Read_Register(_Register, &_Response)) return(false);
				*_Bit_Value = bitRead(_Response, _Bit_Number);
				return(true);
			}

			// Read one bit from an 8-bit register address. Returns false on failure; use Try_Read_Register_Bit for explicit status.
			bool Read_Register_Bit(const uint8_t _Register, const uint8_t _Bit_Number) {
				bool _Bit_Value = false;
				this->Try_Read_Register_Bit(_Register, _Bit_Number, &_Bit_Value);
				return(_Bit_Value);
			}

			// Read multiple bytes from an 8-bit addressed register.
			bool Read_Multiple_Register(const uint8_t _Register, uint8_t * _Data, const uint8_t _Length, const bool _Stop = true) {
				if (_Length > 0 && _Data == nullptr) return(false);
				if (!this->Begin_Device_Transmission()) return(false);
				this->Variables.TWI->write(_Register);
				if (!this->End_Device_Transmission(_Stop)) return(false);
				return(this->Read_Buffer(_Data, _Length));
			}

			// Read multiple bytes from a 16-bit addressed register (address sent MSB first).
			bool Read_Multiple_Register_u16(const uint16_t _Register, uint8_t * _Data, const uint8_t _Length, const bool _Stop = true) {
				if (_Length > 0 && _Data == nullptr) return(false);
				if (!this->Begin_Device_Transmission()) return(false);
				this->Variables.TWI->write((uint8_t)((0xFF00 & (uint16_t)_Register) >> 8));
				this->Variables.TWI->write((uint8_t)(0x00FF & (uint16_t)_Register));
				if (!this->End_Device_Transmission(_Stop)) return(false);
				return(this->Read_Buffer(_Data, _Length));
			}

			// Read multiple bytes without sending a register address (device streams data on read request).
			bool Read_Multiple_Register_NoCMD(uint8_t * _Data, const uint8_t _Length) {
				if (_Length > 0 && _Data == nullptr) return(false);
				if (!this->Device_Ready()) return(false);
				return(this->Read_Buffer(_Data, _Length));
			}

			// ---------------------------------------------------------------
			// Write Operations
			// ---------------------------------------------------------------

			// Write one byte to an 8-bit register address.
			bool Write_Register(const uint8_t _Register, const uint8_t _Data, const bool _Stop = true) {
				if (!this->Begin_Device_Transmission()) return(false);
				this->Variables.TWI->write(_Register);
				this->Variables.TWI->write(_Data);
				return(this->End_Device_Transmission(_Stop));
			}

			// Write a 16-bit word to an 8-bit register address. Pass msb_first=true for big-endian devices.
			bool Write_Register_Word(const uint8_t _Register, const uint16_t _Data, const bool _Stop = true, const bool _MSB_First = false) {
				if (!this->Begin_Device_Transmission()) return(false);
				this->Variables.TWI->write(_Register);
				if (_MSB_First) {
					this->Variables.TWI->write((uint8_t)((_Data >> 8) & 0xFF));
					this->Variables.TWI->write((uint8_t)(_Data & 0xFF));
				} else {
					this->Variables.TWI->write((uint8_t)(_Data & 0xFF));
					this->Variables.TWI->write((uint8_t)((_Data >> 8) & 0xFF));
				}
				return(this->End_Device_Transmission(_Stop));
			}

			// Write multiple bytes to an 8-bit register address. Aborts cleanly if Wire buffer overflows.
			bool Write_Multiple_Register(const uint8_t _Register, const uint8_t * _Data, const uint8_t _Length) {
				if (_Length > 0 && _Data == nullptr) return(false);
				if (!this->Begin_Device_Transmission()) return(false);
				this->Variables.TWI->write(_Register);
				const bool _Buffer_OK = this->Write_Buffer(_Data, _Length);
				if (!this->End_Device_Transmission()) return(false);
				return(_Buffer_OK);
			}

			// Send one command byte without a register address.
			bool Write_Command(const uint8_t _Command, const bool _Stop = true) {
				if (!this->Begin_Device_Transmission()) return(false);
				this->Variables.TWI->write(_Command);
				return(this->End_Device_Transmission(_Stop));
			}

			// Send multiple command bytes without a register address. Aborts cleanly if Wire buffer overflows.
			bool Write_Multiple_Command(const uint8_t * _Command, const uint8_t _Length) {
				if (_Length > 0 && _Command == nullptr) return(false);
				if (!this->Begin_Device_Transmission()) return(false);
				const bool _Buffer_OK = this->Write_Buffer(_Command, _Length);
				if (!this->End_Device_Transmission()) return(false);
				return(_Buffer_OK);
			}

			// ---------------------------------------------------------------
			// Bit Operations (read-modify-write)
			// ---------------------------------------------------------------

			// Set one bit in a register. Skips the write if the bit is already set.
			bool Set_Register_Bit(const uint8_t _Register, const uint8_t _Bit_Number, const bool _Stop = true) {
				if (_Bit_Number > 7) return(false);
				uint8_t _Response = 0x00;
				if (!this->Try_Read_Register(_Register, &_Response)) return(false);
				if (bitRead(_Response, _Bit_Number)) return(true);
				bitSet(_Response, _Bit_Number);
				return(this->Write_Register(_Register, _Response, _Stop));
			}

			// Clear one bit in a register. Skips the write if the bit is already clear.
			bool Clear_Register_Bit(const uint8_t _Register, const uint8_t _Bit_Number, const bool _Stop = true) {
				if (_Bit_Number > 7) return(false);
				uint8_t _Response = 0x00;
				if (!this->Try_Read_Register(_Register, &_Response)) return(false);
				if (!bitRead(_Response, _Bit_Number)) return(true);
				bitClear(_Response, _Bit_Number);
				return(this->Write_Register(_Register, _Response, _Stop));
			}

			// Toggle one bit in a register.
			bool Toggle_Register_Bit(const uint8_t _Register, const uint8_t _Bit_Number, const bool _Stop = true) {
				if (_Bit_Number > 7) return(false);
				uint8_t _Response = 0x00;
				if (!this->Try_Read_Register(_Register, &_Response)) return(false);
				_Response ^= (uint8_t)(1 << _Bit_Number);
				return(this->Write_Register(_Register, _Response, _Stop));
			}

			// Write a specific value to one bit (delegates to Set or Clear).
			bool Write_Register_Bit(const uint8_t _Register, const uint8_t _Bit_Number, const bool _Bit_Value, const bool _Stop = true) {
				return(_Bit_Value ? this->Set_Register_Bit(_Register, _Bit_Number, _Stop)
				                  : this->Clear_Register_Bit(_Register, _Bit_Number, _Stop));
			}

	};

#endif /* defined(__I2C_Functions__) */
