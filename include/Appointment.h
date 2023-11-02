#pragma once
#include <string>

#include "Date.h"
#include "TimeCls.h"

class Appointment {
private:
    int _appId, _urgencyCat, _petId;
    Date _dateApp;
    Time _timeApp;

    std::string _reason;
    bool _attended;
    int _clientId;

public:
    void setAppId(int id);
    void setpetId(int idpet);
    void setDate(Date date);
    void setTime(Time time);
    void setUrgencyCat(int cat);
    void setReason(std::string reason);
    void setAttended(bool attended);

    int getAppId();
    int getUrgencyCat();
    int getpetId();
    Date getDate();
    Time getTime();
    std::string getReason();
    bool getAttended();

    void load();
};
