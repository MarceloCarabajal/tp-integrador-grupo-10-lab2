#pragma once
#include <string>
#include "Transaction.h"


class Income : Transaction {

private:

int _saleId;
std::string _paymentMethod;


public: 

void setSaleId( int saleId);
void setpaymentMethod(std::string method);

int  getSaleId();
std:: string getPaymentMethod();

void load();

};