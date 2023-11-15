#pragma once
#include <string>

class PetRelations {

private:
int _relationId;
int _petId;
int  _clientId;
bool _owner;
bool _estatus;


public: 

void setPetId(int id);
void setClientId( int id) ;
void  setOwner( bool owner);
void setRelationId (int rid);
void setEstatus (bool est);

int  getPetId();
int  getClientId();
bool  getOwner();
int getRelationId ();
bool getEstatus ();

};