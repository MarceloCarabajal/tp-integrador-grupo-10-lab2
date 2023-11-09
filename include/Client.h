#pragma once

#include "Person.h"

class Client : public Person {
private:
    int _clientId;
    char _address[45], _phone[15], _email[45];

public:
    // Client(); //TODO: Constructor
    void setClientId(int clienteId);
    void setAddress(const char *address);
    void setPhone(const char *phone);
    void setEmail(const char *email);

    int getClientId();
    const char *getAddress();
    const char *getPhone();
    const char *getEmail();
    // void load();  // TODO: Creo que el metodo cargar deberia ir en una clase
    //  tipo "clientManager"
};