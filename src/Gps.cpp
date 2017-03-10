#include "Gps.h"
#include "Arduino.h"
#include <SoftwareSerial.h>

Gps::Gps(uint8_t rx, uint8_t tx) : ss(rx, tx) {
	ss.begin(9600);
}

GpsCoordinate Gps::getPosition()
{
    GpsCoordinate coordinate;
    bool again = true;
    float flat, flon, falt, speed, satellites, precision;
    char sz[32];
    int year;
    byte month, day, hour, minute, second, hundredths;
    unsigned long age;
  
    do {
        gps.f_get_position(&flat, &flon);
        falt = gps.f_altitude();
        speed = gps.f_speed_kmph();
        satellites = gps.satellites();
        precision = gps.hdop();
        gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);

        if (flat != TinyGPS::GPS_INVALID_F_ANGLE
         && flon != TinyGPS::GPS_INVALID_F_ANGLE
         && age  != TinyGPS::GPS_INVALID_AGE
         //&& satellites != TinyGPS::GPS_INVALID_SATELLITES
         //&& precision  != TinyGPS::GPS_INVALID_HDOP
         && flat != TinyGPS::GPS_INVALID_F_ALTITUDE
         && speed != TinyGPS::GPS_INVALID_F_SPEED
         )
        {
            sprintf(sz, "%02d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);

            GpsCoordinate coordinate(flat, flon, satellites, precision, falt, speed, sz);
            again = false;
        } else {
            unsigned long start = millis();
            do 
            {
                while (ss.available())
                gps << ss.read();
            } while (millis() - start < 1000);
        }
    } while(again);

    return coordinate;
}

