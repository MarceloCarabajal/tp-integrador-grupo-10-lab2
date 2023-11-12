#include "PetsManager.h"

#include <iostream>

#include "InputForm.h"
#include "listview.h"
#include "rlutil.h"

void PetsManager::load() {
    InputForm idForm;
    Pet  auxPet;
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
        alreadyExists =
            _petsFile.searchReg(searchById, nId) >= 0 ? true : false;
        idForm.clearAll();  // limpiar form
    } while (alreadyExists);

    auxPet = loadForm();
    // Si no se completo el form, salir
    if (auxPet. getPetId() == 0) return;

     auxPet.setPetId(nId);  // set del Id ingresado anteriormente
    if (_petsFile.writeFile(auxPet)) {
        std::cout << "Mascota guardada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar la mascota.\n";
    }
}

 //////////int _petId, _ownerId;
   ////////char  _name[30], _specie[15], _breed[30], _currentDiagnosis[45];
  ////////////  Date _birthDate;



Pet PetsManager::loadForm() {
    InputForm petForm;
    Pet auxPet;
    std::string name, specie, breed, currentDiagnosis;
    Date birthDate; 
    int ownerId;

    petForm.setStrField("Nombre", name, 30);
    petForm.setStrField("Especie", specie, 15);
    petForm.setStrField("Raza", breed, 30);
    petForm.setStrField("Diagnostico actual",currentDiagnosis, 45);
    //TODO: VER LOS DOS SIGUIENTES: 
    petForm.setEmailField("Fecha de nacimiento", birthDate, 45);
    petForm.setIntField("ID Dueño", ownerId, 8);
    if (!petForm.fill()) return auxPet;


   //TODO: PET ID se seteaba mas arriba no? o hay que agregarlo?
    auxPet.setName(name);
    auxPet.setSpecie(specie);
    auxPet.setBreed(breed);
    auxPet.setCurrentDiagnosis(currentDiagnosis);
    auxPet.setBirthDate(birthDate);
    auxPet.setOwnerId(ownerId);
    return auxPet;

}

// Solo compara si coincide el id
bool PetsManager::searchById(Pet reg, int nId) {
    if (reg.getPetId() == nId) return true;
    return false;
}

Pet PetsManager::editForm(int regPos) {
    InputForm petForm;
    Pet auxPet;
    std::string name, specie, breed, currentDiagnosis;
    int  nId, ownerId;
    Date birthDate;

    auxPet = _petsFile.readFile(regPos);
    if (auxPet.getOwnerId() == 0) {
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
    petForm.setStrField("Diagnostico actual",currentDiagnosis, 45);
    //TODO: VER LOS DOS SIGUIENTES: 
    petForm.setEmailField("Fecha de nacimiento", birthDate, 45);
    petForm.setIntField("ID Dueño", ownerId, 8);


    // completar form
    bool success = petForm.fill();
    if (success) {  // si se completa
    //TODO: VER PET ID
        auxPet.setPetId(petId);
        auxPet.setName(name);
        auxPet.setBreed(breed);
        auxPet.setSpecie(specie);
        auxPet.setCurrentDiagnosis(currentDiagnosis);
        auxPet.setBirthDate(birthDate);
        auxPet.setOwnerId(ownerId);
        return auxPet;
    }
    // si no se completa, devolver Mascota vacia
    return auxPet;
}

void PetsManager::edit() {
    InputForm search;
    int nId;
    show();
    std::cout << "\nIngrese el ID de la mascota a modificar.\n";
    search.setIntField("ID Mascota, nId, 4);
    if (!search.fill()) return;  // si no se completa, salir
    int regPos = _petsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No se encontraron resultados.\n";
        system("pause");
        return;
    }
    // Si se encontro, pedir datos
   Pet auxPet = editForm(regPos);
    // Si no se completo el formulario, salir
    if (auxPet.getPetId() == 0) {
        std::cout << "No se realizara la edicion.\n";
        system("pause");
        return;
    }

    // guardar mascota actualizada
    if (_petsfile.updateFile(auxPet, regPos)) {
        std::cout << "Mascota editada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    system("pause");
}

void PetsManager::show() {
    int totalRegs = _petsFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _petsFields;

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
       Pet auxPet = _petsFile.readFile(i);
        cells[cellPos] = std::to_string(auxPet.getPetId());
        cells[cellPos + 1] = auxPet.getName();
        cells[cellPos + 2] = auxPet.getSpecie() ;
        cells[cellPos + 3] = auxPet.getBreed();
        cells[cellPos + 4] = auxPet.getCurrentDiagnosis();
        cells[cellPos + 5] = std::to_string(auxPet.getOwnerId());
        cells[cellPos + 6] = auxPet.getBirthDate().toString();

    
        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        cellPos += _petsFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[7] = {"ID",        "Nombre",   "Especie", "Raza",
                              "Diagnostico", "ID Dueño", "F. nacimiento"};

    // Anchos maximos que van a ocupar cada dato de las columnas
    int colsWidth[7] = {5, 30, 30, 8, 45, 15, 45};
    // Se muestra todo el listado
    listview::printAll("MASCOTAS", columns, cells, totalCells, _petsFields,
                       colsWidth);
    delete[] cells;  // liberar memoria!
}