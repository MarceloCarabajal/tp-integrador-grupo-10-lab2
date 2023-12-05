#include "AppointmentsManager.h"

#include <iostream>

#include "ClientsManager.h"
#include "InputForm.h"
#include "ListView.h"
#include "PetsManager.h"
#include "RelationsManager.h"
#include "rlutil.h"
#include "utils.h"

void AppointmentsManager::load() {
    InputForm appIdForm;
    Appointment auxApp;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id turno ingresado existe
    appIdForm.setIntField("ID Turno", nId, 4);
    do {
        if (!retryIfIdExists(alreadyExists)) return;
        // si no completa el form, salir
        if (!appIdForm.fill()) return;
        alreadyExists = idExists(nId);
    } while (alreadyExists);

    // Si no existe el turno, pedir el resto de datos
    auxApp = loadForm();
    // Si no se completo el form, salir
    if (strlen(auxApp.getReason()) == 0) return;

    // setear id ingresado
    auxApp.setAppId(nId);
    if (_appsFile.writeFile(auxApp)) {
        std::cout << "Turno guardado con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el turno.\n";
    }
    utils::pause();
}

Appointment AppointmentsManager::loadForm() {
    InputForm appForm, petIdForm, clientIdForm, dateForm, timeForm;
    Appointment auxApp;
    PetsManager petsManager;
    ClientsManager clientsManager;
    RelationsManager relationsMgr;
    Date appDate;
    Time appTime;
    std::string reason;
    int petId = 0, clientId = 0;
    bool attended, alreadyExists = true;

    // pedir y buscar si el id mascota ingresado existe
    petIdForm.setIntField("ID Mascota", petId, 4);
    do {
        // si no existe, preguntar si quiere reintentar
        if (!retryIfIdNotExists(alreadyExists)) return auxApp;
        // si no completa el form, salir
        if (!petIdForm.fill()) return auxApp;
        alreadyExists = petsManager.idExists(petId);
    } while (!alreadyExists);  // si no existe, volver a pedir

    // pedir y buscar si el id cliente ingresado existe
    alreadyExists = true;
    clientIdForm.setIntField("ID Cliente", clientId, 4);
    do {
        if (!retryIfIdNotExists(alreadyExists)) return auxApp;
        if (!clientIdForm.fill()) return auxApp;
        alreadyExists = clientsManager.idExists(clientId);
    } while (!alreadyExists);

    // Validar que exista una relacion activa cliente/mascota
    bool relationExists = relationsMgr.relationExists(petId, clientId);
    if (!relationExists) {
        std::cout << "No existe una relación activa entre el cliente y la "
                     "mascota ingresados.\n";
        std::cout
            << "Por favor cargue la relación desde el menú 'Relaciones'.\n";
        utils::pause();
        return auxApp;
    }

    // pedir y validar fecha
    dateForm.setDateField("Fecha", appDate);
    bool validDate = false;
    while (!validDate) {
        if (!dateForm.fill()) return auxApp;
        validDate = validAppDate(appDate);
        if (!retryInvalidDate(validDate)) return auxApp;
    }

    // pedir y validar hora
    timeForm.setTimeField("Hora", appTime);
    bool validTime = false;
    while (!validTime) {
        if (!timeForm.fill()) return auxApp;
        validTime = validAppTime(appDate, appTime);
        if (!retryInvalidTime(validTime)) return auxApp;
    }

    appForm.setBoolField("Asistió", attended);
    appForm.setStrField("Motivo", reason, 30);

    if (!appForm.fill()) return auxApp;

    auxApp.setDate(appDate);
    auxApp.setTime(appTime);
    auxApp.setReason(reason);
    auxApp.setAttended(attended);
    auxApp.setPetId(petId);
    auxApp.setClientId(clientId);
    auxApp.setStatus(true);

    return auxApp;
}

