// I2C Library Definitions
#define __I2C_Functions_Version__	"01.09.00"

// Sensor Address Definitions
#define __I2C_Addr_TCA9548__		(uint8_t)0x70
#define __I2C_Addr_RV3028C7__		(uint8_t)0x52
#define __I2C_Addr_DS28C__			(uint8_t)0x50
#define __I2C_Addr_HDC2010__		(uint8_t)0x40
#define __I2C_Addr_MPL3115A2__		(uint8_t)0x60
#define __I2C_Addr_TSL2561__		(uint8_t)0x39
#define __I2C_Addr_SI1145__		    (uint8_t)0x60
#define __I2C_Addr_MAX17055__		(uint8_t)0x36
#define __I2C_Addr_BQ24298__		(uint8_t)0x6B
#define __I2C_Addr_SHT21__			(uint8_t)0x40
#define __I2C_Addr_SDP810__			(uint8_t)0x25
#define __I2C_Addr_PCF8574_A__		(uint8_t)0x3F
#define __I2C_Addr_PCF8574_B__		(uint8_t)0x3B
#define __I2C_Addr_PCF8574_C__		(uint8_t)0x39
#define __I2C_Addr_PCF8574_D__		(uint8_t)0x3E

// Set Default Address
#define __Mux_Address__             (uint8_t)0x70

// Multiplexer Channel Definirions
#define __Mux_Channel_Off__			(uint8_t)0x00
#define __Mux_Channel_1__			(uint8_t)0x01
#define __Mux_Channel_2__			(uint8_t)0x02
#define __Mux_Channel_3__			(uint8_t)0x04
#define __Mux_Channel_4__			(uint8_t)0x08
#define __Mux_Channel_5__			(uint8_t)0x10
#define __Mux_Channel_6__			(uint8_t)0x20
#define __Mux_Channel_7__			(uint8_t)0x40
#define __Mux_Channel_8__			(uint8_t)0x80

// Define B108AA I2C Port
#define __B108AA_MUX_DS28C__		(uint8_t)1
#define __B108AA_MUX_HDC2010__		(uint8_t)2
#define __B108AA_MUX_SI1145__		(uint8_t)3
#define __B108AA_MUX_MPL3115__		(uint8_t)4
#define __B108AA_MUX_SDP810_X__		(uint8_t)5
#define __B108AA_MUX_SDP810_Y__		(uint8_t)6
#define __B108AA_MUX_SDP810_Z__		(uint8_t)7
#define __B108AA_MUX_Power__		(uint8_t)8