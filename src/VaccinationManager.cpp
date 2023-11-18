#include "VaccinationManager.h"

#include <iostream>

#include "InputForm.h"
#include "ListView.h"
#include "rlutil.h"

void VaccinationManager::load() {
    InputForm idForm;
    Vaccination auxVaccination;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id ingresado existe
    do {
        if (alreadyExists) {
            std::cout
                << "El ID de Vacunacion ya existe, presione cualquier tecla "
                   "para reintentar o ESC para salir.\n";
            if (rlutil::getkey() == rlutil::KEY_ESCAPE) return;
            rlutil::cls();
        }
        idForm.setIntField("ID Vacunacion", nId, 4);
        // si no completa el form, salir
        if (!idForm.fill()) return;
        alreadyExists =
            _vaccinationFile.searchReg(searchById, nId) >= 0 ? true : false;
        idForm.clearAll();  // limpiar form
    } while (alreadyExists);

    auxVaccination = loadForm();
    // Si no se completo el form, salir
    if (auxVaccination.getAplicationId() == 0) return;

    auxVaccination.setAplicationId(nId);  // set del Id ingresado anteriormente
    if (_vaccinationFile.writeFile(auxVaccination)) {
        std::cout << "Vacunacion guardada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar la vacunacion.\n";
    }
}

Vaccination VaccinationManager::loadForm() {
    InputForm vaccinationForm;
    Vaccination auxVaccination;
    std::string nameVaccine;
    Date dateAplication, dateRevaccination;
    int petId;
    bool notified;

    vaccinationForm.setStrField(" Vacuna", nameVaccine, 15);
    vaccinationForm.setIntField("ID Mascota", petId, 4);

    // TODO: VER LOS DOS SIGUIENTES:
    // vaccinationForm.setFechaField("Fecha de aplicacion", dateAplication,
    // XXXXXXXXXXXXXX);
    // vaccinationForm.setFechaField("Fecha de revacunacion", dateRevaccination,
    // XXXXXXXXXXXXXX);
    // vaccinationForm.setIntField("Notificado", notified);
    if (!vaccinationForm.fill()) return auxVaccination;

    auxVaccination.setNameVaccine(nameVaccine);
    auxVaccination.setPetId(petId);
    auxVaccination.setDateAplication(dateAplication);
    auxVaccination.setDateRevaccination(dateRevaccination);
    auxVaccination.setNotified(notified);

    return auxVaccination;
}

// Solo compara si coincide el id
bool VaccinationManager::searchById(Vaccination reg, int nId) {
    if (reg.getAplicationId() == nId) return true;
    return false;
}

Vaccination VaccinationManager::editForm(int regPos) {
    InputForm vaccinationForm;
    Vaccination auxVaccination;
    std::string nameVaccine;
    Date dateAplication, dateRevaccination;
    int petId, nId;
    bool notified;

    auxVaccination = _vaccinationFile.readFile(regPos);
    if (auxVaccination.getAplicationId() == 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxVaccination;
    }
    // Se cargan los datos para mostrarlas en el form.
    nameVaccine = auxVaccination.getNameVaccine();
    nId = auxVaccination.getAplicationId();
    dateAplication = auxVaccination.getDateAplication();
    dateRevaccination = auxVaccination.getDateRevaccination();
    notified = auxVaccination.getNottified();
    petId = auxVaccination.getPeId();

    std::cout << "Editando vacunacion#" << nId << std::endl;
    // configurar form
    vaccinationForm.setEditMode(true);  // modo edicion

    vaccinationForm.setStrField(" Vacuna", nameVaccine, 15);
    vaccinationForm.setIntField("ID Mascota", petId, 4);

    // TODO: VER LOS DOS SIGUIENTES:
    // vaccinationForm.setFechaField("Fecha de aplicacion", dateAplication,
    // XXXXXXXXXXXXXX); vaccinationForm.setFechaField("Fecha de revacunacion",
    // dateRevaccination, XXXXXXXXXXXXXX);
    // vaccinationForm.setIntField("Notificado", notified);

    // completar form
    bool success = vaccinationForm.fill();
    if (success) {  // si se completa

        auxVaccination.setNameVaccine(nameVaccine);
        auxVaccination.setPetId(petId);
        auxVaccination.setDateAplication(dateAplication);
        auxVaccination.setDateRevaccination(dateRevaccination);
        auxVaccination.setNotified(notified);

        return auxVaccination;
    }
    // si no se completa, devolver Vaccination vacio
    return auxVaccination;
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
        system("pause");
        return;
    }
    // Si se encontro, pedir datos
    Vaccination auxVaccination = editForm(regPos);
    // Si no se completo el formulario, salir
    if (auxVaccination.getAplicationId() == 0) {
        std::cout << "No se realizara la edicion.\n";
        system("pause");
        return;
    }

    // guardar vacunacion actualizado
    if (_vaccinationFile.updateFile(auxVaccination, regPos)) {
        std::cout << "Vacunacion editada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    system("pause");
}

void VaccinationManager::show() {
    int totalRegs = _vaccinationFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _vaccinationFields;

    if (totalRegs < 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        system("pause");  // TODO: usar rlutil ?
        return;
    }
    // Se crea la variable que va a contener todas las celdas, segun la cantidad
    // de registros
    std::string *cells = new std::string[totalCells];
    if (cells == NULL) {
        std::cout << "No hay memoria suficiente para mostrar las aplicaciones "
                     "realizadas.\n";
        return;
    }
    int cellPos = 0;  // acumula la posicion actual a asignar
    for (int i = 0; i < totalRegs; i++) {
        Vaccination auxVaccination = _vaccinationFile.readFile(i);
        // Obtener todas las propiedades del cliente
        // Guardarlas en un vector de string
        std::string vecStr[6];
        auxVaccination.toVecString(vecStr);
        for (int cell = 0; cell < _vaccinationFields; cell++) {
            cells[cellPos + cell] = vecStr[cell];
        }
        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        cellPos += _vaccinationFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[6] = {"ID Aplicacion",      " Vacuna",
                              "Id Mascota ",        "Fecha aplicacion",
                              "Fecha revacunacion", "¿Notificado?"};

    ListView VaccinationList;
    VaccinationList.addCells(cells, totalCells);
    VaccinationList.addCols(columns, 6);
    VaccinationList.setTitle("Vacunaciones");
    VaccinationList.show();

    delete[] cells;  // liberar memoria!
}