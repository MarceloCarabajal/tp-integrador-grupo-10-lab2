#include "VetsManager.h"

#include <iostream>

#include "InputForm.h"
#include "ListView.h"
#include "rlutil.h"
#include "utils.h"

void VetsManager::load() {
    InputForm idForm;
    Vet auxVet;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id ingresado existe
    do {
        if (alreadyExists) {
            std::cout
                << "El ID del veterinario ya existe, presione cualquier tecla "
                   "para reintentar o ESC para salir.\n";
            if (rlutil::getkey() == rlutil::KEY_ESCAPE) return;
            rlutil::cls();
        }
        idForm.setIntField("ID Veterinario", nId, 4);
        // si no completa el form, salir
        if (!idForm.fill()) return;
        alreadyExists =
            _vetsFile.searchReg(searchById, nId) >= 0 ? true : false;
        idForm.clearAll();  // limpiar form
    } while (alreadyExists);

    auxVet = loadForm();
    // Si no se completo el form, salir
    if (strcmp(auxVet.getSpeciality(), " ") == 0) return;

    auxVet.setIdVet(nId);  // set del Id ingresado anteriormente
    if (_vetsFile.writeFile(auxVet)) {
        std::cout << "Veterinario guardado con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el veterinario.\n";
    }
}

Vet VetsManager::loadForm() {
    InputForm vetForm;
    Vet auxVet;
    std::string name, lastname, speciality;
    int DNI;

    vetForm.setStrField("Nombre", name, 30);
    vetForm.setStrField("Apellido", lastname, 30);
    vetForm.setStrField("Especialidad", speciality, 15);
    vetForm.setIntField("DNI", DNI, 8);

    if (!vetForm.fill()) return auxVet;

    auxVet.setName(name);
    auxVet.setLastname(lastname);
    auxVet.setIdPerson(DNI);
    auxVet.setSpeciality(speciality);
    auxVet.setStatus(true);
    return auxVet;
}

Vet VetsManager::editForm(int regPos) {
    InputForm vetForm;
    Vet auxVet;
    std::string name, lastname, speciality;
    int DNI, nId;

    auxVet = _vetsFile.readFile(regPos);
    if (auxVet.getIdPerson() == 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxVet;
    }
    // Se cargan los datos para mostrarlas en el form.
    DNI = auxVet.getIdPerson();
    name = auxVet.getName();
    lastname = auxVet.getLastname();
    nId = auxVet.getIdVet();
    speciality = auxVet.getSpeciality();

    std::cout << "Editando Veterinario #" << nId << std::endl;
    // configurar form
    vetForm.setEditMode(true, true);  // modo edicion
    vetForm.setStrField("Nombre", name, 30);
    vetForm.setStrField("Apellido", lastname, 30);
    vetForm.setIntField("DNI", DNI, 8);
    vetForm.setStrField("Especialidad", speciality, 15);

    // completar form
    bool success = vetForm.fill();
    if (success) {  // si se completa
        auxVet.setIdVet(nId);
        auxVet.setIdPerson(DNI);
        auxVet.setName(name);
        auxVet.setLastname(lastname);
        auxVet.setSpeciality(speciality);
        auxVet.setStatus(true);

        return auxVet;
    }
    // si no se completa, devolver  Vete vacio
    return auxVet;
}

void VetsManager::edit() {
    InputForm search;
    int nId;
    show(false);


    int totalRegs= _vetsFile.getTotalRegisters();
    if (totalRegs<=0) return;

    std::cout << "\nIngrese el ID del veterinario a modificar.\n";
    search.setIntField("ID Veterinario", nId, 4);
    if (!search.fill()) return;  // si no se completa, salir
    int regPos = _vetsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No se encontraron resultados.\n";
        utils::pause();
        return;
    }
    // Si se encontro, pedir datos
    Vet auxVet = editForm(regPos);
    // Si no se completo el formulario, salir
    if (auxVet.getIdPerson() == 0) {
        std::cout << "No se realizara la edicion.\n";
        utils::pause();
        return;
    }

    // guardar veterinario actualizado
    if (_vetsFile.updateFile(auxVet, regPos)) {
        std::cout << "Veterinario editado con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    utils::pause();
}

