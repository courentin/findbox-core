#include "Coordinate.h"
#include "math.h"

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

Coordinate::Coordinate(double latitude, double longitude) : latitude(latitude), longitude(longitude)
{

}

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}

double Coordinate::getDistance(const Coordinate* c)
{
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = deg2rad(this->latitude);
	lon1r = deg2rad(this->longitude);
	lat2r = deg2rad(c->latitude);
	lon2r = deg2rad(c->longitude);
	u = sin((lat2r - lat1r)/2);
	v = sin((lon2r - lon1r)/2);
	return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}