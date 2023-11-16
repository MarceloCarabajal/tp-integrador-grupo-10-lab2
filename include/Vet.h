#pragma once
#include <string>
#include "Person.h"

class Vet : public Person {
private: 
 int _vetId;
 char _speciality[15];

public: 
Vet();
Vet(int vetId,std::string speciality,  int personId, std::string name, std::string lastname);




 void setIdVet( int idVet);
 void setSpeciality(std::string speciality); 

 int  getIdVet();
const char* getSpeciality();

 void queryHistory();
 void assignTreatment();
 void issueDiagnosis();
 
 void load( );

 void toVecString(std::string vStr[5]);
};