#pragma once

#include "VetVisits.h"
#include "VppConfigManager.h"
#include "VppFile.h"

class VetVisitsManager {
private:
    const std::string _folderPath = VppConfigManager().getDataPath();
    const std::string _filePath = _folderPath + "VetVisits.vpp";
    VppFile<VetVisits> _vetVisitsFile = VppFile<VetVisits>(_filePath);
    const int _vetVisitsFields = 9;  // total de datos de un regisro VetVisit
    VetVisits loadForm();
    VetVisits editForm(int regPos);
    bool retryIfIdExists(bool exists);
    bool retryIfIdNotExists(bool exists, bool isActive);

public:
    void load();
    void edit();
    void show(bool showAndPause = true);
    void menu();
    void clearDeleted();
    void cancel();
    
    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "VetVisitsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(VetVisits reg, int nId);

    bool idExists(int nId);
    bool isActiveId(int nId);
};
