#include "GpsCoordinate.h"
#include "Arduino.h"

GpsCoordinate::GpsCoordinate(double latitude, double longitude, int nbOfSatellites, double precision, double altitude, double speed, String date) :
	Coordinate(latitude, longitude),
	nbOfSatellites(nbOfSatellites),
	precision(precision),
	altitude(altitude),
	speed(speed),
	date(date)
{

}
