#include "RelationsManager.h"

#include <iostream>
#include "ClientsManager.h"
#include "InputForm.h"
#include "ListView.h"
#include "PetsManager.h"
#include "rlutil.h"
#include "utils.h"


void RelationsManager::load() {
    InputForm idForm;
    PetRelations auxPetR;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id ingresado existe
    
    idForm.setIntField("ID Relación", nId, 4);
    do {
        if (!retryIfIdExists(alreadyExists)) return;
        // si no completa el form, salir
        if (!idForm.fill()) return;
        alreadyExists = idExists(nId);
    } while (alreadyExists);

    // Si no existe la relacion, pedir el resto de datos
    auxPetR= loadForm();
    // Si no se completo el form, salir
       if (auxPetR.getPetId() == -1) return;


    // setear id ingresado
     auxPetR.setRelationId(nId);
    if (_petRelationsFile.writeFile(auxPetR)) {
        std::cout << "Relacion guardada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el turno.\n";
    }
}
    
   

PetRelations RelationsManager::loadForm() {
    InputForm petRelationsForm,petIdForm, clientIdForm;
    PetRelations auxPetR;
    PetsManager petsManager;
    ClientsManager clientsManager;
    bool owner;
    // bool status;
    int clientId=0, petId=0;
    bool alreadyExists = true;

 // pedir y buscar si el id mascota ingresado existe
    petIdForm.setIntField("ID Mascota", petId, 4);
    do {
        // si no existe, preguntar si quiere reintentar
        if (!retryIfIdNotExists(alreadyExists)) return auxPetR;
        // si no completa el form, salir
        if (!petIdForm.fill()) return auxPetR;
        alreadyExists = petsManager.idExists(petId);
    } while (!alreadyExists);  // si no existe, volver a pedir

    // pedir y buscar si el id cliente ingresado existe
    alreadyExists = true;
    clientIdForm.setIntField("ID Cliente", clientId, 4);
    do {
        // si no existe, preguntar si quiere reintentar
        if (!retryIfIdNotExists(alreadyExists)) return auxPetR;
        // si no completa el form, salir
        if (!clientIdForm.fill()) return auxPetR;
        alreadyExists = clientsManager.idExists(clientId);
    } while (!alreadyExists);  // si no existe, volver a pedir

   
    //petRelationsForm.setBoolField("Estado", status);
    petRelationsForm.setBoolField("¿Es propietario?", owner);

    if (!petRelationsForm.fill()) return auxPetR;

    auxPetR.setPetId(petId);
    auxPetR.setClientId(clientId);
    auxPetR.setOwner(owner);
    // auxPetR.setStatus(status);

    return auxPetR;
}

PetRelations RelationsManager::editForm(int regPos) {
    InputForm petRelationsForm;
    PetRelations auxPetR;

    int petId, clientId, nId;
    bool owner;
    //bool status;

    auxPetR = _petRelationsFile.readFile(regPos);
    if (auxPetR.getRelationId() == 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxPetR;
    }
    // Se cargan los datos para mostrarlas en el form.
    nId = auxPetR.getRelationId();
    petId = auxPetR.getPetId();
    clientId = auxPetR.getClientId();
    owner = auxPetR.getOwner();
   // status = auxPetR.getStatus();
    // TODO: VER PARA LLAMAR A LA FUNCION QUE MODIFICA EL ARCHIVO DE MASCOTA SI
    // SE ESTA CARGANDO UN REGISTRO DONDE
    /// OWNER ES TRUE Y MODIFICAR ESE ARCHIVO (EL DE PET)

    std::cout << "Editando Relaciones de la Mascota #" << nId << std::endl;
    //  configurar form

    petRelationsForm.setEditMode(true);  // modo edicion
    petRelationsForm.setIntField("ID Mascota", petId, 4);
    petRelationsForm.setIntField("ID Cliente", clientId, 4);
    petRelationsForm.setBoolField("¿Es propietario?", owner);
   // petRelationsForm.setBoolField("Activo?", status);

    // completar form
    bool success = petRelationsForm.fill();
    if (success) {  // si se completa

        auxPetR.setClientId(clientId);
        auxPetR.setPetId(petId);
        auxPetR.setOwner(owner);
       // auxPetR.setStatus(status);

        return auxPetR;
    }
    // si no se completa, devolver Relacion de la Mascota vacia
    return auxPetR;
}

void RelationsManager::edit() {
    InputForm search;
    int nId;
    show();
    std::cout << "\nIngrese el ID de la relacion a modificar.\n";
    search.setIntField("ID Relacion", nId, 4);
    if (!search.fill()) return;  // si no se completa, salir

    int regPos = _petRelationsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No se encontraron resultados.\n";
        utils::pause();
        return;
    }
    // Si se encontro, pedir datos
    PetRelations auxPetR = editForm(regPos);
    // Si no se completo el formulario, salir
    if (auxPetR.getRelationId() == 0) {
        std::cout << "No se realizara la edicion.\n";
        utils::pause();
        return;
    }

    // guardar relacion de mascota actualizada
    if (_petRelationsFile.updateFile(auxPetR, regPos)) {
        std::cout << "Relación de la Mascota editada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    utils::pause();
}

void RelationsManager::show() {
    int totalRegs = _petRelationsFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _petRelationsFields;

    if (totalRegs < 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        utils::pause();
        return;
    }
    // Se crea la variable que va a contener todas las celdas, segun la cantidad
    // de registros
    std::string *cells = new std::string[totalCells];
    if (cells == NULL) {
        std::cout << "No hay memoria suficiente para mostrar las relaciones.\n";
        return;
    }
    int cellPos = 0;  // acumula la posicion actual a asignar
    for (int i = 0; i < totalRegs; i++) {
        PetRelations auxPetR = _petRelationsFile.readFile(i);
        // Obtener todas las propiedades del cliente
        // Guardarlas en un vector de string
        std::string vecStr[4];
        auxPetR.toVecString(vecStr);
        for (int cell = 0; cell < _petRelationsFields; cell++) {
            cells[cellPos + cell] = vecStr[cell];
        }

        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        cellPos += _petRelationsFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[4] = {"ID RELACION", "ID MASCOTA", "ID CLIENTE",
                              "ES DUENIO?"};

    ListView petsRelationsList;
    petsRelationsList.addCells(cells, totalCells);
    petsRelationsList.addCols(columns, 4);
    petsRelationsList.setTitle(" RELACIONES DE MASCOTAS");
    petsRelationsList.show();
    delete[] cells;  // liberar memoria!
}

// Solo compara si coincide el id
bool RelationsManager::searchById(PetRelations reg, int nId) {
    if (reg.getRelationId() == nId) return true;
    return false;
}

bool RelationsManager::idExists(int nId) {
   return _petRelationsFile.searchReg(searchById, nId) >= 0 ? true : false;
}


bool RelationsManager::retryIfIdExists(bool exists) {
    if (exists) {
        std::cout << "El ID ingresado ya existe, presione cualquier tecla "
                     "para reintentar o ESC para salir.\n";
        if (rlutil::getkey() == rlutil::KEY_ESCAPE) return false;
        rlutil::cls();
    }
    return true;
}

bool RelationsManager::retryIfIdNotExists(bool exists) {
    if (!exists) {
        std::cout << "El ID ingresado NO EXISTE, presione cualquier tecla "
                     "para reintentar o ESC para salir.\n";
        if (rlutil::getkey() == rlutil::KEY_ESCAPE) return false;
        rlutil::cls();
    }
    return true;
}