/* *******************************************************************************
 *  Copyright (C) 2014-2022 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: Generic I2C Functions
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *********************************************************************************/

#ifndef __I2C_Functions__
#define __I2C_Functions__

// Define Arduino Library
#ifndef __Arduino__
#include <Arduino.h>
#endif

class _I2C_Functions {

	public:

        bool begin(void);

	private:


};

extern _I2C_Functions I2C;

#endif /* defined(__I2C_Functions__) */