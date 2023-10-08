#pragma once
#include<string>

class Person{
    private:
        int _personId;
        std::string _name, _lastname, _address, _phone, _email;
    public:
        Person();
        void setName(std::string name);
        void setLastname(std::string lastname);
        void setAddress(std::string address);
        void setPhone(std::string phone);
        void setEmail(std::string email);
        std::string getName();
        std::string getLastname();
        std::string getAddress();
        std::string getPhone();
        std::string getEmail();
        std::string loadPerson();
};