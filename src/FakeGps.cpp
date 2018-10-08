#include "FakeGps.h"
#include "GpsCoordinate.h"
#include "Arduino.h"
#include "DateTime.h"

FakeGps::FakeGps() : latitude(50.280127), longitude(3.972047) {}

FakeGps::FakeGps(double latitude, double longitude) : latitude(latitude), longitude(longitude) {}

GpsCoordinate FakeGps::getPosition()
{
    GpsCoordinate coordinate(latitude, longitude, 8, 0.5, 0.1, 0, DateTime(2017, 03, 03, 03, 03, 03));
    delay(2000);
    return coordinate;
}
