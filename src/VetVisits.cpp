#include "VetVisits.h"
#include <cstring>
using namespace std;
VetVisits::VetVisits (){

_visitId=-1;
_vetId=-1;
_clientId=-1;
_petId=-1;
_saleId=-1;
_date=Date(01,01,1900);
 strcpy(_reason," ");
 strcpy( _diagnosis, " ");

}
VetVisits::VetVisits (int visitid, int vetid, int clientid, int petid, int saleid, Date date,std::string reason, std::string diagnosis ){
_visitId=visitid;
_vetId=vetid;
_clientId=clientid;
_petId=petid;
_saleId=saleid;
_date=date;
 strcpy(_reason,reason.c_str());
 strcpy( _diagnosis,diagnosis.c_str());

}

void VetVisits::setVisitId(int id) {_visitId=id;}
void VetVisits::setVetId(int idvet) {_vetId=idvet;}
void VetVisits::setClientId(int id) {_clientId=id;}
void VetVisits::setPetId(int id) {_petId=id;}
void VetVisits::setSaleId(int id) {_saleId=id;}
void VetVisits::setDate(Date dat) {_date=dat;}
void VetVisits::setReason(std::string reason) {strcpy(_reason,reason.c_str());}
void VetVisits::setDiagnosis(std::string diagnosis) {strcpy(_diagnosis,diagnosis.c_str());}

int VetVisits::getVisitId() {return _visitId;}
Date VetVisits::getDate() {return _date;}
const char* VetVisits::getReason() {return _reason;}
const char* VetVisits::getDiagnosis() {return _diagnosis;}
int VetVisits::getVetId() {return _vetId;}
int VetVisits::getClientId() {return _clientId;}
int VetVisits::getPetId() {return _petId;}
int VetVisits::getSaleId() {return _saleId;}

bool VetVisits::isValidRelation() {}

void VetVisits ::toVecString(std::string vStr[8]) {
    vStr[0] = std::to_string(_visitId);
    vStr[1] = std::to_string(_vetId);
    vStr[2] = std::to_string(_clientId);
    vStr[3] = std::to_string(_petId);
    vStr[4] = std::to_string(_saleId);
    vStr[5] = _date.toString();
    vStr[6] = _reason;
    vStr[7] = _diagnosis;
}
