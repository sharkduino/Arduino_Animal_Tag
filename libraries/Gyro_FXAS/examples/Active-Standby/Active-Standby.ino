#include "Gyro_FXAS.h"
#include <Narcoleptic.h>

constexpr long brate = 9600;

inline void n_delay(long);

void setup() {
	Serial.begin(brate);
	FXAS::begin(FXAS::ODR::HZ_25,
	            FXAS::Range::DPS_250,
	            false);
}

void loop() {
	if (FXAS::isActive) {
		Serial.print("Standby");
		FXAS::standby();
	} else {
		Serial.print("Active");
		FXAS::active();
		n_delay(FXAS::timeToActive());
	}
	Serial.println(": reading data");
	for (int i=0; i<10; i++) {
		FXAS::sample s;
		FXAS::read(s);
		Serial.print(FXAS::sampleToDps(s.x)) ; Serial.write(' ');
		Serial.print(FXAS::sampleToDps(s.y)) ; Serial.write(' ');
		Serial.println(FXAS::sampleToDps(s.z));
		n_delay(40);
	}
}

inline void n_delay(long ms) {
	Serial.end();
	Narcoleptic.delay(ms);
	Serial.begin(brate);
}