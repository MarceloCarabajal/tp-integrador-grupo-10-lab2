#include "Sale.h"

#include <cstring>
#include <iostream>

#include "utils.h"

using namespace std;

Sale::Sale() {
    _saleId = -1;
    _transactionId = -1;
    _totalAmount = 0.00;
    _paymentMethod = -1;
    _saleDate = Date(1, 1, 1900);
    _isVisit = false;
}

Sale::Sale(int saleid, int transactionid, float totalamount, int paymentmethod,
           Date saledate, bool isvisit) {
    _saleId = saleid;
    _transactionId = transactionid;
    _totalAmount = totalamount;
    _paymentMethod = paymentmethod;
    _saleDate = saledate;
    _isVisit = isvisit;
}

void Sale::setSaleId(int id) { _saleId = id; }
void Sale::setTransactionId(int id) { _transactionId = id; }
void Sale::setAmount(float amount) { _totalAmount = amount; }
void Sale::setPaymentMethod(int method) { _paymentMethod = method; }
void Sale::setDate(Date date) { _saleDate = date; }
void Sale::setIsVisit(bool Visit) { _isVisit = Visit; }

int Sale::getSaleId() { return _saleId; }
float Sale::getAmount() { return _totalAmount; }
int Sale::getPaymentMethod() { return _paymentMethod; }
Date Sale::getDate() { return _saleDate; }
bool Sale::getIsVisit() { return _isVisit; }
int Sale::getTransactionId() { return _transactionId; }

void Sale::toVecString(std::string vStr[6]) {
    vStr[0] = std::to_string(_saleId);
    vStr[1] = std::to_string(_transactionId);
    vStr[2] = std::to_string(_paymentMethod);
    vStr[3] = _saleDate.toString();
    vStr[4] = std::to_string(_totalAmount);
    vStr[5] = utils::boolToStr(_isVisit);
}
