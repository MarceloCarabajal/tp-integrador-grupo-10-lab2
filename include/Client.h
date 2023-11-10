#pragma once

#include <string>

#include "Person.h"


class Client : public Person {
private:
    int _clientId;
    char _address[45], _phone[15], _email[45];

public:
    // Client(); //TODO: Constructor
    void setClientId(int clienteId);
    void setAddress(std::string address);
    void setPhone(std::string phone);
    void setEmail(std::string email);

    int getClientId();
    const char *getAddress();
    const char *getPhone();
    const char *getEmail();
    // void load();  // TODO: Creo que el metodo cargar deberia ir en una clase
    //  tipo "clientManager"
};