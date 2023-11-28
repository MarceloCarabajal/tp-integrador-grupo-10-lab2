#pragma once

#include "Pet.h"
#include "VppFile.h"

class PetsManager {
private:
    VppFile<Pet> _petsFile = VppFile<Pet>("Pets.vpp");
    const int _petsFields = 7;  // total de datos de un regisro Pet
    Pet loadForm();
    Pet editForm(int regPos);
    bool retryIfIdNotExists(bool exists);

public:
    void load();
    void edit();
    void show(bool showAndPause = true);
    void clearDeleted();
    void cancel();

    bool updateOwner(int ownerId, int petId);

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "PetsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(Pet reg, int nId);

    bool idExists(int nId);
};
