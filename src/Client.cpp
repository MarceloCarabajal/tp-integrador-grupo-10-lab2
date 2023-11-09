#include "Client.h"

#include <cstring>
#include <iostream>

using namespace std;

void Client::setClientId(int clienteId) { _clientId = clienteId; }
void Client::setAddress(const char *address) { strcpy(_address, address); }
void Client::setPhone(const char *phone) { strcpy(_phone, phone); }
void Client::setEmail(const char *email) { strcpy(_email, email); }

int Client::getClientId() { return _clientId; }
const char *Client::getAddress() { return _address; }
const char *Client::getPhone() { return _phone; }
const char *Client::getEmail() { return _email; }

/* void Client::load() {
    Person::load();

    int clientId;
    std::string address, phone, email;

    cout << "Ingrese Id Cliente:";
    cin >> clientId;
    setClientId(clientId);

    cout << "Ingrese Direccion:";
    cin >> address;
    setAddress(address);

    cout << "Ingrese Telefono:";
    cin >> phone;
    setPhone(phone);

    cout << "Ingrese E-mail:";
    cin >> email;
    setEmail(email);
} */