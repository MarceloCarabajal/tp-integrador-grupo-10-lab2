#include <iostream>
#include <cstring>
#include "Vet.h"
using namespace std;

Vet::Vet() : Person (){
 _vetId = -1;
strcpy(_speciality, " ");
}
Vet::Vet(int vetId,std::string speciality,  int personId, std::string name, std::string lastname)
:Person(personId, name, lastname){
_vetId=vetId;
strcpy(_speciality, speciality.c_str() );
}
void Vet::setIdVet(int vetId) { _vetId = vetId; }
void Vet::setSpeciality(std::string speciality) { strcpy(_speciality , speciality.c_str()); }

int Vet::getIdVet() { return _vetId; }
const char* Vet::getSpeciality() { return _speciality; }

// TODO Completar metodos
void Vet::queryHistory() {}
void Vet::assignTreatment() {}
void Vet::issueDiagnosis() {}


void Vet::toVecString(std::string vStr[5]) {
    vStr[0] = std::to_string(_vetId);
    vStr[1] = Person::getName();
    vStr[2] = Person::getLastname();
    vStr[3] = std::to_string(Person::getIdPerson());
    vStr[4] = _speciality;

}



/* void Vet::load(){

Person::load();

int vetId;
std:: string speciality;

    cout<<"Ingrese ID del veterinario:";
    cin>>vetId;
    setIdVet(vetId);

    cout<<"Ingrese Especialidad:";
    cin>>speciality;
    setSpeciality(speciality);

} */