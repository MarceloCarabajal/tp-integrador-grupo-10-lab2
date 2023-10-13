#pragma once
#include <string>

class Person {
private:
    int _personId;
    std::string _name, _lastname;

public:
    Person();
    void setName(std::string name);
    void setLastname(std::string lastname);

    std::string getName();
    std::string getLastname();
    void load();
};