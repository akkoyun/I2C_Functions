#ifndef __I2C_SENSOR_LIBRARY__
#define __I2C_SENSOR_LIBRARY__

enum I2C_Address {
	__ADDR_TCA9548__			= (uint8_t)0x70,
	__ADDR_RV3028C7__			= (uint8_t)0x52,
	__ADDR_DS28C__				= (uint8_t)0x50,
	__ADDR_HDC2010__			= (uint8_t)0x40,
	__ADDR_MAX17055__			= (uint8_t)0x36,
	__ADDR_BQ24298__			= (uint8_t)0x6B,
	__ADDR_SHT21__				= (uint8_t)0x40
};
enum Multiplexer_Channels {
	__OFF__						= (uint8_t)0,
	__CH1__						= (uint8_t)1,
	__CH2__						= (uint8_t)2,
	__CH3__						= (uint8_t)3,
	__CH4__						= (uint8_t)4,
	__CH5__						= (uint8_t)5,
	__CH6__						= (uint8_t)6,
	__CH7__						= (uint8_t)7,
	__CH8__						= (uint8_t)8
};
enum SHT21_Registers {
	__SHT21_SOFT_RESET_			= (uint8_t)0xFE,
	__SHT21_USER_REGISTER_		= (uint8_t)0xE6,
	__SHT21_T_MEASUREMENT_		= (uint8_t)0xE3,
	__SHT21_H_MEASUREMENT_		= (uint8_t)0xE5
};
enum MAX17055_Registers {
	__MAX17055_Status__			= (uint8_t)0x00,
	__MAX17055_VAlrtTh__		= (uint8_t)0x01,
	__MAX17055_TAlrtTh__		= (uint8_t)0x02,
	__MAX17055_SAlrtTh__		= (uint8_t)0x03,
	__MAX17055_AtRate__			= (uint8_t)0x04,
	__MAX17055_RepCap__			= (uint8_t)0x05,
	__MAX17055_RepSOC__			= (uint8_t)0x06,
	__MAX17055_Age__			= (uint8_t)0x07,
	__MAX17055_Temp__			= (uint8_t)0x08,
	__MAX17055_VCell__			= (uint8_t)0x09,
	__MAX17055_Current__		= (uint8_t)0x0A,
	__MAX17055_AvgCurrent__		= (uint8_t)0x0B,
	__MAX17055_QResidual__		= (uint8_t)0x0C,
	__MAX17055_MixSOC__			= (uint8_t)0x0D,
	__MAX17055_AvSOC__			= (uint8_t)0x0E,
	__MAX17055_MixCap__			= (uint8_t)0x0F,
	__MAX17055_FullCapRep__		= (uint8_t)0x10,
	__MAX17055_TTE__			= (uint8_t)0x11,
	__MAX17055_QRTable00__		= (uint8_t)0x12,
	__MAX17055_FullSocThr__		= (uint8_t)0x13,
	__MAX17055_RCell__			= (uint8_t)0x14,
	__MAX17055_AvgTA__			= (uint8_t)0x16,
	__MAX17055_Cycles__			= (uint8_t)0x17,
	__MAX17055_DesignCap__		= (uint8_t)0x18,
	__MAX17055_AvgVCell__		= (uint8_t)0x19,
	__MAX17055_MaxMinTemp__		= (uint8_t)0x1A,
	__MAX17055_MaxMinVolt__		= (uint8_t)0x1B,
	__MAX17055_MaxMinCurr__		= (uint8_t)0x1C,
	__MAX17055_Config__			= (uint8_t)0x1D,
	__MAX17055_IChgTerm__		= (uint8_t)0x1E,
	__MAX17055_AvCap__			= (uint8_t)0x1F,
	__MAX17055_TTF__			= (uint8_t)0x20,
	__MAX17055_DevName__		= (uint8_t)0x21,
	__MAX17055_QRTable10__		= (uint8_t)0x22,
	__MAX17055_FullCapNom__		= (uint8_t)0x23,
	__MAX17055_AIN__			= (uint8_t)0x27,
	__MAX17055_LearnCfg__		= (uint8_t)0x28,
	__MAX17055_FilterCfg__		= (uint8_t)0x29,
	__MAX17055_RelaxCfg__		= (uint8_t)0x2A,
	__MAX17055_MiscCfg__		= (uint8_t)0x2B,
	__MAX17055_TGain__			= (uint8_t)0x2C,
	__MAX17055_TOff__			= (uint8_t)0x2D,
	__MAX17055_CGain__			= (uint8_t)0x2E,
	__MAX17055_COff__			= (uint8_t)0x2F,
	__MAX17055_QRTable20__		= (uint8_t)0x32,
	__MAX17055_DieTemp__		= (uint8_t)0x34,
	__MAX17055_FullCap__		= (uint8_t)0x35,
	__MAX17055_RComp0__			= (uint8_t)0x38,
	__MAX17055_TempCo__			= (uint8_t)0x39,
	__MAX17055_VEmpty__			= (uint8_t)0x3A,
	__MAX17055_FStat__			= (uint8_t)0x3D,
	__MAX17055_Timer__			= (uint8_t)0x3E,
	__MAX17055_ShdnTimer__		= (uint8_t)0x3F,
	__MAX17055_UserMem1__		= (uint8_t)0x40,
	__MAX17055_QRTable30__		= (uint8_t)0x42,
	__MAX17055_RGain__			= (uint8_t)0x43,
	__MAX17055_dQAcc__			= (uint8_t)0x45,
	__MAX17055_dPAcc__			= (uint8_t)0x46,
	__MAX17055_ConvgCfg__		= (uint8_t)0x49,
	__MAX17055_VFRemCap__		= (uint8_t)0x4A,
	__MAX17055_QH__				= (uint8_t)0x4D,
	__MAX17055_Status2__		= (uint8_t)0xB0,
	__MAX17055_Power__			= (uint8_t)0xB1,
	__MAX17055_UserMem2__		= (uint8_t)0xB2,
	__MAX17055_AvgPower__		= (uint8_t)0xB3,
	__MAX17055_IAlrtTh__		= (uint8_t)0xB4,
	__MAX17055_TTFCfg__			= (uint8_t)0xB5,
	__MAX17055_CVMixCap__		= (uint8_t)0xB6,
	__MAX17055_CVHalfTime__		= (uint8_t)0xB7,
	__MAX17055_CGTempCo__		= (uint8_t)0xB8,
	__MAX17055_Curve__			= (uint8_t)0xB9,
	__MAX17055_HibCfg__			= (uint8_t)0xBA,
	__MAX17055_Config2__		= (uint8_t)0xBB,
	__MAX17055_VRipple__		= (uint8_t)0xBC,
	__MAX17055_RippleCfg__		= (uint8_t)0xBD,
	__MAX17055_TimerH__			= (uint8_t)0xBE,
	__MAX17055_UserMem3__		= (uint8_t)0xD0,
	__MAX17055_ScOcvLim__		= (uint8_t)0xD1,
	__MAX17055_SOCHold__		= (uint8_t)0xD3,
	__MAX17055_MaxPeakPower__	= (uint8_t)0xD4,
	__MAX17055_SusPeakPower__	= (uint8_t)0xD5,
	__MAX17055_PackResistance__	= (uint8_t)0xD6,
	__MAX17055_SysResistance__	= (uint8_t)0xD7,
	__MAX17055_MinSysVoltage__	= (uint8_t)0xD8,
	__MAX17055_MPPCurrent__		= (uint8_t)0xD9,
	__MAX17055_SPPCurrent__		= (uint8_t)0xDA,
	__MAX17055_ModelCfg__		= (uint8_t)0xDB,
	__MAX17055_AtQResidual__	= (uint8_t)0xDC,
	__MAX17055_AtTTE__			= (uint8_t)0xDD,
	__MAX17055_AtAvSOC__		= (uint8_t)0xDE,
	__MAX17055_AtAvCap__		= (uint8_t)0xDF
};
enum MAX17055_STATUS_Register_Bits {
	__MAX17055_POR__			= (uint8_t)1,
	__MAX17055_Imn__			= (uint8_t)2,
	__MAX17055_Bst__			= (uint8_t)3,
	__MAX17055_Imx__			= (uint8_t)6,
	__MAX17055_dSOCi__			= (uint8_t)7,
	__MAX17055_Vmn__			= (uint8_t)8,
	__MAX17055_Tmn__			= (uint8_t)9,
	__MAX17055_Smn__			= (uint8_t)10,
	__MAX17055_Bi__				= (uint8_t)11,
	__MAX17055_Vmx__			= (uint8_t)12,
	__MAX17055_Tmx__			= (uint8_t)13,
	__MAX17055_Smx__			= (uint8_t)14,
	__MAX17055_Br__				= (uint8_t)15
};
enum MAX17055_CONFIG1_Bits { 	// [0x2210] - 0x0000
	__MAX17055_Ber__			= (uint8_t)0,	// [0] Enable alert on battery removal - 0
	__MAX17055_Bei__			= (uint8_t)1,	// [0] Enable alert on battery insertion - 0
	__MAX17055_Aen__			= (uint8_t)2,	// [0] Enable Alert on Fuel-Gauge Outputs - 0
	__MAX17055_FTHRM__			= (uint8_t)3,	// [0] Force Thermistor Bias Switch - 0
	__MAX17055_ETHRM__			= (uint8_t)4,	// [1] Enable Thermistor - 0
	__MAX17055_COMMSH__			= (uint8_t)6,	// [0] Communication Shutdown - 0
	__MAX17055_SHDN__			= (uint8_t)7,	// [0] Shutdown - 0
	__MAX17055_Tex__			= (uint8_t)8,	// [0] Temperature External - 0
	__MAX17055_Ten__			= (uint8_t)9,	// [1] Enable Temperature Channel - 0
	__MAX17055_AINSH__			= (uint8_t)10,	// [0] AIN Pin Shutdown - 0
	__MAX17055_IS__				= (uint8_t)11,	// [0] Current ALRT Sticky - 0
	__MAX17055_VS__				= (uint8_t)12,	// [0] Voltage ALRT Sticky - 0
	__MAX17055_TS__				= (uint8_t)13,	// [1] Temperature ALRT Sticky - 0
	__MAX17055_SAS__			= (uint8_t)14,	// [0] SOC ALRT Sticky - 0
	__MAX17055_TSel__			= (uint8_t)15	// [0] internal die temperature - 0
};
enum MAX17055_CONFIG2_Bits { 	// [0x3658] - 0x0218
	__MAX17055_CPMode__			= (uint8_t)1,	// [0] Constant Power Mode - 0
	__MAX17055_LDMDL__			= (uint8_t)5,	// [0] Load Model - 0
	__MAX17055_TAlrtEn__		= (uint8_t)6,	// [1] Temperature Alert Enable - 0
	__MAX17055_dSOCen__			= (uint8_t)7,	// [0] SOC Change Alert Enable - 0
	__MAX17055_POWR0__			= (uint8_t)8,	// [0] 0 
	__MAX17055_POWR1__			= (uint8_t)9,	// [1] 1
	__MAX17055_POWR2__			= (uint8_t)10,	// [1] 0
	__MAX17055_POWR3__			= (uint8_t)11,	// [0] 0
	__MAX17055_DPEn__			= (uint8_t)12,	// [1] Dynamic Power Enable - 0
	__MAX17055_AtRateEn__		= (uint8_t)13	// [1] AtRate Enable - 0
};
enum BQ24298_Registers {
	__BQ24298_Input_Source__				= (uint8_t)0x00,
	__BQ24298_PowerOn_Config__				= (uint8_t)0x01,
	__BQ24298_Charge_Current_Control__		= (uint8_t)0x02,
	__BQ24298_PreCharge_Current_Control__	= (uint8_t)0x03,
	__BQ24298_Charge_Voltage_Control__		= (uint8_t)0x04,
	__BQ24298_Charge_Timer_Control__		= (uint8_t)0x05,
	__BQ24298_Thermal_Control__				= (uint8_t)0x06,
	__BQ24298_Misc_Control__				= (uint8_t)0x07,
	__BQ24298_System_Status__				= (uint8_t)0x08,
	__BQ24298_Fault__						= (uint8_t)0x09,
	__BQ24298_Version__						= (uint8_t)0x0A
};
enum BQ24298_Current_Limit_Mask {
    __BQ24298_CURRENT_LIM_100__ 			= (uint8_t)0x00,
    __BQ24298_CURRENT_LIM_150__				= (uint8_t)0x01,
    __BQ24298_CURRENT_LIM_500__				= (uint8_t)0x02,
    __BQ24298_CURRENT_LIM_900__				= (uint8_t)0x03,
    __BQ24298_CURRENT_LIM_1200__			= (uint8_t)0x04,
    __BQ24298_CURRENT_LIM_1500__			= (uint8_t)0x05,
    __BQ24298_CURRENT_LIM_2000__			= (uint8_t)0x06,
    __BQ24298_CURRENT_LIM_3000__			= (uint8_t)0x07
};
enum BQ24298_Charge_Fault_Status {
	__BQ24298_NO_CHARGE_FAULT__				= (uint8_t)0x00, // 0b 0000 0000
	__BQ24298_INPUT_OVER_VOLTAGE__			= (uint8_t)0x10, // 0b 0001 0000
	__BQ24298_THERMAL_SHUTDOWN__			= (uint8_t)0x20, // 0b 0010 0000
	__BQ24298_CHARGE_SAFETY_TIME_EXPIRED__	= (uint8_t)0x30 // 0b 0011 0000
};
enum BQ24298_Thermal_Fault_Status {
	__BQ24298_NO_TEMPERATURE_FAULT__ 				= (uint8_t)0x00, // 0b 0000 0000
	__BQ24298_LOWER_THRESHOLD_TEMPERATURE_FAULT__	= (uint8_t)0x05, // 0b 0000 0101
	__BQ24298_HIGHER_THRESHOLD_TEMPERATURE_FAULT__	= (uint8_t)0x06 // 0b 0000 0110
};
enum BQ24298_Charging_Status {
	__BQ24298_NOT_CHARGING__				= (uint8_t)0x00, // 0b 0000 0000
	__BQ24298_PRE_CHARGING__				= (uint8_t)0x10, // 0b 0001 0000
	__BQ24298_FAST_CHARGING__				= (uint8_t)0x20, // 0b 0010 0000
	__BQ24298_CHARGE_TERMINATION_DONE__		= (uint8_t)0x30 // 0b 0011 0000
};
enum BQ24298_VBus_Status {
	__BQ24298_UNKNOWN_MODE__				= (uint8_t)0x00, // 0b 0000 0000
	__BQ24298_USB_HOST_MODE__				= (uint8_t)0x40, // 0b 0100 0000
	__BQ24298_ADAPTER_PORT_MODE__			= (uint8_t)0x80, // 0b 1000 0000
	__BQ24298_BOOST_MODE__					= (uint8_t)0xC0 // 0b 1100 0000
};

#endif
