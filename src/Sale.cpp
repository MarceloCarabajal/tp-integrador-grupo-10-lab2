#include <cstring>
#include <iostream>
#include "Sale.h"

using namespace std;

void Sale::setSaleId(int id){_saleId=id;}
void Sale::setTransactionId( int id){_transactionId=id;}
void Sale::setAmount(float amount){_totalAmount=amount;} 
void Sale::setPaymentMethod(std::string method){strcpy(_paymentMethod,method.c_str());}
void Sale::setDate( Date date){_saleDate=date;}
void Sale::setTime( Time time){_saleTime=time;}
void Sale::setIsVisit( bool Visit){_isVisit=false;}

int Sale::getSaleId(){return _saleId; }
float Sale::getAmount() {return _totalAmount ;}
const char * Sale::getPaymentMethod(){return _paymentMethod;}
Date Sale::getDate(){return _saleDate;} 
Time Sale::getTime(){return _saleTime;} 
bool Sale::getIsVisit(){return _isVisit;}
int Sale::getTransactionId(){return  _transactionId;}



void Sale::toVecString(std::string vStr[7]) {
    vStr[0] = std::to_string(_saleId);
    vStr[1] = std::to_string(_transactionId);
    vStr[2] = std::to_string(_totalAmount);
    vStr[3] = _paymentMethod;
    vStr[4] = _saleDate.toString();
    vStr[5] = _saleTime.toString();
    vStr[6] = _isVisit;
   



//TODO: completar LOAD

/*
void Sale::load(){
int saleId, quantit, transactionId;
float totalAmount;
std:: string paymentMethod;
Date saleDate; 
Time saleTime; 
bool isVisit; 

cout<<
cin>>saleId
set      saleId

cout<<
cin>>quantit
set         quantit

cout<<
cin>>transactionId
set         transactionId
 
cout<<
cin>>totalAmount
set       totalAmount

cout<<
cin>>paymentMethod;
set         paymentMethod;

cout<<
cin>>
set

cout<<
cin>>
set

cout<<
cin>>isVisit
set



}

*/



