// Include I2C Library
#include <I2C_Functions.h>

// Declare Object
I2C_Functions HDC2010(__I2C_Addr_HDC2010__, true, __B108AA_MUX_HDC2010__);

void setup() {

	// Serial Communication Start
	Serial3.begin(115200);

	// Begin Object
	HDC2010.Begin();

	// Header
	Serial3.println(F("       I2C Functions      "));
	Serial3.print(F("         ")); Serial3.println(__I2C_Functions_Version__);
	Serial3.println(F("--------------------------"));

	// Print Sensor Detect
	Serial3.print(F("0x"));
	Serial3.print(HDC2010.Address(), HEX);
	Serial3.print(F(" Device Status : "));
	
	// Control for Device Detect
	if (HDC2010.Detect() == true) {
		
		// Print Status
		Serial3.println(F("OK"));

	} else {

		// Print Status
		Serial3.println(F("FAIL"));

	}

}

void loop() {


}