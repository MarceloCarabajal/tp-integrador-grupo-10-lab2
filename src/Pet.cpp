#include<iostream>
#include "Pet.h"
#include <cstring>
using namespace std;

Pet::Pet (){

_petId=-1;
_ownerId=-1;
strcpy (_name, "");
strcpy (_specie, "");
strcpy (_breed, "");
strcpy (_currentDiagnosis, "");
_birthDate= Date(1,1,1990); 
_status=false;

}

Pet::Pet (int petId, int ownerId, std::string name, std::string specie,
           std::string breed, std::string currentDiagnosis, Date birthDate, bool status){

_petId=petId;
_ownerId=ownerId;
strcpy(_name,name.c_str());
strcpy (_specie,specie.c_str());
strcpy (_breed,breed.c_str());
strcpy (_currentDiagnosis,currentDiagnosis.c_str());
_birthDate=birthDate;
_status=status;


}

void Pet::setPetId(int petId){_petId=petId;}
void Pet::setOwnerId(int ownerId){_ownerId=ownerId;}
void Pet::setName(std::string name){strcpy(_name,name.c_str());  }
void Pet::setSpecie(std::string specie){strcpy(_specie,specie.c_str());   }
void Pet::setBreed(std::string breed) {strcpy(_breed,breed.c_str());}
void Pet::setCurrentDiagnosis(std::string currentDiagnosis){strcpy(_currentDiagnosis,currentDiagnosis.c_str());}
void Pet::setBirthDate(Date birthdate){_birthDate=birthdate;}
void Pet::setStatus(bool status) { _status = status; }



int Pet::getPetId(){return _petId;}
int Pet::getOwnerId(){return _ownerId; }
const char* Pet::getName(){return _name;}
const char* Pet::getSpecie(){return _specie;}
const char* Pet::getBreed(){return _breed;}
const char* Pet::getCurrentDiagnosis(){return _currentDiagnosis;}
Date Pet::getBirthDate(){return _birthDate;}
bool Pet::getStatus() { return _status; }


void Pet::addAppoinment(){}
    
void Pet::toVecString(std::string vStr[7]) {
    vStr[0] = std::to_string(_petId);
    vStr[1] = std::to_string(_ownerId);
    vStr[2] = _name;
    vStr[3] = _specie;
    vStr[4] = _breed;
    vStr[5] = _currentDiagnosis;
    vStr[6] = _birthDate.toString();

    
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