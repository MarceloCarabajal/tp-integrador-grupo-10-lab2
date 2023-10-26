#pragma once
#include <string>


class Person {
private:
    int _personId;
    std::string _name, _lastname;

public:
    Person();
    void setIdPerson(int id);
    void setName(std::string name);
    void setLastname(std::string lastname);


    int getIdPerson ();
    std::string getName();
    std::string getLastname();
    void load();
};