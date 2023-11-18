#pragma once
#include <string>
#include "Date.h"
#include "TimeCls.h"

class Sale { 

private:

int _saleId,  _transactionId;
float _totalAmount;
char _paymentMethod[15];
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
const char * getPaymentMethod();
Date getDate(); 
Time getTime(); 
int getQuantity(); 
bool getIsVisit(); 
int getTransactionId(); 


void load();

    void toVecString(std::string vStr[7]);
} ;