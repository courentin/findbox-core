#include <Gps.h>

/*
   This sample code demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 3, TXPin = 4;

// The serial connection to the GPS device
Gps gps(RXPin, TXPin);

void setup()
{
    Serial.begin(115200);
}


void loop()
{
    GpsCoordinate c = gps.getPosition();

    Serial.println(c.precision);
    Serial.println(c.latitude, 6);
    Serial.print(", ");
    Serial.print(c.longitude, 6);
}
