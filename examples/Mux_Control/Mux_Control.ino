// Include I2C Library
#include <I2C_Functions.h>

// Three sensors behind a TCA9548 multiplexer at the default address (0x70).
// Each object stores its own channel; the library switches the mux automatically
// before every transaction — no manual channel management needed.

// HDC2010 Temperature / Humidity sensor on channel 1
I2C_Functions Temp(__I2C_Addr_HDC2010__, true, 1);

// MPL3115A2 Pressure / Altitude sensor on channel 2
I2C_Functions Pres(__I2C_Addr_MPL3115A2__, true, 2);

// MAX17055 Fuel Gauge on channel 3
I2C_Functions Gauge(__I2C_Addr_MAX17055__, true, 3);

void setup() {

	// Serial Communication Start
	Serial.begin(115200);

	// Begin each object — Wire is started once per Begin() call but the
	// library guards against duplicate bus initializations.
	Temp.Begin();
	Pres.Begin();
	Gauge.Begin();

	// Header
	Serial.println(F("       Mux Control Demo      "));
	Serial.println(F("-----------------------------"));

	// Device Status
	Serial.print(F("HDC2010  ch1 : "));
	Serial.println(Temp.Detect()  ? F("OK") : F("NOT FOUND"));

	Serial.print(F("MPL3115  ch2 : "));
	Serial.println(Pres.Detect()  ? F("OK") : F("NOT FOUND"));

	Serial.print(F("MAX17055 ch3 : "));
	Serial.println(Gauge.Detect() ? F("OK") : F("NOT FOUND"));

	Serial.println(F("-----------------------------"));

}

void loop() {

	Serial.println(F("--- Poll ---"));

	// HDC2010: read measurement configuration register (0x0E)
	// The mux switches to channel 1 automatically before the read.
	if (Temp.Detect()) {

		uint8_t t_reg = 0x00;
		if (Temp.Try_Read_Register(0x0E, &t_reg)) {
			Serial.print(F("HDC2010  0x0E = 0x"));
			Serial.println(t_reg, HEX);
		} else {
			Serial.println(F("HDC2010  read FAIL"));
		}

	}

	// MPL3115A2: read status register (0x00)
	// The mux switches to channel 2 automatically before the read.
	if (Pres.Detect()) {

		uint8_t p_status = 0x00;
		if (Pres.Try_Read_Register(0x00, &p_status)) {
			Serial.print(F("MPL3115  0x00 = 0x"));
			Serial.println(p_status, HEX);
		} else {
			Serial.println(F("MPL3115  read FAIL"));
		}

	}

	// MAX17055: read cell voltage register (0x09, big-endian 16-bit)
	// The mux switches to channel 3 automatically before the read.
	if (Gauge.Detect()) {

		uint16_t vcell = 0x0000;
		if (Gauge.Try_Read_Register_Word(0x09, &vcell, true)) {
			Serial.print(F("MAX17055 0x09 = 0x"));
			Serial.println(vcell, HEX);
		} else {
			Serial.println(F("MAX17055 read FAIL"));
		}

	}

	// Re-detect all devices periodically in case they disconnect or reconnect
	Temp.Detect_Device();
	Pres.Detect_Device();
	Gauge.Detect_Device();

	delay(2000);

}
