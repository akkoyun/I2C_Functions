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
		 * @brief Object multiplexer channel variable.
		 */
		uint8_t TWI_Device_Mux_Channel = 0x00;

		/**
		 * @brief Object multiplexer enable variable.
		 */
		bool Multiplexer_Enable = false;

		/**
		 * @brief Object multiplexer current channel variable.
		 */
		uint8_t _Multiplexer_Current_Channel = 0x00;

	public:

		/**
		 * @brief Object constractor of I2C library.
		 * @param _Address I2C address of device.
		 * @param _Mux_Enable I2C multiplexer enable.
		 * @param _Mux_Channel I2C multiplexer channel.
		 */
		I2C_Functions(uint8_t _Address, bool _Mux_Enable = false, uint8_t _Mux_Channel = 0x00);

		/**
		 * @brief Read specified register on I2C device.
		 * @param _Register Register address.
		 * @return uint8_t Data on specified register.
		 */
		uint8_t Read_Register(uint8_t _Register);

		/**
		 * @brief Write data to specified register on I2C device.
		 * @param _Register Register address.
		 * @param _Data Data register to write on specified register.
		 * @param _Stop Stop I2C connection.
		 * @return true Function success.
		 * @return false Function fails.
		 */
		bool Write_Register(uint8_t _Register, uint8_t _Data, bool _Stop);

		/**
		 * @brief Read multiple data on specified register.
		 * @param _Register Register address.
		 * @param _Data Read data array.
		 * @param _Length Length size of read data.
		 * @param _Stop Stop I2C connection.
		 * @return true Functon success.
		 * @return false Function fails.
		 */
		bool Read_Multiple_Register(uint8_t _Register, uint8_t * _Data, uint8_t _Length, bool _Stop);

		/**
		 * @brief Write multiple data to specified register.
		 * @param _Register Register address.
		 * @param _Data Write data array.
		 * @param _Length Length size of write data.
		 * @return true Function success.
		 * @return false Function fails.
		 */
		bool Write_Multiple_Register(uint8_t _Register, uint8_t * _Data, uint8_t _Length);

		/**
		 * @brief Write command to I2C device.
		 * @param _Command Command data.
		 * @param _Stop Stop I2C connection.
		 * @return true Function success.
		 * @return false Function fails.
		 */
		bool Write_Command(uint8_t _Command, bool _Stop);

		/**
		 * @brief Set specified register bit on I2C device.
		 * @param _Register Register address.
		 * @param _Bit_Number Bit number of specified register data.
		 * @param _Stop Stop I2C connection.
		 * @return true Function success.
		 * @return false Function fails.
		 */
		bool Set_Register_Bit(uint8_t _Register, uint8_t _Bit_Number, bool _Stop);

		/**
		 * @brief Clear specified register bit on I2C device.
		 * @param _Register Register address.
		 * @param _Bit_Number Bit number of specified register data.
		 * @param _Stop Stop I2C connection.
		 * @return true Function success.
		 * @return false Function fails.
		 */
		bool Clear_Register_Bit(uint8_t _Register, uint8_t _Bit_Number, bool _Stop);

		/**
		 * @brief Read specified register bit on I2C device.
		 * @param _Register Register address.
		 * @param _Bit_Number Bit number of specified register data.
		 * @param _Stop Stop I2C connection.
		 * @return true Bit is high.
		 * @return false Bit is low.
		 */
		bool Read_Register_Bit(uint8_t _Register, uint8_t _Bit_Number);

		/**
		 * @brief Binary coded decimal to decimal converter.
		 * @param _Value Value to convert
		 * @return uint8_t Converted value.
		 */
		uint8_t BCDtoDEC(uint8_t _Value);

		/**
		 * @brief Decimal to binary coded decimal converter.
		 * @param _Value Decimal value to convert.
		 * @return uint8_t Converted value.
		 */
		uint8_t DECtoBCD(byte _Value);

		/**
		 * @brief I2C device controller.
		 * @return true I2C device is OK.
		 * @return false I2C device is fail.
		 */
		bool Control_Device(void);

		/**
		 * @brief I2C device controll variable.
		 * @return true I2C device is OK.
		 * @return false I2C device is fail.
		 */
		bool Detect(void);

		/**
		 * @brief Get object I2C adress.
		 * @return uint8_t I2C address of devie.
		 */
		uint8_t Address(void);

		/**
		 * @brief Get object multiplexer channel.
		 * @return uint8_t Mux channel of devie.
		 */
		uint8_t Mux(void);

		/**
		 * @brief Change multiplexer channel to device I2C address.
		 * @return true Channel change success.
		 * @return false Channel change fail.
		 */
		bool Set_Multiplexer(void);

};

#endif /* defined(__I2C_Functions__) */