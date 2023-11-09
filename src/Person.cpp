#include "Person.h"

#include <iostream>


using namespace std;

// CONSTRUCTOR ????

void Person::setIdPerson(int personId) { _personId = personId; }
void Person::setName(std::string name) { std::string _name = name; }
void Person::setLastname(std::string lastname) {
    std::string _lastname = lastname;
}

int Person::getIdPerson() { return _personId; }
const std::string Person::getName() { return _name; }
std::string Person::getLastname() { return _lastname; }

void Person::load() {
    int personId;
    std::string name, lastname;

    cout << "Ingrese ID de persona:";
    cin >> personId;
    setIdPerson(personId);

    cout << "Ingrese Nombre:";
    cin >> name;
    setName(name);

    cout << "Ingrese Apellido:";
    cin >> lastname;
    setLastname(lastname);
}