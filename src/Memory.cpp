#include "Memory.h"
#include "EEPROM.h"

Memory::Memory() :
  discoveries(nullptr)
{
  unsigned int current = 0;
  addr_initialized = current;
  current += sizeof(byte);
  addr_has_secret_coordinate = current;
  current += sizeof(bool);
  addr_is_discovered = current;
  current += sizeof(bool);
  addr_secret_coordinate = current;
  current += sizeof(UnaccurateCoordinate);
  addr_nb_discovered = current;
  current += sizeof(unsigned int);
  addr_discoveries = current;

  initialized = EEPROM[addr_initialized] == 21;

  if (!initialized) {
    setDiscovered(false);
    setHasSecretCoordinate(false);
    setNbDiscovered(0);
    setDiscovered(false);
    EEPROM[addr_initialized] = 21;
    initialized = true;
  }

  nb_discovered = EEPROM[addr_nb_discovered];
  has_secret_coordinate = EEPROM[addr_has_secret_coordinate];
  is_discovered = EEPROM[addr_is_discovered];
  EEPROM.get(addr_secret_coordinate, secret_coordinate);

  if (nb_discovered != 0) {
    // Load discoveries if any
    discoveries = new GpsCoordinate[getNbDiscovered()];
    Serial.println("Addr discoveries :");
    Serial.println(addr_discoveries);
    unsigned n = 0;
    for (unsigned int i = addr_discoveries; i <= addr_discoveries+getNbDiscovered()*sizeof(GpsCoordinate); i+=sizeof(GpsCoordinate)) {
      EEPROM.get(i, discoveries[n++]);
    }
  }
}

void Memory::setHasSecretCoordinate(bool hasSecretCoordinate)
{
  EEPROM[addr_has_secret_coordinate] = hasSecretCoordinate;
  has_secret_coordinate = hasSecretCoordinate;
}

void Memory::setDiscovered(bool isDiscovered)
{
  EEPROM[addr_is_discovered] = isDiscovered;
  is_discovered = isDiscovered;
}

void Memory::setSecretCoordinate(const UnaccurateCoordinate& c)
{
  EEPROM.put(addr_secret_coordinate, c);
  secret_coordinate = c;
}

void Memory::addCoordinate(const GpsCoordinate& c)
{
  // put to the next available slot (TODO: check for overflow here)
  EEPROM.put(addr_discoveries+getNbDiscovered()*sizeof(GpsCoordinate), c);
  setNbDiscovered(getNbDiscovered()+1);
  GpsCoordinate* newtab = new GpsCoordinate[getNbDiscovered()];

  // synchronize with class member
  for (unsigned int i = 0; i < getNbDiscovered()-1; i++)
    newtab[i] = discoveries[i];

  GpsCoordinate* old = discoveries;
  discoveries = newtab;
  delete old;
}

void Memory::setNbDiscovered(unsigned int nb)
{
  EEPROM[addr_nb_discovered] = nb;
  nb_discovered = nb;
}

void Memory::uninitialize()
{
  for (unsigned int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM[addr_initialized] = 121;
  initialized = false;
}

void Memory::clearCoordinates()
{
    setNbDiscovered(0);
}
