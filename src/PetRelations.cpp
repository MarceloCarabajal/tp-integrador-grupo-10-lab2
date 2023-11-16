#include "PetRelations.h"



PetRelations::PetRelations(){
_relationId=-1;
_petId=-1;
_clientId=-1;
_owner=false;
}
PetRelations::PetRelations(int relationId, int petId, int clientId, bool owner){

_relationId=relationId;
_petId=petId;
_clientId=clientId;
_owner=owner;

}

void PetRelations::setPetId(int id) {_petId=id;}
void PetRelations::setClientId(int id) {_clientId=id;}
void PetRelations::setOwner(bool owner) {_owner=owner;}
void PetRelations::setRelationId (int rid){_relationId=rid;}
void PetRelations::setEstatus (bool est){_estatus=est;}

int PetRelations::getPetId() {return _petId; }
int PetRelations::getClientId() {return _clientId; }
bool PetRelations::getOwner() {return _owner;}
int PetRelations::getRelationId (){return _relationId;}
bool PetRelations::getEstatus(){return _estatus;}

void PetRelations::toVecString(std::string vStr[4]) {
    vStr[0] = std::to_string(_relationId);
    vStr[1] = std::to_string(_petId);
    vStr[2] = std::to_string(_clientId);
    vStr[3] = _owner;

}
