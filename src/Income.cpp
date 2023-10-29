#include <iostream>
#include "Income.h"

using namespace std;


void Income::setSaleId( int saleId){_saleId=saleId;}
void  Income::setpaymentMethod(std::string method){ _paymentMethod=method;}

int   Income::getSaleId(){return _saleId;}
std:: string  Income::getPaymentMethod(){return _paymentMethod;}

void Income::load (){

Transaction::load();

int saleId;
std::string method;

cout<<"Ingrese ID del ingreso";
cin>>saleId;
//TODO Ver si se manda por set o esto venia automatico de algun lado

cout<<"Ingrese Metodo de pago recibido:";
cin>>method;
setpaymentMethod(method);

}