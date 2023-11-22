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
}

Appointment AppointmentsManager::loadForm() {
    InputForm AppointmentForm, petIdForm, clientIdForm;
    Appointment auxAppointment;
    PetsManager petsManager;
    ClientsManager clientsManager;
    Date dateApp;
    Time timeApp;
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
        // si no existe, preguntar si quiere reintentar
        if (!retryIfIdNotExists(alreadyExists)) return auxAppointment;
        // si no completa el form, salir
        if (!clientIdForm.fill()) return auxAppointment;
        alreadyExists = clientsManager.idExists(clientId);
    } while (!alreadyExists);  // si no existe, volver a pedir

    AppointmentForm.setDateField("Fecha", dateApp);
    // AppointmentForm.set   ("Hora", timeApp); TODO: Creo que la hr no seria
    // necesaria
    AppointmentForm.setBoolField("Asistió", attended);
    AppointmentForm.setStrField("Motivo", reason, 30);

    if (!AppointmentForm.fill()) return auxAppointment;

    auxAppointment.setDate(dateApp);
    auxAppointment.setTime(timeApp);
    auxAppointment.setReason(reason);
    auxAppointment.setAttended(attended);
    auxAppointment.setPetId(petId);
    auxAppointment.setClientId(clientId);

    return auxAppointment;
}

Appointment AppointmentsManager::editForm(int regPos) {
    InputForm AppointmentForm;
    Appointment auxAppointment;
    Date dateApp;
    Time timeApp;
    std::string reason;
    bool attended;
    int clientId, petId, nId;

    auxAppointment = _appsFile.readFile(regPos);
    if (auxAppointment.getAppId() == 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxAppointment;
    }
    // Se cargan los datos para mostrarlas en el form.
    dateApp = auxAppointment.getDate();
    timeApp = auxAppointment.getTime();
    reason = auxAppointment.getReason();
    nId = auxAppointment.getAppId();
    attended = auxAppointment.getAttended();
    petId = auxAppointment.getpetId();
    clientId = auxAppointment.getClientId();

    std::cout << "Editando Turno #" << nId << std::endl;
    // configurar form
    AppointmentForm.setEditMode(true);  // modo edicion

    AppointmentForm.setDateField("Fecha", dateApp);
    // AppointmentForm.set   ("Hora", timeApp); // TODO: es necesaria?
    AppointmentForm.setBoolField("Asistio", attended);
    AppointmentForm.setStrField("Motivo", reason, 30);
    AppointmentForm.setIntField("Cliente ID", clientId, 4);
    AppointmentForm.setIntField("Mascota ID", petId, 4);

    // completar form
    bool success = AppointmentForm.fill();
    if (success) {  // si se completa

        auxAppointment.setPetId(petId);
        auxAppointment.setDate(dateApp);
        auxAppointment.setTime(timeApp);
        auxAppointment.setReason(reason);
        auxAppointment.setAttended(attended);
        auxAppointment.setClientId(clientId);

        return auxAppointment;
    }
    // si no se completa, devolver  Turno vacio
    return auxAppointment;
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
    if (auxAppointment.getAppId() == 0) {
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
    std::string *cells = new std::string[totalCells];
    if (cells == NULL) {
        std::cout << "No hay memoria suficiente para mostrar los turnos "
                     "veterinarios.\n";
        return;
    }
    int cellPos = 0;  // acumula la posicion actual a asignar
    for (int i = 0; i < totalRegs; i++) {
        Appointment auxAppointment = _appsFile.readFile(i);
        // Obtener todas las propiedades del vete
        // Guardarlas en un vector de string
        std::string vecStr[7];
        auxAppointment.toVecString(vecStr);
        for (int cell = 0; cell < _appsFields; cell++) {
            cells[cellPos + cell] = vecStr[cell];
        }

        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        cellPos += _appsFields;
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