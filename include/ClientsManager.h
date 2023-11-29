#ifndef CLIENTSMANAGER_INCLUDED
#define CLIENTSMANAGER_INCLUDED

#include "Client.h"
#include "VppConfigManager.h"
#include "VppFile.h"

class ClientsManager {
private:
    const std::string _folderPath = VppConfigManager().getDataPath();
    const std::string _filePath = _folderPath + "Clients.vpp";
    VppFile<Client> _clientsFile = VppFile<Client>(_filePath);
    const int _clientsFields = 7;  // total de datos de un regisro Client
    Client loadForm();
    Client editForm(int regPos);
    int getClientSearched();
    int deleteFounded();

public:
    void load();
    void edit();
    void show(bool showAndPause = true);
    void clearSearched();
    void clearDeleted();
    void cancel();
    std::string getFullNameById(int nId);

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "ClientsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(Client reg, int nId);

    bool idExists(int nId);
    bool isActiveId(int nId);
};

#endif /* CLIENTSMANAGER_INCLUDED */