Appointment AppointmentsManager::editForm(int regPos) {
    // Inicializar forms en modo edicion, solo 1 muestra el mensaje de "modo
    // edicion"
    InputForm appForm(true), petIdForm(true, true), clientIdForm(true),
        dateForm(true), timeForm(true);
    Appointment auxApp, auxFormApp;
    RelationsManager relationsMgr;
    PetsManager petsManager;
    ClientsManager clientsManager;
    Date appDate;
    Time appTime;
    std::string reason;
    bool attended, existentId;
    int clientId, petId, nId;

    auxApp = _appsFile.readFile(regPos);
    if (auxApp.getAppId() == -1) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxApp;
    }
    // Se cargan los datos para mostrarlos en el form.
    appDate = auxApp.getDate();
    appTime = auxApp.getTime();
    reason = auxApp.getReason();
    nId = auxApp.getAppId();
    attended = auxApp.getAttended();
    petId = auxApp.getpetId();
    clientId = auxApp.getClientId();

    rlutil::cls();  // limpiar pantalla
    std::cout << "Editando Turno #" << nId << std::endl;

    // pedir y buscar si el id mascota ingresado existe
    petIdForm.setIntField("ID Mascota", petId, 4);
    while (!existentId) {
        if (!petIdForm.fill()) return auxFormApp;
        existentId = petsManager.idExists(petId);
        if (!retryIfIdNotExists(existentId)) return auxFormApp;
    }

    // pedir y buscar id cliente
    clientIdForm.setIntField("ID Cliente", clientId, 4);
    existentId = false;
    while (!existentId) {
        if (!clientIdForm.fill()) return auxFormApp;
        existentId = clientsManager.idExists(clientId);
        if (!retryIfIdNotExists(existentId)) return auxFormApp;
    }

    // Validar que exista una relacion activa cliente/mascota
    bool relationExists = relationsMgr.relationExists(petId, clientId);
    if (!relationExists) {
        std::cout << "No existe una relación activa entre el cliente y la "
                     "mascota ingresados.\n";
        std::cout
            << "Por favor cargue la relación desde el menú 'Relaciones'.\n";
        utils::pause();
        return auxFormApp;
    }

    // pedir y validar fecha
    dateForm.setDateField("Fecha", appDate);
    bool validDate = false;
    while (!validDate) {
        if (!dateForm.fill()) return auxFormApp;
        validDate = validAppDate(appDate);
        if (!retryInvalidDate(validDate)) return auxFormApp;
        // si no fue una fecha valida, reasignar variable para mostrarla con el
        // valor actual
        if (!validDate) appDate = auxApp.getDate();
    }

    // pedir y validar hora
    timeForm.setTimeField("Hora", appTime);
    bool validTime = false;
    while (!validTime) {
        if (!timeForm.fill()) return auxFormApp;
        validTime = validAppTime(appDate, appTime);
        // si deja el mismo horario, es válido, no está duplicado
        if (auxApp.getTime() == appTime) validTime = true;
        if (!retryInvalidTime(validTime)) return auxFormApp;
        // si no fue una hora valida, reasignar variable para mostrarla con el
        // valor actual
        if (!validTime) appTime = auxApp.getTime();
    }

    appForm.setBoolField("Asistio", attended);
    appForm.setStrField("Motivo", reason, 30);

    // completar resto de datos
    bool success = appForm.fill();
    if (success) {  // si se completa, asignar objeto turno
        auxFormApp.setAppId(nId);
        auxFormApp.setPetId(petId);
        auxFormApp.setDate(appDate);
        auxFormApp.setTime(appTime);
        auxFormApp.setReason(reason);
        auxFormApp.setAttended(attended);
        auxFormApp.setClientId(clientId);
        auxFormApp.setStatus(true);

        return auxFormApp;
    }
    // si no se completa, devolver  Turno vacio
    return auxFormApp;
}

void AppointmentsManager::edit() {
    InputForm search;
    int nId;
    show(false);
    int totalRegs = _appsFile.getTotalRegisters();
    if (totalRegs <= 0) return;

    std::cout << "\nIngrese el ID del turno a modificar.\n";
    search.setIntField("ID Turno", nId, 4);
    if (!search.fill()) return;  // si no se completa, salir
    int regPos = _appsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No existe un turno con el ID ingresado.\n";
        utils::pause();
        return;
    }
    // Si se encontro, pedir datos
    Appointment auxApp = editForm(regPos);
    // Si no se completo el formulario, salir
    if (auxApp.getAppId() == -1) {
        std::cout << "No se realizara la edicion.\n";
        utils::pause();
        return;
    }

    // guardar turno actualizado
    if (_appsFile.updateFile(auxApp, regPos)) {
        std::cout << "Turno editado con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    utils::pause();
}

