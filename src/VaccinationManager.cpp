#include "VaccinationManager.h"

#include <iostream>

#include "InputForm.h"
#include "ListView.h"
#include "PetsManager.h"
#include "rlutil.h"
#include "utils.h"

void VaccinationManager::load() {
    InputForm idForm;
    Vaccination auxVaccination;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id ingresado existe
    idForm.setIntField("ID Vacunación", nId, 4);
    do {
        if (!retryIfIdExists(alreadyExists)) return;
        // si no completa el form, salir
        if (!idForm.fill()) return;
        alreadyExists = idExists(nId);
    } while (alreadyExists);
    // Si no existe el id de vac, pedir el resto de datos
    auxVaccination = loadForm();
    // Si no se completo el form, salir
    if (auxVaccination.getPeId() == -1) return;

    // setear id ingresado
    auxVaccination.setAplicationId(nId);  // set del Id ingresado anteriormente
    if (_vaccinationFile.writeFile(auxVaccination)) {
        std::cout << "Vacunacion guardada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar la vacunacion.\n";
    }
}

Vaccination VaccinationManager::loadForm() {
    InputForm vaccinationForm, petIdForm, dateForm, dateFormR;
    PetsManager petsManager;
    Vaccination auxVaccination;
    std::string nameVaccine;
    Date dateAplication, dateRevaccination;
    int petId = 0;
    bool alreadyExists = true;
    // bool notified;

    // pedir y buscar si el id mascota ingresado existe
    petIdForm.setIntField("ID Mascota", petId, 4);
    do {
        // si no existe, preguntar si quiere reintentar
        if (!retryIfIdNotExists(alreadyExists)) return auxVaccination;
        // si no completa el form, salir
        if (!petIdForm.fill()) return auxVaccination;
        alreadyExists = petsManager.idExists(petId);
    } while (!alreadyExists);  // si no existe, volver a pedir

    vaccinationForm.setStrField(" Vacuna", nameVaccine, 15);
    vaccinationForm.setDateField("Fecha de Aplicacion", dateAplication);
    if (!vaccinationForm.fill()) return auxVaccination;
    dateFormR.setDateField("Fecha de revacunacion", dateRevaccination);
    bool validDate = true;
    do {
        if (!validDate) {
            std::cout << "La fecha debe ser un año posterior a la fecha de "
                         "aplicación.\n";
        }
        if (!dateFormR.fill()) return auxVaccination;
        validDate = validVaccRevaccDate(dateAplication, dateRevaccination);
    } while (!validDate);

    // vaccinationForm.setBoolField("Notificado", notified);

    auxVaccination.setNameVaccine(nameVaccine);
    auxVaccination.setPetId(petId);
    auxVaccination.setDateAplication(dateAplication);
    auxVaccination.setDateRevaccination(dateRevaccination);
    auxVaccination.setStatus(true);
    // auxVaccination.setNotified(notified);

    return auxVaccination;
}

