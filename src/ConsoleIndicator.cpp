#include "ConsoleIndicator.h"
#include "Arduino.h"

ConsoleIndicator::ConsoleIndicator(int baudrate)
{
    Serial.begin(baudrate);
}

void ConsoleIndicator::showDistance(double distance)
{
    if (distance <= 0) {
      Serial.print(distance/1000);
      Serial.println(" km");
    } else {
      Serial.print(distance);
      Serial.println(" m");
    }
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
