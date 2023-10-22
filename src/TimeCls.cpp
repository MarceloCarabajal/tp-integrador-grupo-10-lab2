#include "TimeCls.h"

void Time::setHour(int hour) { _hour = hour; }

void Time::setMin(int min) { _min = min; }

void Time::setSec(int sec) { _sec = sec; }

int Time::getHour() const { return _hour; }

int Time::getMin() const { return _min; }

int Time::getSec() const { return _sec; }