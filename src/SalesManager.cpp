#include "SalesManager.h"

#include <iostream>
// VppFile<Sale> _salesFile = VppFile<Sale>("sales.vpp"); _salesFields
#include "InputForm.h"
#include "ListView.h"
#include "rlutil.h"
#include "ItemSale.h"

void SalesManager::load() {
    InputForm idForm;
    Sale auxSale;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id ingresado existe
    do {
        if (alreadyExists) {
            std::cout
                << "El ID de la venta ya existe, presione cualquier tecla "
                   "para reintentar o ESC para salir.\n";
            if (rlutil::getkey() == rlutil::KEY_ESCAPE) return;
            rlutil::cls();
        }
        idForm.setIntField("ID Venta", nId, 4);
        // si no completa el form, salir
        if (!idForm.fill()) return;
        alreadyExists =
            _salesFile.searchReg(searchById, nId) >= 0 ? true : false;
        idForm.clearAll();  // limpiar form
    } while (alreadyExists);

    auxSale = loadForm();
    // Si no se completo el form, salir
    if (auxSale.getTransactionId() == -1) return;

    auxSale.setSaleId(nId);  // set del Id ingresado anteriormente
    if (_salesFile.writeFile(auxSale)) {
        std::cout << "Venta guardada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar la venta.\n";
    }
}

Sale SalesManager::loadForm() {
    InputForm saleForm, dateForm, consultForm;
    Sale auxSale;
    int transactionId, paymentMethod;
    float totalAmount;
    Date saleDate;
    bool isVisit;

    saleForm.setIntField("Id Transaccion", transactionId, 4);
    dateForm.setDateField("Fecha", saleDate);

    bool validDate = false;
    while (!validDate) {
        if (!dateForm.fill()) return auxSale;
        validDate = validAppDate(saleDate);
        if (!retryInvalidDate(validDate)) return auxSale;
    }

    saleForm.setRangeField("Metodo Pago[1-3]", paymentMethod, 1, 3);
    saleForm.setFloatField("Total", totalAmount);

    if (!saleForm.fill()) return auxSale;

    consultForm.setBoolField("¿Es Consulta [SI/NO]?", isVisit);

    if (!consultForm.fill()) return auxSale;

    auxSale.setPaymentMethod(paymentMethod);
    auxSale.setTransactionId(transactionId);
    auxSale.setDate(saleDate);
    auxSale.setAmount(totalAmount);
    auxSale.setIsVisit(isVisit);
    return auxSale;

    // TODO: Una vez cargada la venta, hacer que se genere la transaccion de
    // INGRESO en el archivo correspondiente
}

Sale SalesManager::editForm(int regPos) {
    InputForm saleForm(true), dateForm(true), consultForm(true);
    Sale auxSale, auxFormSale;
    int transactionId, nId, paymentMethod;
    float totalAmount;
    Date saleDate;
    Time saleTime;
    bool isVisit;

    auxSale = _salesFile.readFile(regPos);
    if (auxSale.getSaleId() == -1) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxSale;
    }
    // Se cargan los datos para mostrarlas en el form.
    transactionId = auxSale.getTransactionId();
    paymentMethod = auxSale.getPaymentMethod();
    saleDate = auxSale.getDate();
    nId = auxSale.getSaleId();
    isVisit = auxSale.getIsVisit();

    rlutil::cls();  // limpiar pantalla

    std::cout << "Editando Venta #" << nId << std::endl;
    // configurar form

    saleForm.setIntField("Id Transaccion", transactionId,
                         4);  ////TODO: DEBERIA VENIR AUTOMATICO

    // pedir y validar fecha

    dateForm.setDateField("Fecha", saleDate);

    bool validDate = false;
    while (!validDate) {
        if (!dateForm.fill()) return auxFormSale;
        validDate = validAppDate(saleDate);
        if (!retryInvalidDate(validDate)) return auxFormSale;
        // si no fue una fecha valida, reasignar variable para mostrarla con el
        // valor actual
        if (!validDate) saleDate = auxFormSale.getDate();
    }

    saleForm.setRangeField("Metodo Pago[1-3] ", paymentMethod, 1, 3);
    saleForm.setFloatField("Total", totalAmount);
    consultForm.setBoolField("¿Es Consulta [SI/NO]?", isVisit);

    //TODO: VER LO SIGUIENTE


    /*
     (visit) --------- llamar a load item sale .
    si es visita deberia cargar un ID que tengamos en producto para la visita?
    si se vendio mas de un producto que se sigan cargando subitems 
    hacer que al finalizar la carga de la venta se genere automaticamente un "income"
    */

    if (!consultForm.fill()) return auxFormSale;

    // completar form
    bool success = saleForm.fill();

    if (success) {  // si se completa
        auxFormSale.setSaleId(nId);
        auxFormSale.setPaymentMethod(paymentMethod);
        auxFormSale.setTransactionId(transactionId);
        auxFormSale.setDate(saleDate);
        auxFormSale.setAmount(totalAmount);
        auxFormSale.setIsVisit(isVisit);

        return auxFormSale;
    }
    // si no se completa, devolver Venta vacia
    return auxFormSale;
}

