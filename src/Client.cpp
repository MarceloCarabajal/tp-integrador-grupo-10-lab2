#include<iostream>
#include "Client.h"

using namespace std;
 
void Client::setClientId(int clienteId ){ _clientId = clienteId; }
void Client::setAddress(std::string address){ std::string _address=address;}
void Client::setPhone(std::string phone){std::string _phone=phone;}
void Client::setEmail(std::string email){std::string _email=email;}


int Client::getClientId (){return _clientId;}
std::string Client::getAddress(){return _address;}
std::string Client::getPhone(){return _phone; }
std::string Client::getEmail(){return _email;}


void Client::load(){

   Person::load();

int clientId;
std::string address, phone, email;

cout<<"Ingrese Id Cliente:";
cin>> clientId;
setClientId(clientId);

cout<<"Ingrese Direccion:";
cin>>address;
setAddress(address);

cout<<"Ingrese Telefono:";
cin>>phone;
setPhone(phone);

cout<<"Ingrese E-mail:";
cin>>email;
setEmail(email);
}