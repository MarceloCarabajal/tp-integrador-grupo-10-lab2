#pragma once
#include "Transaction.h"
 
class Income : public Transaction {

private:

int _saleId;



public: 
//TODO: FALTA CONSTRUCTOR
void setSaleId( int saleId);


int  getSaleId();


void load();

void toVecString(std::string vStr[7]);

};