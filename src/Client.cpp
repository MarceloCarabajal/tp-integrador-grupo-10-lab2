#include "Client.h"

#include <cstring>
#include <iostream>

using namespace std;

Client::Client() : Person() {
    _clientId = -1;
    strcpy(_address, "");
    strcpy(_phone, "");
    strcpy(_email, "");
}

Client::Client(int clientId, int personId, std::string name,
               std::string lastname, std::string address, std::string phone,
               std::string email)
    : Person(personId, name, lastname) {
    _clientId = clientId;
    strcpy(_address, address.c_str());
    strcpy(_phone, phone.c_str());
    strcpy(_email, email.c_str());
}

void Client::setClientId(int clienteId) { _clientId = clienteId; }
void Client::setAddress(std::string address) {
    strcpy(_address, address.c_str());
}
void Client::setPhone(std::string phone) { strcpy(_phone, phone.c_str()); }
void Client::setEmail(std::string email) { strcpy(_email, email.c_str()); }

int Client::getClientId() { return _clientId; }
const char *Client::getAddress() { return _address; }
const char *Client::getPhone() { return _phone; }
const char *Client::getEmail() { return _email; }
