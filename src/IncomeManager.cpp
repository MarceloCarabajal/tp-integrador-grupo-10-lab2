#include "IncomeManager.h"

#include <iostream>

#include "InputForm.h"
#include "ListView.h"
#include "rlutil.h"
#include "utils.h"

void IncomeManager::load() {
    InputForm idForm;
    Income auxIncome;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id ingresado existe
    do {
        if (alreadyExists) {
            std::cout
                << "El ID del ingreso ya existe, presione cualquier tecla "
                   "para reintentar o ESC para salir.\n";
            if (rlutil::getkey() == rlutil::KEY_ESCAPE) return;
            rlutil::cls();
        }
        idForm.setIntField("ID Ingreso", nId, 4);
        // si no completa el form, salir
        if (!idForm.fill()) return;
        alreadyExists =
            _incomeFile.searchReg(searchById, nId) >= 0 ? true : false;
        idForm.clearAll();  // limpiar form
    } while (alreadyExists);

    auxIncome = loadForm();
    // Si no se completo el form, salir
    if (auxIncome.getIdTransaction() == -1) return;

    auxIncome.setIdTransaction(nId);  // set del Id ingresado anteriormente
    if (_incomeFile.writeFile(auxIncome)) {
        std::cout << "Ingreso guardado con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el ingreso.\n";
    }
}

Income IncomeManager::loadForm() {
    InputForm incomeForm;
    Income auxIncome;
    std::string description, paymentMethod;
    int saleId;
    Date transDate;
    Time transTime;
    float amount;

    incomeForm.setStrField("Descripción", description, 45);
    incomeForm.setStrField("Metodo de pago", paymentMethod, 15);
    incomeForm.setDateField("Fecha", transDate);
    /////incomeForm.setTIME(phone, 15);
    incomeForm.setIntField("ID Venta", saleId, 4);
    incomeForm.setFloatField("Total", amount);

    if (!incomeForm.fill()) return auxIncome;

    auxIncome.setDescription(description);
    auxIncome.setPaymentMethod(paymentMethod);
    auxIncome.setDateTrans(transDate);
    auxIncome.setTimeTrans(transTime);
    auxIncome.setAmount(amount);
    auxIncome.setSaleId(saleId);

    return auxIncome;
}

// Solo compara si coincide el id
bool IncomeManager::searchById(Income reg, int nId) {
    if (reg.getIdTransaction() == nId) return true;
    return false;
}

Income IncomeManager::editForm(int regPos) {
    InputForm incomeForm;
    Income auxIncome;
    std::string description, paymentMethod;
    int saleId, nId;
    Date transDate;
    Time transTime;
    float amount;

    auxIncome = _incomeFile.readFile(regPos);
    if (auxIncome.getIdTransaction() == -1) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxIncome;
    }
    // Se cargan los datos para mostrarlas en el form.

    description = auxIncome.getDescription();
    paymentMethod = auxIncome.getPaymentMehod();
    nId = auxIncome.getIdTransaction();
    transDate = auxIncome.getDateTrans();
    transTime = auxIncome.getTimeTrans();
    amount = auxIncome.getAmount();
    saleId = auxIncome.getSaleId();

    std::cout << "Editando ingreso #" << nId << std::endl;
    // configurar form
    incomeForm.setEditMode(true);  // modo edicion

    incomeForm.setStrField("Descripción", description, 45);
    incomeForm.setStrField("Metodo de pago", paymentMethod, 15);
    incomeForm.setDateField("Fecha", transDate);
    /////incomeForm.setTIME(phone, 15);
    incomeForm.setIntField("ID Venta", saleId, 4);
    /// incomeForm.setFloatField("Total", amount,XXXXXXXX );

    // completar form
    bool success = incomeForm.fill();
    if (success) {  // si se completa
        auxIncome.setDescription(description);
        auxIncome.setPaymentMethod(paymentMethod);
        auxIncome.setDateTrans(transDate);
        auxIncome.setTimeTrans(transTime);
        auxIncome.setAmount(amount);
        auxIncome.setSaleId(saleId);
        return auxIncome;
    }
    // si no se completa, devolver Ingreso vacio
    return auxIncome;
}

void IncomeManager::edit() {
    InputForm search;
    int nId;
    show();
    std::cout << "\nIngrese el ID de la transacción a modificar.\n";
    search.setIntField("ID Transacción", nId, 4);
    if (!search.fill()) return;  // si no se completa, salir
    int regPos = _incomeFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No se encontraron resultados.\n";
        utils::pause();
        return;
    }
    // Si se encontro, pedir datos
    Income auxIncome = editForm(regPos);
    // Si no se completo el formulario, salir
    if (auxIncome.getIdTransaction() == 0) {
        std::cout << "No se realizara la edicion.\n";
        utils::pause();
        return;
    }

    // guardar ingreso actualizado
    if (_incomeFile.updateFile(auxIncome, regPos)) {
        std::cout << "Ingreso editado con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    utils::pause();
}

void IncomeManager::show() {
    int totalRegs = _incomeFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _incomesFields;

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
        Income auxIncome = _incomeFile.readFile(i);
        // Obtener todas las propiedades del cliente
        // Guardarlas en un vector de string
        std::string vecStr[7];
        auxIncome.toVecString(vecStr);
        for (int cell = 0; cell < _incomesFields; cell++) {
            cells[cellPos + cell] = vecStr[cell];
        }
        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        cellPos += _incomesFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[7] = {"ID Transaccion", "Id Venta",    "Fecha",
                              "Hora",           "Descripción", "Total",
                              "Metodo de pago"};

    ListView incomesList;
    incomesList.addCells(cells, totalCells);
    incomesList.addCols(columns, 7);
    incomesList.setTitle("INGRESOS");
    incomesList.show();

    delete[] cells;  // liberar memoria!
}