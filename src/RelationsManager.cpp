#include "RelationsManager.h"

#include <iostream>

#include "InputForm.h"
#include "ListViewc.h"
#include "rlutil.h"

void RelationsManager::load() {
    InputForm idForm;
    PetRelations auxPetR;
    int nId = 0;
    bool alreadyExists = false;
/*
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
        alreadyExists =
            _petsFile.searchReg(searchById, nId) >= 0 ? true : false;
        idForm.clearAll();  // limpiar form
    } while (alreadyExists);
    */

    auxPetR = loadForm();
    // Si no se completo el form, salir
    if (auxPetR.getPetId() == 0) return;

    auxPetR.setPetId(nId);  // set del Id ingresado anteriormente
    if (_petRelationsFile.writeFile(auxPetR)) {
        std::cout << "Relación guardada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar la relacion.\n";
    }
}


int _petId;
int  _clientId;
bool _owner;

PetRelations RelationsManager::loadForm() {
    InputForm petRelationsForm;
    PetRelations auxPetR;
    bool owner;
    int clientId, petId;

   petRelationsForm.setIntField("ID Mascota", petId, 4);
   petRelationsForm.setIntField("ID Cliente", clientId, 4);
   //TODO: Ver como validamos BOOL 
  ////petRelationsForm.setIntField("¿Es propietario?", owner, xxxxxxxxxxx;
    if (!petRelationsForm.fill()) return auxPetR;

    auxPetR.setPetId(petId);
    auxPetR.setClientId(clientId);
    auxPetR.setOwner(owner);

    return auxPetR;
}
/*
// Solo compara si coincide el id
bool RelationsManager::searchById(PetRelations reg, int nId) {
    if (reg.getPetId() == nId) return true;
    return false;
}*/

PetRelations RelationsManager::editForm(int regPos) {
    InputForm petRelationsForm;
    PetRelations auxPetR;

    int petId,clientId; 
    bool owner;
  

    auxPetR = _petRelationsFile.readFile(regPos);
    if (auxPetR.getPetId() == 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxPetR;
    }
    // Se cargan los datos para mostrarlas en el form.
    petId = auxPetR.getPetId();
    clientId = auxPetR.getClientId();
    owner = auxPetR.getOwner();
    //TODO: VER PARA LLAMAR A LA FUNCION QUE MODIFICA EL ARCHIVO DE MASCOTA SI SE ESTA CARGANDO UN REGISTRO DONDE 
    ///OWNER ES TRUE Y MODIFICAR ESE ARCHIVO (EL DE PET)

    std::cout << "Editando Relaciones de la Mascota #" << nId << std::endl;
    // configurar form

    petRelationsForm.setEditMode(true);  // modo edicion
    petRelationsForm.setIntField("ID Mascota", petId, 4);
    petRelationsForm.setIntField("ID Cliente", clientId, 4);
   //TODO: Ver como validamos BOOL 
  ////petRelationsForm.setIntField("¿Es propietario?", owner, xxxxxxxxxxx;


   
    // completar form
    bool success = petRelationsForm.fill();
    if (success) {  // si se completa
            

        auxPetR.setClientId(clientId);
        auxPetR.setPetId(petId);
        auxPetR.setOwner(owner);
    
        return auxPetR;
    }
    // si no se completa, devolver Relacion de la Mascota vacia
    return auxPetR;
}

void RelationsManager::edit() {
    InputForm search;
    int nId;
    show();
    std::cout << "\nIngrese el ID de la mascota cuya relacion se quiere modificar.\n";
    search.setIntField("ID Mascota", nId, 4);
    if (!search.fill()) return;  // si no se completa, salir
    int regPos = _petRelationsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No se encontraron resultados.\n";
        system("pause");
        return;
    }
    // Si se encontro, pedir datos
    PetRelations auxPetR = editForm(regPos);
    // Si no se completo el formulario, salir
    if (auxPetR.getPetId() == 0) {
        std::cout << "No se realizara la edicion.\n";
        system("pause");
        return;
    }

    // guardar mascota actualizada
    if (_petRelationsFile.updateFile(auxPetR, regPos)) {
        std::cout << "Relación de la Mascota editada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    system("pause");
}

void RelationsManager::show() {
    int totalRegs = _petRelationsFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _petRelationsFields;

    if (totalRegs < 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        system("pause");  // TODO: usar rlutil ?
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
        PetRelations auxPetR = _petRelationsFile.readFile(i);
        cells[cellPos] = std::to_string(auxPetR.getPetId());
        cells[cellPos + 1] = std::to_string(auxPetR.getClientId());
        //TODO: VER BOOL COMO LO PONEMOS
       /// cells[cellPos + 2] = auxPet.getOwner();
        

        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        cellPos += _petRelationsFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[3] = {"ID MASCOTA",          "ID CLIENTE",   "ES DUEÑO?"};

    ListView petsRelationsList;
    petsRelationsList.addCells(cells, totalCells);
    petsRelationsList.addCols(columns, 3);
    petsRelationsList.setTitle(" RELACIONES DE MASCOTAS");
    petsRelationsList.show();
    delete[] cells;  // liberar memoria!
}

