#include "Buy.h"

#include <cstring>
#include <iostream>

using namespace std;

void Buy::setBuyId(int id) { _buyId = id; }
void Buy::setAmount(float importe) { _totalAmount = importe; }
void Buy::setpaymentMethod(std::string method) {
    strcpy(_paymentMethod, method.c_str());
}
void Buy::setDate(Date date) { _buyDate = date; }
void Buy::setTime(Time time) { _buyTime = time; }
void Buy::setProductId(int ProductId) { _productId = ProductId; }
void Buy::setQuantity(int qty) { _quantity = qty; }
void Buy::setTransactionId(int id) { _transactionId = id; }

int Buy::getBuyId() { return _buyId; }
float Buy::getTotalAmount() { return _totalAmount; }
const char *Buy::getPaymentMethod() { return _paymentMethod; }
Date Buy::getbuyDate() { return _buyDate; }
Time Buy::getbuyTime() { return _buyTime; }
int Buy::getProductId() { return _productId; }
int Buy::getQuantity() { return _quantity; }
int Buy::getTransaction() { return _transactionId; }


void Buy::toVecString(std::string vStr[8]) {
    vStr[0] = std::to_string(_buyId);
    vStr[1] = std::to_string(_productId);
    vStr[2] = std::to_string (_quantity);
    vStr[3] = std::to_string(_transactionId);
    vStr[4] = std::to_string(_totalAmount);
    vStr[5] = _paymentMethod;
    vStr[6] = _buyDate.toString();
    vStr[7] = _buyTime.toString();
}
