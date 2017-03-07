#include "FakeGps.h"
#include "GpsCoordinate.h"
#include "Arduino.h"

FakeGps::FakeGps()
{

}

GpsCoordinate *FakeGps::getPosition()
{
    GpsCoordinate *coordinate = new GpsCoordinate(50.280127, 3.972047, 8, 0.5, 0.1, 0, 10);
    delay(2000);
    return coordinate;
}