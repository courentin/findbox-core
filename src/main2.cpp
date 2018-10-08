#include <Gps.h>
#include <FakeGps.h>
#include <Coordinate.h>
#include <UnaccurateCoordinate.h>

/*
   This sample code demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 3, TXPin = 4;
UnaccurateCoordinate secret(49.418392, 2.824809, 10);

// The serial connection to the GPS device
GpsInterface* gps = new Gps(RXPin, TXPin);
//GpsInterface* gps = new FakeGps(49.417691, 2.825509);

int ledOrange = 5;
int ledVerte  = 6;
int ledRouge  = 7;
int pushButton = 8;
/*
void setup()
{
  pinMode(ledOrange, OUTPUT);
  pinMode(ledVerte, OUTPUT);
  pinMode(ledRouge, OUTPUT);
  pinMode(pushButton, INPUT);

  Serial.begin(115200);
}

int pushed;

void loop()
{
    digitalWrite(ledOrange, HIGH);
    digitalWrite(ledVerte, HIGH);
    digitalWrite(ledRouge, HIGH);
    do {
      pushed = digitalRead(pushButton);
      if(pushed == HIGH) {
        pushed = 0;
      } else {
        pushed = 1;
      }
    } while(!pushed);

    digitalWrite(ledOrange, LOW);
    GpsCoordinate current = gps->getPosition();

    Serial.print(current.getLatitude(), 6);
    Serial.print(", ");
    Serial.println(current.getLongitude(), 6);

    double dist = current.getDistance(secret);
    digitalWrite(ledOrange, HIGH);
    if (dist < 100) {
      Serial.println("Succes ! Your at the secret position !");
      digitalWrite(ledVerte, LOW);
    } else {
      Serial.print("Fail ! You'r ");
      Serial.print(dist/1000);
      Serial.println("km far from the secret position !");
      digitalWrite(ledRouge, LOW);
    }

    delay(3000);
}
*/
