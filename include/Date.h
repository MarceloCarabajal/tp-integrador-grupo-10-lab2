#pragma once

#include <iostream>

class Date {
private:
    int _day, _month, _year;

public:
    Date();

    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);
    int getDay();
    int getMonth();
    int getYear();

    std::string toString();
};