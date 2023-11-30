#include "ItemSaleManager.h"

#include <iostream>

#include "InputForm.h"
#include "ListView.h"
#include "SalesManager.h"
#include "rlutil.h"
#include "utils.h"


void ItemSaleManager::load() {
    InputForm idForm;
    ItemSaleManager IsManager;
    ItemSale auxIs;

    auxIs = loadForm();
    // Si no se completo el form, salir
    if (auxIs.getQuantity() == 0) return;

    if (_itemSaleFile.writeFile(auxIs)) {
        std::cout << "item de venta guardada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el item.\n";
    }
}

ItemSale ItemSaleManager::loadForm() {
    InputForm itemForm, saleForm;
    ItemSale auxIs;
    SalesManager salesManager;
    int productId, quantity, saleId;
    float unitPrice;

    bool alreadyExists = true;

    // pedir y buscar si el id venta ingresado existe
    alreadyExists = true;
    saleForm.setIntField("ID Venta", saleId, 4);
    do {
        if (!retryIfIdNotExists(alreadyExists)) return auxIs;
        if (!saleForm.fill()) return auxIs;
        alreadyExists = salesManager.idExists(saleId);
    } while (!alreadyExists);

    itemForm.setIntField("id producto", productId, 4);
    itemForm.setRangeField("Cantidad [1-1000]", quantity, 1, 1000);
    itemForm.setFloatField("Precio Unitario", unitPrice);

    if (!itemForm.fill()) return auxIs;

    auxIs.setProductId(productId);
    auxIs.setUnitPrice(unitPrice);
    auxIs.setQuantity(quantity);
    auxIs.setSaleId(saleId);

    return auxIs;
}

