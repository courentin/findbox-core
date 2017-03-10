#ifndef GPS_COORDINATE_H
#define GPS_COORDINATE_H

#include "Coordinate.h"
#include "Arduino.h"

class GpsCoordinate : public Coordinate
{
	public:
		int nbOfSatellites;
		double precision;
		double altitude;
		double speed;
		String date;
		GpsCoordinate();
		GpsCoordinate(double latitude, double longitude, int nbOfSatellites, double precision, double altitude, double speed, String date);
};

#endif