#include <iostream>
#include "Income.h"

using namespace std;


void Income::setSaleId( int saleId){_saleId=saleId;}


int   Income::getSaleId(){return _saleId;}


/*
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

}*/