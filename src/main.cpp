#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "findbox_types.h"
#include "Display.h"
#include "Memory.h"
#include "Locker.h"

static const int RXPin = PA10, TXPin = PA9;
static const int lockerPin = PA3;
static const uint32_t GPSBaud = 9600;
static const int discoveringRadiusInMeters = 300;
static const int gpsTimeoutInSeconds = 10 * 60;

Coordinates secretLocation = {48.891416333, 2.3924458330};
TinyGPSPlus gps;
SoftwareSerial serial(RXPin, TXPin);

Display display = Display();
Memory memory = Memory();
Locker locker = Locker();

void lookForLocation(int gpsTimeoutInSeconds)
{
    bool hasAccurateLocation = false;
    bool isTimeout = false;
    while (!hasAccurateLocation && !isTimeout)
    {
        display.showLoading();
        while (serial.available() > 0)
        {
            hasAccurateLocation =
                gps.encode(serial.read()) &&
                gps.location.isValid() &&
                gps.hdop.isValid() &&
                gps.hdop.hdop() <= 10;
        }
        if (millis() > 5000 && gps.charsProcessed() < 10)
        {
            display.showError(Error::GPS_NOT_FOUND);
            return;
        }

        isTimeout = millis() > gpsTimeoutInSeconds * 1000;
    }

    if (isTimeout)
    {
        display.showError(Error::GPS_TIMEOUT);
        return;
    }

    Coordinates currentLocation = {gps.location.lat(), gps.location.lng()};
    double distanceInMeters = TinyGPSPlus::distanceBetween(currentLocation.latitude, currentLocation.longitude, secretLocation.latitude, secretLocation.longitude);
    if (distanceInMeters < discoveringRadiusInMeters)
    {
        display.showDistance(0);
        memory.setDiscovered();
        locker.openingSequence(20);
    }
    else
    {
        display.showDistance(distanceInMeters);
    }
}

void setup()
{
    locker.init(lockerPin); // Needs to be done first to avoid unlocking in the meantime
    display.init();
    serial.begin(GPSBaud);

    if (memory.isDiscovered())
        locker.openingSequence(7);

    else
        lookForLocation(gpsTimeoutInSeconds);

    delay(18000);
    display.setLowConsumptionMode();
}

void loop()
{
}
