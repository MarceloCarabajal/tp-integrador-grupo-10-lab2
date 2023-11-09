#pragma once
#include "Transaction.h"


class Expense: Transaction {

private: 	
int _buyId;


public: 

void setBuyId( int id);


int  getBuyId();


void load ();
};