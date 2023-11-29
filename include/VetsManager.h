#pragma once

#include "Vet.h"
#include "VppConfigManager.h"
#include "VppFile.h"

class VetsManager {
private:
    const std::string _folderPath = VppConfigManager().getDataPath();
    const std::string _filePath = _folderPath + "Vets.vpp";
    VppFile<Vet> _vetsFile = VppFile<Vet>(_filePath);
    const int _vetsFields = 5;  // total de datos de un regisro Pet
    Vet loadForm();
    Vet editForm(int regPos);

public:
    void load();
    void edit();
    void show(bool showAndPause = true);
    void clearDeleted();
    void cancel();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "VetsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(Vet reg, int nId);

    bool idExists(int nId);
};
