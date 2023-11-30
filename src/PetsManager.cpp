#include "PetsManager.h"

#include <iostream>

#include "ClientsManager.h"
#include "Date.h"
#include "InputForm.h"
#include "ListView.h"
#include "RelationsManager.h"
#include "rlutil.h"
#include "utils.h"

void PetsManager::load() {
    InputForm idForm;
    RelationsManager relsManager;
    Pet auxPet;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id ingresado existe
    do {
        if (alreadyExists) {
            // Si existe pero está dada de baja
            if (!isActiveId(nId)) {
                std::cout << "La mascota se encuentra dada de baja.\n";
                std::cout << "Si desea utilizar este ID, seleccione la "
                             "opción 'Limpiar registros' del menú para "
                             "eliminar el registro.\n";
            } else {
                std::cout << "El ID de Mascota ya existe.\n";
            }
            std::cout << "Presione cualquier tecla para reintentar o ESC para "
                         "salir.\n";
            // esperar tecla
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
    // Si no se completo el form o se canceló la carga, salir
    if (auxPet.getOwnerId() == -1) return;

    auxPet.setPetId(nId);  // set del Id ingresado anteriormente
    if (_petsFile.writeFile(auxPet)) {
        std::cout << "Mascota guardada con exito!\n";
        int newRel = relsManager.autogenerateNew(auxPet.getOwnerId(), nId);
        if (newRel > 0) {
            printf("Se generó una nueva relación con id #%d.\n", newRel);
        } else {
            std::cout << "Ocurrió un error al actualizar el registro de "
                         "relaciones.\n";
        }
    } else {
        std::cout << "Ocurrio un error al guardar la mascota.\n";
    }
}

Pet PetsManager::loadForm() {
    InputForm petForm, clientIdForm;
    Pet auxPet;
    ClientsManager clientsManager;
    std::string name, specie, breed, currentDiagnosis;
    Date birthDate;
    int ownerId;
    bool alreadyExists = true;

    // pedir y buscar si el id cliente ingresado existe
    alreadyExists = true;
    clientIdForm.setIntField("ID Dueño", ownerId, 4);
    do {
        if (!retryIfIdNotExists(alreadyExists)) return auxPet;
        if (!clientIdForm.fill()) return auxPet;
        alreadyExists = clientsManager.idExists(ownerId);
    } while (!alreadyExists);

    petForm.setStrField("Nombre", name, 30);
    petForm.setStrField("Especie", specie, 15);
    petForm.setStrField("Raza", breed, 30);
    petForm.setStrField("Diagnostico actual", currentDiagnosis, 45);
    petForm.setDateField("Fecha de nacimiento", birthDate);
    if (!petForm.fill()) return auxPet;

    auxPet.setName(name);
    auxPet.setSpecie(specie);
    auxPet.setBreed(breed);
    auxPet.setCurrentDiagnosis(currentDiagnosis);
    auxPet.setBirthDate(birthDate);
    auxPet.setOwnerId(ownerId);
    auxPet.setStatus(true);
    return auxPet;
}

Pet PetsManager::editForm(int regPos) {
    InputForm petForm(true), clientIdForm(true, true), confirmForm;
    Pet auxPet, auxFormPet;
    std::string name, specie, breed, currentDiagnosis;
    ClientsManager clientsManager;
    RelationsManager relsManager;
    int nId, ownerId;
    Date birthDate;
    bool existentId, alreadyExists = true;

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

    // rlutil::cls();
    std::cout << "Editando Mascota #" << nId << std::endl;

    // pedir y buscar id dueño
    clientIdForm.setIntField("ID Dueño", ownerId, 4);
    existentId = false;
    while (!existentId) {
        if (!clientIdForm.fill()) return auxFormPet;
        existentId = clientsManager.idExists(ownerId);
        if (!retryIfIdNotExists(existentId)) return auxFormPet;
    }

    // Si el id del dueño es distinto, se crea una nueva relación o se solicita
    // editar la existente
    bool newOwner = auxPet.getOwnerId() != ownerId;
    if (newOwner) {
        bool relExists = relsManager.relationExists(auxPet.getPetId(), ownerId);
        if (relExists) {
            std::cout << "Ya existe una relación entre esta mascota y el ID de "
                         "cliente ingresado.\n";
            std::cout
                << "Si desea cambiar el dueño, edite la relación existente.\n";
            utils::pause();
            return auxFormPet;
        } else {
            std::cout << "\nATENCIÓN: Se cambió el ID dueño, esta acción "
                         "creara una nueva "
                         "relación en nuestros registros.\n";
            std::cout << "Desea continuar?\n";
            bool confirm;
            confirmForm.setBoolField("[SI/NO]", confirm);
            if (!confirmForm.fill()) return auxFormPet;
            if (!confirm) return auxFormPet;
            int newRel = relsManager.autogenerateNew(auxPet.getOwnerId(),
                                                     auxPet.getPetId());
            if (newRel != -1) {
                printf("Se generó una nueva relación con id #%d.\n", newRel);
            } else {
                std::cout << "Ocurrió un error al actualizar el registro de "
                             "relaciones.\n";
                return auxFormPet;
            }
        }
    }

    // configurar form
    petForm.setStrField("Nombre", name, 30);
    petForm.setStrField("Especie", specie, 15);
    petForm.setStrField("Raza", breed, 30);
    petForm.setStrField("Diagnostico actual", currentDiagnosis, 45);
    petForm.setDateField("Fecha de nacimiento", birthDate);

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
        auxFormPet.setStatus(true);

        return auxFormPet;
    }
    // si no se completa, devolver Mascota vacia
    return auxFormPet;
}

void PetsManager::edit() {
    InputForm search, confirmForm;
    int nId;
    show(false);
    std::cout << "\nIngrese el ID de la mascota a modificar.\n";
    search.setIntField("ID Mascota", nId, 4);
    if (!search.fill()) return;  // si no se completa, salir
    int regPos = _petsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No se encontraron resultados.\n";
        utils::pause();
        return;
    }
    // Si existe pero está dada de baja
    if (!isActiveId(nId)) {
        std::cout << "La mascota se encuentra dada de baja.\n";
        std::cout << "Si desea eliminarla definitivamente o reutilizar este "
                     "ID, seleccione la "
                     "opción 'Limpiar registros' del menú.\n";
        utils::pause();
        return;
    }

    // Si se encontro, pedir datos
    Pet auxPet = editForm(regPos);
    // Si no se completo el formulario o canceló la carga, salir
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

void PetsManager::show(bool showAndPause) {
    int totalRegs = _petsFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de
    // datos que contiene 1 registro
    int totalCells = totalRegs * _petsFields;

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
        std::cout << "No hay memoria suficiente para mostrar las mascotas.\n";
        return;
    }
    int rowPos = 0;  // acumula la posicion actual a asignar
    for (int i = 0; i < totalRegs; i++) {
        Pet auxPet = _petsFile.readFile(i);
        // Obtener todas las propiedades de la Mascota
        // Guardarlas en un vector de string
        std::string vecStr[7];
        auxPet.toVecString(vecStr);
        for (int cell = 0; cell < _petsFields; cell++) {
            if (auxPet.getStatus()) {
                cells[rowPos + cell] = vecStr[cell];
            } else {
                cells[rowPos + cell] = "";
            }
        }
        // se incrementa la posicion de la celda segun la cantidad de datos
        // que contiene el registro, que equivale a una fila de la lista
        rowPos += _petsFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[7] = {"ID",   "ID Dueño",    "Nombre",       "Especie",
                              "Raza", "Diagnóstico", "F. nacimiento"};

    ListView petsList;
    petsList.addCells(cells, totalCells);
    petsList.addCols(columns, 7);
    petsList.setTitle("MASCOTAS");
    petsList.show();
    delete[] cells;  // liberar memoria!

    if (showAndPause) utils::pause();
}
bool PetsManager::retryIfIdNotExists(bool exists) {
    if (!exists) {
        std::cout << "El ID ingresado NO EXISTE, presione cualquier tecla "
                     "para reintentar o ESC para salir.\n";
        if (rlutil::getkey() == rlutil::KEY_ESCAPE) return false;
        rlutil::cls();
    }
    return true;
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

// buscar si no fue dado de baja
bool PetsManager::isActiveId(int nId) {
    int regPos = _petsFile.searchReg(searchById, nId);
    if (regPos < 0) return false;
    Pet auxPet = _petsFile.readFile(regPos);
    if (auxPet.getPetId() == -1) return false;
    return auxPet.getStatus();
}

void PetsManager::clearDeleted() {
    InputForm confirmForm;
    bool confirm;
    std::cout << "Esta acción buscará Mascotas dadas de baja e "
                 "intentará eliminarlos definitivamente. Desea continuar?\n";
    confirmForm.setBoolField("[SI/NO]", confirm);
    if (!confirmForm.fill()) return;
    if (!confirm) return;
    std::cout << "Buscando registros...\n";
    int deleted = _petsFile.deleteAllMarked();
    switch (deleted) {
        case 0:
            std::cout << "No se encontraron mascotas dados de baja.\n";
            break;
        case -1:
            std::cout << "Ocurrió un error al intentar eliminar las mascotas\n";
            break;
        default:
            printf("Se eliminaron %d registros con éxito!\n", deleted);
            break;
    }
    utils::pause();
}

void PetsManager::cancel() {
    InputForm searchId, confirmForm;
    int nId;
    bool confirm;
    // mostrar mascotas
    show(false);

    std::cout << "\nIngrese el ID de la mascota a dar de baja.\n";
    searchId.setIntField("ID Mascota", nId, 4);
    if (!searchId.fill()) return;  // si no se completa, salir
    int regPos = _petsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No existe una mascota con el ID ingresado.\n";
        utils::pause();
        return;
    }

    printf("Se seleccionó la mascota #%d, confirma la baja provisoria.\n", nId);
    confirmForm.setBoolField("[SI/NO]", confirm);
    if (!confirmForm.fill()) return;
    if (!confirm) {
        std::cout << "No se realizará la baja.\n";
        utils::pause();
        return;
    }

    bool success = _petsFile.markForDelete(regPos);

    if (success) {
        std::cout << "Baja realizada con éxito!\n";
    } else {
        std::cout << "Ocurrió un error al intentar realizar la baja.\n";
    }
    utils::pause();
}

// Esta funcion es utilizada por RelationsManager para actualizar el id del
// dueño
bool PetsManager::updateOwner(int ownerId, int petId) {
    int regPos = _petsFile.searchReg(searchById, petId);
    if (regPos < 0) return false;
    Pet auxPet = _petsFile.readFile(petId);
    if (auxPet.getPetId() == -1) return false;
    auxPet.setOwnerId(ownerId);
    bool success = _petsFile.updateFile(auxPet, regPos);
    return success;
}

std::string PetsManager::getNameById(int nId) {
    int regPos = _petsFile.searchReg(searchById, nId);
    Pet auxPet = _petsFile.readFile(regPos);
    if (auxPet.getPetId() == -1) return "ERROR";
    return auxPet.getName();
}