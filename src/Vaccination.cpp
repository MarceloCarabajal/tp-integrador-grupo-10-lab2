#include "Vaccination.h"

#include <cstring>
#include <iostream>

#include "utils.h"

using namespace std;

Vaccination::Vaccination() {
    _petId = -1;
    _aplicationId = -1;
    strcpy(_nameVaccine, "");
    _dateAplication = Date(1, 1, 1990);
    _dateRevaccination = Date(1, 1, 1990);
    _status = false;
}

Vaccination::Vaccination(int petId, int aplicationId, std::string nameVaccine,
                         Date dateAplication, Date dateRevaccination,
                         bool notified, bool status) {
    _petId = petId;
    _aplicationId = aplicationId;
    strcpy(_nameVaccine, nameVaccine.c_str());
    _dateAplication = dateAplication;
    _dateRevaccination = dateAplication;
    _status = status;
}

void Vaccination::setAplicationId(int apli) { _aplicationId = apli; }
void Vaccination::setPetId(int Idp) { _petId = Idp; }
void Vaccination::setDateAplication(Date Apli) { _dateAplication = Apli; }
void Vaccination::setDateRevaccination(Date Revacci) {
    _dateRevaccination = Revacci;
}
void Vaccination::setNameVaccine(std::string name) {
    strcpy(_nameVaccine, name.c_str());
}
void Vaccination::setNotified(bool noti) { _notified = noti; }
void Vaccination::setStatus(bool status) { _status = status; }

int Vaccination::getAplicationId() { return _aplicationId; }
int Vaccination::getPeId() { return _petId; }
Date Vaccination::getDateAplication() { return _dateAplication; }
Date Vaccination::getDateRevaccination() { return _dateRevaccination; }
const char* Vaccination::getNameVaccine() { return _nameVaccine; }
bool Vaccination::getNotified() { return _notified; }
bool Vaccination::getStatus() { return _status; }

void Vaccination::toVecString(std::string vStr[6]) {
    vStr[0] = std::to_string(_aplicationId);
    vStr[1] = std::to_string(_petId);
    vStr[2] = _nameVaccine;
    vStr[3] = _dateAplication.toString();
    vStr[4] = _dateRevaccination.toString();
    vStr[5] = utils::boolToStr(_notified);
}