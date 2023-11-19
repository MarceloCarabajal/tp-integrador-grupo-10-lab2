#pragma once
#include <string>

#include "Date.h"
#include "TimeCls.h"

class Transaction {
private:
    int _idTransaction;
    Date _transDate;
    Time _transTime;
    char _description[45];
    float _amount;
    char _paymentMethod[15];

public:
    void setIdTransaction(int idTrx);
    void setDateTrans(Date date);
    void setTimeTrans(Time time);
    void setDescription(std::string desc);
    void setAmount(float amount);
    void setPaymentMethod(std::string met);

    int getIdTransaction();
    Date getDateTrans();
    Time getTimeTrans();
    const char* getDescription();
    float getAmount();
    const char* getPaymentMehod();

    void load();
};
