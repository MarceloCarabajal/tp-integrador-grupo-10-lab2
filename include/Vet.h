#pragma once
#include "Person.h"

class Vet :  Person {
private: 
 int _vetId;
 char _speciality[15];

public: 
 void setIdVet( int idVet);
 void setSpeciality(const char* speciality); 

 int  getIdVet();
const char* getSpeciality();

 void queryHistory();
 void assignTreatment();
 void issueDiagnosis();
 
 void load( );

};