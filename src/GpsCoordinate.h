#ifndef GPS_COORDINATE_H
#define GPS_COORDINATE_H

#include "UnaccurateCoordinate.h"
#include "Arduino.h"
#include "DateTime.h"

class GpsCoordinate : public UnaccurateCoordinate
{
protected:
	unsigned int nbOfSatellites;
	double altitude;
	double speed;
	unsigned int year;
	DateTime date;
public:
	double getAltitude() const { return altitude; }
	unsigned int getNbOfSatellites() const { return nbOfSatellites; }
	double getSpeed() const { return speed; }
	DateTime getDate() const { return date; }
	GpsCoordinate(double latitude, double longitude, unsigned int nbOfSatellites, double precision, double altitude, double speed, DateTime date);
	GpsCoordinate();
};

#endif
