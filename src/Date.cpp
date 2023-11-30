#include "Date.h"

#include <ctime>
#include <iostream>
#include <string>

Date::Date() {
    time_t rawTime =
        time(NULL);  // obtiene la fecha/hora actual en formato raw (segundos)
    struct tm* timeVars =
        localtime(&rawTime);  // da formato local y asigna a timeVars
    _day = timeVars->tm_mday;
    _month = timeVars->tm_mon + 1;     // +1 porque los meses van de 0 a 11
    _year = timeVars->tm_year + 1900;  // +1900 porque los años van desde 1900
}

// Crear estructura tm con los datos de fecha
struct tm Date::makeTm(const Date& d) {
    std::tm tm = {0};
    tm.tm_year = d._year - 1900;  // años desde 1900
    tm.tm_mon = d._month - 1;     // meses desde enero (0 a 11)
    tm.tm_mday = d._day;          // dias
    return tm;
}

// Obtener diferencia en dias entre dos fechas
int Date::operator-(const Date& d) {
    struct tm thisTM = makeTm(*this);
    struct tm dTM = makeTm(d);
    time_t thisTime = std::mktime(&thisTM);
    time_t dTime = std::mktime(&dTM);
    double seconds = difftime(thisTime, dTime);
    int daySeconds = 60 * 60 * 24;
    return seconds / daySeconds;
}

Date::Date(int day, int month, int year) {
    setDay(day);
    setMonth(month);
    setYear(year);
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

bool Date::operator<(const Date& d) {
    if (_year < d._year) return true;
    if (_year > d._year) return false;
    if (_month < d._month) return true;
    if (_month > d._month) return false;
    if (_day < d._day) return true;
    return false;
}

bool Date::operator>(const Date& d) {
    // si es menor o igual, no es mayor
    return (*this < d || *this == d) ? false : true;
}

bool Date::operator==(const Date& d) {
    bool equal = _year == d._year && _month == d._month && _day == d._day;
    return equal;
}
