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
#ifndef __I2C_Functions_Definitions__
#include "Definition.h"
#endif

// I2C Control Functions
class I2C_Functions {

	private:

		/**
		 * @brief Object I2C address variable.
		 */
		uint8_t TWI_Address = 0x00;

		/**
		 * @brief Object detect variable.
		 */
		bool TWI_Device = false;

		/**
		 * @brief Object multiplexer enable variable.
		 */
		bool Multiplexer_Enable = false;

		/**
		 * @brief Object multiplexer channel variable.
		 */
		uint8_t TWI_Device_Mux_Channel = 0x00;

		/**
		 * @brief Object multiplexer current channel variable.
		 */
		uint8_t _Multiplexer_Current_Channel = 0x00;

	public:

		/**
		 * @brief Object constructor of I2C library.
		 * @param _Address I2C address of device.
		 * @param _Mux_Enable I2C multiplexer enable.
		 * @param _Mux_Channel I2C multiplexer channel.
		 */
		I2C_Functions(uint8_t _Address, bool _Mux_Enable = false, uint8_t _Mux_Channel = 0x00) : TWI_Address(_Address), TWI_Device(false), Multiplexer_Enable(_Mux_Enable), TWI_Device_Mux_Channel(_Mux_Channel) {

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

		/**
		 * @brief Read specified register on I2C device.
		 * @param _Register Register address.
		 * @return uint8_t Data on specified register.
		 */
		uint8_t Read_Register(uint8_t _Register) {

			// Declare Response Variable
			uint8_t _Response = 0x00;

			// Control for Device
			if (this->TWI_Device) {

				// Control for Multiplexer
				this->Set_Multiplexer();

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
					_Response = 0x00;

				}

			} else {

				// Set Error Variable
				_Response = 0x00;

			}
			
			// End Function
			return(_Response);

		}

