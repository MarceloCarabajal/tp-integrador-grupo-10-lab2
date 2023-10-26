#pragma once

#include "Person.h"

class Client :  Person {
private:   
    int _clientId;
    std::string _address, _phone, _email;

public:
    Client();
    void setClientId(int clienteId );
    void setAddress(std::string address);
    void setPhone(std::string phone);
    void setEmail(std::string email);

    int getClientId ();
    std::string getAddress();
    std::string getPhone();
    std::string getEmail();
    void load();  // TODO: Creo que el metodo cargar deberia ir en una clase
                  // tipo "clientManager"
};