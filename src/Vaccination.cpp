#include <cstring>
#include <iostream>
#include "Vaccination.h"

using namespace std;

Vaccination::Vaccination(){

_petId=-1;
_aplicationId=-1;
strcpy (_nameVaccine, "");
_dateAplication= Date(1,1,1990); 
_dateRevaccination=Date (1,1,1990); 
}

Vaccination::Vaccination(int petId, int aplicationId, std::string nameVaccine, Date dateAplication, Date  dateRevaccination, bool notified){

_petId=petId;
_aplicationId=aplicationId;
strcpy(_nameVaccine,nameVaccine.c_str());
_dateAplication=dateAplication;
_dateRevaccination=dateAplication;
}


void Vaccination::setAplicationId (int apli){_aplicationId=apli;}
void Vaccination::setPetId (int Idp){_petId=Idp;  }
void Vaccination::setDateAplication (Date Apli){_dateAplication=Apli; }
void Vaccination::setDateRevaccination (Date Revacci){_dateRevaccination=Revacci;}
void Vaccination::setNameVaccine (std::string name ){strcpy(_nameVaccine,name.c_str());}
void Vaccination::setNotified (bool noti){_notified=noti;}


int Vaccination::getAplicationId(){return  _aplicationId;}
int Vaccination::getPeId(){return _petId;}
Date  Vaccination::getDateAplication(){return _dateAplication;}
Date  Vaccination::getDateRevaccination(){return _dateRevaccination;}
const char * Vaccination::getNameVaccine(){return _nameVaccine;}
bool  Vaccination::getNottified(){return _notified;}


    
void Vaccination::toVecString(std::string vStr[6]) {
    vStr[0] = std::to_string(_aplicationId);
    vStr[1] = std::to_string(_petId);
    vStr[2] = _nameVaccine;
    vStr[3] = _dateAplication.toString();
    vStr[4] = _dateRevaccination.toString();
    if (_notified!= 'no'&& _notified!= 'NO' && _notified != 'No'){
    vStr[5] = "si"; }else {vStr[5] = "no"; }


    
}