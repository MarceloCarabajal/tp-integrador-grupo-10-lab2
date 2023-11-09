#include "Vet.h"

#include <iostream>

using namespace std;

void Vet::setIdVet(int vetId) { _vetId = vetId; }
void Vet::setSpeciality(std::string speciality) { _speciality = speciality; }

int Vet::getIdVet() { return _vetId; }
std::string Vet::getSpeciality() { return _speciality; }

// TODO Completar metodos
void Vet::queryHistory() {}
void Vet::assignTreatment() {}
void Vet::issueDiagnosis() {}
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