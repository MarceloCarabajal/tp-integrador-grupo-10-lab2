#include<iostream>
#include "Appointment.h"
using namespace std;
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

void Appointment::setUrgencyCat(int cat) { _urgencyCat = cat; }

void Appointment::setReason(std::string reason) { _reason = reason; }

void Appointment::setAttended(bool attended) { _attended = attended; }

int Appointment::getAppId() { return _appId; }
int Appointment::getpetId() { return _petId; }
Date Appointment::getDate() { return _dateApp; }
Time Appointment::getTime() { return _timeApp; }
int Appointment::getUrgencyCat() { return _urgencyCat; }
std::string Appointment::getReason() { return _reason; }
bool Appointment::getAttended() { return _attended; }

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


}