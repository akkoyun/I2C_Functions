#include <I2C_Functions.h>

// Declare Object
I2C_Functions HDC2010(0x52, 3);

void setup() {

	// Serial Communication Start
	Serial.begin(115200);

	// Start I2C
	HDC2010.Begin();

	// Header
	Serial.println(F("       I2C Functions      "));
	Serial.println(F("--------------------------"));

}

void loop() {

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