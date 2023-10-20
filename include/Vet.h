#pragma once
#include <string>

class Vet {
private: 
 int _vetId;
 std:: string _speciality;

public: 
 void setIdVet( int idVet);
 void setSpeciality( std:: string speciality); 

 int  getIdVet();
std:: string getSpeciality();

 void queryHistory();
 void assignTreatment();
 void issueDiagnosis();
 void load();

};