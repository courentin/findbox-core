#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate
{
    public:
        double latitude, longitude;
	    Coordinate(double latitude, double longitude);
        /**
         * This method return the distance in km
         * between this and the argument.
         **/
        double getDistance(const Coordinate*);
};

#endif