		/**
		 * @brief Write data to specified register on I2C device.
		 * @param _Register Register address.
		 * @param _Data Data register to write on specified register.
		 * @param _Stop Stop I2C connection.
		 * @return true Function success.
		 * @return false Function fails.
		 */
		bool Write_Register(uint8_t _Register, uint8_t _Data, bool _Stop) {

			// Control for Device
			if (this->TWI_Device) {

				// Control for Multiplexer
				this->Set_Multiplexer();

				// Connect to Device
				Wire.beginTransmission(this->TWI_Address);

				// Send Register Address
				Wire.write(_Register);

				// Send Data
				Wire.write(_Data);

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

		/**
		 * @brief Read multiple data on specified register.
		 * @param _Register Register address.
		 * @param _Data Read data array.
		 * @param _Length Length size of read data.
		 * @param _Stop Stop I2C connection.
		 * @return true Function success.
		 * @return false Function fails.
		 */
		bool Read_Multiple_Register(uint8_t _Register, uint8_t * _Data, uint8_t _Length, bool _Stop) {

			// Control for Device
			if (this->TWI_Device) {

				// Control for Multiplexer
				this->Set_Multiplexer();

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

		/**
		 * @brief Write multiple data to specified register.
		 * @param _Register Register address.
		 * @param _Data Write data array.
		 * @param _Length Length size of write data.
		 * @return true Function success.
		 * @return false Function fails.
		 */
		bool Write_Multiple_Register(uint8_t _Register, uint8_t * _Data, uint8_t _Length) {

			// Control for Device
			if (this->TWI_Device) {

				// Control for Multiplexer
				this->Set_Multiplexer();

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

		/**
		 * @brief Write command to I2C device.
		 * @param _Command Command data.
		 * @param _Stop Stop I2C connection.
		 * @return true Function success.
		 * @return false Function fails.
		 */
		bool Write_Command(uint8_t _Command, bool _Stop) {

			// Control for Device
			if (this->TWI_Device) {

				// Control for Multiplexer
				this->Set_Multiplexer();

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

		/**
		 * @brief Write multiple command to I2C device.
		 * @param _Command Command data.
		 * @param _Length Command length.
		 * @return true Function success.
		 * @return false Function fails.
		 */
		bool Write_Multiple_Command(uint8_t * _Command, uint8_t _Length) {

			// Control for Device
			if (this->TWI_Device) {

				// Control for Multiplexer
				this->Set_Multiplexer();

				// Connect to Device
				Wire.beginTransmission(this->TWI_Address);

				// Write Registers Loop
				for (size_t i = 0; i < _Length; i++) Wire.write(_Command[i]);

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

		/**
		 * @brief Set specified register bit on I2C device.
		 * @param _Register Register address.
		 * @param _Bit_Number Bit number of specified register data.
		 * @param _Stop Stop I2C connection.
		 * @return true Function success.
		 * @return false Function fails.
		 */
		bool Set_Register_Bit(uint8_t _Register, uint8_t _Bit_Number, bool _Stop) {

			// Control for Device
			if (this->TWI_Device) {

				// Control for Multiplexer
				this->Set_Multiplexer();

				// Read Register
				uint8_t _Response = Read_Register(_Register);

				// Control Bit value
				if (bitRead(_Response, _Bit_Number) == false) {

					// Set Bit
					_Response = bitSet(_Response, _Bit_Number);

					// Write Register
					bool _Write_Response = Write_Register(_Register, _Response, _Stop);

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

		/**
		 * @brief Clear specified register bit on I2C device.
		 * @param _Register Register address.
		 * @param _Bit_Number Bit number of specified register data.
		 * @param _Stop Stop I2C connection.
		 * @return true Function success.
		 * @return false Function fails.
		 */
		bool Clear_Register_Bit(uint8_t _Register, uint8_t _Bit_Number, bool _Stop) {

			// Control for Device
			if (this->TWI_Device) {

				// Control for Multiplexer
				this->Set_Multiplexer();

				// Read Register
				uint8_t _Response = Read_Register(_Register);

				// Control Bit value
				if (bitRead(_Response, _Bit_Number) == true) {

					// Set Bit
					_Response = bitClear(_Response, _Bit_Number);

					// Write Register
					bool _Write_Response = Write_Register(_Register, _Response, _Stop);

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

		/**
		 * @brief Read specified register bit on I2C device.
		 * @param _Register Register address.
		 * @param _Bit_Number Bit number of specified register data.
		 * @param _Stop Stop I2C connection.
		 * @return true Bit is high.
		 * @return false Bit is low.
		 */
		bool Read_Register_Bit(uint8_t _Register, uint8_t _Bit_Number) {

			// Control for Multiplexer
			this->Set_Multiplexer();

			// Read Register
			uint8_t _Response = Read_Register(_Register);

			// Read Bit
			bool _Bit_Value = bitRead(_Response, _Bit_Number);

			// End Function
			return(_Bit_Value);

		}

		/**
		 * @brief I2C device controller.
		 * @return true I2C device is OK.
		 * @return false I2C device is fail.
		 */
		bool Control_Device(void) {

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

		/**
		 * @brief I2C device control variable.
		 * @return true I2C device is OK.
		 * @return false I2C device is fail.
		 */
		bool Detect(void) {

			// End Functions
			return(this->TWI_Device);

		}

		/**
		 * @brief Get object I2C address.
		 * @return uint8_t I2C address of devie.
		 */
		uint8_t Address(void) {

			// End Functions
			return(this->TWI_Address);

		}

		/**
		 * @brief Get object multiplexer channel.
		 * @return uint8_t Mux channel of devie.
		 */
		uint8_t Mux(void) {

			// End Functions
			return(this->TWI_Device_Mux_Channel);

		}

		/**
		 * @brief Change multiplexer channel to device I2C address.
		 * @return true Channel change success.
		 * @return false Channel change fail.
		 */
		bool Set_Multiplexer(void) {

			// Declare Result Variable
			bool Result = true;

			// Control for Multiplexer
			if (this->Multiplexer_Enable) {

				// Coltrol for Current Mux Channel
				if (this->_Multiplexer_Current_Channel != this->TWI_Device_Mux_Channel) {

					// Connect I2C Multiplexer
					Wire.beginTransmission((uint8_t)__Mux_Address__);

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

};

#endif /* defined(__I2C_Functions__) */