#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <FlashStorage_STM32.h>

static const int RXPin = PA10, TXPin = PA9;
static const uint32_t GPSBaud = 9600;
static const int errorMarginInMeters = 300;

struct Coordinates
{
    double latitude;
    double longitude;
};

Coordinates secretLocation = {48.891416333, 2.3924458330};

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial serial(RXPin, TXPin);

enum class Error
{
    GPS_NOT_FOUND = 1,
};

class Display
{
public:
    Display(uint8_t addr);
    void showError(Error error);
    void showDistance(double distanceInKm);
    void clear();
    void showLoading(int delayBetweenStepsInMs);
    void setLowConsumptionMode();
    void setNormalMode();

private:
    Adafruit_7segment segments;
};

Display::Display(uint8_t addr = 0x70) : segments()
{
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

void Display::showDistance(double distanceInKm)
{
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
    Memory();
    bool isDiscovered();
    void setDiscovered();

private:
    uint16_t is_discovered_address = 0;
};

Memory::Memory()
{
}

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

void openingSequence(int openDurationInSeconds)
{
}

Display display;
Memory memory;

void setup()
{
    display = Display();
    memory = Memory();
    serial.begin(GPSBaud);
    display.showDistance(0);
}

void loop()
{
    if (memory.isDiscovered())
    {
        openingSequence(7);
    }
    else
    {
        bool hasAccurateLocation = false;
        while (serial.available() > 0 && !hasAccurateLocation)
        {
            display.showLoading();
            hasAccurateLocation =
                gps.encode(serial.read()) &&
                gps.location.isValid() &&
                gps.hdop.isValid() &&
                gps.hdop.hdop() <= 10;
        }

        if (hasAccurateLocation)
        {
            Coordinates currentLocation = {gps.location.lat(), gps.location.lng()};
            double distance = TinyGPSPlus::distanceBetween(currentLocation.latitude, currentLocation.longitude, secretLocation.latitude, secretLocation.longitude) / 1000;
            if (distance < errorMarginInMeters)
            {
                display.showDistance(0);
                memory.setDiscovered();
                openingSequence(20);
            }
            else
            {
                display.showDistance(distance);
            }
        }

        if (millis() > 5000 && gps.charsProcessed() < 10)
        {
            display.showError(Error::GPS_NOT_FOUND);
            while (true)
                ;
        }
    }
    delay(18000);
    display.setLowConsumptionMode();
}
