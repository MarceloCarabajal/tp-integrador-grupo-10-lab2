#pragma once
#include <string>
#include "Date.h"
#include "TimeCls.h"

class Sale { 

private:

int _saleId, _quantit, _transactionId;
float _totalAmount;
std:: string _paymentMethod;
Date _saleDate; 
Time _saleTime; 
bool _isVisit; 


public: 

void setSaleId(int id);
void setAmount(float amount); 
void setPaymentMethod( std::string method); 
void setDate( Date date); 
void setTime( Time time); 
void setQuantity( int qty); 
void setIsVisit( bool isVisit); 
void setTransactionId( int id); 

int getSaleId();
float getAmount();
std::string getPaymentMethod();
Date getDate(); 
Time getTime(); 
int getQuantity(); 
bool getIsVisit(); 
int getTransactionId(); 


void load();


} ;