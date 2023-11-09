#include "Person.h"

#include <cstring>
#include <iostream>

using namespace std;

// CONSTRUCTOR ????

void Person::setIdPerson(int personId) { _personId = personId; }
void Person::setName(const char *name) { strcpy(_name, name); }
void Person::setLastname(const char *lastname) { strcpy(_lastname, lastname); }

int Person::getIdPerson() { return _personId; }
const char *Person::getName() { return _name; }
const char *Person::getLastname() { return _lastname; }

/* void Person::load() {
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
} */