#include "ClientsManager.h"

#include <iostream>

#include "InputForm.h"
#include "listview.h"
#include "rlutil.h"

void ClientsManager::load() {
    InputForm idForm;
    Client auxClient;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id ingresado existe
    do {
        if (alreadyExists) {
            std::cout << "El ID de cliente ya existe, presione cualquier tecla "
                         "para reintentar o ESC para salir.\n";
            if (rlutil::getkey() == rlutil::KEY_ESCAPE) return;
            rlutil::cls();
        }
        idForm.setIntField("ID Cliente", nId, 4);
        // si no completa el form, salir
        if (!idForm.fill()) return;
        alreadyExists =
            _clientsFile.searchReg(searchById, nId) >= 0 ? true : false;
        idForm.clearAll();  // limpiar form
    } while (alreadyExists);

    auxClient = loadForm();
    // Si no se completo el form, salir
    if (auxClient.getIdPerson() == 0) return;

    auxClient.setClientId(nId);  // set del Id ingresado anteriormente
    if (_clientsFile.writeFile(auxClient)) {
        std::cout << "Cliente guardado con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el cliente.\n";
    }
}

Client ClientsManager::loadForm() {
    InputForm clientForm;
    Client auxClient;
    std::string name, lastname, address, email, phone;
    int DNI;

    clientForm.setStrField("Nombre", name, 30);
    clientForm.setStrField("Apellido", lastname, 30);
    clientForm.setAlphanumeric("Direccion", address, 45);
    clientForm.setPhoneField(phone, 15);
    clientForm.setEmailField(email, 45);
    clientForm.setIntField("DNI", DNI, 8);
    if (!clientForm.fill()) return auxClient;

    auxClient.setName(name);
    auxClient.setLastname(lastname);
    auxClient.setAddress(address);
    auxClient.setPhone(phone);
    auxClient.setEmail(email);
    auxClient.setIdPerson(DNI);
    return auxClient;
}

// Solo compara si coincide el id
bool ClientsManager::searchById(Client reg, int nId) {
    if (reg.getClientId() == nId) return true;
    return false;
}

Client ClientsManager::editForm(int regPos) {
    InputForm clientForm;
    Client auxClient;
    std::string name, lastname, address, email, phone;
    int DNI, nId;

    auxClient = _clientsFile.readFile(regPos);
    if (auxClient.getIdPerson() == 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxClient;
    }
    // Se cargan los datos para mostrarlas en el form.
    DNI = auxClient.getIdPerson();
    name = auxClient.getName();
    lastname = auxClient.getLastname();
    nId = auxClient.getClientId();
    address = auxClient.getAddress();
    email = auxClient.getEmail();
    phone = auxClient.getPhone();

    std::cout << "Editando cliente #" << nId << std::endl;
    // configurar form
    clientForm.setEditMode(true);  // modo edicion
    clientForm.setStrField("Nombre", name, 30);
    clientForm.setStrField("Apellido", lastname, 30);
    clientForm.setAlphanumeric("Direccion", address, 45);
    clientForm.setPhoneField(phone, 15);
    clientForm.setEmailField(email, 45);
    clientForm.setIntField("DNI", DNI, 8);

    // completar form
    bool success = clientForm.fill();
    if (success) {  // si se completa
        auxClient.setIdPerson(DNI);
        auxClient.setName(name);
        auxClient.setLastname(lastname);
        auxClient.setAddress(address);
        auxClient.setPhone(phone);
        auxClient.setEmail(email);
        return auxClient;
    }
    // si no se completa, devolver Client vacio
    return auxClient;
}

void ClientsManager::edit() {
    InputForm search;
    int nId;
    show();
    std::cout << "\nIngrese el ID del cliente a modificar.\n";
    search.setIntField("ID Cliente", nId, 4);
    if (!search.fill()) return;  // si no se completa, salir
    int regPos = _clientsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No se encontraron resultados.\n";
        system("pause");
        return;
    }
    // Si se encontro, pedir datos
    Client auxClient = editForm(regPos);
    // Si no se completo el formulario, salir
    if (auxClient.getIdPerson() == 0) {
        std::cout << "No se realizara la edicion.\n";
        system("pause");
        return;
    }

    // guardar cliente actualizado
    if (_clientsFile.updateFile(auxClient, regPos)) {
        std::cout << "Cliente editado con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    system("pause");
}

void ClientsManager::show() {
    int totalRegs = _clientsFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _clientsFields;

    if (totalRegs < 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        system("pause");  // TODO: usar rlutil ?
        return;
    }
    // Se crea la variable que va a contener todas las celdas, segun la cantidad
    // de registros
    std::string *cells = new std::string[totalCells];
    if (cells == NULL) {
        std::cout << "No hay memoria suficiente para mostrar los clientes.\n";
        return;
    }
    int cellPos = 0;  // acumula la posicion actual a asignar
    for (int i = 0; i < totalRegs; i++) {
        Client auxClient = _clientsFile.readFile(i);
        cells[cellPos] = std::to_string(auxClient.getClientId());
        cells[cellPos + 1] = auxClient.getName();
        cells[cellPos + 2] = auxClient.getLastname();
        cells[cellPos + 3] = std::to_string(auxClient.getIdPerson());
        cells[cellPos + 4] = auxClient.getAddress();
        cells[cellPos + 5] = auxClient.getPhone();
        cells[cellPos + 6] = auxClient.getEmail();
        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        cellPos += _clientsFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[7] = {"ID",        "Nombre",   "Apellido", "DNI",
                              "Direccion", "Telefono", "Email"};

    // Anchos maximos que van a ocupar cada dato de las columnas
    int colsWidth[7] = {5, 30, 30, 8, 45, 15, 45};
    // Se muestra todo el listado
    listview::printAll("CLIENTES", columns, cells, totalCells, _clientsFields,
                       colsWidth);
    delete[] cells;  // liberar memoria!
}