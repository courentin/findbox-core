#ifndef DATETIME_H
#define DATETIME_H

#include "Arduino.h"

class DateTime {
private:
    unsigned short int year;
    unsigned short int month;
    unsigned short int day;
    unsigned short int hour;
    unsigned short int minute;
    unsigned short int second;

public:
    DateTime(unsigned short int year, unsigned short int month, unsigned short int day);
    DateTime (unsigned short int year, unsigned short int month, unsigned short int day, unsigned short int hour, unsigned short int minute, unsigned short int second);
    DateTime();
    String toString();
    virtual ~DateTime ();
};

#endif
