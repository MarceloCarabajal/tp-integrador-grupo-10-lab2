#pragma once
#include <string>

class PetRelations {
private:
    int _relationId;
    int _petId;
    int _clientId;
    bool _owner;
    bool _status;

public:
    PetRelations();
    PetRelations(int relationId, int petId, int clientId, bool ownwer,
                 bool status);

    void setPetId(int id);
    void setClientId(int id);
    void setOwner(bool owner);
    void setRelationId(int rid);
    void setStatus(bool est);

    int getPetId();
    int getClientId();
    bool getOwner();
    int getRelationId();
    bool getStatus();

    void toVecString(std::string vStr[4]);
};