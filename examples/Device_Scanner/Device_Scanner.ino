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

	// Set Sensor Name Row
	uint8_t _Row = 24;

	// Control I2C Bus
	for (uint8_t j = 6; j < 21; j = j + 2) {

		// Control Device Line 1
		for (uint8_t i = 11; i < 121; i = i + 7) {

			// Handle Reserved
			if (_Address > 0x03 and _Address < 0x78) {

				// Declare Object
				I2C_Functions Scanner(_Address, true, Mux_Address);

				// Control Device
				if (Scanner.Detect()) {

					// Print Sensor Address
					Terminal.Text(j, i, CYAN, String("0x"));
					Terminal.Text(j, i + 2, CYAN, String(_Address, HEX));

					// Print Sensor Name
					if (_Address == __I2C_Addr_TCA9548__) {
						Terminal.Text(_Row, 2, CYAN, "0x" + String(__I2C_Addr_TCA9548__, HEX) + " - " + String("TCA9548"));
						_Row++;
					}
					if (_Address == __I2C_Addr_RV3028C7__) {
						Terminal.Text(_Row, 2, CYAN, "0x" + String(__I2C_Addr_RV3028C7__, HEX) + " - " + String("RV3028C7"));
						_Row++;
					}
					if (_Address == __I2C_Addr_DS28C__) {
						Terminal.Text(_Row, 2, CYAN, "0x" + String(__I2C_Addr_DS28C__, HEX) + " - " + String("DS28C"));
						_Row++;
					}
					if (_Address == __I2C_Addr_HDC2010__) {
						Terminal.Text(_Row, 2, CYAN, "0x" + String(__I2C_Addr_HDC2010__, HEX) + " - " + String("HDC2010"));
						_Row++;
					}
					if (_Address == __I2C_Addr_MAX17055__) {
						Terminal.Text(_Row, 2, CYAN, "0x" + String(__I2C_Addr_MAX17055__, HEX) + " - " + String("MAX17055"));
						_Row++;
					}
					if (_Address == __I2C_Addr_BQ24298__) {
						Terminal.Text(_Row, 2, CYAN, "0x" + String(__I2C_Addr_BQ24298__, HEX) + " - " + String("BQ24298"));
						_Row++;
					}
					if (_Address == __I2C_Addr_SHT21__) {
						Terminal.Text(_Row, 2, CYAN, "0x" + String(__I2C_Addr_SHT21__, HEX) + " - " + String("SHT21"));
						_Row++;
					}					
					if (_Address == __I2C_Addr_SDP810__) {
						Terminal.Text(_Row, 2, CYAN, "0x" + String(__I2C_Addr_SDP810__, HEX) + " - " + String("SDP810"));
						_Row++;
					}

				} else {

					Terminal.Text(j, i, WHITE, "----");

				}

				// Print Mux Channel
				Terminal.Text(22, 115, CYAN, String(Mux_Address));

			}

			// Handle Address
			_Address++;

		}

	}	

	// Multiplexer Set
	if (Serial.available() > 0) {
		
		// Read Serial
		uint8_t _Read = Serial.read();

		// Decide Mux Channel
		if (_Read == '0') Mux_Address = 0;
		if (_Read == '1') Mux_Address = 1;
		if (_Read == '2') Mux_Address = 2;
		if (_Read == '3') Mux_Address = 3;
		if (_Read == '4') Mux_Address = 4;
		if (_Read == '5') Mux_Address = 5;
		if (_Read == '6') Mux_Address = 6;
		if (_Read == '7') Mux_Address = 7;
		if (_Read == '8') Mux_Address = 8;

		// Clear Sensor List
		Terminal.Text(24,2,CYAN,String(F("                                ")));
		Terminal.Text(25,2,CYAN,String(F("                                ")));
		Terminal.Text(26,2,CYAN,String(F("                                ")));
		Terminal.Text(27,2,CYAN,String(F("                                ")));
		Terminal.Text(28,2,CYAN,String(F("                                ")));
		Terminal.Text(29,2,CYAN,String(F("                                ")));
		Terminal.Text(30,2,CYAN,String(F("                                ")));

	}

}