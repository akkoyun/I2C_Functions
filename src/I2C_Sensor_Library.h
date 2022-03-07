#ifndef __I2C_SENSOR_LIBRARY__
#define __I2C_SENSOR_LIBRARY__

enum I2C_Address {
	__ADDR_TCA9548__		= (uint8_t)0x70,
	__ADDR_RV3028C7__		= (uint8_t)0x52,
	__ADDR_DS28C__			= (uint8_t)0x50,
	__ADDR_HDC201__			= (uint8_t)0x40,
	__ADDR_MAX17055__		= (uint8_t)0x36,
	__ADDR_BQ24298__		= (uint8_t)0x6B,
	__ADDR_SHT21__			= (uint8_t)0x40
};


enum Multiplexer_Channels {
	__OFF__					= 0,
	__CH1__					= 1,
	__CH2__					= 2,
	__CH3__					= 3,
	__CH4__					= 4,
	__CH5__					= 5,
	__CH6__					= 6,
	__CH7__					= 7,
	__CH8__					= 8
};

enum SHT21_Registers {
	__SHT21_SOFT_RESET_		= (uint8_t)0xFE,
	__SHT21_USER_REGISTER_	= (uint8_t)0xE6,
	__SHT21_T_MEASUREMENT_	= (uint8_t)0xE3,
	__SHT21_H_MEASUREMENT_	= (uint8_t)0xE5
};

#endif
