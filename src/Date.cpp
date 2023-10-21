#include "Date.h"

#include <iostream>


Date::Date() {
    _day = 1;
    _month = 1;
    _year = 2000;
}

void Date::setDay(int day) {
    if (day >= 1 && day <= 31) {
        _day = day;
    } else {
        std::cout << "Valor inválido" << std::endl;
    }
}

void Date::setMonth(int month) {
    if (month >= 1 && month <= 12) {
        _month = month;
    } else {
        std::cout << "Valor inválido" << std::endl;
    }
}

void Date::setYear(int year) { _year = year; }

int Date::getDay() { return _day; }

int Date::getMonth() { return _month; }

int Date::getYear() { return _year; }
