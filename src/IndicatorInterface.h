#ifndef INDICATOR_INTERFACE_H
#define INDICATOR_INTERFACE_H

#include "Arduino.h"

class IndicatorInterface
{
	public:
		virtual void showDistance(double) = 0;
		virtual void hideDistance() = 0;
		virtual void showError(String error = "") = 0;
		virtual void hideError() = 0;
		virtual void showWait() = 0;
		virtual void hideWait() = 0;
};

#endif