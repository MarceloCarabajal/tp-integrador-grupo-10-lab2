#include "VetVisitsManager.h"

#include <iostream>

#include "ClientsManager.h"
#include "Date.h"
#include "InputForm.h"
#include "ListView.h"
#include "PetsManager.h"
#include "RelationsManager.h"
#include "VetsManager.h"
#include "rlutil.h"
#include "utils.h"

void VetVisitsManager::load() {
    InputForm idForm;
    VetVisits auxVetVisits;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id ingresado existe

    do {
        if (alreadyExists) {
            if (!isActiveId(nId)) {
                std::cout
                    << "El ID de la consulta está dado de baja, elija otro "
                       "ID o elimine el registro desde el menú 'Limpiar "
                       "registros'.\n";
            } else {
                std::cout << "El ID de la consulta ya existe, elija otro.\n";
            }
            std::cout << "presione cualquier tecla para reintentar o ESC para "
                         "salir.\n";
            if (rlutil::getkey() == rlutil::KEY_ESCAPE) return;
            rlutil::cls();
        }

        idForm.setIntField("ID Consulta", nId, 4);
        // si no completa el form, salir
        if (!idForm.fill()) return;
        alreadyExists =
            _vetVisitsFile.searchReg(searchById, nId) >= 0 ? true : false;
        idForm.clearAll();  // limpiar form
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
    InputForm vetvisitsForm, petIdForm, clientIdForm, vetForm;
    VetVisits auxVetVisits;
    RelationsManager relationsMgr;
    PetsManager petsManager;
    ClientsManager clientsManager;
    VetsManager vetsManager;
    std::string reason, diagnosis;
    Date date;
    int clientId, petId, saleId, vetId;
    bool alreadyExists = true, isActive = true;

    // pedir y buscar si el id mascota ingresado existe
    petIdForm.setIntField("ID Mascota", petId, 4);
    do {
        // si no existe, preguntar si quiere reintentar
        if (!retryIfIdNotExists(alreadyExists, isActive)) return auxVetVisits;
        // si no completa el form, salir
        if (!petIdForm.fill()) return auxVetVisits;
        alreadyExists = petsManager.idExists(petId);
    } while (!alreadyExists);  // si no existe, volver a pedir

    // pedir y buscar si el id cliente ingresado existe
    alreadyExists = true;
    isActive = true;

    clientIdForm.setIntField("ID Cliente", clientId, 4);
    do {
        // si no existe, preguntar si quiere reintentar
        if (!retryIfIdNotExists(alreadyExists, isActive)) return auxVetVisits;
        // si no completa el form, salir
        if (!clientIdForm.fill()) return auxVetVisits;
        alreadyExists = clientsManager.idExists(clientId);
    } while (!alreadyExists);  // si no existe, volver a pedir

    // Validar que exista una relacion activa cliente/mascota
    bool relationExists = relationsMgr.relationExists(petId, clientId);
    if (!relationExists) {
        std::cout << "No existe una relación activa entre el cliente y la "
                     "mascota ingresados.\n";
        std::cout
            << "Por favor cargue la relación desde el menú 'Relaciones'.\n";
        utils::pause();
        return auxVetVisits;
    }

    // pedir y buscar si el id vete ingresado existe
    alreadyExists = true;
    isActive = true;

    vetForm.setIntField("ID vete", vetId, 4);
    do {
        // si no existe, preguntar si quiere reintentar
        if (!retryIfIdNotExists(alreadyExists, isActive)) return auxVetVisits;
        // si no completa el form, salir
        if (!vetForm.fill()) return auxVetVisits;
        alreadyExists = vetsManager.idExists(vetId);
    } while (!alreadyExists);  // si no existe, volver a pedir

    vetvisitsForm.setStrField("Motivo", reason, 30);
    vetvisitsForm.setAlphanumeric("Diagnóstico", diagnosis, 240);
    vetvisitsForm.setDateField("Fecha", date);
    vetvisitsForm.setIntField("ID Venta", saleId, 4);

    if (!vetvisitsForm.fill()) return auxVetVisits;

    auxVetVisits.setReason(reason);
    auxVetVisits.setDiagnosis(diagnosis);
    auxVetVisits.setDate(date);
    auxVetVisits.setClientId(clientId);
    auxVetVisits.setPetId(petId);
    auxVetVisits.setVetId(vetId);
    auxVetVisits.setSaleId(saleId);
    auxVetVisits.setStatus(true);

    return auxVetVisits;
}

VetVisits VetVisitsManager::editForm(int regPos) {
    InputForm vetvisitsForm(true, true), petIdForm(true), clientIdForm(true),
        vetForm(true);
    VetVisits auxVetVisits, auxFormVetVisits;
    RelationsManager relationsMgr;
    PetsManager petsManager;
    VetsManager vetsManager;
    ClientsManager clientsManager;
    std::string reason, diagnosis;
    Date date;
    int clientId, petId, saleId, vetId, nId;
    bool existentId;
    bool isActive = true;

    auxVetVisits = _vetVisitsFile.readFile(regPos);
    if (auxVetVisits.getVisitId() == -1) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxFormVetVisits;
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

    rlutil::cls();  // limpiar pantalla
    std::cout << "Editando Consulta #" << nId << std::endl;
    // configurar form

    vetvisitsForm.setStrField("Motivo", reason, 30);
    vetvisitsForm.setAlphanumeric("Diagnóstico", diagnosis, 240);
    vetvisitsForm.setDateField("Fecha", date);

    clientIdForm.setIntField("ID Cliente", clientId, 4);
    existentId = false;
    isActive = true;
    while (!existentId) {
        if (!clientIdForm.fill()) return auxFormVetVisits;
        existentId = clientsManager.idExists(clientId);
        if (!retryIfIdNotExists(existentId, isActive)) return auxFormVetVisits;
    }

    petIdForm.setIntField("ID Mascota", petId, 4);
    existentId = false;
    isActive = true;
    while (!existentId) {
        if (!petIdForm.fill()) return auxFormVetVisits;
        existentId = petsManager.idExists(petId);
        if (!retryIfIdNotExists(existentId, isActive)) return auxFormVetVisits;
    }

    // Validar que exista una relacion activa cliente/mascota
    bool relationExists = relationsMgr.relationExists(petId, clientId);
    if (!relationExists) {
        std::cout << "No existe una relación activa entre el cliente y la "
                     "mascota ingresados.\n";
        std::cout
            << "Por favor cargue la relación desde el menú 'Relaciones'.\n";
        utils::pause();
        return auxVetVisits;
    }

    vetvisitsForm.setIntField("ID Venta", saleId, 4);

    vetForm.setIntField("ID Vete", vetId, 4);
    existentId = false;
    isActive = true;
    while (!existentId) {
        if (!vetForm.fill()) return auxFormVetVisits;
        existentId = vetsManager.idExists(vetId);
        if (!retryIfIdNotExists(existentId, isActive)) return auxFormVetVisits;
    }

    // completar form
    bool success = vetvisitsForm.fill();
    if (success) {  // si se completa
        auxVetVisits.setVisitId(nId);
        auxVetVisits.setReason(reason);
        auxVetVisits.setDiagnosis(diagnosis);
        auxVetVisits.setDate(date);
        auxVetVisits.setClientId(clientId);
        auxVetVisits.setPetId(petId);
        auxVetVisits.setVetId(vetId);
        auxVetVisits.setSaleId(saleId);
        auxVetVisits.setStatus(true);

        return auxVetVisits;
    }
    // si no se completa, devolver Mascota vacia
    return auxVetVisits;
}

void VetVisitsManager::edit() {
    InputForm search;
    int nId;
    show(false);

    int totalRegs = _vetVisitsFile.getTotalRegisters();
    if (totalRegs <= 0) return;

    std::cout << "\nIngrese el ID de la consulta a modificar.\n";
    search.setIntField("ID consulta ", nId, 4);
    if (!search.fill()) return;  // si no se completa, salir
    int regPos = _vetVisitsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No se encontraron resultados.\n";
        utils::pause();
        return;
    }

    // Si existe pero está dada de baja
    if (!isActiveId(nId)) {
        std::cout << "La consulta se encuentra dada de baja.\n";
        std::cout << "Si desea eliminarla definitivamente "
                     " seleccione laopción 'Limpiar registros' del menú.\n";
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

void VetVisitsManager::show(bool showAndPause) {
    int totalRegs = _vetVisitsFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _vetVisitsFields;

    if (totalRegs < 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        utils::pause();
        return;
    }
    if (totalRegs == 0) {
        std::cout << "No hay registros para mostrar.\n";
        utils::pause();
        return;
    }
    // Se crea la variable que va a contener todas las celdas, segun la
    // cantidad de registros
    std::string *cells = new std::string[totalCells];
    if (cells == NULL) {
        std::cout << "No hay memoria suficiente para mostrar las consultas.\n";
        return;
    }
    int rowPos = 0;  // acumula la posicion actual a asignar
    for (int i = 0; i < totalRegs; i++) {
        VetVisits auxVetVisits = _vetVisitsFile.readFile(i);
        // Obtener todas las propiedades de la consulta
        // Guardarlas en un vector de string
        std::string vecStr[9];
        auxVetVisits.toVecString(vecStr);

        vecStr[8] = PetsManager().getNameById(auxVetVisits.getPetId());
        for (int cell = 0; cell < _vetVisitsFields; cell++) {
            if (auxVetVisits.getStatus()) {
                cells[rowPos + cell] = vecStr[cell];
            } else {
                cells[rowPos + cell] = "";
            }
        }

        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        rowPos += _vetVisitsFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[9] = {"ID CONSULTA", "ID VETE",     "ID CLIENTE",
                              "ID MASCOTA",  "ID VENTA",    "FECHA",
                              "MOTIVO",      "DIAGNÓSTICO", "NOMBRE MASCOTA"};

    ListView petsList;
    petsList.addCells(cells, totalCells);
    petsList.addCols(columns, 9);
    petsList.setTitle("CONSULTAS");
    petsList.show();
    delete[] cells;  // liberar memoria!
    if (showAndPause) utils::pause();
}

// Solo compara si coincide el id
bool VetVisitsManager::searchById(VetVisits reg, int nId) {
    if (reg.getVisitId() == nId) return true;
    return false;
}

bool VetVisitsManager::idExists(int nId) {
    return _vetVisitsFile.searchReg(searchById, nId) >= 0 ? true : false;
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

bool VetVisitsManager::retryIfIdNotExists(bool exists, bool isActive) {
    if (!exists) {
        std::cout << "El ID ingresado NO EXISTE.\n";
    }
    if (exists && !isActive) {
        std::cout << "El ID ingresado está dado de baja.\n";
    }
    if (exists && isActive) return true;
    std::cout
        << " presione cualquier tecla para reintentar o ESC para salir.\n";
    if (rlutil::getkey() == rlutil::KEY_ESCAPE) return false;
    rlutil::cls();
    return true;
}

bool VetVisitsManager::isActiveId(int nId) {
    int regPos = _vetVisitsFile.searchReg(searchById, nId);
    if (regPos == -1) return false;
    VetVisits auxVetVisits = _vetVisitsFile.readFile(regPos);
    if (auxVetVisits.getStatus()) return true;
    return false;
}

void VetVisitsManager::clearDeleted() {
    InputForm confirmForm;
    bool confirm;
    std::cout << "Esta acción buscará Consultas dadas de baja e "
                 "intentará eliminarlas definitivamente. Desea continuar?\n";
    confirmForm.setBoolField("[SI/NO]", confirm);
    if (!confirmForm.fill()) return;
    if (!confirm) return;
    std::cout << "Buscando registros...\n";
    int deleted = _vetVisitsFile.deleteAllMarked();
    switch (deleted) {
        case 0:
            std::cout << "No se encontraron Consultas dadas de baja.\n";
            break;
        case -1:
            std::cout
                << "Ocurrió un error al intentar eliminar las consultas\n";
            break;
        default:
            printf("Se eliminaron %d registros con éxito!\n", deleted);
            break;
    }
    utils::pause();
}

void VetVisitsManager::cancel() {
    InputForm searchId, confirmForm;
    int nId;
    bool confirm;
    // mostrar vacunacion
    show(false);

    std::cout << "\nIngrese el ID de la Consulta a dar de baja.\n";
    searchId.setIntField("ID Consulta", nId, 4);
    if (!searchId.fill()) return;  // si no se completa, salir
    int regPos = _vetVisitsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No existe Consulta con el ID ingresado.\n";
        utils::pause();
        return;
    }

    printf("Se seleccionó la Consulta #%d, confirma la baja provisoria.\n",
           nId);
    confirmForm.setBoolField("[SI/NO]", confirm);
    if (!confirmForm.fill()) return;
    if (!confirm) {
        std::cout << "No se realizará la baja.\n";
        utils::pause();
        return;
    }

    bool success = _vetVisitsFile.markForDelete(regPos);

    if (success) {
        std::cout << "Baja realizada con éxito!\n";
    } else {
        std::cout << "Ocurrió un error al intentar realizar la baja.\n";
    }
    utils::pause();
}

int VetVisitsManager::getActiveVetVisitsCount() {
    int total = _vetVisitsFile.getTotalRegisters();
    if (total < 0) return -1;
    int active = 0;
    for (int i = 0; i < total; i++) {
        VetVisits auxVV = _vetVisitsFile.readFile(i);
        if (auxVV.getStatus()) active++;
    }
    return active;
}

VetVisits* VetVisitsManager::getActiveVetVisits() {
    int total = _vetVisitsFile.getTotalRegisters();
    if (total <= 0) return NULL;
    int totalActive = getActiveVetVisitsCount();
    int activeCount = 0;
    VetVisits* vetv = new VetVisits[total];
    VetVisits* activeVetVisit = new VetVisits[totalActive];
    if (vetv == NULL) return NULL;
    if (activeVetVisit == NULL) return NULL;
    if (!_vetVisitsFile.readFile(vetv, total)) return NULL;
    for (int i = 0; i < total; i++) {
        if (vetv[i].getStatus()) {
            activeVetVisit[activeCount] = vetv[i];
            activeCount++;
        }
    }
    return activeVetVisit;
}