void SalesManager::edit() {
    InputForm search;
    int nId;
    show();
    std::cout << "\nIngrese el ID de la venta a modificar.\n";
    search.setIntField("ID Venta", nId, 4);
    if (!search.fill()) return;  // si no se completa, salir
    int regPos = _salesFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No se encontraron resultados.\n";
        system("pause");
        return;
    }
    // Si se encontro, pedir datos
    Sale auxSale = editForm(regPos);
    // Si no se completo el formulario, salir
    if (auxSale.getSaleId() == 0) {
        std::cout << "No se realizara la edicion.\n";
        system("pause");
        return;
    }

    // guardar venta actualizada
    if (_salesFile.updateFile(auxSale, regPos)) {
        std::cout << "Venta editada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    system("pause");
}

void SalesManager::show() {
    int totalRegs = _salesFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _salesFields;

    if (totalRegs < 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        system("pause");
        return;
    }

    
    if (totalRegs == 0) {
        std::cout << "No hay registros para mostrar.\n";
        utils::pause();
        return;
    }
    // Se crea la variable que va a contener todas las celdas, segun la cantidad
    // de registros
    std::string *cells = new std::string[totalCells];
    if (cells == NULL) {
        std::cout << "No hay memoria suficiente para mostrar las ventas\n";
        return;
    }
    int cellPos = 0;  // acumula la posicion actual a asignar
    for (int i = 0; i < totalRegs; i++) {
        Sale auxSale = _salesFile.readFile(i);
        // Obtener todas las propiedades del cliente
        // Guardarlas en un vector de string
        std::string vecStr[6];
        auxSale.toVecString(vecStr);
        for (int cell = 0; cell < _salesFields; cell++) {
            cells[cellPos + cell] = vecStr[cell];
        }
        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        cellPos += _salesFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[6] = {"ID Sale", "ID Transaccion", "Metodo de pago",
                              "Fecha",   "Total $",      "¿Es Consulta?"};
    ListView salesList;
    salesList.addCells(cells, totalCells);
    salesList.addCols(columns, 6);
    salesList.setTitle("VENTAS");
    salesList.show();
    delete[] cells;  // liberar memoria!
}

// Solo compara si coincide el id
bool SalesManager::searchById(Sale reg, int nId) {
    if (reg.getSaleId() == nId) return true;
    return false;
}

bool SalesManager::idExists(int nId) {
    return _salesFile.searchReg(searchById, nId) >= 0 ? true : false;
}

bool SalesManager::validAppDate(Date date) {
    Date today;
    if (date < today || date == today) return true;
    return false;
}

bool SalesManager::retryInvalidDate(bool valid) {
    if (!valid) {
        std::cout
            << "La fecha debe ser menor o igual a la actual.\n"
               "Presione cualquier tecla para reintentar o ESC para salir.\n";
        if (rlutil::getkey() == rlutil::KEY_ESCAPE) return false;
        rlutil::cls();
    }
    return true;
}