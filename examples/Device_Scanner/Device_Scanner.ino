#include <I2C_Functions.h>

// Define Console Library
#ifndef __Console__
#include <Console.h>
#endif

// Declare Global Variable
uint8_t Mux_Address = 0x00;

void setup() {

	// Serial Communication Start
	Serial.begin(115200);

	// Start Console
	Terminal.Begin(Serial);

	// Draw Table
	Terminal.I2C_Scanner_Table();

}

void loop() {

	// Declare Address Variable
	uint8_t _Address = 0x00;

	for (uint8_t j = 6; j < 21; j = j + 2) {

		// Control Device Line 1
		for (uint8_t i = 11; i < 121; i = i + 7) {

			// Handle Reserved
			if (_Address > 0x03 and _Address < 0x78) {

				// Declare Object
				I2C_Functions Scanner(_Address, Mux_Address);

				// Start Object
				Scanner.Begin();

				// Control Device
				if (Scanner.Detect()) {

					// Print Sensor Address
					Terminal.Text(j, i, CYAN, String("0x"));
					Terminal.Text(j, i + 2, CYAN, String(_Address, HEX));

				} else {

					Terminal.Text(j, i, WHITE, "----");

				}

			}

			// Handle Address
			_Address++;

		}

	}	

	// Multiplexer Set
	if (Serial.available() > 0) Mux_Address = Serial.read() - 48;

	// Print Mux Channel
	Terminal.Text(22, 115, CYAN, String(Mux_Address));

}