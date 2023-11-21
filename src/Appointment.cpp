#include "Appointment.h"

#include <cstring>
#include <iostream>

using namespace std;

Appointment::Appointment (){

_appId=-1;
_petId=-1;
strcpy (_reason, " ");
_attended="no";
_clientId=-1;
_dateApp= Date(1,1,1990); 
_timeApp=Time (00,00,00);

}

Appointment::Appointment(int appId, int petID, Date dateApp, Time timeApp, std::string reason,
 bool  attended, int clientId){

_petId=petID;
_appId=appId;
_clientId=clientId;
_attended=attended;
strcpy(_reason,reason.c_str());
_dateApp=dateApp;
_timeApp=timeApp;


}


/**
 * @brief
 * Esta función permite definir el ID de la consulta.
 * @param id ID a ser definido para a consulta.
 *  */

void Appointment::setAppId(int id) { _appId = id; }

/**
 * @brief
 * Esta función permite definir el ID de la mascota
 * @param idpet
 */
void Appointment::setpetId(int idpet) { _petId = idpet; }

void Appointment::setDate(Date date) { _dateApp = date; }

void Appointment::setTime(Time time) { _timeApp = time; }

// void Appointment::setUrgencyCat(int cat) { _urgencyCat = cat; }

void Appointment::setReason(std::string reason) {
    strcpy(_reason, reason.c_str());
}

void Appointment::setAttended(bool attended) { _attended = attended; }
void Appointment::setClientId(int idc) { _clientId = idc; }

int Appointment::getAppId() { return _appId; }
int Appointment::getpetId() { return _petId; }
Date Appointment::getDate() { return _dateApp; }
Time Appointment::getTime() { return _timeApp; }
// int Appointment::getUrgencyCat() { return _urgencyCat; }
const char *Appointment::getReason() { return _reason; }
bool Appointment::getAttended() { return _attended; }
int Appointment::getClientId() { return _clientId; }

void Appointment::toVecString(std::string vStr[7]) {
    vStr[0] = std::to_string(_appId);
    vStr[1] = std::to_string(_petId);
    vStr[2] = _dateApp.toString();
    vStr[3] = _timeApp.toString();
    vStr[4] = _reason;
    vStr[5] = _attended;
    vStr[6] = std::to_string(_clientId);
}

/*
void Appointment::load() {

int petId, appId, urgencyCat;
Date dateApp;
Time timeApp ;
int auxDia,auxMes,auxAnio,auxHour,auxMinutes;
std::string reason;
bool attended;

cout<<"Ingrese Id de la Mascota:";
cin>>petId;
setpetId(petId);


cout<<"Ingrese Id del turno ";
cin>>appId;
setAppId(appId);


cout<<"Ingrese Dia del turno:";
cin>>auxDia;
dateApp.setDay(auxDia);

cout <<"Ingrese Mes del turno:";
cin>>auxMes;
dateApp.setMonth(auxMes);

cout <<"Ingrese Anio del turno:";
cin>>auxAnio;
dateApp.setYear(auxAnio);


cout<<"Ingrese Hora del turno:";
cin>>auxHour;
timeApp.setHour(auxHour);

cout<<"Ingrese Minutos del turno:";
cin>>auxMinutes;
timeApp.setMin(auxMinutes);


cout<<"Ingrese Categoria del Turno ";
cin>>urgencyCat;
setUrgencyCat(urgencyCat);

cout<<"Ingrese Motivo del Turno ";
cin>>reason;
setReason(reason);

cout<<"Ingrese Estado del turno (Asistencia) ";
cin>>attended;
setAttended(attended);


}*/