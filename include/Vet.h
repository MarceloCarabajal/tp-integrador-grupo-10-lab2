#pragma once
#include <string>
#include "Person.h"

class Vet :  Person {
private: 
 int _vetId;
 char _speciality[15];

public: 
 void setIdVet( int idVet);
 void setSpeciality(std::string speciality); 

 int  getIdVet();
const char* getSpeciality();

 void queryHistory();
 void assignTreatment();
 void issueDiagnosis();
 
 void load( );

};