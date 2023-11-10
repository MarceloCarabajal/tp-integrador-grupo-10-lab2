#include <iostream>
#include <string>

#include "Menu.h"

// #include "VppFile.h"

#include "ClientsManager.h"
#include "Date.h"
#include "EmailTemplate.h"
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

void subMenuClientes() {
    Menu subMenu("CLIENTES", true);
    ClientsManager clients;

    subMenu.addOption("1. Cargar Cliente", loadClient);
    subMenu.addOption("2. Mostrar Clientes", showClients);
    subMenu.showMenu();
}

int main() {
    Menu test;

    // TODO: verificar que exista la carpeta data antes de iniciar todo

    test.addOption("1. Gestion de Clientes", subMenuClientes);
    test.addOption("2. Gestion de Turnos", funcSubMenu);
    test.addOption("3. Gestion de Inventarios", funcSubMenu);
    test.addOption("4. Enviar email", sendTestEmail);
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