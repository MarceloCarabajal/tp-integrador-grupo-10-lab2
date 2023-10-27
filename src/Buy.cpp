#include<iostream>
#include "Buy.h"
using namespace std;

void Buy::setBuyId( int  id){ _buyId=id;}   
void Buy::setAmount( float  importe){_totalAmount=importe;}  
void Buy::setpaymentMethod (std::string method){ _paymentMethod=method;}
void Buy::setDate ( Date date){_buyDate= date;}
void Buy::setTime ( Time time ){_buyTime=time;}
void Buy::setProductId ( int ProductId){_productId=ProductId;}
void Buy::setQuantity( int qty){_quantity=qty;}
void Buy::setTransactionId ( int id){_transactionId=id;}

int Buy::getBuyId(){return _buyId;}
float Buy::getTotalAmount(){return _totalAmount;}
std:: string Buy::getPaymentMethod(){return _paymentMethod;}
Date Buy::getbuyDate(){return _buyDate;}
Time Buy::getbuyTime(){return _buyTime;} 
int Buy::getProductId (){return _productId;} 
int Buy::getQuantity (){return _quantity;}
int Buy::getTransaction (){return _transactionId;}



void Buy::load(){


int buyId, productId,quantity,transactionId;
float totalAmount; 
std:: string paymentMethod; 
Date buyDate;
Time buyTime ;

cout<<"Ingrese Id de la Compra:";
cin>>buyId;
setBuyId(buyId);


cout<<"Ingrese Id del producto:";
cin>>productId;
setProductId(productId);

cout<<"Ingrese cantidad comprada:";
cin>>quantity;
setQuantity(quantity);

cout<<"Ingrese importe total:";
cin>>totalAmount;
setAmount(totalAmount);

cout<<"Ingrese metodo de pago:";
cin>>paymentMethod;
setpaymentMethod(paymentMethod);

cout<<"Ingrese Fecha de la compra:";
cin>>buyDate;
setDate(buyDate);

cout<<"Ingrese Hora de la compra:";
cin>>buyTime;
setTime(buyTime);



//TODO: ver tema del ID Transaccion, habiamos dicho que venia de otro lado?   
/*cout<<
cin>>
set
*/

}