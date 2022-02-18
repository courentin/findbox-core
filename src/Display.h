#ifndef display_h
#define display_h

#include <SPI.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "findbox_types.h"

class Display
{
public:
    void init(uint8_t addr = 0x70)
    {
        this->segments = Adafruit_7segment();
        segments.begin(addr);
    }

    void showError(Error error)
    {
        char errorCode[4];
        sprintf(errorCode, "E%03d", error);
        segments.print(errorCode);
        segments.blinkRate(HT16K33_BLINK_OFF);
        segments.writeDisplay();
    }

    void showDistance(double distanceInMeters)
    {
        double distanceInKm = distanceInMeters / 1000;
        if (distanceInKm <= 9999)
        {
            segments.print(distanceInKm, 2);
            this->disableBlinking();
            segments.writeDisplay();
        }
        else
        {
            segments.print(9999);
            this->enableBlinking();
            segments.writeDisplay();
        }
    }

    void enableBlinking()
    {
        segments.blinkRate(HT16K33_BLINK_1HZ);
        segments.writeDisplay();
    }

    void disableBlinking()
    {
        segments.blinkRate(HT16K33_BLINK_OFF);
        segments.writeDisplay();
    }

    void clear()
    {
        segments.clear();
        segments.writeDisplay();
    }

    void showOpen()
    {
        segments.clear();

        segments.writeDigitRaw(0, B0111001);
        segments.writeDigitRaw(1, B0001001);
        segments.writeDigitRaw(3, B0001001);
        segments.writeDigitRaw(4, B0001111);

        segments.writeDisplay();
    }

    void showLoading(int delayBetweenStepsInMs = 100)
    {
        uint8_t digitSteps[] = {0, 1, 3, 4, 4, 4, 4, 3, 1, 0, 0, 0};
        uint8_t maskSteps[] = {B0000001, B0000001, B0000001, B0000001, B0000010, B0000100, B0001000, B0001000, B0001000, B0001000, B0010000, B0100000};
        uint8_t currentStep = millis() / 100 % 12;

        segments.clear();
        segments.writeDigitRaw(digitSteps[currentStep], maskSteps[currentStep]);
        segments.writeDisplay();
    }

    void setLowConsumptionMode()
    {
        segments.setBrightness(5);
        segments.writeDisplay();
    }
    void setNormalMode()
    {
        segments.setBrightness(15);
        segments.writeDisplay();
    }

private:
    Adafruit_7segment segments;
};

#endif
