#include "Sale.h"

void Sale::setSaleId(int id){_saleId=id;}
void Sale::setQuantity( int qty){_quantit=qty;}
void Sale::setTransactionId( int id){_transactionId=id;}
void Sale::setAmount(float amount){_totalAmount=amount;} 
void Sale::setPaymentMethod( std::string method){_paymentMethod=method;}
void Sale::setDate( Date date){_saleDate=date;}
void Sale::setTime( Time time){_saleTime=time;}
void Sale::setIsVisit( bool Visit){_isVisit=false;}

int Sale::getSaleId(){return _saleId; }
float Sale::getAmount() {return _totalAmount ;}
std::string Sale::getPaymentMethod(){return _paymentMethod;}
Date Sale::getDate(){return _saleDate;} 
Time Sale::getTime(){return _saleTime;} 
int Sale::getQuantity(){return _quantit;}
bool Sale::getIsVisit(){return _isVisit;}
int Sale::getTransactionId(){return  _transactionId;}


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



