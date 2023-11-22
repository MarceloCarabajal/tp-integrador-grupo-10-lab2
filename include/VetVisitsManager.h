#pragma once

#include "VetVisits.h"
#include "VppFile.h"

class VetVisitsManager {
private:
    VppFile<VetVisits> _vetVisitsFile = VppFile <VetVisits>("VetVisits.vpp");
    const int _vetVisitsFields = 8;  // total de datos de un regisro VetVisit
 VetVisits loadForm();
  VetVisits  editForm(int regPos);



public:
    void load();
    void edit();
    void show();
    void menu();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "VetVisitsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(VetVisits reg, int nId);
};
