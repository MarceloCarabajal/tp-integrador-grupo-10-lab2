#pragma once

class Time{
private:
    int _hour, _min, _sec;
public:
    Time();
    void setHour(int hour);
    void setMin(int min);
    void setSec(int sec);
};