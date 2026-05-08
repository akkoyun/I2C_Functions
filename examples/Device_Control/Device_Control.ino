// Include I2C Library
#include <I2C_Functions.h>

// Declare Object
I2C_Functions HDC2010(__I2C_Addr_HDC2010__);

// Declare Example Read Register
const uint8_t Example_Read_Register = 0x00;

// Declare Example Write Control
const bool Example_Write_Enable = false;

// Declare Example Write Register
const uint8_t Example_Write_Register = 0x00;

// Declare Example Write Value
const uint8_t Example_Write_Value = 0x00;

void setup() {

	// Serial Communication Start
	Serial.begin(115200);

	// Begin Object
	HDC2010.Begin();

	// Header
	Serial.println(F("       I2C Functions      "));
	Serial.print(F("         ")); Serial.println(F("03.00.01"));
	Serial.println(F("--------------------------"));

	// Print Sensor Detect
	Serial.print(F("0x"));
	Serial.print(HDC2010.Address(), HEX);
	Serial.print(F(" Device Status : "));
	
	// Control for Device Detect
	if (HDC2010.Detect()) {

		// Declare Response Variable
		uint8_t Register_Value = 0x00;
		bool Write_Status = false;

		// Read Register With Explicit Status
		bool Read_Status = HDC2010.Try_Read_Register(Example_Read_Register, &Register_Value);

		// Write Register With Explicit Status
		if (Example_Write_Enable) Write_Status = HDC2010.Write_Register(Example_Write_Register, Example_Write_Value, true);
		
		// Print Status
		Serial.println(F("OK"));

		// Print Write Result Header
		Serial.print(F("Write Demo Status : "));

		// Control for Write Enable
		if (Example_Write_Enable) {

			// Print Write Register Header
			Serial.print(F("ENABLED (0x"));
			Serial.print(Example_Write_Register, HEX);
			Serial.print(F(") : "));

			// Control for Write Status
			if (Write_Status) {

				// Print Write Status
				Serial.print(F("OK"));
				Serial.print(F(" Data : 0x"));
				Serial.println(Example_Write_Value, HEX);

			} else {

				// Print Write Status
				Serial.println(F("FAIL"));

			}

		} else {

			// Print Write Status
			Serial.println(F("DISABLED (set Example_Write_Enable only for a known safe writable register)"));

		}

		// Print Read Result Header
		Serial.print(F("Read 0x"));
		Serial.print(Example_Read_Register, HEX);
		Serial.print(F(" Status : "));

		// Control for Read Status
		if (Read_Status) {

			// Print Read Status
			Serial.print(F("OK"));
			Serial.print(F(" Data : 0x"));
			Serial.println(Register_Value, HEX);

		} else {

			// Print Read Status
			Serial.println(F("FAIL"));

		}

	} else {

		// Print Status
		Serial.println(F("FAIL"));

	}

}

void loop() {


}