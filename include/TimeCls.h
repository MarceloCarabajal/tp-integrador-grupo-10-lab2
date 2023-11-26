#pragma once
#include <string>

class Time {
private:
    int _hour, _min, _sec;

public:
    Time();
    Time(int hour, int min, int sec);

    void setHour(int hour);
    void setMin(int min);
    void setSec(int sec);
    int getHour() const;  // Método constante para obtener la hora
    int getMin() const;   // Método constante para obtener los minutos
    int getSec() const;   // Método constante para obtener los segundos

    std::string toString();
    bool operator==(const Time& t);
};