#pragma once
#include <string>
#include "Person.h"

class Vet : public Person {
private: 
 int _vetId;
 char _speciality[15];
 bool _status;

public: 
Vet();
Vet(int vetId,std::string speciality,  int personId, std::string name, std::string lastname,bool status);




 void setIdVet( int idVet);
 void setSpeciality(std::string speciality); 
 void setStatus(bool status);

 int  getIdVet();
 const char* getSpeciality();
 bool getStatus();


 void queryHistory();
 void assignTreatment();
 void issueDiagnosis();
 
 void load( );

 void toVecString(std::string vStr[5]);
};