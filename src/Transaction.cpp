#include <iostream>
#include <cstring>
#include "Transaction.h"
using namespace std;


Transaction::Transaction (){
 _idTransaction=-1;
 _transDate= Date(1,1,1900);
 _transTime=Time(00,00,00);
 strcpy( _description, " ");
_amount=0.00;
 strcpy( _paymentMethod, " ");
    
}
Transaction::Transaction (int idtrans, Date transdate, Time transtime, std::string descrip, float amount,std::string payment){
_idTransaction=idtrans;
_transDate=transdate;
_transTime=transtime;
strcpy(_description, descrip.c_str()) ;
_amount=amount;
strcpy(_paymentMethod,payment.c_str());
}

void Transaction::setIdTransaction(int idTrx ){_idTransaction=idTrx;}
void Transaction::setDateTrans( Date transDate){_transDate=transDate;   }
void Transaction::setTimeTrans ( Time transTime){_transTime=transTime;}
void Transaction::setDescription(std::string desc ){strcpy (_description,desc.c_str());}
void Transaction::setAmount(float amount ){_amount=amount;    }
void Transaction::setPaymentMethod (std::string met){strcpy (_paymentMethod, met.c_str());}


int Transaction::getIdTransaction(){return _idTransaction;}
Date Transaction::getDateTrans(){return _transDate;}
Time Transaction::getTimeTrans(){return _transTime;}
const char* Transaction::getDescription(){return _description  ;  }
float Transaction::getAmount(){return _amount;}
const char * Transaction::getPaymentMehod(){return _paymentMethod;}




/*

void Transaction::load (){
//TODO: ver TIME de transaccion. Si lo agregamos en LOAD o lo sacamos de atributo/set/get

int idTransaction;
Date transDate;
Time transTime;
std::string description;
float amount;
int auxDay,auxMonth, auxYear;


cout<<"Ingrese ID de transaccion:";
cin>>idTransaction;
setIdTransaction(idTransaction);


cout<<"Ingrese Dia de realizacion de la transaccion:";
cin>>auxDay;
transDate.setDay(auxDay);

cout<<"Ingrese Mes de realizacion de la transaccion:";
cin>>auxMonth;
transDate.setMonth(auxMonth);

cout<<"Ingrese Anio de realizacion de la transaccion:";
cin>>auxYear;
transDate.setYear(auxYear);

cout<<"Ingrese descripcion la transaccion:";
cin>>description;
setDescription(description);

cout<<"Ingrese importe de la transaccion:";
cin>>amount;
setAmount (amount);




}*/