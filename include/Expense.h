#pragma once
#include <string>


class Expense {
	
int _buyId;
std:: string _paymentMethod;


void setBuyId( int id);
void setPaymentMethod(std:: string  method );

int  getBuyId();
std:: string getPaymentMethod();

};