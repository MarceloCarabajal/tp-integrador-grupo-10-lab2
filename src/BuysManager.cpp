#include "BuysManager.h"

#include <iostream>

#include "InputForm.h"
#include "ListView.h"
#include "rlutil.h"
#include "utils.h"

void BuysManager::load() {
    InputForm idForm;
    Buy auxBuy;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id ingresado existe
    do {
        if (alreadyExists) {
            std::cout
                << "El ID de la compra ya existe, presione cualquier tecla "
                   "para reintentar o ESC para salir.\n";
            if (rlutil::getkey() == rlutil::KEY_ESCAPE) return;
            rlutil::cls();
        }
        idForm.setIntField("ID Compra", nId, 4);
        // si no completa el form, salir
        if (!idForm.fill()) return;
        alreadyExists =
            _buysFile.searchReg(searchById, nId) >= 0 ? true : false;
        idForm.clearAll();  // limpiar form
    } while (alreadyExists);

    auxBuy = loadForm();
    // Si no se completo el form, salir
    if (auxBuy.getProductId() == -1) return;

    auxBuy.setBuyId(nId);  // set del Id ingresado anteriormente
    if (_buysFile.writeFile(auxBuy)) {
        std::cout << "Compra guardado con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar la compra\n";
    }
}

Buy BuysManager::loadForm() {
    InputForm buyForm;
    Buy auxBuy;
    std::string paymentMethod;
    int productId, quantity, trxId;
    float totalAmount;
    Date buyDate;
    Time buyTime;

    buyForm.setStrField("Metodo Pago", paymentMethod, 15);
    buyForm.setIntField("ID producto", productId, 4);
    //// este numero se copia en los objetos de la clase transaccion
    // TODO: Este es el que se tiene que generar solo?
    buyForm.setIntField("ID Transacción", trxId, 4);
    buyForm.setRangeField("Cantidad", quantity, 1, 1000);
    buyForm.setFloatField("Total", totalAmount);
    buyForm.setDateField("Fecha", buyDate);
    ////saleForm.setAlphanumeric("Hora, buyTime, 45);//TODO: hace falta la hora?

    if (!buyForm.fill()) return auxBuy;

    auxBuy.setpaymentMethod(paymentMethod);
    auxBuy.setProductId(productId);
    auxBuy.setTransactionId(trxId);
    auxBuy.setQuantity(quantity);
    auxBuy.setDate(buyDate);
    auxBuy.setTime(buyTime);
    return auxBuy;
}

Buy BuysManager::editForm(int regPos) {
    InputForm buyForm;
    Buy auxBuy, auxFormBuy;
    std::string paymentMethod;
    int nId, productId, quantity, transactionId;
    float totalAmount;
    Date buyDate;
    Time buyTime;

    auxBuy = _buysFile.readFile(regPos);
    if (auxBuy.getBuyId() == -1) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxBuy;
    }
    // Se cargan los datos para mostrarlas en el form.

    transactionId = auxBuy.getTransactionId();
    productId = auxBuy.getProductId();
    nId = auxBuy.getBuyId();
    buyDate = auxBuy.getbuyDate();
    buyTime = auxBuy.getbuyTime();
    totalAmount = auxBuy.getTotalAmount();
    quantity = auxBuy.getQuantity();
    paymentMethod = auxBuy.getPaymentMethod();

    std::cout << "Editando compra #" << nId << std::endl;
    // configurar form
    buyForm.setEditMode(true, true);  // modo edicion

    buyForm.setStrField("Metodo Pago", paymentMethod, 15);
    buyForm.setIntField("ID producto", productId, 4);
    buyForm.setIntField(
        "ID Transacción", transactionId,
        4);  //// este numero se copia en los objetos de la clase transaccion
    buyForm.setRangeField("Cantidad", quantity, 1, 1000);
    buyForm.setFloatField("Total", totalAmount);
    buyForm.setDateField("Fecha", buyDate);
    /// saleForm.setAlphanumeric("Hora, buyTime, 45);//TODO:

    // completar form
    bool success = buyForm.fill();
    if (success) {  // si se completa

        auxFormBuy.setBuyId(nId);
        auxFormBuy.setpaymentMethod(paymentMethod);
        auxFormBuy.setProductId(productId);
        auxFormBuy.setTransactionId(transactionId);
        auxFormBuy.setQuantity(quantity);
        auxFormBuy.setDate(buyDate);
        auxFormBuy.setTime(buyTime);

        return auxFormBuy;
    }
    // si no se completa, devolver Compra vacia
    return auxFormBuy;
}

void BuysManager::edit() {
    InputForm search;
    int nId;
    show();
    std::cout << "\nIngrese el ID de la compra a modificar.\n";
    search.setIntField("ID Compra", nId, 4);
    if (!search.fill()) return;  // si no se completa, salir
    int regPos = _buysFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No se encontraron resultados.\n";
        utils::pause();
        return;
    }
    // Si se encontro, pedir datos
    Buy auxBuy = editForm(regPos);
    // Si no se completo el formulario, salir
    if (auxBuy.getBuyId() == -1) {
        std::cout << "No se realizara la edicion.\n";
        utils::pause();
        return;
    }

    // guardar compra actualizada
    if (_buysFile.updateFile(auxBuy, regPos)) {
        std::cout << "Compra editada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    utils::pause();
}

void BuysManager::show() {
    int totalRegs = _buysFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _buysFields;

    if (totalRegs < 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        utils::pause();
        return;
    }
    // Se crea la variable que va a contener todas las celdas, segun la cantidad
    // de registros
    std::string *cells = new std::string[totalCells];
    if (cells == NULL) {
        std::cout << "No hay memoria suficiente para mostrar las compras.\n";
        return;
    }
    int cellPos = 0;  // acumula la posicion actual a asignar
    for (int i = 0; i < totalRegs; i++) {
        Buy auxBuy = _buysFile.readFile(i);
        // Obtener todas las propiedades de la compra
        // Guardarlas en un vector de string
        std::string vecStr[8];
        auxBuy.toVecString(vecStr);
        for (int cell = 0; cell < _buysFields; cell++) {
            cells[cellPos + cell] = vecStr[cell];
        }
        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        cellPos += _buysFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[8] = {
        "ID",      "ID producto",    "Cantidad", "Id Transaccion",
        "Total $", "Metodo de pago", "Fecha",    "Hora"};

    ListView buysList;
    buysList.addCells(cells, totalCells);
    buysList.addCols(columns, 8);
    buysList.setTitle("COMPRAS");
    buysList.show();

    delete[] cells;  // liberar memoria!
}

// Solo compara si coincide el id
bool BuysManager::searchById(Buy reg, int nId) {
    if (reg.getBuyId() == nId) return true;
    return false;
}

bool BuysManager::idExists(int nId) {
    return _buysFile.searchReg(searchById, nId) >= 0 ? true : false;
}