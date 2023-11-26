#include "AppointmentsManager.h"

#include <iostream>

#include "ClientsManager.h"
#include "InputForm.h"
#include "ListView.h"
#include "PetsManager.h"
#include "rlutil.h"
#include "utils.h"

void AppointmentsManager::load() {
    InputForm appIdForm;
    Appointment auxAppointment;
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
    auxAppointment = loadForm();
    // Si no se completo el form, salir
    if (strlen(auxAppointment.getReason()) == 0) return;

    // setear id ingresado
    auxAppointment.setAppId(nId);
    if (_appsFile.writeFile(auxAppointment)) {
        std::cout << "Turno guardado con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el turno.\n";
    }
    utils::pause();
}

Appointment AppointmentsManager::loadForm() {
    InputForm AppointmentForm, petIdForm, clientIdForm, dateForm, timeForm;
    Appointment auxAppointment;
    PetsManager petsManager;
    ClientsManager clientsManager;
    Date appDate;
    Time appTime;
    std::string reason;
    int petId = 0, clientId = 0;
    bool attended, alreadyExists = true;

    // pedir y buscar si el id mascota ingresado existe
    petIdForm.setIntField("ID Mascota", petId, 4);
    do {
        // si no existe, preguntar si quiere reintentar
        if (!retryIfIdNotExists(alreadyExists)) return auxAppointment;
        // si no completa el form, salir
        if (!petIdForm.fill()) return auxAppointment;
        alreadyExists = petsManager.idExists(petId);
    } while (!alreadyExists);  // si no existe, volver a pedir

    // pedir y buscar si el id cliente ingresado existe
    alreadyExists = true;
    clientIdForm.setIntField("ID Cliente", clientId, 4);
    do {
        if (!retryIfIdNotExists(alreadyExists)) return auxAppointment;
        if (!clientIdForm.fill()) return auxAppointment;
        alreadyExists = clientsManager.idExists(clientId);
    } while (!alreadyExists);

    // pedir y validar fecha
    dateForm.setDateField("Fecha", appDate);
    bool validDate = true;
    do {
        if (!validDate) {
            std::cout << "La fecha debe ser mayor o igual a la actual.\n";
        }
        if (!dateForm.fill()) return auxAppointment;
        validDate = true;  // validAppDate(appDate);
    } while (!validDate);

    // pedir y validar hora
    timeForm.setTimeField("Hora", appTime);
    bool validTime = false;
    while (!validTime) {
        if (!timeForm.fill()) return auxAppointment;
        validTime = true;  // validAppTime(appDate, appTime);
        if (!retryInvalidTime(validTime)) return auxAppointment;
    }

    AppointmentForm.setBoolField("Asistió", attended);
    AppointmentForm.setStrField("Motivo", reason, 30);

    if (!AppointmentForm.fill()) return auxAppointment;

    auxAppointment.setDate(appDate);
    auxAppointment.setTime(appTime);
    auxAppointment.setReason(reason);
    auxAppointment.setAttended(attended);
    auxAppointment.setPetId(petId);
    auxAppointment.setClientId(clientId);
    auxAppointment.setStatus(true);

    return auxAppointment;
}

Appointment AppointmentsManager::editForm(int regPos) {
    InputForm AppointmentForm, dateForm;
    Appointment auxAppointment, auxFormAppointment;
    Date appDate;
    Time appTime;
    std::string reason;
    bool attended;
    int clientId, petId, nId;

    auxAppointment = _appsFile.readFile(regPos);
    if (auxAppointment.getAppId() == -1) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxAppointment;
    }
    // Se cargan los datos para mostrarlas en el form.
    appDate = auxAppointment.getDate();
    appTime = auxAppointment.getTime();
    reason = auxAppointment.getReason();
    nId = auxAppointment.getAppId();
    attended = auxAppointment.getAttended();
    petId = auxAppointment.getpetId();
    clientId = auxAppointment.getClientId();

    std::cout << "Editando Turno #" << nId << std::endl;
    // configurar form
    AppointmentForm.setEditMode(true);  // modo edicion

    AppointmentForm.setDateField("Fecha", appDate);
    bool validDate = true;
    do {
        if (!validDate) {
            std::cout << "La fecha debe ser mayor o igual a la actual.\n";
        }
        if (!dateForm.fill()) return auxAppointment;
        validDate = validAppDate(appDate);
    } while (!validDate);

    // AppointmentForm.set   ("Hora", appTime); // TODO: es necesaria?
    AppointmentForm.setBoolField("Asistio", attended);
    AppointmentForm.setStrField("Motivo", reason, 30);
    AppointmentForm.setIntField("Cliente ID", clientId, 4);
    AppointmentForm.setIntField("Mascota ID", petId, 4);

    // completar form
    bool success = AppointmentForm.fill();
    if (success) {  // si se completa
        auxFormAppointment.setAppId(nId);
        auxFormAppointment.setPetId(petId);
        auxFormAppointment.setDate(appDate);
        auxFormAppointment.setTime(appTime);
        auxFormAppointment.setReason(reason);
        auxFormAppointment.setAttended(attended);
        auxFormAppointment.setClientId(clientId);
        auxFormAppointment.setStatus(true);

        return auxFormAppointment;
    }
    // si no se completa, devolver  Turno vacio
    return auxFormAppointment;
}

void AppointmentsManager::edit() {
    InputForm search;
    int nId;
    show();
    std::cout << "\nIngrese el ID del turno a modificar.\n";
    search.setIntField("ID Turno", nId, 4);
    if (!search.fill()) return;  // si no se completa, salir
    int regPos = _appsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No se encontraron resultados.\n";
        utils::pause();
        return;
    }
    // Si se encontro, pedir datos
    Appointment auxAppointment = editForm(regPos);
    // Si no se completo el formulario, salir
    if (auxAppointment.getAppId() == -1) {
        std::cout << "No se realizara la edicion.\n";
        utils::pause();
        return;
    }

    // guardar turno actualizado
    if (_appsFile.updateFile(auxAppointment, regPos)) {
        std::cout << "Turno editado con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    utils::pause();
}

void AppointmentsManager::show() {
    int totalRegs = _appsFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _appsFields;

    if (totalRegs < 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
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
        Appointment auxAppointment = _appsFile.readFile(i);
        // Obtener todas las propiedades del vete
        // Guardarlas en un vector de string
        std::string vecStr[7];
        auxAppointment.toVecString(vecStr);
        for (int cell = 0; cell < _appsFields; cell++) {
            // solo llena las celdas si es un registro activo
            if (auxAppointment.getStatus()) {
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
    std::string columns[8] = {"ID",     "ID Mascota", "Fecha",     "Hora",
                              "Motivo", "Asistio",    "ID Cliente"};

    ListView appvetsList;
    appvetsList.addCells(cells, totalCells);
    appvetsList.addCols(columns, 7);
    appvetsList.setTitle("TURNOS");
    appvetsList.show();

    delete[] cells;  // liberar memoria!
    utils::pause();
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