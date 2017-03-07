#ifndef CONSOLE_INDICATOR_H
#define CONSOLE_INDICATOR_H

#include "IndicatorInterface.h"
#include "Arduino.h"

class ConsoleIndicator : public IndicatorInterface
{
    public:
        ConsoleIndicator(int baudrate);

        void showDistance(double);
		void hideDistance();
		void showError(String error = "");
		void hideError();
		void showWait();
		void hideWait();
};

#endif