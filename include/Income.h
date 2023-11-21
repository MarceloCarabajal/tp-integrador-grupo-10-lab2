#pragma once
#include "Transaction.h"
 
class Income : public Transaction {

private:

int _saleId;



public: 

Income ();
Income (int saleId, int idTransaction,Date transDate,Time transTime,std::string description,float amount,std::string paymentMethod);

void setSaleId( int saleId);
int  getSaleId();

void load();
void toVecString(std::string vStr[7]);

};