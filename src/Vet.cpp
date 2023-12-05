#include "Vet.h"

#include <cstring>
#include <iostream>

using namespace std;

Vet::Vet() : Person() {
    _vetId = -1;
    strcpy(_speciality, " ");
    _status = false;
}
Vet::Vet(int vetId, std::string speciality, int personId, std::string name,
         std::string lastname, bool status)
    : Person(personId, name, lastname) {
    _vetId = vetId;
    strcpy(_speciality, speciality.c_str());
    _status = status;
}

void Vet::setIdVet(int vetId) { _vetId = vetId; }
void Vet::setSpeciality(std::string speciality) {
    strcpy(_speciality, speciality.c_str());
}
void Vet::setStatus(bool status) { _status = status; }

int Vet::getIdVet() { return _vetId; }
const char* Vet::getSpeciality() { return _speciality; }
bool Vet::getStatus() { return _status; }

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