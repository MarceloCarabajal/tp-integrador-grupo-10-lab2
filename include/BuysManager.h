#pragma once

#include "Buy.h"
#include "VppFile.h"

class BuysManager {
private:
    VppFile<Buy> _buysFile = VppFile<Buy>("Buys.vpp");
    const int _buysFields = 8;  // total de datos de un regisro Buy
    Buy loadForm();
    Buy editForm(int regPos);
    bool retryIfIdNotExists(bool exists);

public:
    void load();
    void edit();
    void show(bool showAndPause = true);
    void clearDeleted();
    void cancel();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "BuysManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(Buy reg, int nId);

    bool idExists(int nId);
};
