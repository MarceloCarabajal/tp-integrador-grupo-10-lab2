#pragma once
#include "Transaction.h"


class Income : Transaction {

private:

int _saleId;



public: 

void setSaleId( int saleId);


int  getSaleId();


void load();

};