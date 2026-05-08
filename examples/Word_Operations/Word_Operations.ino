// Include I2C Library
#include <I2C_Functions.h>

// Declare Object — MAX17055 Fuel Gauge (16-bit registers, big-endian)
I2C_Functions Gauge(__I2C_Addr_MAX17055__);

// MAX17055 register addresses
const uint8_t REG_VCell    = 0x09;  // Cell voltage (read-only)
const uint8_t REG_RepSOC   = 0x06;  // Reported state of charge (read-only)
const uint8_t REG_Config   = 0x1D;  // Configuration register (read/write)

void setup() {

	// Serial Communication Start
	Serial.begin(115200);

	// Begin Object
	Gauge.Begin();

	// Header
	Serial.println(F("     Word Operations Demo    "));
	Serial.println(F("----------------------------"));

	// Device Check
	if (!Gauge.Detect()) {
		Serial.println(F("Device not found. Check wiring."));
		return;
	}

	Serial.print(F("Device 0x"));
	Serial.print(Gauge.Address(), HEX);
	Serial.println(F(" detected"));
	Serial.println(F("----------------------------"));

	// --- Try_Read_Register_Word: big-endian (most sensors send MSB first) ---
	uint16_t vcell = 0x0000;
	if (Gauge.Try_Read_Register_Word(REG_VCell, &vcell, true)) {
		Serial.print(F("[Read Word BE] VCell raw = 0x"));
		Serial.println(vcell, HEX);
	} else {
		Serial.println(F("[Read Word BE] FAILED"));
	}

	// --- Try_Read_Register_Word: little-endian (LSB first, default) ---
	uint16_t vcell_le = 0x0000;
	if (Gauge.Try_Read_Register_Word(REG_VCell, &vcell_le)) {
		Serial.print(F("[Read Word LE] VCell raw = 0x"));
		Serial.println(vcell_le, HEX);
	} else {
		Serial.println(F("[Read Word LE] FAILED"));
	}

	// --- Read_Register_Word: convenience wrapper, returns 0x0000 on failure ---
	uint16_t soc = Gauge.Read_Register_Word(REG_RepSOC, true);
	Serial.print(F("[Read Wrap BE] SoC raw   = 0x"));
	Serial.println(soc, HEX);

	// --- Read_Multiple_Register: read a block of registers ---
	uint8_t block[6];
	if (Gauge.Read_Multiple_Register(REG_VCell, block, 6)) {
		Serial.println(F("[Read Multi]   6-byte block from 0x09:"));
		for (uint8_t i = 0; i < 6; i++) {
			Serial.print(F("               ["));
			Serial.print(i);
			Serial.print(F("] = 0x"));
			Serial.println(block[i], HEX);
		}
	} else {
		Serial.println(F("[Read Multi]   FAILED"));
	}

	// --- Write_Register_Word: big-endian write to configuration register ---
	// NOTE: Only write to registers documented as writable in the datasheet.
	// This example reads the config first, then writes back the same value.
	uint16_t config = 0x0000;
	if (Gauge.Try_Read_Register_Word(REG_Config, &config, true)) {
		Serial.print(F("[Write Word BE] Config read = 0x"));
		Serial.println(config, HEX);

		if (Gauge.Write_Register_Word(REG_Config, config, true, true)) {
			Serial.println(F("[Write Word BE] Config written back OK"));
		} else {
			Serial.println(F("[Write Word BE] Write FAILED"));
		}
	}

	Serial.println(F("----------------------------"));
	Serial.println(F("Done."));

}

void loop() {

}
