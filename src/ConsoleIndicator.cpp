#include "ConsoleIndicator.h"
#include "Arduino.h"

ConsoleIndicator::ConsoleIndicator(int baudrate)
{
    Serial.begin(baudrate);
}

void ConsoleIndicator::showDistance(double distance)
{
    Serial.print(distance);
    Serial.println(" km");
}

void ConsoleIndicator::hideDistance()
{
    Serial.println("HIDE DISTANCE ...");
}

void ConsoleIndicator::showError(String error)
{
    Serial.print("ERROR : ");
    Serial.println(error);
}

void ConsoleIndicator::hideError()
{
    Serial.println("HIDE ERROR");
}

void ConsoleIndicator::showWait()
{
    Serial.println("WAIT ...");
}

void ConsoleIndicator::hideWait()
{
    Serial.println("HIDE WAIT ...");
}
