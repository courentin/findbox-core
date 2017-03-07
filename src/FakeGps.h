#ifndef FAKE_GPS_H
#define FAKE_GPS_H

#include "GpsCoordinate.h"
#include "GpsInterface.h"

class FakeGps : public GpsInterface
{
	public:
        FakeGps();
		GpsCoordinate* getPosition();
};

#endif