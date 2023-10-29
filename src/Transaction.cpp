#include <iostream>

#include "Transaction.h"
using namespace std;


void Transaction::setIdTransaction(int idTrx ){_idTransaction=idTrx;}
void Transaction::setDateTrans( Date transDate){_transDate=transDate;   }
void Transaction::setTimeTrans ( Time transTime){_transTime=transTime;}
void Transaction::setDescription(std:: string desc ){_description=desc;}
void Transaction::setAmount(float amount ){_amount=amount;    }

int Transaction::getIdTransaction(){return _idTransaction;}
Date Transaction::getDateTrans(){return _transDate;}
Time Transaction::getTimeTrans(){return _transTime;}
std::string Transaction::getDescription(){return _description  ;  }
float Transaction::getAmount(){return _amount;}


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




}