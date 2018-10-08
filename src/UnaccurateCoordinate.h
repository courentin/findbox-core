#ifndef SECRET_COORDINATE_H
#define SECRET_COORDINATE_H

#include "Coordinate.h"

class UnaccurateCoordinate : public Coordinate {
protected:
  // in metter
  double radius;
public:
  UnaccurateCoordinate(double latitude = 0, double longitude = 0, double radius = 0) : Coordinate(latitude, longitude), radius(radius) {}
  double getRadius() { return radius; };
};

#endif
