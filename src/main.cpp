#include "config.h"

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "findbox_types.h"
#include "Display.h"
#include "Memory.h"
#include "Locker.h"


TinyGPSPlus gps;
SoftwareSerial serial(RX_PIN, TX_PIN);

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
            display.showError();
            return;
        }

        isTimeout = millis() > gpsTimeoutInSeconds * 1000;
    }

    if (isTimeout)
    {
        display.showError();
        return;
    }

    Coordinates currentLocation = {gps.location.lat(), gps.location.lng()};
    double distanceInMeters = TinyGPSPlus::distanceBetween(currentLocation.latitude, currentLocation.longitude, secretLocation.latitude, secretLocation.longitude);
    if (distanceInMeters < discoveringRadiusInMeters)
    {
        display.showDistance(0);
        display.enableBlinking();
        memory.setDiscovered();
        locker.openingSequence(20);
        display.disableBlinking();
    }
    else
    {
        display.showDistance(distanceInMeters);
    }
}

void setup()
{
    locker.init(LOCKER_PIN); // Needs to be done first to avoid unlocking in the meantime
    
    #ifdef I2C_PULL_UP_PIN
        digitalWrite(I2C_PULL_UP_PIN, HIGH);
        pinMode(I2C_PULL_UP_PIN, OUTPUT);
    #endif

    display.init();
    serial.begin(GPSBaud);
    memory.setUndiscovered();

    if (memory.isDiscovered()) {
        display.showOpen();
        display.enableBlinking();
        locker.openingSequence(7);
        display.disableBlinking();
    } else {
        lookForLocation(gpsTimeoutInSeconds);
    }

    delay(18000);
    display.setLowConsumptionMode();
}

void loop()
{
}
