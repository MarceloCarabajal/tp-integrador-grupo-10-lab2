#pragma once
#include "Date.h"
#include "TimeCls.h"


class Buy { 

private: 

int _buyId, _productId,_quantity,_transactionId;
float _totalAmount; 
char _paymentMethod[15]; 
Date _buyDate;
Time _buyTime ;


public: 


void setBuyId( int  id);    
void setAmount( float  importe);    ///CORREGÍ TIPO DE DATO, ESTABA INT
void setpaymentMethod (const char* method);
void setDate ( Date date);
void setTime ( Time time );
void setProductId ( int ProductId);
void setQuantity( int qty);
void setTransactionId ( int id);

int getBuyId(); 
float getTotalAmount(); 
const char* getPaymentMethod();
Date getbuyDate(); 
Time getbuyTime(); 
int getProductId (); 
int getQuantity (); 
int getTransaction (); 
void load();

} ;