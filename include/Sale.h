#pragma once
#include <string>

#include "Date.h"
#include "TimeCls.h"

class Sale {
private:
    int _saleId, _transactionId, _paymentMethod;
    float _totalAmount;
    Date _saleDate;
    Time _saleTime;
    bool _isVisit;

public:
    Sale();
    Sale(int saleid, int transactionid, float totalamount, int paymentmethod,
         Date saledate, bool isvisit);

    void setSaleId(int id);
    void setAmount(float amount);
    void setPaymentMethod(int method);
    void setDate(Date date);
    void setTime(Time time);
    void setQuantity(int qty);
    void setIsVisit(bool isVisit);
    void setTransactionId(int id);

    int getSaleId();
    float getAmount();
    int getPaymentMethod();
    Date getDate();
    Time getTime();
    int getQuantity();
    bool getIsVisit();
    int getTransactionId();

    void load();

    void toVecString(std::string vStr[7]);
};