void VetsManager::show(bool showAndPause) {
    int totalRegs = _vetsFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _vetsFields;

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
    std::string *cells = new std::string[totalCells];
    if (cells == NULL) {
        std::cout
            << "No hay memoria suficiente para mostrar los veterinarios.\n";
        return;
    }
    int rowPos = 0;  // acumula la posicion actual a asignar
    for (int i = 0; i < totalRegs; i++) {
        Vet auxVet = _vetsFile.readFile(i);
        // Obtener todas las propiedades del vete
        // Guardarlas en un vector de string
        std::string vecStr[5];
        auxVet.toVecString(vecStr);
        for (int cell = 0; cell < _vetsFields; cell++) {
            if (auxVet.getStatus()) {
                cells[rowPos + cell] = vecStr[cell];
            } else {
                cells[rowPos + cell] = "";
            }
        }

        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        rowPos += _vetsFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[5] = {"ID", "Nombre", "Apellido", "DNI",
                              "Especialidad"};

    ListView vetsList;
    vetsList.addCells(cells, totalCells);
    vetsList.addCols(columns, 5);
    vetsList.setTitle("VETERINARIOS");
    vetsList.show();
    delete[] cells;  // liberar memoria!
}

// Solo compara si coincide el id
bool VetsManager::searchById(Vet reg, int nId) {
    if (reg.getIdVet() == nId) return true;
    return false;
}

bool VetsManager::idExists(int nId) {
    return _vetsFile.searchReg(searchById, nId) >= 0 ? true : false;
}

void VetsManager::clearDeleted() {
    InputForm confirmForm;
    bool confirm;
    std::cout << "Esta acción buscará Veterinarios dadas de baja e "
                 "intentará eliminarlas definitivamente. Desea continuar?\n";
    confirmForm.setBoolField("[SI/NO]", confirm);
    if (!confirmForm.fill()) return;
    if (!confirm) return;
    std::cout << "Buscando registros...\n";
    int deleted = _vetsFile.deleteAllMarked();
    switch (deleted) {
        case 0:
            std::cout << "No se encontraron Veterinarios dados de baja.\n";
            break;
        case -1:
            std::cout
                << "Ocurrió un error al intentar eliminar los Veterinarios\n";
            break;
        default:
            printf("Se eliminaron %d registros con éxito!\n", deleted);
            break;
    }
    utils::pause();
}

void VetsManager::cancel() {
    InputForm searchId, confirmForm;
    int nId;
    bool confirm;
    // mostrar vacunacion
    show(false);

    std::cout << "\nIngrese el ID del Veterinario a dar de baja.\n";
    searchId.setIntField("ID Veterinario", nId, 4);
    if (!searchId.fill()) return;  // si no se completa, salir
    int regPos = _vetsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No existe Veterinarios con el ID ingresado.\n";
        utils::pause();
        return;
    }

    printf("Se seleccionó el Veterinario #%d, confirma la baja provisoria.\n",
           nId);
    confirmForm.setBoolField("[SI/NO]", confirm);
    if (!confirmForm.fill()) return;
    if (!confirm) {
        std::cout << "No se realizará la baja.\n";
        utils::pause();
        return;
    }

    bool success = _vetsFile.markForDelete(regPos);

    if (success) {
        std::cout << "Baja realizada con éxito!\n";
    } else {
        std::cout << "Ocurrió un error al intentar realizar la baja.\n";
    }
    utils::pause();
}

bool VetsManager::isActiveId(int nId) {
    int regPos = _vetsFile.searchReg(searchById, nId);
    if (regPos == -1) return false;
    Vet auxVet = _vetsFile.readFile(regPos);
    if (auxVet.getStatus()) return true;
    return false;
}
