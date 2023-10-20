#pragma once

class Date{
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
};