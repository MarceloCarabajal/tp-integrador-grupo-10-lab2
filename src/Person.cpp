#include "Person.h"

#include <cstring>
#include <iostream>

using namespace std;

// CONSTRUCTOR ????

void Person::setIdPerson(int personId) { _personId = personId; }
void Person::setName(std::string name) { strcpy(_name, name.c_str()); }
void Person::setLastname(std::string lastname) {
    strcpy(_lastname, lastname.c_str());
}

int Person::getIdPerson() { return _personId; }
const char *Person::getName() { return _name; }
const char *Person::getLastname() { return _lastname; }
