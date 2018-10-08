#include "Arduino.h"
#include "Memory.h"

void setup()
{
  Serial.begin(9600);
  Memory m;
/*
  bool discovered = m.isDiscovered();
  Serial.print("Discovered : ");
  Serial.println(discovered);
  m.setDiscovered(!discovered);

  bool has = m.hasSecretCoordinate();
  Serial.print("Has : ");
  Serial.println(has);
  m.setHasSecretCoordinate(!has);
  m.setSecretCoordinate(UnaccurateCoordinate(49.418399, 2.824809, 10));
  */
  //m.clearCoordinates();

  unsigned int nb = m.getNbDiscovered();
  Serial.print("Nb : ");
  Serial.println(nb);

  UnaccurateCoordinate d = m.getSecretCoordinate();
  Serial.println(d.getLatitude(), 6);
  Serial.println(d.getLongitude(), 6);

  if (nb == 0) {
    GpsCoordinate c(49.418393, 2.824810, 7, 100, 0, 0, DateTime(2016, 12, 12, 3, 4, 1));
    m.addCoordinate(c);
    GpsCoordinate c1(49.418391, 2.824808, 6, 99, 0, 0, DateTime(2015, 11, 9, 2, 1, 5));
    m.addCoordinate(c1);
  } else {
    GpsCoordinate* co = m.getDiscoveries();
    Serial.print("Nb of disc : ");
    Serial.println(nb);

    for (unsigned int i = 0; i < nb; i++) {
      Serial.print("nb[");
      Serial.print(i);
      Serial.print("] : ");
      Serial.println(co[i].getLatitude(), 6);
      Serial.println(co[i].getLongitude(), 6);
      Serial.println(co[i].getDate().toString());
    }

/*
    for (Memory::iterator i = m.begin(); i != m.end(); i++) {
      Serial.print("EL : ");
      const GpsCoordinate& c = *i;
      Serial.println(c.getLatitude());
    }
*/
  }
}

void loop()
{

}
