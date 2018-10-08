#include "GpsCoordinate.h"
#include "Arduino.h"
#include "DateTime.h"

GpsCoordinate::GpsCoordinate(double latitude, double longitude, unsigned int nbOfSatellites, double precision, double altitude, double speed, DateTime date) :
	UnaccurateCoordinate(latitude, longitude, precision),
	nbOfSatellites(nbOfSatellites),
	altitude(altitude),
	speed(speed),
	date(date)
{

}

GpsCoordinate::GpsCoordinate() :
	UnaccurateCoordinate(),
	nbOfSatellites(0),
	altitude(0),
	speed(0),
	date()
	{}
