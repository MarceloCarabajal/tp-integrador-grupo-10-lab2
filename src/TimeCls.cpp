#include "TimeCls.h"

#include <ctime>

// #include <iostream>
#include <string>

Time::Time() {
    time_t rawTime;
    struct tm* timeVars;
    time(&rawTime);                  // obtiene la hora actual
    timeVars = localtime(&rawTime);  // da formato
    _hour = timeVars->tm_hour;
    _min = timeVars->tm_min;
    _sec = timeVars->tm_sec;
}

Time::Time(int hour, int min, int sec) {
    setHour(hour);
    setMin(min);
    setSec(sec);
}

void Time::setHour(int hour) { _hour = hour; }

void Time::setMin(int min) { _min = min; }

void Time::setSec(int sec) { _sec = sec; }

int Time::getHour() const { return _hour; }

int Time::getMin() const { return _min; }

int Time::getSec() const { return _sec; }

std::string Time::toString() {
    std::string hour = std::to_string(_hour);
    std::string min = std::to_string(_min);
    std::string sec = std::to_string(_sec);
    if (_hour < 10) hour = "0" + hour;
    if (_min < 10) min = "0" + min;
    if (_sec < 10) sec = "0" + sec;
    return hour + ":" + min + ":" + sec;
}

bool Time::operator==(const Time& t) {
    bool equal =
        _hour == t.getHour() && _min == t.getMin() && _sec == t.getSec();
    return equal;
}