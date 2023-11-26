#include "PetsManager.h"

#include <iostream>

#include "Date.h"
#include "InputForm.h"
#include "ListView.h"
#include "rlutil.h"
#include "utils.h"

void PetsManager::load() {
    InputForm idForm;
    Pet auxPet;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id ingresado existe
    do {
        if (alreadyExists) {
            std::cout << "El ID de Mascota ya existe, presione cualquier tecla "
                         "para reintentar o ESC para salir.\n";
            if (rlutil::getkey() == rlutil::KEY_ESCAPE) return;
            rlutil::cls();
        }
        idForm.setIntField("ID Mascota", nId, 4);
        // si no completa el form, salir
        if (!idForm.fill()) return;
        alreadyExists = idExists(nId);
        idForm.clearAll();  // limpiar form
    } while (alreadyExists);

    auxPet = loadForm();
    // Si no se completo el form, salir
    if (auxPet.getOwnerId() == -1) return;

    auxPet.setPetId(nId);  // set del Id ingresado anteriormente
    if (_petsFile.writeFile(auxPet)) {
        std::cout << "Mascota guardada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar la mascota.\n";
    }
}

Pet PetsManager::loadForm() {
    InputForm petForm;
    Pet auxPet;
    std::string name, specie, breed, currentDiagnosis;
    Date birthDate;
    int ownerId;

    petForm.setStrField("Nombre", name, 30);
    petForm.setStrField("Especie", specie, 15);
    petForm.setStrField("Raza", breed, 30);
    petForm.setStrField("Diagnostico actual", currentDiagnosis, 45);
    petForm.setDateField("Fecha de nacimiento", birthDate);
    petForm.setIntField("ID Dueño", ownerId, 4);
    if (!petForm.fill()) return auxPet;

    auxPet.setName(name);
    auxPet.setSpecie(specie);
    auxPet.setBreed(breed);
    auxPet.setCurrentDiagnosis(currentDiagnosis);
    auxPet.setBirthDate(birthDate);
    auxPet.setOwnerId(ownerId);
    return auxPet;
}

Pet PetsManager::editForm(int regPos) {
    InputForm petForm;
    Pet auxPet, auxFormPet;
    std::string name, specie, breed, currentDiagnosis;
    int nId, ownerId;
    Date birthDate;

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

    std::cout << "Editando Mascota #" << nId << std::endl;
    // configurar form
    petForm.setEditMode(true);  // modo edicion
    petForm.setStrField("Nombre", name, 30);
    petForm.setStrField("Especie", specie, 15);
    petForm.setStrField("Raza", breed, 30);
    petForm.setStrField("Diagnostico actual", currentDiagnosis, 45);
    petForm.setDateField("Fecha de nacimiento", birthDate);
    petForm.setIntField("ID Dueño", ownerId, 4);

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
        return auxFormPet;
    }
    // si no se completa, devolver Mascota vacia
    return auxFormPet;
    ;
}

void PetsManager::edit() {
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

void PetsManager::show() {
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
    int cellPos = 0;  // acumula la posicion actual a asignar
    for (int i = 0; i < totalRegs; i++) {
        Pet auxPet = _petsFile.readFile(i);
        // Obtener todas las propiedades de la Mascota
        // Guardarlas en un vector de string
        std::string vecStr[7];
        auxPet.toVecString(vecStr);
        for (int cell = 0; cell < _petsFields; cell++) {
            cells[cellPos + cell] = vecStr[cell];
        }

        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        cellPos += _petsFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[7] = {"ÍD",   "ID Dueño",    "Nombre",       "Especie",
                              "Raza", "Diagnóstico", "F. nacimiento"};

    ListView petsList;
    petsList.addCells(cells, totalCells);
    petsList.addCols(columns, 7);
    petsList.setTitle("MASCOTAS");
    petsList.show();
    delete[] cells;  // liberar memoria!
}

// Solo compara si coincide el id
bool PetsManager::searchById(Pet reg, int nId) {
    if (reg.getPetId() == nId) return true;
    return false;
}

bool PetsManager::idExists(int nId) {
    // Si devuelve un nro de posicion, existe
    return _petsFile.searchReg(searchById, nId) >= 0 ? true : false;
}