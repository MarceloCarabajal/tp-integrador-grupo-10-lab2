#include<iostream>
#include "Person.h"

using namespace std;

//CONSTRUCTOR ????int _personId;
    int _personId;
    std::string _name, _lastname;

void setIdPerson(int personId){_personId= personId;}
void setName(std::string name){ std::string _name=name;}
void setLastname(std::string lastname){ std::string _lastname=lastname;}

std::string getName(){return _name;}
std::string getLastname(){ return  _lastname;}

void load(){
    int personId;
    std::string name, lastname;

    cout<<"Ingrese ID de persona:";
    cin>>personId;
    setIdPerson(personId);

    cout<<"Ingrese Nombre:";
    cin>>name;
    setName(name);

    cout <<"Ingrese Apellido:";
    cin>>lastname;
    setLastname(lastname);
    
}