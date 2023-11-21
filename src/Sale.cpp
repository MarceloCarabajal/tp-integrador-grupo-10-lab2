#include "Sale.h"

#include <cstring>
#include <iostream>

using namespace std;


Sale::Sale(){

     _saleId=-1;
     _transactionId=-1;
     _totalAmount=0.00;
     strcpy( _paymentMethod, " ");
    _saleDate= Date (1,1,1900);
    _saleTime=Time(0,0,0);
    _isVisit=false;
    
}

Sale::Sale (int saleid, int transactionid, float totalamount, std::string paymentmethod, Date saledate, Time saletime, bool isvisit)
{
_saleId=saleid;
_transactionId=transactionid;
_totalAmount=totalamount;
strcpy(_paymentMethod, paymentmethod.c_str());
_saleDate=saledate;
_saleTime=saletime;
_isVisit=isvisit;

}

void Sale::setSaleId(int id) { _saleId = id; }
void Sale::setTransactionId(int id) { _transactionId = id; }
void Sale::setAmount(float amount) { _totalAmount = amount; }
void Sale::setPaymentMethod(std::string method) {
    strcpy(_paymentMethod, method.c_str());
}
void Sale::setDate(Date date) { _saleDate = date; }
void Sale::setTime(Time time) { _saleTime = time; }
void Sale::setIsVisit(bool Visit) { _isVisit = false; }

int Sale::getSaleId() { return _saleId; }
float Sale::getAmount() { return _totalAmount; }
const char* Sale::getPaymentMethod() { return _paymentMethod; }
Date Sale::getDate() { return _saleDate; }
Time Sale::getTime() { return _saleTime; }
bool Sale::getIsVisit() { return _isVisit; }
int Sale::getTransactionId() { return _transactionId; }

void Sale::toVecString(std::string vStr[7]) {
    vStr[0] = std::to_string(_saleId);
    vStr[1] = std::to_string(_transactionId);
    vStr[2] = std::to_string(_totalAmount);
    vStr[3] = _paymentMethod;
    vStr[4] = _saleDate.toString();
    vStr[5] = _saleTime.toString();
    vStr[6] = _isVisit;
}
