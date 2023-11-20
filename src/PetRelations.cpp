#include "PetRelations.h"

PetRelations::PetRelations() {
    _relationId = -1;
    _petId = -1;
    _clientId = -1;
    _owner = false;
    _status = false;
}
PetRelations::PetRelations(int relationId, int petId, int clientId, bool owner,
                           bool status) {
    _relationId = relationId;
    _petId = petId;
    _clientId = clientId;
    _owner = owner;
    _status = status;
}

void PetRelations::setPetId(int id) { _petId = id; }
void PetRelations::setClientId(int id) { _clientId = id; }
void PetRelations::setOwner(bool owner) { _owner = owner; }
void PetRelations::setRelationId(int rid) { _relationId = rid; }
void PetRelations::setStatus(bool st) { _status = st; }

int PetRelations::getPetId() { return _petId; }
int PetRelations::getClientId() { return _clientId; }
bool PetRelations::getOwner() { return _owner; }
int PetRelations::getRelationId() { return _relationId; }
bool PetRelations::getStatus() { return _status; }

void PetRelations::toVecString(std::string vStr[4]) {
    vStr[0] = std::to_string(_relationId);
    vStr[1] = std::to_string(_petId);
    vStr[2] = std::to_string(_clientId);
    vStr[3] = _owner;
}
