#include<iostream>
#include "Pet.h"
using namespace std;

//TODO:  CONSTRUCTOR ?

void Pet::setPetId(int petId){_petId=petId;}
void Pet::setOwnerId(int ownerId){_ownerId=ownerId;}
void Pet::setName(std::string name){_name=name;  }
void Pet::setSpecie(std::string specie){_specie=specie;   }
void Pet::setBreed(std::string breed) {_breed=breed;}
void Pet::setCurrentDiagnosis(std::string currentDiagnosis){_currentDiagnosis=currentDiagnosis;}
void Pet::setBirthDate(Date birthdate){_birthDate=birthdate;}

int Pet::getPetId(){return _petId;}
int Pet::getOwnerId(){return _ownerId; }
std::string Pet::getName(){return _name;}
std::string Pet::getSpecie(){return _specie;}
std::string Pet::getBreed(){return _breed;}
std::string Pet::getCurrentDiagnosis(){return _currentDiagnosis;}
Date Pet::getBirthDate(){return _birthDate;}

void Pet::addAppoinment(){
    
}
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
    
}