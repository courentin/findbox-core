#ifndef locker_h
#define locker_h

#include "Arduino.h"

class Locker
{
public:
    void init(int pin)
    {
        this->pin = pin;
        digitalWrite(pin, LOW);
        pinMode(pin, OUTPUT);
    }

    void openingSequence(int openDurationInSeconds)
    {
        digitalWrite(pin, HIGH);
        delay(openDurationInSeconds * 1000);
        digitalWrite(pin, LOW);
    }

private:
    int pin;
};

#endif
