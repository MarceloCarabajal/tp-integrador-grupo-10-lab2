#pragma once
#include <string>


class Expense {

private: 	
int _buyId;
std:: string _paymentMethod;

public: 

void setBuyId( int id);
void setPaymentMethod(std:: string  method );

int  getBuyId();
std:: string getPaymentMethod();

void load ();
};