void AppointmentsManager::show(bool showAndPause) {
    int totalRegs = _appsFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _appsFields;

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

    // Se crea la variable que va a contener todas las celdas, segun la cantidad
    // de registros
    std::string* cells = new std::string[totalCells];
    if (cells == NULL) {
        std::cout << "No hay memoria suficiente para mostrar los turnos "
                     "veterinarios.\n";
        return;
    }
    int rowPos = 0;  // acumula la posicion actual de la fila a asignar
    for (int i = 0; i < totalRegs; i++) {
        Appointment auxApp = _appsFile.readFile(i);
        // Obtener todas las propiedades del vete
        // Guardarlas en un vector de string
        std::string vecStr[7];
        auxApp.toVecString(vecStr);
        for (int cell = 0; cell < _appsFields; cell++) {
            // solo llena las celdas si es un registro activo
            if (auxApp.getStatus()) {
                cells[rowPos + cell] = vecStr[cell];
            } else {
                cells[rowPos + cell] = "";
            }
        }

        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        rowPos += _appsFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[7] = {"ID",     "ID Mascota", "Fecha",     "Hora",
                              "Motivo", "Asistió",    "ID Cliente"};

    ListView appvetsList;
    appvetsList.addCells(cells, totalCells);
    appvetsList.addCols(columns, 7);
    appvetsList.setTitle("TURNOS");
    appvetsList.show();

    delete[] cells;  // liberar memoria!
    if (showAndPause) utils::pause();
}

void AppointmentsManager::clearExpired() {
    InputForm confirmForm;
    bool confirm;
    std::cout << "Buscando turnos expirados...\n";
    int expired = getExpiredApps();
    if (expired < 0) {
        std::cout << "Ocurrió no error al leer los registros.\n";
        utils::pause();
        return;
    }
    if (expired == 0) {
        std::cout << "No hay turnos expirados.\n";
        utils::pause();
        return;
    }

    std::cout << "Se encontraron " << expired << " turnos expirados.\n";
    std::cout << "Desea eliminarlos? esta acción es irreversible.\n";
    confirmForm.setBoolField("[Si/No]", confirm);
    if (!confirmForm.fill()) return;
    if (confirm) {
        std::cout << "Eliminación en curso...\n";
        int deleted = deleteAllExpired();
        switch (deleted) {
            case -1:
                std::cout
                    << "Ocurrió un error al intentar eliminar los registros.\n";
                break;
            case 0:
                std::cout
                    << "No se pudieron eliminar los turnos de los registros, "
                       "pero ya no aparecerán en el listado.\n";
                std::cout << "Puede intentar eliminarlos definitivamente desde "
                             "el menu 'Limpiar registros'.\n";
                break;
            default:
                printf("Se eliminaron %d turnos con exito.\n", deleted);
                break;
        }
    }
    utils::pause();
}

void AppointmentsManager::clearDeleted() {
    InputForm confirmForm;
    bool confirm;
    std::cout << "Esta acción buscará turnos con eliminación pendiente e "
                 "intentará eliminarlos definitivamente. Desea continuar?\n";
    confirmForm.setBoolField("[SI/NO]", confirm);
    if (!confirmForm.fill()) return;
    if (!confirm) return;
    std::cout << "Buscando registros...\n";
    int deleted = _appsFile.deleteAllMarked();
    switch (deleted) {
        case 0:
            std::cout
                << "No se encontraron turnos con eliminación pendiente.\n";
            break;
        case -1:
            std::cout << "Ocurrió un error al intentar eliminar los turnos.\n";
            break;
        default:
            printf("Se eliminaron %d registros con éxito!\n", deleted);
            break;
    }
    utils::pause();
}

void AppointmentsManager::cancel() {
    InputForm searchId, confirmForm;
    int nId;
    bool confirm;
    // mostrar turnos
    show(false);

    std::cout << "\nIngrese el ID del turno a cancelar.\n";
    searchId.setIntField("ID Turno", nId, 4);
    if (!searchId.fill()) return;  // si no se completa, salir
    int regPos = _appsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No existe un turno con el ID ingresado.\n";
        utils::pause();
        return;
    }

    printf(
        "Se seleccionó el turno #%d, confirma la cancelación? esta acción es "
        "irreversible.\n",
        nId);
    confirmForm.setBoolField("[SI/NO]", confirm);
    if (!confirmForm.fill()) return;
    if (!confirm) {
        std::cout << "No se realizará la cancelación.\n";
        utils::pause();
        return;
    }

    bool success = _appsFile.markForDelete(regPos);
    int deleted = _appsFile.deleteAllMarked();
    if (success && deleted > 0) {
        std::cout << "Turno cancelado con éxito!\n";
    } else {
        std::cout << "Ocurrió un error al intentar cancelar el turno.\n";
    }
    utils::pause();
}

int AppointmentsManager::getActiveAppsCount() {
    int total = _appsFile.getTotalRegisters();
    if (total < 0) return -1;
    int active = 0;
    for (int i = 0; i < total; i++) {
        Appointment auxApp = _appsFile.readFile(i);
        if (auxApp.getStatus()) active++;
    }
    return active;
}

Appointment* AppointmentsManager::getActiveApps() {
    int total = _appsFile.getTotalRegisters();
    if (total <= 0) return NULL;
    int totalActive = getActiveAppsCount();
    int activeCount = 0;
    Appointment* apps = new Appointment[total];
    Appointment* activeApps = new Appointment[totalActive];
    if (apps == NULL) return NULL;
    if (activeApps == NULL) return NULL;
    if (!_appsFile.readFile(apps, total)) return NULL;
    for (int i = 0; i < total; i++) {
        if (apps[i].getStatus()) {
            activeApps[activeCount] = apps[i];
            activeCount++;
        }
    }
    return activeApps;
}

