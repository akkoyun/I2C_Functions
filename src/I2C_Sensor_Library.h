#ifndef __I2C_SENSOR_LIBRARY__
#define __I2C_SENSOR_LIBRARY__

// Define I2C Addresses
#define	__ADDR_TCA9548__	(uint8_t)0x70
#define	__ADDR_RV3028C7__	(uint8_t)0x52
#define	__ADDR_DS28C__		(uint8_t)0x50
#define	__ADDR_HDC201__		(uint8_t)0x40
#define	__ADDR_MAX17055__	(uint8_t)0x36
#define	__ADDR_BQ24298__	(uint8_t)0x6B
#define	__ADDR_SHT21__		(uint8_t)0x40

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
	__SHT21_SOFT_RESET_		= 0xFE,
	__SHT21_USER_REGISTER_	= 0xE6,
	__SHT21_T_MEASUREMENT_	= 0xE3,
	__SHT21_H_MEASUREMENT_	= 0xE5,
};

#endif
