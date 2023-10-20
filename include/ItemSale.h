#pragma once
#include <string>

class ItemSale {

private: 
 int _productId, _quantity, _saleId;
 float _unitPrice;


public: 
 void setProductId( int productId);
 void setQuantity( int quantity);
 void setUnitPrice( float total);
 void setSaleId( int saleId);


 int getProductId();
 int getQuantity();
 float getUnitPrice();
 int getSaleId();

void load();
};