#pragma once
#include <string>
#include "Date.h"
#include "TimeCls.h"


class Appointment {

private: 
 int _appId, _urgencyCat, _petId;
 Date _date;
 Time _time;
 
 std:: string _reason; 
 bool _attended;
 int _clientId;
 

 public: 
 void setAppId( int id);
 void setUrgencyCat (int urg);
 void setpetId (int idpet);
 void setDate( Date date);
 void setTime( Time time);
 void setUrgencyCat( int cat);
 void setReason( std::string reason);
 void setAttended( bool attended);

 int getAppId();
 int getUrgencyCat ();
 int getpetId ();
 Date getDate();
 Time getTime();
 int getUrgencyCat();
 std::string getReason();
 bool getAttended();
 
void load();
};
