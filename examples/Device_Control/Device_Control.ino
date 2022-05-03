#include <I2C_Functions.h>

void setup() {

	// Serial Communication Start
	Serial.begin(115200);

	// Header
	Serial.println(F("       I2C Functions      "));
	Serial.print(F("         ")); Serial.println(__I2C_Functions_Version__);
	Serial.println(F("--------------------------"));

}

void loop() {

	// Declare Object
	I2C_Functions HDC2010(__I2C_Addr_HDC2010__, true, __Mux_Channel_3__);

	// Print Sensor Detect
	Serial.print(F("0x"));
	Serial.print(HDC2010.Address(), HEX);
	Serial.print(F(" Device Status : "));
	if (HDC2010.Detect() == true) {
		
		// Print Status
		Serial.println(F("OK"));

	} else {

		// Print Status
		Serial.println(F("FAIL"));

	}
	

	// Loop Delay
	delay(1000);

}