#pragma once

#include "Vaccination.h"
#include "VppFile.h"

class VaccinationManager {
private:
    VppFile<Vaccination> _vaccinationFile = VppFile<Vaccination>("vaccinations.vpp");
    const int _vaccinationFields = 6;  // total de datos de un regisro Client
    Vaccination loadForm();
    Vaccination editForm(int regPos);
   bool retryIfIdExists(bool exists);
    bool retryIfIdNotExists(bool exists);

public:
    void load();
    void edit();
    void show();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "ClientsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(Vaccination reg, int nId);

    bool idExists(int nId);
};
