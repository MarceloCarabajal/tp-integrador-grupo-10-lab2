#include<iostream>
#include "Pet.h"
#include <cstring>
using namespace std;

//TODO:  CONSTRUCTOR ?

void Pet::setPetId(int petId){_petId=petId;}
void Pet::setOwnerId(int ownerId){_ownerId=ownerId;}
void Pet::setName(std::string name){strcpy(_name,name.c_str());  }
void Pet::setSpecie(std::string specie){strcpy(_specie,specie.c_str());   }
void Pet::setBreed(std::string breed) {strcpy(_breed,breed.c_str());}
void Pet::setCurrentDiagnosis(std::string currentDiagnosis){strcpy(_currentDiagnosis,currentDiagnosis.c_str());}
void Pet::setBirthDate(Date birthdate){_birthDate=birthdate;}

int Pet::getPetId(){return _petId;}
int Pet::getOwnerId(){return _ownerId; }
const char* Pet::getName(){return _name;}
const char* Pet::getSpecie(){return _specie;}
const char* Pet::getBreed(){return _breed;}
const char* Pet::getCurrentDiagnosis(){return _currentDiagnosis;}
Date Pet::getBirthDate(){return _birthDate;}

void Pet::addAppoinment(){}
    
void Pet::toVecString(std::string vStr[7]) {
    vStr[0] = std::to_string(_petId);
    vStr[1] = std::to_string(_ownerId);
    vStr[2] = _name;
    vStr[3] = _specie;
    vStr[4] = _breed;
    vStr[5] = _currentDiagnosis;
    vStr[6] = _birthDate;
}




/*
void Pet::loadPet(){

int petId, ownerId, auxDay, auxMonth, auxYear;
std::string name, specie, breed, currentDiagnosis; 
Date birthDate;


cout<<"Ingrese ID de la mascota:";
cin>>petId;
setPetId(petId);


cout<<"Ingrese ID del dueño:";
cin>>ownerId; 
setOwnerId(ownerId);

cout<<"Ingrese Nombre de la Mascota:";
cin>>name;
setName(name);

cout<<"Ingrese Especie:";
cin>>specie;
setSpecie(specie);

cout<<"Ingrese Raza:";
cin>>breed;
setBreed(breed);

cout<<"Ingrese diagnostico actual :";
cin>>currentDiagnosis; 
setCurrentDiagnosis(currentDiagnosis);


cout<<"Ingrese Dia  de nacimiento:";
cin>>auxDay;
birthDate.setDay(auxDay);

cout <<"Ingrese Mes  de nacimiento:";
cin>>auxMonth;
birthDate.setMonth(auxMonth);

cout <<"Ingrese Anio de naciiento:";
cin>>auxYear;
birthDate.setYear(auxYear);

    
}
void Pet::recordVaccination(){
    
}*/