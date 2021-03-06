#include "Gps.h"
#include "Arduino.h"
#include <SoftwareSerial.h>

Gps::Gps(uint8_t rx, uint8_t tx) : ss(rx, tx) {
	ss.begin(9600);
}

GpsCoordinate Gps::getPosition()
{
	while (
		   !gps.satellites.isValid()
		|| !gps.hdop.isValid()
		|| !gps.location.isValid()
		|| ! gps.altitude.isValid()
	) {
		unsigned long start = millis();
		do
		{
		  while (ss.available())
			gps.encode(ss.read());
		} while (millis() - start < 1000);

		if (millis() > 5000 && gps.charsProcessed() < 10)
		  Serial.println(F("No GPS data received: check wiring"));
	}

	char sz[32];
    sprintf(sz, "%02d-%02d-%02d %02d:%02d:%02d", gps.date.year(), gps.date.month(), gps.date.day(), gps.time.hour(), gps.time.minute(), gps.time.second());

	GpsCoordinate coordinate(
		gps.location.lat(),
		gps.location.lng(),
		gps.satellites.value(),
		gps.hdop.value(),
		gps.altitude.meters(),
		gps.speed.kmph(),
		sz);

    return coordinate;
}
