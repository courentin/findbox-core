#ifndef findbox_types_h
#define findbox_types_h

struct Coordinates
{
    double latitude;
    double longitude;
};

enum class Error
{
    GPS_NOT_FOUND = 1,
    GPS_TIMEOUT = 2,
};

#endif