int AppointmentsManager::getPendingApps() {
    Date today;
    int total = _appsFile.getTotalRegisters();
    int pending = 0;
    if (total <= 0) return -1;
    Appointment* apps = new Appointment[total];
    if (apps == NULL) return -1;
    if (!_appsFile.readFile(apps, total)) return -1;
    for (int i = 0; i < total; i++) {
        bool isActive = apps[i].getStatus();
        if (isActive && apps[i].getDate() > today) {
            pending++;
        }
    }
    delete[] apps;
    return pending;
}

// Solo compara si coincide el id
bool AppointmentsManager::searchById(Appointment reg, int nId) {
    if (reg.getAppId() == nId) return true;
    return false;
}

bool AppointmentsManager::idExists(int nId) {
    // Si devuelve un nro de posición, existe
    return _appsFile.searchReg(searchById, nId) >= 0 ? true : false;
}

bool AppointmentsManager::retryIfIdExists(bool exists) {
    if (exists) {
        std::cout << "El ID ingresado ya existe, presione cualquier tecla "
                     "para reintentar o ESC para salir.\n";
        if (rlutil::getkey() == rlutil::KEY_ESCAPE) return false;
        rlutil::cls();
    }
    return true;
}

bool AppointmentsManager::retryIfIdNotExists(bool exists) {
    if (!exists) {
        std::cout << "El ID ingresado NO EXISTE, presione cualquier tecla "
                     "para reintentar o ESC para salir.\n";
        if (rlutil::getkey() == rlutil::KEY_ESCAPE) return false;
        rlutil::cls();
    }
    return true;
}

bool AppointmentsManager::retryInvalidDate(bool valid) {
    if (!valid) {
        std::cout
            << "La fecha debe ser mayor o igual a la actual.\n"
               "Presione cualquier tecla para reintentar o ESC para salir.\n";
        if (rlutil::getkey() == rlutil::KEY_ESCAPE) return false;
        rlutil::cls();
    }
    return true;
}

bool AppointmentsManager::retryInvalidTime(bool valid) {
    if (!valid) {
        std::cout
            << "La hora ingresada es inválida o ya "
               "existe otro turno con el mismo horario.\n"
               "Presione cualquier tecla para reintentar o ESC para salir.\n";
        if (rlutil::getkey() == rlutil::KEY_ESCAPE) return false;
        rlutil::cls();
    }
    return true;
}

bool AppointmentsManager::validAppDate(Date date) {
    Date today;
    if (date < today) return false;
    return true;
}

bool AppointmentsManager::validAppTime(const Date& date, const Time& time) {
    int total = _appsFile.getTotalRegisters();
    if (total <= 0) return true;
    // Verificar que el turno no esté duplicado
    for (int i = 0; i < total; i++) {
        Appointment auxApp = _appsFile.readFile(i);
        if (auxApp.getAppId() == -1) return true;
        Time auxTime = auxApp.getTime();
        bool sameTime = auxTime.getHour() == time.getHour() &&
                        auxTime.getMin() == time.getMin();
        if (auxApp.getDate() == date && sameTime) return false;
    }
    // Verificar que no sea un horario pasado si es en el mismo dia
    bool sameDay = Date() == date;
    Time now;
    bool oldTime =
        now.getHour() > time.getHour() ||
        (now.getHour() >= time.getHour() && now.getMin() >= time.getMin());
    if (sameDay && oldTime) return false;
    return true;
}

int AppointmentsManager::getExpiredApps() {
    Date today;
    int total = _appsFile.getTotalRegisters();
    int expired = 0;
    if (total <= 0) return -1;
    Appointment* apps = new Appointment[total];
    if (apps == NULL) return -1;
    if (!_appsFile.readFile(apps, total)) return -1;
    for (int i = 0; i < total; i++) {
        bool isActive = apps[i].getStatus();
        if (isActive && apps[i].getDate() < today) {
            expired++;
        }
    }
    return expired;
}

int AppointmentsManager::deleteAllExpired() {
    Date today;
    int total = _appsFile.getTotalRegisters();
    int deleted = 0;
    if (total <= 0) return -1;
    Appointment* apps = new Appointment[total];
    if (apps == NULL) return -1;
    if (!_appsFile.readFile(apps, total)) return -1;
    // marcar registros a eliminar
    for (int i = 0; i < total; i++) {
        if (apps[i].getDate() < today) {
            bool success = _appsFile.markForDelete(i);
            if (!success) return -1;
            deleted++;
            // quitar comentario para debuggear
            /* printf("Eliminando registro nro %d id %d.\n", i,
                   apps[i].getAppId()); */
        }
    }
    // eliminacion física, si da error devuelve 0
    if (_appsFile.deleteAllMarked() == -1) return 0;
    return deleted;
}
