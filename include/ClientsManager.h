#ifndef CLIENTSMANAGER_INCLUDED
#define CLIENTSMANAGER_INCLUDED

#include "Client.h"
#include "VppFile.h"

class ClientsManager {
private:
    VppFile<Client> _clientsFile = VppFile<Client>("clients.vpp");
    const int _clientsFields = 7;  // total de datos de un regisro Client
    Client loadForm();
    Client editForm(int regPos);
    int  getClientSearched();
    int deleteFounded();
  

public:
    void load();
    void edit();
     void show(bool showAndPause = true);
    void clearSearched();
    void clearDeleted();
    void cancel();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "ClientsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(Client reg, int nId);

    bool idExists(int nId);
};

#endif /* CLIENTSMANAGER_INCLUDED */
