#pragma once
#include <string>
#include "Date.h"
#include "Time.h"

class Transaction {

private:

int _idTransaction;
Date _date;
Time _time;
std::string _description;
float _amount;

public:  

void setIdTransaction(int idTrx );
void setDate( Date date);
void setTime ( Time time);
void setDescription(std:: string desc );
void setAmount(float amount );

int getIdTransaction();
Date getDate();
Time getTime();
std::string getDescription();
float getAmount();


};