Vaccination VaccinationManager::editForm(int regPos) {
    InputForm vaccinationForm(true), petIdForm(true, true), dateAForm(true),
        dateRForm(true);
    Vaccination auxVaccination;
    PetsManager petsManager;
    Vaccination auxFormVacc;
    std::string nameVaccine;
    Date dateAplication, dateRevaccination;
    int petId, nId;
    bool notified, existentId;

    auxVaccination = _vaccinationFile.readFile(regPos);
    if (auxVaccination.getAplicationId() == -1) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxVaccination;
    }
    // Se cargan los datos para mostrarlas en el form.
    nameVaccine = auxVaccination.getNameVaccine();
    nId = auxVaccination.getAplicationId();
    dateAplication = auxVaccination.getDateAplication();
    dateRevaccination = auxVaccination.getDateRevaccination();
    notified = auxVaccination.getNotified();
    petId = auxVaccination.getPeId();

    rlutil::cls();  // limpiar pantalla

    std::cout << "Editando vacunacion#" << nId << std::endl;

    // pedir y buscar si el id mascota ingresado existe
    petIdForm.setIntField("ID Mascota", petId, 4);
    existentId = false;
    while (!existentId) {
        if (!petIdForm.fill()) return auxFormVacc;
        existentId = petsManager.idExists(petId);
        if (!retryIfIdNotExists(existentId)) return auxFormVacc;
    }

    dateAForm.setDateField("Fecha de aplicacion", dateAplication);
    if (!dateAForm.fill()) return auxFormVacc;

    dateRForm.setDateField("Fecha de revacunacion", dateRevaccination);
    bool validDate = true;
    do {
        if (!validDate) {
            dateRevaccination = auxVaccination.getDateRevaccination();
            std::cout << "La fecha debe ser un año posterior a la fecha de "
                         "aplicación.\n";
        }
        if (!dateRForm.fill()) return auxFormVacc;
        validDate = validVaccRevaccDate(dateAplication, dateRevaccination);

    } while (!validDate);
    vaccinationForm.setStrField(" Vacuna", nameVaccine, 15);
    vaccinationForm.setBoolField("Notificado", notified);

    // completar form
    bool success = vaccinationForm.fill();
    if (success) {  // si se completa
        auxFormVacc.setAplicationId(nId);
        auxFormVacc.setNameVaccine(nameVaccine);
        auxFormVacc.setPetId(petId);
        auxFormVacc.setDateAplication(dateAplication);
        auxFormVacc.setDateRevaccination(dateRevaccination);
        auxFormVacc.setNotified(notified);
        auxFormVacc.setStatus(true);
        return auxFormVacc;
    }
    // si no se completa, devolver Vaccination vacio
    return auxFormVacc;
}

void VaccinationManager::edit() {
    InputForm search;
    int nId;
    show();
    std::cout << "\nIngrese el ID del vacunaciona modificar.\n";
    search.setIntField("ID Vacunacion", nId, 4);
    if (!search.fill()) return;  // si no se completa, salir
    int regPos = _vaccinationFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No se encontraron resultados.\n";
        utils::pause();
        return;
    }
    // Si se encontro, pedir datos
    Vaccination auxVaccination = editForm(regPos);
    // Si no se completo el formulario, salir
    if (auxVaccination.getPeId() == -1) {
        std::cout << "No se realizara la edicion.\n";
        utils::pause();
        return;
    }

    // guardar vacunacion actualizado
    if (_vaccinationFile.updateFile(auxVaccination, regPos)) {
        std::cout << "Vacunacion editada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    utils::pause();
}

