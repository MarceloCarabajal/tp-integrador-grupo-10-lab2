#include "VetVisits.h"


void VetVisits::setVisitId(int id) {_visitId=id;}
void VetVisits::setVetId(int idvet) {_vetId=idvet;}
void VetVisits::setClientId(int id) {_clientId=id;}
void VetVisits::setPetId(int id) {_petId=id;}
void VetVisits::setSaleId(int id) {_saleId=id;}
void VetVisits::setDate(Date dat) {_date=dat;}
void VetVisits::setReason(std::string reason) {_reason=reason;}
void VetVisits::setDiagnosis(std::string diagnosis) {_diagnosis=diagnosis;}

int VetVisits::getVisitId() {return _visitId;}
Date VetVisits::getDate() {return _date;}
std::string VetVisits::getReason() {return _reason;}
std::string VetVisits::getDiagnosis() {return _diagnosis;}
int VetVisits::getVetId() {return _vetId;}
int VetVisits::getClientId() {return _clientId;}
int VetVisits::getPetId() {return _petId;}
int VetVisits::getSaleId() {return _saleId;}

bool VetVisits::isValidRelation() {}