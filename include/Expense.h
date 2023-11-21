#pragma once
#include "Transaction.h"


class Expense: public Transaction {

private: 	
int _buyId;


public: 
Expense ();
Expense (int buyid, int idTransaction,Date transDate,Time transTime,std::string description,float amount,std::string paymentMethod);

void setBuyId( int id);
int  getBuyId();


void load ();
void toVecString(std::string vStr[7]);

};