void VaccinationManager::show(bool showAndPause) {
    int totalRegs = _vaccinationFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _vaccinationFields;

    if (totalRegs < 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        utils::pause();
        return;
    }
    // Se crea la variable que va a contener todas las celdas, segun la cantidad
    // de registros
    std::string* cells = new std::string[totalCells];
    if (cells == NULL) {
        std::cout << "No hay memoria suficiente para mostrar las aplicaciones "
                     "realizadas.\n";
        return;
    }
    int rowPos = 0;  // acumula la posicion actual a asignar
    for (int i = 0; i < totalRegs; i++) {
        Vaccination auxVaccination = _vaccinationFile.readFile(i);
        // Obtener todas las propiedades del cliente
        // Guardarlas en un vector de string
        std::string vecStr[6];
        auxVaccination.toVecString(vecStr);
        for (int cell = 0; cell < _vaccinationFields; cell++) {
            if (auxVaccination.getStatus()) {
                cells[rowPos + cell] = vecStr[cell];
            } else {
                cells[rowPos + cell] = "";
            }
        }
        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        rowPos += _vaccinationFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[6] = {"ID Aplicacion", "Id Mascota ",  "Vacuna",
                              "Aplicacion",    "Revacunacion", "¿Notificado?"};

    ListView VaccinationList;
    VaccinationList.addCells(cells, totalCells);
    VaccinationList.addCols(columns, 6);
    VaccinationList.setTitle("Vacunaciones");
    VaccinationList.show();

    delete[] cells;  // liberar memoria!

    if (showAndPause) utils::pause();
}

void VaccinationManager::show(Vaccination* regs, int totalRegs) {
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    int totalCells = totalRegs * _vaccinationFields;

    // Se crea la variable que va a contener todas las celdas, segun la cantidad
    // de registros
    std::string* cells = new std::string[totalCells];
    if (cells == NULL) {
        std::cout << "No hay memoria suficiente para mostrar las aplicaciones "
                     "realizadas.\n";
        return;
    }

    int rowPos = 0;  // acumula la posicion actual a asignar
    for (int i = 0; i < totalRegs; i++) {
        // Obtener todas las propiedades del cliente
        // Guardarlas en un vector de string
        std::string vecStr[6];
        regs[i].toVecString(vecStr);
        for (int cell = 0; cell < _vaccinationFields; cell++) {
            if (regs[i].getStatus()) {
                cells[rowPos + cell] = vecStr[cell];
            } else {
                cells[rowPos + cell] = "";
            }
        }
        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        rowPos += _vaccinationFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[6] = {"ID Aplicacion", "Id Mascota ",  "Vacuna",
                              "Aplicacion",    "Revacunacion", "¿Notificado?"};

    ListView VaccinationList;
    VaccinationList.addCells(cells, totalCells);
    VaccinationList.addCols(columns, 6);
    VaccinationList.setTitle("Vacunaciones");
    VaccinationList.show();

    delete[] regs;
    delete[] cells;
}

void VaccinationManager::configAndSendNotif() {
    InputForm remainingDaysForm(true);
    int remainingDays = 15;

    std::cout << "A continuación se mostrarán las vacunaciones pendientes sin "
                 "notificar.\n";
    std::cout << "Por favor ingrese cantidad de días restantes para la "
                 "revacunación.\n";
    std::cout << "Si deja el campo vacío, se mostrarán las vacunaciones "
                 "pendientes para los PRÓXIMOS 15 DÍAS.\n";

    remainingDaysForm.setRangeField("Días[1-365]", remainingDays, 1, 365);
    if (!remainingDaysForm.fill()) return;
    int totalPending = pendingCount(remainingDays, true);
    if (totalPending == -1) {
        std::cout << "Ocurrió un error al intentar leer los registros.\n";
        utils::pause();
        return;
    }
    if (totalPending == 0) {
        std::cout << "No se encontraron vacunaciones pendientes para el rango "
                     "ingresado.\n";
        utils::pause();
        return;
    }

    Vaccination* pending = getPendingToNotif(remainingDays);
    if (pending == NULL) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        utils::pause();
        return;
    }
    show(pending, totalPending);
    utils::pause();
}

// Solo compara si coincide el id
bool VaccinationManager::searchById(Vaccination reg, int nId) {
    if (reg.getAplicationId() == nId) return true;
    return false;
}

bool VaccinationManager::idExists(int nId) {
    return _vaccinationFile.searchReg(searchById, nId) >= 0 ? true : false;
}

bool VaccinationManager::retryIfIdExists(bool exists) {
    if (exists) {
        std::cout << "El ID ingresado ya existe, presione cualquier tecla "
                     "para reintentar o ESC para salir.\n";
        if (rlutil::getkey() == rlutil::KEY_ESCAPE) return false;
        rlutil::cls();
    }
    return true;
}

bool VaccinationManager::retryIfIdNotExists(bool exists) {
    if (!exists) {
        std::cout << "El ID ingresado NO EXISTE, presione cualquier tecla "
                     "para reintentar o ESC para salir.\n";
        if (rlutil::getkey() == rlutil::KEY_ESCAPE) return false;
        rlutil::cls();
    }
    return true;
}

bool VaccinationManager::validVaccRevaccDate(Date dateA, Date dateR) {
    int Year = dateA.getYear();
    Year++;
    if (dateA.getDay() == dateR.getDay() &&
        dateA.getMonth() == dateR.getMonth() && dateR.getYear() == Year) {
        return true;
    } else {
        return false;
    }
}

bool VaccinationManager::validAplicDate(Date date) {
    Date today;
    if (date == today) return true;
    return false;
}

void VaccinationManager::clearDeleted() {
    InputForm confirmForm;
    bool confirm;
    std::cout << "Esta acción buscará Vacunaciones dadas de baja e "
                 "intentará eliminarlas definitivamente. Desea continuar?\n";
    confirmForm.setBoolField("[SI/NO]", confirm);
    if (!confirmForm.fill()) return;
    if (!confirm) return;
    std::cout << "Buscando registros...\n";
    int deleted = _vaccinationFile.deleteAllMarked();
    switch (deleted) {
        case 0:
            std::cout << "No se encontraron Vacunaciones dadas de baja.\n";
            break;
        case -1:
            std::cout
                << "Ocurrió un error al intentar eliminar las vacunaciones\n";
            break;
        default:
            printf("Se eliminaron %d registros con éxito!\n", deleted);
            break;
    }
    utils::pause();
}

void VaccinationManager::cancel() {
    InputForm searchId, confirmForm;
    int nId;
    bool confirm;
    // mostrar vacunacion
    show(false);

    std::cout << "\nIngrese el ID de la Vacunacion a dar de baja.\n";
    searchId.setIntField("ID Vacunación", nId, 4);
    if (!searchId.fill()) return;  // si no se completa, salir
    int regPos = _vaccinationFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No existe Vacunacion con el ID ingresado.\n";
        utils::pause();
        return;
    }

    printf("Se seleccionó la Vacunacion #%d, confirma la baja provisoria.\n",
           nId);
    confirmForm.setBoolField("[SI/NO]", confirm);
    if (!confirmForm.fill()) return;
    if (!confirm) {
        std::cout << "No se realizará la baja.\n";
        utils::pause();
        return;
    }

    bool success = _vaccinationFile.markForDelete(regPos);

    if (success) {
        std::cout << "Baja realizada con éxito!\n";
    } else {
        std::cout << "Ocurrió un error al intentar realizar la baja.\n";
    }
    utils::pause();
}

