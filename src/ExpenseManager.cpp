#include "ExpenseManager.h"

#include <iostream>

#include "InputForm.h"
#include "ListView.h"
#include "rlutil.h"
#include "utils.h"

void ExpenseManager::load() {
    InputForm idForm;
    Expense auxExpense;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id ingresado existe
    do {
        if (alreadyExists) {
            std::cout << "El ID del gasto ya existe, presione cualquier tecla "
                         "para reintentar o ESC para salir.\n";
            if (rlutil::getkey() == rlutil::KEY_ESCAPE) return;
            rlutil::cls();
        }
        idForm.setIntField("ID Egreso", nId, 4);
        // si no completa el form, salir
        if (!idForm.fill()) return;
        alreadyExists =
            _expenseFile.searchReg(searchById, nId) >= 0 ? true : false;
        idForm.clearAll();  // limpiar form
    } while (alreadyExists);

    auxExpense = loadForm();
    // Si no se completo el form, salir
    if (auxExpense.getIdTransaction() == -1) return;

    auxExpense.setIdTransaction(nId);  // set del Id ingresado anteriormente
    if (_expenseFile.writeFile(auxExpense)) {
        std::cout << "Ingreso guardado con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el ingreso.\n";
    }
}

Expense ExpenseManager::loadForm() {
    InputForm expenseForm;
    Expense auxExpense;
    std::string description, paymentMethod;
    int buyId;
    Date transDate;
    Time transTime;
    float amount;

    expenseForm.setStrField("Descripción", description, 45);
    expenseForm.setStrField("Metodo de pago", paymentMethod, 15);
    expenseForm.setDateField("Fecha", transDate);
    /////expenseForm.setTIME(phone, 15);
    expenseForm.setIntField("ID Gasto", buyId, 4);
    expenseForm.setFloatField("Total", amount);

    if (!expenseForm.fill()) return auxExpense;

    auxExpense.setDescription(description);
    auxExpense.setPaymentMethod(paymentMethod);
    auxExpense.setDateTrans(transDate);
    auxExpense.setTimeTrans(transTime);
    auxExpense.setAmount(amount);
    auxExpense.setBuyId(buyId);

    return auxExpense;
}

Expense ExpenseManager::editForm(int regPos) {
    InputForm expenseForm;
    Expense auxExpense, auxFormExpense;
    std::string description, paymentMethod;
    int buyId, nId;
    Date transDate;
    Time transTime;
    float amount;

    auxExpense = _expenseFile.readFile(regPos);
    if (auxExpense.getIdTransaction() == -1) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxExpense;
    }
    // Se cargan los datos para mostrarlas en el form.

    description = auxExpense.getDescription();
    paymentMethod = auxExpense.getPaymentMehod();
    nId = auxExpense.getIdTransaction();
    transDate = auxExpense.getDateTrans();
    transTime = auxExpense.getTimeTrans();
    amount = auxExpense.getAmount();
    buyId = auxExpense.getBuyId();

    std::cout << "Editando egreso #" << nId << std::endl;
    // configurar form
    expenseForm.setEditMode(true);  // modo edicion

    expenseForm.setStrField("Descripción", description, 45);
    expenseForm.setStrField("Metodo de pago", paymentMethod, 15);
    expenseForm.setDateField("Fecha", transDate);
    /////expenseForm.setTIME(phone, 15);
    expenseForm.setIntField("ID Egreso", buyId, 4);
    expenseForm.setFloatField("Total", amount);

    // completar form
    bool success = expenseForm.fill();
    if (success) {  // si se completa
        auxFormExpense.setDescription(description);
        auxFormExpense.setPaymentMethod(paymentMethod);
        auxFormExpense.setDateTrans(transDate);
        auxFormExpense.setTimeTrans(transTime);
        auxFormExpense.setAmount(amount);
        auxFormExpense.setBuyId(buyId);
        return auxFormExpense;
    }
    // si no se completa, devolver Ingreso vacio
    return auxFormExpense;
}

void ExpenseManager::edit() {
    InputForm search;
    int nId;
    show();
    std::cout << "\nIngrese el ID de la transacción a modificar.\n";
    search.setIntField("ID Transacción", nId, 4);
    if (!search.fill()) return;  // si no se completa, salir
    int regPos = _expenseFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No se encontraron resultados.\n";
        utils::pause();
        return;
    }
    // Si se encontro, pedir datos
    Expense auxExpense = editForm(regPos);
    // Si no se completo el formulario, salir
    if (auxExpense.getIdTransaction() == -1) {
        std::cout << "No se realizara la edicion.\n";
        utils::pause();
        return;
    }

    // guardar ingreso actualizado
    if (_expenseFile.updateFile(auxExpense, regPos)) {
        std::cout << "Egreso editado con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    utils::pause();
}

void ExpenseManager::show() {
    int totalRegs = _expenseFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _expenseFields;

    if (totalRegs < 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        utils::pause();
        return;
    }
    // Se crea la variable que va a contener todas las celdas, segun la cantidad
    // de registros
    std::string *cells = new std::string[totalCells];
    if (cells == NULL) {
        std::cout
            << "No hay memoria suficiente para mostrar las transacciones.\n";
        return;
    }
    int cellPos = 0;  // acumula la posicion actual a asignar
    for (int i = 0; i < totalRegs; i++) {
        Expense auxExpense = _expenseFile.readFile(i);
        // Obtener todas las propiedades del cliente
        // Guardarlas en un vector de string
        std::string vecStr[7];
        auxExpense.toVecString(vecStr);
        for (int cell = 0; cell < _expenseFields; cell++) {
            cells[cellPos + cell] = vecStr[cell];
        }
        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        cellPos += _expenseFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[7] = {"ID Transaccion", "Id Gasto",    "Fecha",
                              "Hora",           "Descripción", "Total",
                              "Metodo de pago"};

    ListView expensesList;
    expensesList.addCells(cells, totalCells);
    expensesList.addCols(columns, 7);
    expensesList.setTitle("EGRESOS");
    expensesList.show();

    delete[] cells;  // liberar memoria!
}

// Solo compara si coincide el id
bool ExpenseManager::searchById(Expense reg, int nId) {
    if (reg.getIdTransaction() == nId) return true;
    return false;
}

bool ExpenseManager::idExists(int nId) {
    return _expenseFile.searchReg(searchById, nId) >= 0 ? true : false;
}