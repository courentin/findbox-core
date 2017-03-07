#ifndef GPS_INTERFACE_H
#define GPS_INTERFACE_H

#include "GpsCoordinate.h"

class GpsInterface
{
	public:
		virtual GpsCoordinate* getPosition() = 0;
};

#endif