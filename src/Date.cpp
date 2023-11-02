#include "Date.h"

#include <iostream>
#include <string>

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

std::string Date::toString() {
    std::string day = std::to_string(_day);
    std::string month = std::to_string(_month);
    std::string year = std::to_string(_year);
    if (_day < 10) day = "0" + day;
    if (_month < 10) month = "0" + month;
    return day + "/" + month + "/" + year;
}