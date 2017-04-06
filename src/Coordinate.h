#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate
{
private:
    double latitude, longitude;
public:
    Coordinate(double latitude, double longitude) : latitude(latitude), longitude(longitude) {}
    /**
     * This method return the distance in km
     * between this and the argument.
     **/
    double getDistance(const Coordinate*);
    double getLatitude() { return latitude; }
    double getLongitude() { return longitude; }
};

#endif
