#pragma once

#include "PetRelations.h"
#include "VppConfigManager.h"
#include "VppFile.h"

class RelationsManager {
private:
    const std::string _folderPath = VppConfigManager().getDataPath();
    const std::string _filePath = _folderPath + "PetRelations.vpp";
    VppFile<PetRelations> _petRelationsFile = VppFile<PetRelations>(_filePath);
    // relId, petId, clientId, owner?, clientName, petName = 6
    const int _petRelationsFields = 6;  // total de datos a mostrar en ListView
    PetRelations loadForm();
    PetRelations editForm(int regPos);
    bool retryIfIdExists(bool exists);
    bool retryIfIdNotExists(bool exists);
    bool newOwner(int petId, int clientId);

public:
    void load();
    void edit();
    void show(bool showAndPause = true);
    bool updateRelation(PetRelations petR, int regPos);
    void deleteRel();

    int autogenerateNew(int clientId, int petId);

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "RelationsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(PetRelations reg, int nId);
    static bool searchRelation(PetRelations reg, int petId, int clientId);

    bool relationExists(int petId, int clientId);
    PetRelations searchGetRelation(int petId, int clientId);
    bool idExists(int nId);
};
