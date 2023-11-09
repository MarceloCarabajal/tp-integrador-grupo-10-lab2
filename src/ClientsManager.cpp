#include "ClientsManager.h"

#include "InputForm.h"
#include "listview.h"

void ClientsManager::load() {
    InputForm clientForm;
    std::string name, lastname, address, phone, email;
    int DNI;
    clientForm.setStrField("Nombre", name, 30);
    clientForm.setStrField("Apellido", lastname, 30);
    clientForm.setAlphanumeric("Direccion", address, 45);
    clientForm.setStrField("Telefono[Sin 0 ni 15]", phone,
                           15);  // TODO: Crear metodo para telefonos
    // clientForm.setIntField("Telefono[Sin 0 ni 15]", phone, 15); // stoi out
    // of range, arreglar
    clientForm.setEmailField(email, 45);
    clientForm.setIntField("DNI", DNI, 8);
    if (clientForm.fill()) {
        Client auxClient;
        auxClient.setName(name.c_str());
        auxClient.setLastname(lastname.c_str());
        auxClient.setAddress(address.c_str());
        auxClient.setPhone(phone.c_str());
        auxClient.setEmail(email.c_str());
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
    int totalCells = totalRegs * _clientsFields;
    // std::cout << "total obtenido" << totalRegs << ".\n" << std::endl;
    if (totalRegs < 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        system("pause");  // TODO: usar rlutil ?
        return;
    }
    std::string *cells = new std::string[totalCells];
    if (cells == NULL) {
        std::cout << "No hay memoria suficiente para mostrar los clientes.\n";
        return;
    }
    int cellPos = 0;
    for (int i = 0; i < totalRegs; i++) {
        Client auxClient = _clientsFile.readFile(i);
        cells[cellPos] = auxClient.getAddress();
        cells[cellPos + 1] = auxClient.getLastname();
        cells[cellPos + 2] = std::to_string(auxClient.getIdPerson());
        cells[cellPos + 3] = auxClient.getAddress();
        cells[cellPos + 4] = auxClient.getPhone();
        cells[cellPos + 5] = auxClient.getEmail();
        cellPos += _clientsFields;
    }
    std::cout << cells[1] << cells[2] << std::endl;  // test
    std::string columns[6] = {"Nombre",    "Apellido", "DNI",
                              "Direccion", "Telefono", "Email"};
    int colsWidth[6] = {30, 30, 8, 45, 15, 45};
    listview::printAll("CLIENTES", columns, cells, totalCells, _clientsFields,
                       colsWidth);
    delete[] cells;
}
