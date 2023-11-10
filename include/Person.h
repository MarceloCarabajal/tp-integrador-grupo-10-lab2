#pragma once
#include <string>
class Person {
private:
    int _personId;
    char _name[30], _lastname[30];

public:
    // Person(); //TODO: Constructor
    void setIdPerson(int id);
    void setName(std::string name);
    void setLastname(std::string lastname);

    int getIdPerson();
    const char *getName();
    const char *getLastname();
    // void load(); //TODO: Eliminar
};