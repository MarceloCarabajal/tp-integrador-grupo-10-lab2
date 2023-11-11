#pragma once

#include <string>

#include "Person.h"

class Client : public Person {
private:
    int _clientId;
    char _address[45], _phone[15], _email[45];

public:
    Client();
    Client(int clientId, int personId, std::string name, std::string lastname,
           std::string address, std::string phone, std::string email);
    void setClientId(int clienteId);
    void setAddress(std::string address);
    void setPhone(std::string phone);
    void setEmail(std::string email);

    int getClientId();
    const char *getAddress();
    const char *getPhone();
    const char *getEmail();
};