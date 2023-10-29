#pragma once
#include <string>
#include "Transaction.h"


class Expense: Transaction {

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