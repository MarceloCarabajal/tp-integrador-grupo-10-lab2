#include "Person.h"

#include <cstring>
#include <iostream>

Person::Person() {
    _personId = 0;
    strcpy(_name, "");
    strcpy(_lastname, "");
}

Person::Person(int id, std::string name, std::string lastname) {
    _personId = id;
    strcpy(_name, name.c_str());
    strcpy(_lastname, lastname.c_str());
}

void Person::setIdPerson(int personId) { _personId = personId; }
void Person::setName(std::string name) { strcpy(_name, name.c_str()); }
void Person::setLastname(std::string lastname) { strcpy(_lastname, lastname.c_str());
}

int Person::getIdPerson() { return _personId; }
const char *Person::getName() { return _name; }
const char *Person::getLastname() { return _lastname; }
