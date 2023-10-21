#pragma once
#include <string>
#include "Date.h"
#include "Time.h"


class Buy {

private: 

int _buyId, _productId,_quantity,_transactionId;
float _totalAmount; 
std:: string _paymentMethod; 
Date _buyDate;
Time _buyTime ;


public: 


void setBuyId( Inventory item);    ///PENDIENTE CORREGIR INVENTORY
void setAmount( float  importe);    ///CORREGÍ TIPO DE DATO, ESTABA INT
void setpaymentMethod (std::string method);
void setDate ( Date date);
void setTime ( Time time );
void setProductId ( int ProductId);
void setQuantity( int qty);
void setTransactionId ( int id);

int getBuyId(); 
float getTotalAmount(); 
std:: string getPaymentMethod();
Date getbuyDate(); 
Time getbuyTime(); 
int getProductId (); 
int getQuiantity (); 
int getTransaction (); 
void load();

} ;