#pragma once

#include "PetRelations.h"
#include "VppFile.h"

class RelationsManager {
private:
    VppFile<PetRelations> _petRelationsFile = VppFile<PetRelations>("PetRelations.vpp");
    const int _petRelationsFields = 3;  // total de datos de un regisro PetRelations
    PetRelations loadForm();
    PetRelations editForm(int regPos);

public:
    void load();
    void edit();
    void show();
    void menu();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "RelationsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(PetRelations reg, int nId);
};

