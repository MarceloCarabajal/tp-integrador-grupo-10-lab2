#pragma once
#include <string>
#include "Date.h"



class Vaccination {
    
private:

int _aplicationId,_petId;
Date _dateAplication, _dateRevaccination;
char _nameVaccine[15];
bool _notified;


public: 


Vaccination();

Vaccination(int petId, int aplicationId, std::string nameVaccine, Date dateAplication, Date  dateRevaccination, bool notified);


void setAplicationId (int apli);
void setPetId (int Idp);
void setDateAplication (Date Apli);
void setDateRevaccination (Date Revacci);
void setNameVaccine (std::string name );
void setNotified (bool noti);


int getAplicationId();
int getPeId();
Date  getDateAplication();
Date  getDateRevaccination();
const char * getNameVaccine();
bool  getNottified();


void toVecString(std::string vStr[6]);
};

