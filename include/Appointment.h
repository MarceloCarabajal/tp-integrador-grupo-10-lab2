#pragma once
#include <string>
#include "Date.h"
#include "TimeCls.h"

class Appointment {
private:
    int _appId,  _petId;
   // int _urgencyCat;
    Date _dateApp;
    Time _timeApp;

    char _reason[30];
    bool _attended;
    int _clientId;

public:


    void setAppId(int id);
    void setpetId(int idpet);
    void setDate(Date date);
    void setTime(Time time);
  //  void setUrgencyCat(int cat);
    void setReason(std::string reason);
    void setAttended(bool attended);
    void setClientId (int idc);

    int getAppId();
   // int getUrgencyCat();
    int getpetId();
    Date getDate();
    Time getTime();
    const char* getReason();
    bool getAttended();
    int getClientId ();

    void load();


    void toVecString(std::string vStr[7]);


};
