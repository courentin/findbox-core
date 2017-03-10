#include "FakeGps.h"
#include "GpsCoordinate.h"
#include "Arduino.h"

FakeGps::FakeGps()
{

}

GpsCoordinate FakeGps::getPosition()
{
    GpsCoordinate coordinate(50.280127, 3.972047, 8, 0.5, 0.1, 0, "2017-03-03 03:03:03");
    delay(2000);
    return coordinate;
}