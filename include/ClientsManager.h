#ifndef CLIENTSMANAGER_INCLUDED
#define CLIENTSMANAGER_INCLUDED

#include "Client.h"
#include "VppFile.h"

class ClientsManager {
private:
    VppFile<Client> _clientsFile = VppFile<Client>("clients.vpp");
    const int _clientsFields = 6;  // cantidad de datos que guardan

public:
    void load();
    void show();
};

#endif /* CLIENTSMANAGER_INCLUDED */
