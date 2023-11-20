#include "SalesManager.h"

#include <iostream>
// VppFile<Sale> _salesFile = VppFile<Sale>("sales.vpp"); _salesFields
#include "InputForm.h"
#include "ListView.h"
#include "rlutil.h"

void SalesManager::load() {
    InputForm idForm;
    Sale auxSale;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id ingresado existe
    do {
        if (alreadyExists) {
            std::cout << "El ID de la venta ya existe, presione cualquier tecla "
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
    if (auxSale.getSaleId() == 0) return;

   auxSale.setSaleId(nId);  // set del Id ingresado anteriormente
    if (_salesFile.writeFile(auxSale)) {
        std::cout << "Venta guardada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar la venta.\n";
    }
}

Sale SalesManager::loadForm() {
    InputForm saleForm;
    Sale auxSale;
    std::string paymentMethod;
    int  transactionId;
    float totalAmount;
    Date saleDate;
    Time saleTime;
    bool isVisit;

    saleForm.setIntField("Id Transaccion", transactionId, 4);
    saleForm.setDateField("Fecha", saleDate);
    ////saleForm.setAlphanumeric("Hora, saleTime, 45);
    saleForm.setStrField("Metodo Pago", paymentMethod, 15);
    saleForm.setFloatField("Total", totalAmount);
    saleForm.setBoolField ("¿Es Consulta?", isVisit)


    if (!saleForm.fill()) return auxSale;

   auxSale.setPaymentMethod(paymentMethod);
   auxSale.setTransactionId(transactionId);
   auxSale.setDate(saleDate);
   auxSale.setTime(saleTime);
   auxSale.setAmount(totalAmount);
    return auxSale;
}

// Solo compara si coincide el id
bool SalesManager::searchById(Sale reg, int nId) {
    if (reg.getSaleId() == nId) return true;
    return false;
}

Sale SalesManager::editForm(int regPos) {
    InputForm saleForm;
    Sale auxSale;
     std::string paymentMethod;
    int  quantit, transactionId, nId;
    float totalAmount;
    Date saleDate;
    Time saleTime;
    bool isVisit;
    
    
   

   auxSale = _salesFile.readFile(regPos);
    if (auxSale.getSaleId() == 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxSale;
    }
    // Se cargan los datos para mostrarlas en el form.
    transactionId =auxSale.getTransactionId();
    paymentMethod =auxSale.getPaymentMethod();
    saleDate =auxSale.getDate();
    nId =auxSale.getSaleId();
    saleTime =auxSale.getTime();
    isVisit =auxSale.getIsVisit();
  
    std::cout << "Editando Venta #" << nId << std::endl;
    // configurar form
    saleForm.setEditMode(true);  // modo edicion
    saleForm.setIntField("Id Transaccion", transactionId, 4);    ////TODO: DEBERIA VENIR AUTOMATICO
    saleForm.setDateField("Fecha", saleDate);
    saleForm.setStrField("Metodo Pago", paymentMethod, 15);
    saleForm.setFloatField("Total", totalAmount);
    saleForm.setBoolField ("¿Es Consulta?", isVisit);
 ////TODO: saleForm.setHORARIO("Hora, saleTime, 45);


    // completar form
    bool success = saleForm.fill();
    if (success) {  // si se completa
       auxSale.setPaymentMethod(paymentMethod);
       auxSale.setTransactionId(transactionId);
        auxSale.setDate(saleDate);
        auxSale.setTime(saleTime);
        auxSale.setAmount(totalAmount);
        return auxSale;
    }
    // si no se completa, devolver Venta vacia
    return auxSale;
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
        system("pause");  // TODO: usar rlutil ?
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
        std::string vecStr[7];
       auxSale.toVecString(vecStr);
        for (int cell = 0; cell < _salesFields; cell++) {
            cells[cellPos + cell] = vecStr[cell];
        }
        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        cellPos += _salesFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[8] = {"ID Sale",      "ID Transaccion", "Total $",
                              "Metodo de pago", "Fecha", "Hora", "¿Es Consulta?"};


    ListView salesList;
    salesList.addCells(cells, totalCells);
    salesList.addCols(columns, 7);
    salesList.setTitle("VENTAS");
    salesList.show();
    delete[] cells;  // liberar memoria!
}