// Include I2C Library
#include <I2C_Functions.h>

// Declare Object — PCF8574 I/O expander, address variant A
I2C_Functions Expander(__I2C_Addr_PCF8574_A__);

// Target register and bit for the demo
const uint8_t Control_Register = 0x00;
const uint8_t Target_Bit       = 3;

void setup() {

	// Serial Communication Start
	Serial.begin(115200);

	// Begin Object
	Expander.Begin();

	// Header
	Serial.println(F("       Bit Control Demo     "));
	Serial.println(F("----------------------------"));

	// Device Check
	if (!Expander.Detect()) {
		Serial.println(F("Device not found. Check wiring."));
		return;
	}

	Serial.print(F("Device 0x"));
	Serial.print(Expander.Address(), HEX);
	Serial.println(F(" detected"));
	Serial.println(F("----------------------------"));

	// --- Try_Read_Register_Bit: explicit status + value via pointer ---
	bool bit_state = false;
	bool read_ok = Expander.Try_Read_Register_Bit(Control_Register, Target_Bit, &bit_state);

	Serial.print(F("[Try_Read] Bit "));
	Serial.print(Target_Bit);
	Serial.print(F(" = "));

	if (read_ok) {
		Serial.println(bit_state ? F("1") : F("0"));
	} else {
		Serial.println(F("READ FAILED"));
	}

	// --- Set_Register_Bit: reads, sets only if needed, writes back ---
	Serial.print(F("[Set]      Bit "));
	Serial.print(Target_Bit);
	Serial.print(F(" -> "));
	Serial.println(Expander.Set_Register_Bit(Control_Register, Target_Bit) ? F("OK") : F("FAIL"));

	// Verify
	Expander.Try_Read_Register_Bit(Control_Register, Target_Bit, &bit_state);
	Serial.print(F("           Bit "));
	Serial.print(Target_Bit);
	Serial.print(F(" = "));
	Serial.println(bit_state ? F("1") : F("0"));

	// --- Clear_Register_Bit: reads, clears only if needed, writes back ---
	Serial.print(F("[Clear]    Bit "));
	Serial.print(Target_Bit);
	Serial.print(F(" -> "));
	Serial.println(Expander.Clear_Register_Bit(Control_Register, Target_Bit) ? F("OK") : F("FAIL"));

	// Verify
	Expander.Try_Read_Register_Bit(Control_Register, Target_Bit, &bit_state);
	Serial.print(F("           Bit "));
	Serial.print(Target_Bit);
	Serial.print(F(" = "));
	Serial.println(bit_state ? F("1") : F("0"));

	// --- Toggle_Register_Bit: always flips ---
	Serial.print(F("[Toggle]   Bit "));
	Serial.print(Target_Bit);
	Serial.print(F(" -> "));
	Serial.println(Expander.Toggle_Register_Bit(Control_Register, Target_Bit) ? F("OK") : F("FAIL"));

	// Verify
	Expander.Try_Read_Register_Bit(Control_Register, Target_Bit, &bit_state);
	Serial.print(F("           Bit "));
	Serial.print(Target_Bit);
	Serial.print(F(" = "));
	Serial.println(bit_state ? F("1") : F("0"));

	// --- Write_Register_Bit: sets or clears based on bool value ---
	bool target_value = false;
	Serial.print(F("[Write]    Bit "));
	Serial.print(Target_Bit);
	Serial.print(F(" <- "));
	Serial.print(target_value ? F("1") : F("0"));
	Serial.print(F(" -> "));
	Serial.println(Expander.Write_Register_Bit(Control_Register, Target_Bit, target_value) ? F("OK") : F("FAIL"));

	// Final state
	Expander.Try_Read_Register_Bit(Control_Register, Target_Bit, &bit_state);
	Serial.print(F("           Bit "));
	Serial.print(Target_Bit);
	Serial.print(F(" = "));
	Serial.println(bit_state ? F("1") : F("0"));

	Serial.println(F("----------------------------"));
	Serial.println(F("Done."));

}

void loop() {

}
