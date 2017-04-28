#include "Coordinate.h"
#include "math.h"
#include "TinyGPS++.h"

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}

double Coordinate::getDistance(const Coordinate& c)
{
    return TinyGPSPlus::distanceBetween(this->latitude, this->longitude, c.latitude, c.longitude);
}
