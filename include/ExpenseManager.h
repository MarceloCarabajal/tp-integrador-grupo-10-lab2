#pragma once

#include "Expense.h"
#include "VppFile.h"

class ExpenseManager {
private:
    VppFile<Expense> _expenseFile = VppFile<Expense>("expenses.vpp");
    const int _expenseFields = 7;  // total de datos de un registro Income
    Expense loadForm();
    Expense editForm(int regPos);

public:
    void load();
    void edit();
    void show();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "ExpenseManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(Expense reg, int nId);

    bool idExists(int nId);
};