bool ItemSaleManager::retryIfIdNotExists(bool exists) {
    if (!exists) {
        std::cout << "El ID ingresado NO EXISTE, presione cualquier tecla "
                     "para reintentar o ESC para salir.\n";
        if (rlutil::getkey() == rlutil::KEY_ESCAPE) return false;
        rlutil::cls();
    }
    return true;
}
/*
ItemSale ItemSaleManagereditForm(int regPos) {
    InputForm petForm(true), clientIdForm(true);
    Pet auxPet, auxFormPet;
    std::string name, specie, breed, currentDiagnosis;
    ClientsManager clientsManager;
    int nId, ownerId;
    Date birthDate;
    bool existentId, alreadyExists = true;

    auxPet = _petsFile.readFile(regPos);
    if (auxPet.getPetId() == -1) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxPet;
    }
    // Se cargan los datos para mostrarlas en el form.
    ownerId = auxPet.getOwnerId();
    name = auxPet.getName();
    specie = auxPet.getSpecie();
    breed = auxPet.getBreed();
    nId = auxPet.getPetId();
    currentDiagnosis = auxPet.getCurrentDiagnosis();
    birthDate = auxPet.getBirthDate();

    rlutil::cls();
    std::cout << "Editando Mascota #" << nId << std::endl;

    // pedir y buscar id dueño
    clientIdForm.setIntField("ID Dueño", ownerId, 4);
    existentId = false;
    while (!existentId) {
        if (!clientIdForm.fill()) return auxFormPet;
        existentId = clientsManager.idExists(ownerId);
        if (!retryIfIdNotExists(existentId)) return auxFormPet;
    }

    // configurar form
    petForm.setEditMode(true, true);  // modo edicion
    petForm.setStrField("Nombre", name, 30);
    petForm.setStrField("Especie", specie, 15);
    petForm.setStrField("Raza", breed, 30);
    petForm.setStrField("Diagnostico actual", currentDiagnosis, 45);
    petForm.setDateField("Fecha de nacimiento", birthDate);
    /// petForm.setIntField("ID Dueño", ownerId, 4);

    // completar form
    bool success = petForm.fill();
    if (success) {  // si se completa

        auxFormPet.setPetId(nId);
        auxFormPet.setName(name);
        auxFormPet.setBreed(breed);
        auxFormPet.setSpecie(specie);
        auxFormPet.setCurrentDiagnosis(currentDiagnosis);
        auxFormPet.setBirthDate(birthDate);
        auxFormPet.setOwnerId(ownerId);
        auxFormPet.setStatus(true);

        return auxFormPet;
    }
    // si no se completa, devolver Mascota vacia
    return auxFormPet;
}

void ItemSaleManager::edit() {
    InputForm search;
    int nId;
    show();
    std::cout << "\nIngrese el ID de la mascota a modificar.\n";
    search.setIntField("ID Mascota", nId, 4);
    if (!search.fill()) return;  // si no se completa, salir
    int regPos = _petsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No se encontraron resultados.\n";
        utils::pause();
        return;
    }
    // Si se encontro, pedir datos
    Pet auxPet = editForm(regPos);
    // Si no se completo el formulario, salir
    if (auxPet.getPetId() == -1) {
        std::cout << "No se realizara la edicion.\n";
        utils::pause();
        return;
    }

    // guardar mascota actualizada
    if (_petsFile.updateFile(auxPet, regPos)) {
        std::cout << "Mascota editada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    utils::pause();
}

void ItemSaleManager::show(bool showAndPause) {
    int totalRegs = _petsFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _petsFields;

    if (totalRegs < 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        utils::pause();
        return;
    }
    // Se crea la variable que va a contener todas las celdas, segun la cantidad
    // de registros
    std::string *cells = new std::string[totalCells];
    if (cells == NULL) {
        std::cout << "No hay memoria suficiente para mostrar las mascotas.\n";
        return;
    }
    int rowPos = 0;  // acumula la posicion actual a asignar
    for (int i = 0; i < totalRegs; i++) {
        Pet auxPet = _petsFile.readFile(i);
        // Obtener todas las propiedades de la Mascota
        // Guardarlas en un vector de string
        std::string vecStr[7];
        auxPet.toVecString(vecStr);
        for (int cell = 0; cell < _petsFields; cell++) {
            if (auxPet.getStatus()) {
                cells[rowPos + cell] = vecStr[cell];
            } else {
                cells[rowPos + cell] = "";
            }
        }
        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        rowPos += _petsFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[7] = {"ID",   "ID Dueño",    "Nombre",       "Especie",
                              "Raza", "Diagnóstico", "F. nacimiento"};

    ListView petsList;
    petsList.addCells(cells, totalCells);
    petsList.addCols(columns, 7);
    petsList.setTitle("MASCOTAS");
    petsList.show();
    delete[] cells;  // liberar memoria!

    if (showAndPause) utils::pause();
}

}
// Solo compara si coincide el id
bool ItemSaleManager:searchById(Pet reg, int nId) {
    if (reg.getPetId() == nId) return true;
    return false;
}

bool ItemSaleManager::idExists(int nId) {
    // Si devuelve un nro de posicion, existe
    return _petsFile.searchReg(searchById, nId) >= 0 ? true : false;
}

void ItemSaleManager:clearDeleted() {
    InputForm confirmForm;
    bool confirm;
    std::cout << "Esta acción buscará Mascotas dadas de baja e "
                 "intentará eliminarlos definitivamente. Desea continuar?\n";
    confirmForm.setBoolField("[SI/NO]", confirm);
    if (!confirmForm.fill()) return;
    if (!confirm) return;
    std::cout << "Buscando registros...\n";
    int deleted = _petsFile.deleteAllMarked();
    switch (deleted) {
        case 0:
            std::cout << "No se encontraron mascotas dados de baja.\n";
            break;
        case -1:
            std::cout << "Ocurrió un error al intentar eliminar las mascotas\n";
            break;
        default:
            printf("Se eliminaron %d registros con éxito!\n", deleted);
            break;
    }
    utils::pause();
}

void ItemSaleManager::cancel() {
    InputForm searchId, confirmForm;
    int nId;
    bool confirm;
    // mostrar mascotas
    show(false);

    std::cout << "\nIngrese el ID de la mascota a dar de baja.\n";
    searchId.setIntField("ID Mascota", nId, 4);
    if (!searchId.fill()) return;  // si no se completa, salir
    int regPos = _petsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No existe una mascota con el ID ingresado.\n";
        utils::pause();
        return;
    }

    printf("Se seleccionó la mascota #%d, confirma la baja provisoria.\n", nId);
    confirmForm.setBoolField("[SI/NO]", confirm);
    if (!confirmForm.fill()) return;
    if (!confirm) {
        std::cout << "No se realizará la baja.\n";
        utils::pause();
        return;
    }

    bool success = _petsFile.markForDelete(regPos);

    if (success) {
        std::cout << "Baja realizada con éxito!\n";
    } else {
        std::cout << "Ocurrió un error al intentar realizar la baja.\n";
    }
    utils::pause();
}

bool ItemSaleManager::updateOwner(int ownerId, int petId) {
    int regPos = _petsFile.searchReg(searchById, petId);
    if (regPos < 0) return false;
    Pet auxPet = _petsFile.readFile(petId);
    if (auxPet.getPetId() == -1) return false;
    auxPet.setOwnerId(ownerId);
    bool success = _petsFile.updateFile(auxPet, regPos);
    return success;
}*/

