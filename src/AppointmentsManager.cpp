#include "AppointmentsManager.h"

#include <iostream>

#include "InputForm.h"
#include "ListView.h"
#include "rlutil.h"
#include "utils.h"

void AppointmentsManager::load() {
    InputForm idForm;
    Appointment auxAppointment;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id ingresado existe
    do {
        if (alreadyExists) {
            std::cout << "El ID del turno ya existe, presione cualquier tecla "
                         "para reintentar o ESC para salir.\n";
            if (rlutil::getkey() == rlutil::KEY_ESCAPE) return;
            rlutil::cls();
        }
        idForm.setIntField("ID Turno", nId, 4);
        // si no completa el form, salir
        if (!idForm.fill()) return;
        alreadyExists =
            _appointmentsFile.searchReg(searchById, nId) >= 0 ? true : false;
        idForm.clearAll();  // limpiar form
    } while (alreadyExists);

    auxAppointment = loadForm();
    // Si no se completo el form, salir
    if (auxAppointment.getAppId() == 0) return;

    auxAppointment.setAppId(nId);  // set del Id ingresado anteriormente
    if (_appointmentsFile.writeFile(auxAppointment)) {
        std::cout << "Veterinario guardado con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el veterinario.\n";
    }
}

Appointment AppointmentsManager::loadForm() {
    InputForm AppointmentForm;
    Appointment auxAppointment;
    Date dateApp;
    Time timeApp;
    std::string reason;
    bool attended;
    int clientId, petId;

    AppointmentForm.setDateField("Fecha", dateApp);
    // AppointmentForm.set   ("Hora", timeApp); TODO: Creo que la hr no seria
    // necesaria
    AppointmentForm.setBoolField("Asistió", attended);
    AppointmentForm.setStrField("Motivo", reason, 30);
    AppointmentForm.setIntField("Cliente ID", clientId, 4);
    AppointmentForm.setIntField("Mascota ID", petId, 4);

    if (!AppointmentForm.fill()) return auxAppointment;

    auxAppointment.setpetId(petId);
    auxAppointment.setDate(dateApp);
    auxAppointment.setTime(timeApp);
    auxAppointment.setReason(reason);
    auxAppointment.setAttended(attended);
    auxAppointment.setClientId(clientId);

    return auxAppointment;
}

// Solo compara si coincide el id
bool AppointmentsManager::searchById(Appointment reg, int nId) {
    if (reg.getAppId() == nId) return true;
    return false;
}

Appointment AppointmentsManager::editForm(int regPos) {
    InputForm AppointmentForm;
    Appointment auxAppointment;
    Date dateApp;
    Time timeApp;
    std::string reason;
    bool attended;
    int clientId, petId, nId;

    auxAppointment = _appointmentsFile.readFile(regPos);
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

        auxAppointment.setpetId(petId);
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
    int regPos = _appointmentsFile.searchReg(searchById, nId);
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
    if (_appointmentsFile.updateFile(auxAppointment, regPos)) {
        std::cout << "Turno editado con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    utils::pause();
}

void AppointmentsManager::show() {
    int totalRegs = _appointmentsFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _AppointmentsFields;

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
        Appointment auxAppointment = _appointmentsFile.readFile(i);
        // Obtener todas las propiedades del vete
        // Guardarlas en un vector de string
        std::string vecStr[7];
        auxAppointment.toVecString(vecStr);
        for (int cell = 0; cell < _AppointmentsFields; cell++) {
            cells[cellPos + cell] = vecStr[cell];
        }

        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        cellPos += _AppointmentsFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[8] = {"ID Turno", "ID Mascota", "Fecha",     "Hora",
                              "Motivo",   "Asistio",    "ID Cliente"};

    ListView appvetsList;
    appvetsList.addCells(cells, totalCells);
    appvetsList.addCols(columns, 7);
    appvetsList.setTitle("TURNOS");
    appvetsList.show();

    delete[] cells;  // liberar memoria!
}
