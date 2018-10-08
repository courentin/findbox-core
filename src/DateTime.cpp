#include "DateTime.h"

DateTime::DateTime(unsigned short int year, unsigned short int month, unsigned short int day) :
    year(year),
    month(month),
    day(day),
    hour(0),
    minute(0),
    second(0)
{

}

DateTime::DateTime(unsigned short int year, unsigned short int month, unsigned short int day, unsigned short int hour, unsigned short int minute, unsigned short int second) :
    year(year),
    month(month),
    day(day),
    hour(hour),
    minute(minute),
    second(second)
{

}

DateTime::DateTime() :
    year(0),
    month(0),
    day(0),
    hour(0),
    minute(0),
    second(0)
{

}

String DateTime::toString() {
    // TODO: format numbers with leading zero
    // TODO: do not print time when no time is defined
    String output = String(year)+"-" + String(month)+"-"+String(day)+" "+String(hour)+":"+String(minute)+":"+String(second);
    return output;
}

DateTime::~DateTime()
{

}
