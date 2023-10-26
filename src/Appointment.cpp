#include "Appointment.h"


void Appointment::setAppId( int id){_appId=id;}
void Appointment::setUrgencyCat (int urg){ _urgencyCat=urg;}
void Appointment::setpetId (int idpet){_petId=idpet;}
void Appointment::setDate( Date date){ _date=date; }
void Appointment::setTime( Time time){_time=time;}
void Appointment::setUrgencyCat( int cat){_urgencyCat=cat; }
void Appointment::setReason( std::string reason){ _reason=reason;}
void Appointment::setAttended( bool attended){_attended=attended; }

int Appointment::getAppId(){return _appId; }
int  Appointment::getUrgencyCat (){ return _urgencyCat;}
int  Appointment::getpetId (){return _petId;}
Date Appointment::getDate(){return _date;}
Time Appointment::getTime(){return _time; }
int Appointment::getUrgencyCat(){return _urgencyCat; }
std::string Appointment::getReason(){return _reason; }
bool Appointment::getAttended(){return _attended; }
 
void Appointment::load(){



}