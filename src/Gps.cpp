#include "Gps.h"
#include "Arduino.h"
#include <SoftwareSerial.h>

Gps::Gps(uint8_t rx, uint8_t tx) : ss(rx, tx) {
	ss.begin(9600);
}

GpsCoordinate* Gps::getPosition()
{
    GpsCoordinate *coordinate;

    bool again = true;
    float flat, flon, falt, speed, satellites, precision;
    do {
        gps.f_get_position(&flat, &flon);
        falt = gps.f_altitude();
        speed = gps.f_speed_kmph();
        satellites = gps.satellites();
        precision = gps.hdop();

        if (flat != TinyGPS::GPS_INVALID_F_ANGLE
         && flon != TinyGPS::GPS_INVALID_F_ANGLE
         //&& satellites != TinyGPS::GPS_INVALID_SATELLITES
         //&& precision  != TinyGPS::GPS_INVALID_HDOP
         && flat != TinyGPS::GPS_INVALID_F_ALTITUDE
         && speed != TinyGPS::GPS_INVALID_F_SPEED
         )
        {
            coordinate = new GpsCoordinate(flat, flon, satellites, precision, falt, speed, 1);
            again = false;
        } else {
            unsigned long start = millis();
            do 
            {
                while (ss.available())
                gps.encode(ss.read());
            } while (millis() - start < 1000);
        }
    } while(again);

    return coordinate;
}

