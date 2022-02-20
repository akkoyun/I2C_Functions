#include "I2C_Functions.h"

void setup() {

	// Serial Communication Start
	Serial.begin(115200);

	// Header
	Serial.println("       I2C Functions      ");
	Serial.println("--------------------------");

}

void loop() {

	// Sensor Address
	uint8_t _Sensor_Address = 0x40;	// HDC2010 TH Sensor

	// Sensor Detect
	bool _Sensor_Control = I2C.Control_Device(_Sensor_Address);

	// Print Sensor Detect
	Serial.print("Device Status : ");
	if (_Sensor_Control == true) {
		
		// Print Status
		Serial.println("OK");

	} else {

		// Print Status
		Serial.println("FAIL");

	}
	

	// Loop Delay
	delay(1000);

}