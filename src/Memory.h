#ifndef MEMORY_H
#define MEMORY_H

#include "UnaccurateCoordinate.h"
#include "GpsCoordinate.h"

class Memory {
private:
  bool has_secret_coordinate;
  bool is_discovered;
  unsigned int nb_discovered;
  UnaccurateCoordinate secret_coordinate;
  GpsCoordinate* discoveries;
  bool initialized;

  unsigned int addr_initialized;
  unsigned int addr_has_secret_coordinate;
  unsigned int addr_secret_coordinate;
  unsigned int addr_is_discovered;
  unsigned int addr_nb_discovered;
  unsigned int addr_discoveries;

public:
  Memory();
  bool hasSecretCoordinate() const { return has_secret_coordinate; };
  void setHasSecretCoordinate(bool);
  const UnaccurateCoordinate& getSecretCoordinate() const { return secret_coordinate; };
  void setSecretCoordinate(const UnaccurateCoordinate&);
  bool isDiscovered() const { return is_discovered; };
  void setDiscovered(bool);
  unsigned int getNbDiscovered() const { return nb_discovered; };
  void setNbDiscovered(unsigned int);
  void addCoordinate(const GpsCoordinate&);
  void clearCoordinates();
  GpsCoordinate* getDiscoveries() { return discoveries; }
  void uninitialize();

  class iterator {
  private:
    unsigned int i;
    unsigned int nb;
    GpsCoordinate* tab;
  public:
    iterator(unsigned int nb = 0, GpsCoordinate* tab = nullptr, unsigned int i = 0) : i(i), nb(nb), tab(tab){}
    const GpsCoordinate& operator*() const { return tab[i]; }
    iterator& operator++() {
      Serial.println(i);
      i += 1;
      return *this;
    }
    bool operator==(iterator other) const {return i == other.i;}
    bool operator!=(iterator other) const {return !(*this == other);}
  };

  iterator begin() { return iterator(getNbDiscovered(), discoveries); }
  iterator end() { return iterator(getNbDiscovered(), discoveries, getNbDiscovered() -1); }
};

#endif
