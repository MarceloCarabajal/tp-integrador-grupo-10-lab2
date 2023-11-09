#include<iostream>

#include "Expense.h"

using namespace std;


void Expense::setBuyId( int id){_buyId=id;}


int  Expense::getBuyId(){return _buyId;}


/*
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


}*/