#include "I2C_Functions.h"

void setup() {

	// Serial Communication Start
	Serial.begin(115200);

	// Header
	Serial.println("       I2C Functions      ");
	Serial.println("--------------------------");

}

void loop() {

	// Sensor Detect
	bool _Sensor_Control = I2C.Control_Device(__I2C__HDC2010__Addr__);

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