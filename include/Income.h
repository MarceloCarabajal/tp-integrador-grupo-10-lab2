#pragma once
#include <string>


class Income {

private:

int _saleId;
std::string _paymentMethod;


public: 

void setSaleId( int saleId);
void setpaymentMethod(std::string method);

int  getSaleId();
std:: string getPaymentMethod();

};