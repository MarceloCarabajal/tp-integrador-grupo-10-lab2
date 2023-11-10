#include "ClientsManager.h"

#include "InputForm.h"
#include "listview.h"

void ClientsManager::load() {
    InputForm clientForm;
    std::string name, lastname, address, email, phone;
    int DNI;
    clientForm.setStrField("Nombre", name, 30);
    clientForm.setStrField("Apellido", lastname, 30);
    clientForm.setAlphanumeric("Direccion", address, 45);
    clientForm.setPhoneField(phone, 15);
    clientForm.setEmailField(email, 45);
    clientForm.setIntField("DNI", DNI, 8);
    if (clientForm.fill()) {
        Client auxClient;
        auxClient.setName(name);
        auxClient.setLastname(lastname);
        auxClient.setAddress(address);
        auxClient.setPhone(phone);
        auxClient.setEmail(email);
        auxClient.setIdPerson(DNI);
        if (_clientsFile.writeFile(auxClient)) {
            std::cout << "Cliente agregado con exito!\n";
        } else {
            std::cout << "Ocurrio un error al guardar el cliente.\n";
        }
    }
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
        cells[cellPos] = auxClient.getName();
        cells[cellPos + 1] = auxClient.getLastname();
        cells[cellPos + 2] = std::to_string(auxClient.getIdPerson());
        cells[cellPos + 3] = auxClient.getAddress();
        cells[cellPos + 4] = auxClient.getPhone();
        cells[cellPos + 5] = auxClient.getEmail();
        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        cellPos += _clientsFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[6] = {"Nombre",    "Apellido", "DNI",
                              "Direccion", "Telefono", "Email"};

    // Anchos maximos que van a ocupar cada dato de las columnas
    int colsWidth[6] = {30, 30, 8, 45, 15, 45};
    // Se muestra todo el listado
    listview::printAll("CLIENTES", columns, cells, totalCells, _clientsFields,
                       colsWidth);
    delete[] cells;  // liberar memoria!
}