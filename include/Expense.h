#pragma once
#include "Transaction.h"


class Expense: public Transaction {

private: 	
int _buyId;


public: 

void setBuyId( int id);


int  getBuyId();


void load ();

void toVecString(std::string vStr[7]);

};