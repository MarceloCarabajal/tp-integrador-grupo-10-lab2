#include "Buy.h"

#include <cstring>
#include <iostream>

using namespace std;

Buy::Buy(){
_buyId=-1;
_productId=-1;
_quantity=-1;
_transactionId=-1;
_totalAmount=0.00;
strcpy (_paymentMethod, "");
_buyDate= Date(1,1,1990);
_status = false;

}

Buy::Buy (int buyid, int productid, int quantityid, int transaccionid,float totalamount, std::string paymentmethod, Date buydate,bool status){
_buyId=buyid;
_productId=productid;
_quantity=quantityid;
_transactionId=transaccionid;
_totalAmount=totalamount;
strcpy (_paymentMethod,paymentmethod.c_str());
_buyDate=buydate;
 _status = status;


}

void Buy::setBuyId(int id) { _buyId = id; }
void Buy::setAmount(float importe) { _totalAmount = importe; }
void Buy::setpaymentMethod(std::string method) {strcpy(_paymentMethod, method.c_str());
}
void Buy::setDate(Date date) { _buyDate = date; }
void Buy::setProductId(int ProductId) { _productId = ProductId; }
void Buy::setQuantity(int qty) { _quantity = qty; }
void Buy::setTransactionId(int id) { _transactionId = id; }
void Buy::setStatus(bool status) { _status = status; }

int Buy::getBuyId() { return _buyId; }
float Buy::getTotalAmount() { return _totalAmount; }
const char *Buy::getPaymentMethod() { return _paymentMethod; }
Date Buy::getbuyDate() { return _buyDate; }
int Buy::getProductId() { return _productId; }
int Buy::getQuantity() { return _quantity; }
int Buy::getTransactionId() { return _transactionId; }
bool Buy::getStatus() { return _status; }


void Buy::toVecString(std::string vStr[7]) {
    vStr[0] = std::to_string(_buyId);
    vStr[1] = std::to_string(_productId);
    vStr[2] = std::to_string (_quantity);
    vStr[3] = std::to_string(_transactionId);
    vStr[4] = std::to_string(_totalAmount);
    vStr[5] = _paymentMethod;
    vStr[6] = _buyDate.toString();

}
