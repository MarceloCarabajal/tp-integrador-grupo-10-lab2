#include "Appointment.h"

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

void Appointment::setDate(Date date) { _date = date; }

void Appointment::setTime(Time time) { _time = time; }

void Appointment::setUrgencyCat(int cat) { _urgencyCat = cat; }

void Appointment::setReason(std::string reason) { _reason = reason; }

void Appointment::setAttended(bool attended) { _attended = attended; }

int Appointment::getAppId() { return _appId; }
int Appointment::getpetId() { return _petId; }
Date Appointment::getDate() { return _date; }
Time Appointment::getTime() { return _time; }
int Appointment::getUrgencyCat() { return _urgencyCat; }
std::string Appointment::getReason() { return _reason; }
bool Appointment::getAttended() { return _attended; }

void Appointment::load() {









}