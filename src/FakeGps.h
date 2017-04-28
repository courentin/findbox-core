#ifndef FAKE_GPS_H
#define FAKE_GPS_H

#include "GpsCoordinate.h"
#include "GpsInterface.h"

class FakeGps : public GpsInterface
{
	public:
		FakeGps();
		FakeGps(double latitude, double longitude);
		GpsCoordinate getPosition();
	private:
		double latitude, longitude;
};

#endif
