#include "Buy.h"

#include <cstring>
#include <iostream>

using namespace std;

Buy::Buy() {
    _buyId = -1;
    _productId = -1;
    _quantity = -1;
    _transactionId = -1;
    _unitPrice = 0.00;
    _paymentMethod = -1;
    _buyDate = Date(1, 1, 1990);
    _status = false;
}

Buy::Buy(int buyid, int productid, int quantityid, int transaccionid,
         float unitprice, int paymentmethod, Date buydate, bool status) {
    _buyId = buyid;
    _productId = productid;
    _quantity = quantityid;
    _transactionId = transaccionid;
    _unitPrice = unitprice;
    _paymentMethod = paymentmethod;
    _buyDate = buydate;
    _status = status;
}

void Buy::setBuyId(int id) { _buyId = id; }
void Buy::setunitprice(float up) { _unitPrice = up; }
void Buy::setpaymentMethod(int method) { _paymentMethod = method; }

void Buy::setDate(Date date) { _buyDate = date; }
void Buy::setProductId(int ProductId) { _productId = ProductId; }
void Buy::setQuantity(int qty) { _quantity = qty; }
void Buy::setTransactionId(int id) { _transactionId = id; }
void Buy::setStatus(bool status) { _status = status; }

int Buy::getBuyId() { return _buyId; }
float Buy::getunitprice() { return _unitPrice; }
int Buy::getPaymentMethod() { return _paymentMethod; }
Date Buy::getbuyDate() { return _buyDate; }
int Buy::getProductId() { return _productId; }
int Buy::getQuantity() { return _quantity; }
int Buy::getTransactionId() { return _transactionId; }
bool Buy::getStatus() { return _status; }

void Buy::toVecString(std::string vStr[7]) {
    vStr[0] = std::to_string(_buyId);
    vStr[1] = std::to_string(_productId);
    vStr[2] = std::to_string(_transactionId);
    vStr[3] = std::to_string(_paymentMethod);
    vStr[4] = _buyDate.toString();
    vStr[5] = std::to_string(_quantity);
    vStr[6] = std::to_string(_unitPrice);
}
