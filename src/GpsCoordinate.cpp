#include "GpsCoordinate.h"

GpsCoordinate::GpsCoordinate(double latitude, double longitude, int nbOfSatellites, double precision, double altitude, double speed, int date) :
	Coordinate(latitude, longitude),
	nbOfSatellites(nbOfSatellites),
	precision(precision),
	altitude(altitude),
	speed(speed),
	date(date)
{

}
