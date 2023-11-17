#include <iostream>
#include <string>

#include "Menu.h"

// #include "VppFile.h"

#include "ClientsManager.h"
#include "Date.h"
#include "EmailTemplate.h"
#include "PetsManager.h"
#include "ProductManager.h"
#include "RelationsManager.h"
#include "VetsManager.h"
#include "functions.h"
#include "isvalid.h"

using namespace std;

void funcCualquier() {
    cout << "funcion que hace cualquier cosa\n";
    system("pause");
}

void funcSubMenu() {
    Menu subMenu("Otro Menu", true);
    subMenu.addOption("1. Cualquier cosa", funcCualquier);
    subMenu.addOption("2. Otra cualquier cosa", funcCualquier);
    subMenu.showMenu();
}

void sendTestEmail() {
    std::string emailTo;
    EmailTemplate emailHTML("data\\notification.html");
    bool successFormat = emailHTML.setEmailData("Facundo", "Nueva notificacion",
                                                Date(2, 11, 2023));
    if (!successFormat) {
        cout << "Error al crear email\n";
        system("pause");
        return;
    }

    cout << "Destinatario: ";
    cin >> emailTo;
    cout << "Enviando email..\n";
    bool isSent =
        sendEmail(emailTo.c_str(), "Nueva notificacion", emailHTML.getHTML());

    if (isSent) {
        notifSound();
        cout << "\n EMAIL ENVIADO!.\n";
    } else {
        cout << "Ocurrio un error :(\n";
    }
    system("pause");
}

void loadClient() {
    ClientsManager clients;
    clients.load();
    system("pause");
}

void showClients() {
    ClientsManager clients;
    clients.show();
    system("pause");
}

void editClients() {
    ClientsManager clients;
    clients.edit();
    system("pause");
}

void subMenuClientes() {
    Menu subMenu("CLIENTES", true);
    ClientsManager clients;

    subMenu.addOption("1. Cargar Cliente", loadClient);
    subMenu.addOption("2. Mostrar Clientes", showClients);
    subMenu.addOption("3. Editar cliente", editClients);
    subMenu.showMenu();
}

void loadVet() {
    VetsManager vets;
    vets.load();
    system("pause");
}
void showVets() {
    VetsManager vets;
    vets.show();
    system("pause");
}
void editVets() {
    VetsManager vets;
    vets.edit();
    system("pause");
}

void subMenuVeterinarios() {
    Menu subMenu("VETERINARIOS", true);
    VetsManager vets;

    subMenu.addOption("1. Cargar Veterinario", loadVet);
    subMenu.addOption("2. Mostrar Veterinarios", showVets);
    subMenu.addOption("3. Editar Veterinario", editVets);
    subMenu.showMenu();
}

void loadPet() {
    PetsManager pets;
    pets.load();
    system("pause");
}
void showPets() {
    PetsManager pets;
    pets.show();
    system("pause");
}

void editPets() {
    PetsManager pets;
    pets.edit();
    system("pause");
}

void subMenuMascotas() {
    Menu subMenu("MASCOTAS", true);
    PetsManager pets;

    subMenu.addOption("1. Cargar Mascota", loadPet);
    subMenu.addOption("2. Mostrar Mascotas", showPets);
    subMenu.addOption("3. Editar Mascota", editPets);
    subMenu.showMenu();
}

void loadRelation() {
    RelationsManager petsRelations;
    petsRelations.load();
    system("pause");
}

void showRelations() {
    RelationsManager petsRelations;
    petsRelations.show();
    system("pause");
}

void editRelation() {
    RelationsManager petsRelations;
    petsRelations.edit();
    system("pause");
}

void subMenuRelaciones() {
    Menu subMenu("RELACIONES", true);
    RelationsManager petsRelations;

    subMenu.addOption("1. Cargar Relacion", loadRelation);
    subMenu.addOption("2. Mostrar Mascotas", showRelations);
    subMenu.addOption("3. Editar Mascota", editRelation);
    subMenu.showMenu();
}
void loadProduct() {
    ProductManager products;
    products.load();
    system("pause");
}

void showProduct() {
    ProductManager products;
    products.show();
    system("pause");
}

void editProduct() {
    ProductManager products;
    products.edit();
    system("pause");
}

void subMenuProductos() {
    Menu subMenu("PRODUCTOS", true);
    ProductManager products;

    subMenu.addOption("1. Cargar Producto", loadProduct);
    subMenu.addOption("2. Mostrar producto", showProduct);
    subMenu.addOption("3. Editar producto", editProduct);
    subMenu.showMenu();
}

int main() {
    Menu test;

    // TODO: verificar que exista la carpeta data antes de iniciar todo

    test.addOption("1. Gestion de Clientes", subMenuClientes);
    test.addOption("2. Gestion de Turnos", funcSubMenu);
    test.addOption("3. Gestion de Inventarios", funcSubMenu);
    test.addOption("4. Enviar email", sendTestEmail);
    test.addOption("5. Gestion de Veterinarios", subMenuVeterinarios);
    test.addOption("6. Gestion de Mascotas", subMenuMascotas);
    test.addOption("7. Gestion de Relaciones", subMenuRelaciones);
    test.addOption("8. Gestion de Productos", subMenuProductos);
    test.showMenu();

    system("pause");
    return 0;
}

// Consultas:
/*
- Esta bien que en las clases NO tengamos los metodos cargar?, lo hacen los
  "managers"
- Esta bien que en las clases no validemos en los set?, de nuevo lo hacen los
  "managers" con "InputForm"
- La creacion de los objetos de SubMenu, por ej. submenu gestion de clientes,
  los creamos en clientManager? o en otra clase/cpp?
*/

// Solucion Menus:
/*
Hacer una clase Menus que tenga todos los objetos xManagers creados y submenus
*/