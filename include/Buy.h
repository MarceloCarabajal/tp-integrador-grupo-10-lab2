#pragma once
#include <string>

#include "Date.h"
#include "TimeCls.h"

class Buy {
private:
    int _buyId, _productId, _quantity, _transactionId;
    float _unitPrice;
    int _paymentMethod;
    Date _buyDate;
    bool _status;

    // TODO: Consideramos ingresar una compra por cada transaccion, es decir un
    // producto con su cantidad. Por eso no tenemos ItemBuy como en Sale */
public:
    Buy();
    Buy( int buyid, int productid, int quantityid, int transaccionid,
        float unitPrice, int paymentmethod, Date buydate,
        bool status);

    void setBuyId(int id);
    void setunitprice(float importe);
    void setpaymentMethod(int method);
    void setDate(Date date);
    void setProductId(int ProductId);
    void setQuantity(int qty);
    void setTransactionId(int id);
    void setStatus(bool status);

    int getBuyId();
    float getunitprice();
    int getPaymentMethod();
    Date getbuyDate();
    int getProductId();
    int getQuantity();
    int getTransactionId();
    bool getStatus();
    void load();

    void toVecString(std::string vStr[7]);
};