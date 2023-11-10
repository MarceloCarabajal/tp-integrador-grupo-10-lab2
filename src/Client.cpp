#include "Client.h"

#include <cstring>
#include <iostream>

using namespace std;

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