#pragma once
#include <string>
#include "Date.h"
#include "TimeCls.h"

class Transaction {

private:

int _idTransaction;
Date _transDate;
Time _transTime;
std::string _description;
float _amount;

public:  

void setIdTransaction(int idTrx );
void setDateTrans( Date date);
void setTimeTrans ( Time time);
void setDescription(std:: string desc );
void setAmount(float amount );

int getIdTransaction();
Date getDateTrans();
Time getTimeTrans();
std::string getDescription();
float getAmount();

void load();

};