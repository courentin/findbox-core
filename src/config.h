#define BOARD_BENOIT 1
#define BOARD_CORENTIN 2

#include <Arduino.h>
#include "findbox_types.h"

static const uint32_t GPSBaud = 9600;
static const int discoveringRadiusInMeters = 50;
static const int gpsTimeoutInSeconds = 10 * 60;

#define RX_PIN PB11
#define TX_PIN PB10

#ifndef BOARD_CONFIG
#error The macro BOARD_CONFIG must be defined in platformio.ini
#endif

#if BOARD_CONFIG == BOARD_BENOIT
    #define LOCKER_PIN PA5
    #define I2C_PULL_UP_PIN PA2
    Coordinates secretLocation = {48.858075, 2.348579};
#elif BOARD_CONFIG == BOARD_CORENTIN
    #define LOCKER_PIN PA3
    Coordinates secretLocation = {48.8907321, 2.3422532};
#else
#error The value of BOARD_CONFIG is not recognized
#endif
