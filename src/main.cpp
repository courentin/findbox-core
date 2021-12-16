#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <FlashStorage_STM32.h>

static const int RXPin = PA10, TXPin = PA9;
static const int lockerPin = PB3;
static const uint32_t GPSBaud = 9600;
static const int discoveringRadiusInMeters = 300;
static const int gpsTimeoutInSeconds = 10 * 60;

struct Coordinates
{
    double latitude;
    double longitude;
};

Coordinates secretLocation = {48.891416333, 2.3924458330};
TinyGPSPlus gps;
SoftwareSerial serial(RXPin, TXPin);

enum class Error
{
    GPS_NOT_FOUND = 1,
    GPS_TIMEOUT = 2,
};

class Display
{
public:
    void init(uint8_t addr);
    void showError(Error error);
    void showDistance(double distanceInMeters);
    void clear();
    void showLoading(int delayBetweenStepsInMs);
    void setLowConsumptionMode();
    void setNormalMode();

private:
    Adafruit_7segment segments;
};

void Display::init(uint8_t addr = 0x70)
{
    this->segments = Adafruit_7segment();
    segments.begin(addr);
}

void Display::showError(Error error)
{
    char errorCode[4];
    sprintf(errorCode, "E%03d", error);
    segments.print(errorCode);
    segments.blinkRate(HT16K33_BLINK_OFF);
    segments.writeDisplay();
}

void Display::showDistance(double distanceInMeters)
{
    double distanceInKm = distanceInMeters / 1000;
    if (distanceInKm <= 9999)
    {
        segments.print(distanceInKm, 2);
        segments.blinkRate(HT16K33_BLINK_OFF);
        segments.writeDisplay();
    }
    else
    {
        segments.print(9999);
        segments.blinkRate(HT16K33_BLINK_1HZ);
        segments.writeDisplay();
    }
}

void Display::clear()
{
    segments.clear();
    segments.writeDisplay();
}

void Display::showLoading(int delayBetweenStepsInMs = 100)
{
    uint8_t digitSteps[] = {0, 1, 3, 4, 4, 4, 4, 3, 1, 0, 0, 0};
    uint8_t maskSteps[] = {B0000001, B0000001, B0000001, B0000001, B0000010, B0000100, B0001000, B0001000, B0001000, B0001000, B0010000, B0100000};
    uint8_t currentStep = millis() / 100 % 12;

    segments.clear();
    segments.writeDigitRaw(digitSteps[currentStep], maskSteps[currentStep]);
    segments.writeDisplay();
}

void Display::setLowConsumptionMode()
{
    segments.setBrightness(5);
    segments.writeDisplay();
}

void Display::setNormalMode()
{
    segments.setBrightness(15);
    segments.writeDisplay();
}

class Memory
{
public:
    bool isDiscovered();
    void setDiscovered();
    void setUndiscovered();

private:
    uint16_t is_discovered_address = 0;
};

bool Memory::isDiscovered()
{
    bool isDiscovered = false;
    EEPROM.get(is_discovered_address, isDiscovered);

    return isDiscovered;
}

void Memory::setDiscovered()
{
    EEPROM.put(is_discovered_address, true);
    EEPROM.commit();
}

void Memory::setUndiscovered()
{
    EEPROM.put(is_discovered_address, false);
    EEPROM.commit();
}

class Locker
{
public:
    void init(int pin);
    void openingSequence(int openDurationInSeconds);

private:
    int pin;
};

void Locker::init(int pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void Locker::openingSequence(int openDurationInSeconds)
{
    digitalWrite(pin, HIGH);
    delay(openDurationInSeconds * 1000);
    digitalWrite(pin, LOW);
}

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
    display.init();
    locker.init(lockerPin);
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
