#include "VetVisitsManager.h"

#include <iostream>
#include "ClientsManager.h"
#include "PetsManager.h"
#include "VetsManager.h"
#include "Date.h"
#include "InputForm.h"
#include "ListView.h"
#include "rlutil.h"
#include "utils.h"

void VetVisitsManager::load() {
    InputForm idForm;
    VetVisits auxVetVisits;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id ingresado existe
    idForm.setIntField("ID Consulta", nId, 4);



do {
        if (!retryIfIdExists(alreadyExists)) return;
        // si no completa el form, salir
        if (!idForm.fill()) return;
        alreadyExists = idExists(nId);
    } while (alreadyExists);

    // Si no existe el turno, pedir el resto de datos
 auxVetVisits = loadForm();
if (auxVetVisits.getPetId() == -1) return;

    
       // setear id ingresado
     auxVetVisits.setVisitId(nId);


    if (_vetVisitsFile.writeFile(auxVetVisits)) {
        std::cout << "Consulta  guardada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar la consulta .\n";
    }
}

VetVisits VetVisitsManager::loadForm() {
    InputForm vetvisitsForm, petIdForm, clientIdForm,vetForm;
    VetVisits auxVetVisits;
    PetsManager petsManager;
    ClientsManager clientsManager;
    VetsManager vetsManager;
    std::string reason, diagnosis;
    Date date;
    int clientId, petId, saleId, vetId;
    bool alreadyExists = true;

// pedir y buscar si el id mascota ingresado existe
    petIdForm.setIntField("ID Mascota", petId, 4);
    do {
        // si no existe, preguntar si quiere reintentar
        if (!retryIfIdNotExists(alreadyExists)) return auxVetVisits;
        // si no completa el form, salir
        if (!petIdForm.fill()) return auxVetVisits;
        alreadyExists = petsManager.idExists(petId);
    } while (!alreadyExists);  // si no existe, volver a pedir

    // pedir y buscar si el id cliente ingresado existe
    alreadyExists = true;
    clientIdForm.setIntField("ID Cliente", clientId, 4);
    do {
        // si no existe, preguntar si quiere reintentar
        if (!retryIfIdNotExists(alreadyExists)) return auxVetVisits;
        // si no completa el form, salir
        if (!clientIdForm.fill()) return auxVetVisits;
        alreadyExists = clientsManager.idExists(clientId);
    } while (!alreadyExists);  // si no existe, volver a pedir

// pedir y buscar si el id vete ingresado existe
    alreadyExists = true;
    vetForm.setIntField("ID vete", vetId, 4);
    do {
        // si no existe, preguntar si quiere reintentar
        if (!retryIfIdNotExists(alreadyExists)) return auxVetVisits;
        // si no completa el form, salir
        if (!vetForm.fill()) return auxVetVisits;
        alreadyExists = vetsManager.idExists(vetId);
    } while (!alreadyExists);  // si no existe, volver a pedir

    vetvisitsForm.setStrField("Motivo", reason, 30);
    vetvisitsForm.setStrField("Diagnóstico", diagnosis, 240);
    vetvisitsForm.setDateField("Fecha", date);
    vetvisitsForm.setIntField("ID Venta", saleId, 4);
    vetvisitsForm.setIntField("ID Vete", vetId, 4);

    if (!vetvisitsForm.fill()) return auxVetVisits;

    auxVetVisits.setReason(reason);
    auxVetVisits.setDiagnosis(diagnosis);
    auxVetVisits.setDate(date);
    auxVetVisits.setClientId(clientId);
    auxVetVisits.setPetId(petId);
    auxVetVisits.setVetId(vetId);
    auxVetVisits.setSaleId(saleId);

    return auxVetVisits;
}

