#pragma once
#include <string>
#include "Date.h"
#include "Time.h"


class VetVisits {

private:  
 int  _visitId,_vetId,_clientId, _petId,_saleId; 
 Date _date;
 std::string _reason, _diagnosis;
 
public: 

 void setVisitId( int id );
 void setVetId( int id);
 void setClientId( int id);
 void setPetId( int id);
 void setsaleId (int id);
 void setDate( Date fecha);
 void setReason( std::string reason);
 void setDiagnosis( std::string diagnosis);

int getVisitId();
Date getDate();
std::string getReason();
std::string getDiagnosis();
int getVetId();
int getClientId(); 
int getPetId(); 

bool isValidRelation();

};