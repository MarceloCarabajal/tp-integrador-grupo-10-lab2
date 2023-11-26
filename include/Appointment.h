#pragma once
#include <string>

#include "Date.h"
#include "TimeCls.h"

class Appointment {
private:
    int _appId, _petId;
    // int _urgencyCat;
    Date _dateApp;
    Time _timeApp;

    char _reason[30];
    bool _attended;
    int _clientId;

    bool _status;

public:
    Appointment();

    Appointment(int appId, int petID, Date dateApp, Time timeApp,
                std::string reason, bool attended, int clientId, bool status);

    void setAppId(int id);
    void setPetId(int idpet);
    void setDate(Date date);
    void setTime(Time time);
    //  void setUrgencyCat(int cat);
    void setReason(std::string reason);
    void setAttended(bool attended);
    void setClientId(int idc);
    void setStatus(bool status);

    int getAppId();
    // int getUrgencyCat();
    int getpetId();
    Date getDate();
    Time getTime();
    const char* getReason();
    bool getAttended();
    int getClientId();
    bool getStatus();

    void toVecString(std::string vStr[7]);
};
