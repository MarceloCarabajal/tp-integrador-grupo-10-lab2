#include<iostream>

#include "Expense.h"

using namespace std;


void Expense::setBuyId( int id){_buyId=id;}


int  Expense::getBuyId(){return _buyId;}

void Expense::toVecString(std::string vStr[7]) {
    vStr[0] = std::to_string(Transaction::getIdTransaction());
    vStr[1] = std::to_string(_buyId);
    vStr[2] = Transaction::getDateTrans().toString();
    vStr[3] = Transaction::getTimeTrans().toString();
    vStr[4] = Transaction::getDescription();
    vStr[5] = Transaction::getAmount();
    vStr[6] = Transaction::getPaymentMehod();


}

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