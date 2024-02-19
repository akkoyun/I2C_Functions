// Include I2C Library
#include <I2C_Functions.h>

// Declare Object
I2C_Functions HDC2010(__I2C_Addr_HDC2010__);

void setup() {

	// Serial Communication Start
	Serial.begin(115200);

	// Begin Object
	HDC2010.Begin();

	// Header
	Serial.println(F("       I2C Functions      "));
	Serial.print(F("         ")); Serial.println(__I2C_Functions_Version__);
	Serial.println(F("--------------------------"));

	// Print Sensor Detect
	Serial.print(F("0x"));
	Serial.print(HDC2010.Address(), HEX);
	Serial.print(F(" Device Status : "));
	
	// Control for Device Detect
	if (HDC2010.Detect()) {
		
		// Print Status
		Serial.println(F("OK"));

	} else {

		// Print Status
		Serial.println(F("FAIL"));

	}

}

void loop() {


}