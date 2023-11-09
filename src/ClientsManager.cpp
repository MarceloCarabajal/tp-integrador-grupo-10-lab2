#include "ClientsManager.h"

#include "InputForm.h"
#include "listview.h"

void ClientsManager::load() {
    InputForm clientForm;
    std::string name, lastname, address, phone, email;
    int DNI;
    clientForm.setStrField("Nombre", name);
    clientForm.setStrField("Apellido", lastname);
    clientForm.setAlphanumeric("Direccion", address);
    clientForm.setStrField("Telefono", phone);
    clientForm.setEmailField(email);
    clientForm.setIntField("DNI", DNI);
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
    std::cout << "total obtenido" << totalRegs << ".\n" << std::endl;
    if (totalRegs < 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        system("pause");  // TODO: usar rlutil ?
        return;
    }
    std::string *cells = new std::string[totalRegs * _clientsFields];
    if (cells == NULL) {
        std::cout << "No hay memoria suficiente para mostrar los clientes.\n";
        return;
    }
    int cellPos = 0;
    Client auxClient = _clientsFile.readFile(0);
    std::cout << auxClient.getName();
    /*     for (int i = 0; i < totalRegs; i++) {
            std::cout << "cellPos: " << cellPos << "de "
                      << totalRegs * _clientsFields << std::endl;
            auxClient = _clientsFile.readFile(i);
            std::cout << auxClient.getAddress();
            cells[i] = auxClient.getAddress();
                     cells[cellPos + 1] = auxClient.getLastname();
                    cells[cellPos + 2] =
       std::to_string(auxClient.getIdPerson()); cells[cellPos + 3] =
       auxClient.getAddress(); cells[cellPos + 4] = auxClient.getPhone();
                    cells[cellPos + 5] = auxClient.getEmail();
            cellPos += _clientsFields;
            std::cout << "fin vuelta " << i << std::endl;
            std::cout << cells[i] << std::endl;
        } */
    std::string columns[6] = {"Nombre",    "Apellido", "DNI",
                              "Direccion", "Telefono", "Email"};
    int colsWidth[6] = {15, 15, 9, 30, 15, 30};
    listview::printAll("CLIENTES", columns, cells, totalRegs, _clientsFields,
                       colsWidth);

    delete[] cells;
}
