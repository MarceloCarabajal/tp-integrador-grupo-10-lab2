#include "PetRelations.h"

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