// Obtener la cantidad de vacunaciones pendientes de revacunacion en los
// proximos 15 dias por defecto
int VaccinationManager::pendingCount(int remainingDays, bool onlyUnnotified) {
    int totalRegs = _vaccinationFile.getTotalRegisters();
    int totalPending = 0;
    Date today;
    if (totalRegs < 0) return -1;
    for (int i = 0; i < totalRegs; i++) {
        Vaccination auxVaccination = _vaccinationFile.readFile(i);
        if (auxVaccination.getStatus()) {
            // Si solo se quieren las no notificadas, saltear las notificadas
            if (onlyUnnotified && auxVaccination.getNotified()) continue;
            Date dateRevaccination = auxVaccination.getDateRevaccination();
            int diff = dateRevaccination - today;
            if (diff > 0 && diff <= remainingDays) {
                totalPending++;
            }
        }
    }
    return totalPending;
}

Vaccination* VaccinationManager::getPendingToNotif(int remainingDays) {
    int totalRegs = _vaccinationFile.getTotalRegisters();
    int totalPending =
        pendingCount(remainingDays, true);  // solo las no notificadas
    int pendingCount = 0;
    Vaccination* pending = new Vaccination[totalPending];
    Date today;
    if (totalRegs < 0) return NULL;
    for (int i = 0; i < totalRegs; i++) {
        Vaccination auxVaccination = _vaccinationFile.readFile(i);
        if (auxVaccination.getStatus()) {
            Date dateRevaccination = auxVaccination.getDateRevaccination();
            int diff = dateRevaccination - today;
            if (diff > 0 && diff <= remainingDays) {
                pending[pendingCount] = auxVaccination;
                pendingCount++;
            }
        }
    }
    return pending;
}