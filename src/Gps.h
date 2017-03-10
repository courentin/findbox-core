#ifndef GPS_H
#define GPS_H

#include "GpsInterface.h"
#include <SoftwareSerial.h>
#include <inttypes.h>
#include <TinyGPS.h>

class Gps : public GpsInterface
{
    public:
        Gps(uint8_t rx, uint8_t tx);
		GpsCoordinate getPosition();
    private:
        TinyGPS gps;
	    SoftwareSerial ss;
};

#endif