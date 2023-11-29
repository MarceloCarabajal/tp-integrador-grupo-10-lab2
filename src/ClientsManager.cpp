#include "ClientsManager.h"

#include <iostream>

#include "InputForm.h"
#include "ListView.h"
#include "rlutil.h"
#include "utils.h"

using namespace std;

void ClientsManager::load() {
    InputForm idForm;
    Client auxClient;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id ingresado existe
    do {
        if (alreadyExists) {
            if (!isActiveId(nId)) {
                std::cout << "El ID de cliente está dado de baja, elija otro "
                             "ID o elimine el registro desde el menú 'Limpiar "
                             "registros'.\n";
            } else {
                std::cout << "El ID de cliente ya existe, elija otro.\n";
            }
            std::cout << "presione cualquier tecla para reintentar o ESC para "
                         "salir.\n";
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
    auxClient.setStatus(true);
    return auxClient;
}

Client ClientsManager::editForm(int regPos) {
    InputForm clientForm(true);
    Client auxClient, auxFormClient;
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
    clientForm.setEditMode(true, true);  // modo edicion
    clientForm.setStrField("Nombre", name, 30);
    clientForm.setStrField("Apellido", lastname, 30);
    clientForm.setAlphanumeric("Direccion", address, 45);
    clientForm.setPhoneField(phone, 15);
    clientForm.setEmailField(email, 45);
    clientForm.setIntField("DNI", DNI, 8);

    // completar form
    bool success = clientForm.fill();
    if (success) {  // si se completa
        auxFormClient.setClientId(nId);
        auxFormClient.setIdPerson(DNI);
        auxFormClient.setName(name);
        auxFormClient.setLastname(lastname);
        auxFormClient.setAddress(address);
        auxFormClient.setPhone(phone);
        auxFormClient.setEmail(email);
        auxFormClient.setStatus(true);

        return auxFormClient;
    }
    // si no se completa, devolver Client vacio
    return auxFormClient;
}

void ClientsManager::edit() {
    InputForm search;
    int nId;
    show(false);
    std::cout << "\nIngrese el ID del cliente a modificar.\n";
    search.setIntField("ID Cliente", nId, 4);
    if (!search.fill()) return;  // si no se completa, salir
    int regPos = _clientsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No se encontraron resultados.\n";
        utils::pause();
        return;
    }
    // Si existe pero está dada de baja
    if (!isActiveId(nId)) {
        std::cout << "El cliente se encuentra dado de baja.\n";
        std::cout << "Si desea eliminarlo definitivamente o reutilizar este "
                     "ID, seleccione la "
                     "opción 'Limpiar registros' del menú.\n";
        utils::pause();
        return;
    }

    // Si se encontro, pedir datos
    Client auxClient = editForm(regPos);
    // Si no se completo el formulario, salir
    if (auxClient.getIdPerson() == 0) {
        std::cout << "No se realizara la edicion.\n";
        utils::pause();
        return;
    }

    // guardar cliente actualizado
    if (_clientsFile.updateFile(auxClient, regPos)) {
        std::cout << "Cliente editado con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    utils::pause();
}

void ClientsManager::show(bool showAndPause) {
    int totalRegs = _clientsFile.getTotalRegisters();

    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _clientsFields;

    if (totalRegs < 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        utils::pause();
        return;
    }
    if (totalRegs == 0) {
        std::cout << "No hay clientes para mostrar.\n";
        utils::pause();
        return;
    }
    // Se crea la variable que va a contener todas las celdas, segun la cantidad
    // de registros
    std::string* cells = new std::string[totalCells];
    if (cells == NULL) {
        std::cout << "No hay memoria suficiente para mostrar los clientes.\n";
        return;
    }
    int rowPos = 0;  // acumula la posicion actual a asignar
    for (int i = 0; i < totalRegs; i++) {
        Client auxClient = _clientsFile.readFile(i);
        // Obtener todas las propiedades del cliente
        // Guardarlas en un vector de string
        std::string vecStr[7];
        auxClient.toVecString(vecStr);
        for (int cell = 0; cell < _clientsFields; cell++) {
            if (auxClient.getStatus()) {
                cells[rowPos + cell] = vecStr[cell];
            } else {
                cells[rowPos + cell] = "";
            }
        }
        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        rowPos += _clientsFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[7] = {"ID",        "Nombre",   "Apellido", "DNI",
                              "Direccion", "Telefono", "Email"};

    ListView clientsList;
    clientsList.addCells(cells, totalCells);
    clientsList.addCols(columns, 7);
    clientsList.setTitle("CLIENTES");
    clientsList.show();

    delete[] cells;  // liberar memoria!
    if (showAndPause) utils::pause();
}

void ClientsManager::clearDeleted() {
    InputForm confirmForm;
    bool confirm;
    std::cout << "Esta acción buscará clientes dados de baja e "
                 "intentará eliminarlos definitivamente. Desea continuar?\n";
    confirmForm.setBoolField("[SI/NO]", confirm);
    if (!confirmForm.fill()) return;
    if (!confirm) return;
    std::cout << "Buscando registros...\n";
    int deleted = _clientsFile.deleteAllMarked();
    switch (deleted) {
        case 0:
            std::cout << "No se encontraron clientes dados de baja.\n";
            break;
        case -1:
            std::cout
                << "Ocurrió un error al intentar eliminar los clientes.\n";
            break;
        default:
            printf("Se eliminaron %d registros con éxito!\n", deleted);
            break;
    }
    utils::pause();
}

// Solo compara si coincide el id
bool ClientsManager::searchById(Client reg, int nId) {
    if (reg.getClientId() == nId) return true;
    return false;
}

bool ClientsManager::idExists(int nId) {
    return _clientsFile.searchReg(searchById, nId) >= 0 ? true : false;
}

bool ClientsManager::isActiveId(int nId) {
    int regPos = _clientsFile.searchReg(searchById, nId);
    if (regPos == -1) return false;
    Client auxClient = _clientsFile.readFile(regPos);
    if (auxClient.getStatus()) return true;
    return false;
}

void ClientsManager::cancel() {
    InputForm searchId, confirmForm;
    int nId;
    bool confirm;
    // mostrar clientes
    show(false);

    std::cout << "\nIngrese el ID del cliente a dar de baja.\n";
    searchId.setIntField("ID Cliente", nId, 4);
    if (!searchId.fill()) return;  // si no se completa, salir
    int regPos = _clientsFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No existe un cliente con el ID ingresado.\n";
        utils::pause();
        return;
    }

    printf("Se seleccionó el cliente #%d, confirma la baja provisoria.\n", nId);
    confirmForm.setBoolField("[SI/NO]", confirm);
    if (!confirmForm.fill()) return;
    if (!confirm) {
        std::cout << "No se realizará la cancelación.\n";
        utils::pause();
        return;
    }

    bool success = _clientsFile.markForDelete(regPos);

    if (success > 0) {
        std::cout << "Baja realizada con éxito!\n";
    } else {
        std::cout << "Ocurrió un error al intentar realizar la baja.\n";
    }
    utils::pause();
}

std::string ClientsManager::getFullNameById(int nId) {
    Client auxClient;
    int regPos = _clientsFile.searchReg(searchById, nId);
    auxClient = _clientsFile.readFile(regPos);
    if (auxClient.getIdPerson() == 0) return "ERROR";
    std::string fullName = std::string(auxClient.getName()) + " " +
                           std::string(auxClient.getLastname());
    return fullName;
}