VetVisits VetVisitsManager::editForm(int regPos) {
    InputForm vetvisitsForm;
    VetVisits auxVetVisits;
    std::string reason, diagnosis;
    Date date;
    int clientId, petId, saleId, vetId, nId;

    auxVetVisits = _vetVisitsFile.readFile(regPos);
    if (auxVetVisits.getVisitId() == -1) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxVetVisits;
    }
    // Se cargan los datos para mostrarlas en el form.
    clientId = auxVetVisits.getClientId();
    saleId = auxVetVisits.getSaleId();
    petId = auxVetVisits.getPetId();
    vetId = auxVetVisits.getVetId();
    nId = auxVetVisits.getVisitId();
    reason = auxVetVisits.getReason();
    date = auxVetVisits.getDate();
    diagnosis = auxVetVisits.getDiagnosis();

    std::cout << "Editando Consulta #" << nId << std::endl;
    // configurar form
    vetvisitsForm.setEditMode(true);  // modo edicion
    vetvisitsForm.setStrField("Motivo", reason, 30);
    vetvisitsForm.setStrField("Diagnóstico", diagnosis, 240);
    vetvisitsForm.setDateField("Fecha", date);
    vetvisitsForm.setIntField("ID Cliente", clientId, 4);
    vetvisitsForm.setIntField("ID Mascota", petId, 4);
    vetvisitsForm.setIntField("ID Venta", saleId, 4);
    vetvisitsForm.setIntField("ID Vete", vetId, 4);

    // completar form
    bool success = vetvisitsForm.fill();
    if (success) {  // si se completa

        auxVetVisits.setReason(reason);
        auxVetVisits.setDiagnosis(diagnosis);
        auxVetVisits.setDate(date);
        auxVetVisits.setClientId(clientId);
        auxVetVisits.setPetId(petId);
        auxVetVisits.setVetId(vetId);
        auxVetVisits.setSaleId(saleId);
        return auxVetVisits;
    }
    // si no se completa, devolver Mascota vacia
    return auxVetVisits;
}

void VetVisitsManager::edit() {
    InputForm search;
    int nId;
    show();
    std::cout << "\nIngrese el ID de la consulta a modificar.\n";
    search.setIntField("ID consulta ", nId, 4);
    if (!search.fill()) return;  // si no se completa, salir
    int regPos = _vetVisitsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No se encontraron resultados.\n";
        utils::pause();
        return;
    }
    // Si se encontro, pedir datos
    VetVisits auxVetVisits = editForm(regPos);
    // Si no se completo el formulario, salir
    if (auxVetVisits.getPetId() == -1) {
        std::cout << "No se realizara la edicion.\n";
        utils::pause();
        return;
    }

    // guardar consulta actualizada
    if (_vetVisitsFile.updateFile(auxVetVisits, regPos)) {
        std::cout << "Consulta  editada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    utils::pause();
}

void VetVisitsManager::show() {
    int totalRegs = _vetVisitsFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _vetVisitsFields;

    if (totalRegs < 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        utils::pause();
        return;
    }
    // Se crea la variable que va a contener todas las celdas, segun la cantidad
    // de registros
    std::string *cells = new std::string[totalCells];
    if (cells == NULL) {
        std::cout << "No hay memoria suficiente para mostrar las consultas.\n";
        return;
    }
    int cellPos = 0;  // acumula la posicion actual a asignar
    for (int i = 0; i < totalRegs; i++) {
        VetVisits auxVetVisits = _vetVisitsFile.readFile(i);
        // Obtener todas las propiedades de la consulta
        // Guardarlas en un vector de string
        std::string vecStr[8];
        auxVetVisits.toVecString(vecStr);
        for (int cell = 0; cell < _vetVisitsFields; cell++) {
            cells[cellPos + cell] = vecStr[cell];
        }

        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        cellPos += _vetVisitsFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[8] = {"ID CONSULTA", "ID VETE",    "ID CLIENTE",
                              "ID MASCOTA",  "ID VENTA",   "FECHA",
                              "MOTIVO",      "DIAGNÓSTICO"};

    ListView petsList;
    petsList.addCells(cells, totalCells);
    petsList.addCols(columns, 8);
    petsList.setTitle("CONSULTAS");
    petsList.show();
    delete[] cells;  // liberar memoria!
}

// Solo compara si coincide el id
bool VetVisitsManager::searchById(VetVisits reg, int nId) {
    if (reg.getVisitId() == nId) return true;
    return false;
}

bool VetVisitsManager::idExists(int nId) {
    _vetVisitsFile.searchReg(searchById, nId) >= 0 ? true : false;
}



bool VetVisitsManager::retryIfIdExists(bool exists) {
    if (exists) {
        std::cout << "El ID ingresado ya existe, presione cualquier tecla "
                     "para reintentar o ESC para salir.\n";
        if (rlutil::getkey() == rlutil::KEY_ESCAPE) return false;
        rlutil::cls();
    }
    return true;
}

bool VetVisitsManager::retryIfIdNotExists(bool exists) {
    if (!exists) {
        std::cout << "El ID ingresado NO EXISTE, presione cualquier tecla "
                     "para reintentar o ESC para salir.\n";
        if (rlutil::getkey() == rlutil::KEY_ESCAPE) return false;
        rlutil::cls();
    }
    return true;
}