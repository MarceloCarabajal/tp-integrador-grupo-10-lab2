#pragma once

#include "Vet.h"
#include "VppFile.h"

class VetsManager {
private:
    VppFile<Vet> _vetsFile = VppFile<Vet>("Vets.vpp");
    const int _vetsFields = 5;  // total de datos de un regisro Pet
    Vet loadForm();
    Vet editForm(int regPos);

public:
    void load();
    void edit();
    void show();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "VetsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(Vet reg, int nId);
};
