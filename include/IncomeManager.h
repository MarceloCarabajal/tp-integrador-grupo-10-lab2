#pragma once
#include "Income.h"
#include "VppConfigManager.h"
#include "VppFile.h"

class IncomeManager {
private:
    const std::string _folderPath = VppConfigManager().getDataPath();
    const std::string _filePath = _folderPath + "Incomes.vpp";
    VppFile<Income> _incomeFile = VppFile<Income>(_filePath);
    const int _incomesFields = 7;  // total de datos de un registro Income
    Income loadForm();
    Income editForm(int regPos);

public:
    void load();
    void edit();
    void show(bool showAndPause = true);

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "IncomeManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(Income reg, int nId);

    bool idExists(int nId);
};
