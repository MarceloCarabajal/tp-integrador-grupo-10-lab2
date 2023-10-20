#pragma once
#include <string>

class PetRelations {

private:
int _petId;
int  _clientId;
bool _owner;


public: 

void setPetId(int id);
void setClientId( int id) ;
void  setOwner( bool owner);

int  getPetId();
int  getClientId();
bool  getOwner();


};