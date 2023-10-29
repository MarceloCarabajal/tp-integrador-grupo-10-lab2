#include<iostream>
#include "Expense.h"

using namespace std;


void Expense::setBuyId( int id){_buyId=id;}
void Expense::setPaymentMethod(std:: string  method ){ _paymentMethod =method;}

int  Expense::getBuyId(){return _buyId;}
std:: string Expense::getPaymentMethod(){return _paymentMethod; }

void Expense::load (){

Transaction::load();

int buyId;
std:: string paymentMethod;

cout<<"Ingrese Id del gasto";
cin>>buyId;
setBuyId(buyId);

cout<<"Ingrese metodo de pago";
cin>>paymentMethod;
setPaymentMethod(paymentMethod);


}