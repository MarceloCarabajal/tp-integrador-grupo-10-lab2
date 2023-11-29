#pragma once
#include <string>

#include "Date.h"
#include "TimeCls.h"

class Buy {
private:
    int _buyId, _productId, _quantity, _transactionId;
    float _totalAmount;
    char _paymentMethod[15];
    Date _buyDate;
  

//TODO: Consideramos ingresar una compra por cada transaccion, es decir un producto con su cantidad. Por eso no tenemos ItemBuy como en Sale */
public:

Buy();
Buy (int buyid, int productid, int quantityid, int transaccionid,float totalamount, std::string paymentmethod, Date buydate);
 
    void setBuyId(int id);
    void setAmount(float importe);
    void setpaymentMethod(std::string method);
    void setDate(Date date);
    void setProductId(int ProductId);
    void setQuantity(int qty);
    void setTransactionId(int id);

    int getBuyId();
    float getTotalAmount();
    const char* getPaymentMethod();
    Date getbuyDate();
    int getProductId();
    int getQuantity();
    int getTransactionId();
    void load();

    void toVecString(std::string vStr[7]);
};