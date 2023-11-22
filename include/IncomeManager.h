#pragma once
#include "Income.h"
#include "VppFile.h"

class IncomeManager {
private:
    VppFile<Income> _incomeFile = VppFile<Income>("incomes.vpp");
    const int _incomesFields = 7;  // total de datos de un registro Income
    Income loadForm();
    Income editForm(int regPos);

public:
    void load();
    void edit();
    void show();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "IncomeManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(Income reg, int nId);

    bool idExists(int nId);
};
