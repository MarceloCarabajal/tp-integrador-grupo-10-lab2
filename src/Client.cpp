#include "Client.h"

#include <cstring>
#include <iostream>

using namespace std;

Client::Client() : Person() {
    _clientId = -1;
    strcpy(_address, "");
    strcpy(_phone, "");
    strcpy(_email, "");
    _status = false;
}

Client::Client(int clientId, int personId, std::string name,
               std::string lastname, std::string address, std::string phone,
               std::string email, bool status)
    : Person(personId, name, lastname) {
    _clientId = clientId;
    strcpy(_address, address.c_str());
    strcpy(_phone, phone.c_str());
    strcpy(_email, email.c_str());
    _status = status;
}

void Client::setClientId(int clienteId) { _clientId = clienteId; }
void Client::setAddress(std::string address) {
    strcpy(_address, address.c_str());
}
void Client::setPhone(std::string phone) { strcpy(_phone, phone.c_str()); }
void Client::setEmail(std::string email) { strcpy(_email, email.c_str()); }
void Client::setStatus(bool status) { _status = status; }

int Client::getClientId() { return _clientId; }
const char *Client::getAddress() { return _address; }
const char *Client::getPhone() { return _phone; }
const char *Client::getEmail() { return _email; }
bool Client::getStatus() { return _status; }

void Client::toVecString(std::string vStr[7]) {
    vStr[0] = std::to_string(_clientId);
    vStr[1] = Person::getName();
    vStr[2] = Person::getLastname();
    vStr[3] = std::to_string(Person::getIdPerson());
    vStr[4] = _address;
    vStr[5] = _phone;
    vStr[6] = _email;
}
