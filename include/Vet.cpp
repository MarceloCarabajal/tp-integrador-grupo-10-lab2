#include<iostream>
#include "Vet.h"
using namespace std;



void setIdVet( int vetId){ _vetId = vetId;}
void setSpeciality( std:: string speciality){ _speciality = speciality; }

int  getIdVet(){return _vetId;  }
std:: string getSpeciality(){ return _speciality; }

void queryHistory(){
    
}
void assignTreatment(){
    
}
void issueDiagnosis(){
    
}
void load(){

Person::load();

int vetId;
std:: string speciality;

    cout<<"Ingrese ID del veterinario:";
    cin>>vetId;
    setIdVet(vetId);

    cout<<"Ingrese Especialidad:";
    cin>>speciality;
    setSpeciality(speciality);

}