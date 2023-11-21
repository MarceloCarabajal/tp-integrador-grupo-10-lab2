#include <iostream>
#include "ItemSale.h"
using namespace std;


ItemSale::ItemSale(){
_productId=-1;
 _quantity=0;
  _saleId=0;
 _unitPrice=0;

}

ItemSale::ItemSale (int productid, int quantity, int saleid, float unitprice){

_productId=productid;
_quantity=quantity;
_saleId=saleid;
_unitPrice=unitprice;

}

void ItemSale::setProductId( int productId){_productId=productId;}
void ItemSale::setQuantity( int quantity){_quantity=quantity;}
void ItemSale::setUnitPrice( float total){_unitPrice=total;}
void ItemSale::setSaleId( int saleId){_saleId=saleId;}

int ItemSale::getProductId(){return _productId;}
int ItemSale::getQuantity(){return _quantity;}
float ItemSale::getUnitPrice(){return _unitPrice;}
int ItemSale::getSaleId(){return _saleId;}

void ItemSale::load(){
    
int productId, quantity, saleId;
 float unitPrice;

 
cout<<"Ingrese ID de la venta:";
cin>>saleId;

cout<<"Ingrese ID del producto:";
cin>>productId;

cout<<"Ingrese cantidad vendida:";
cin>>quantity;

cout<<"Ingrese PrecioUnitario:";
cin>>unitPrice;


}