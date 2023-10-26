#include <iostream>

#include "Menu.h"
#include "VppFile.h"
#include "functions.h"
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
    // TODO: Probar cuerpo HTML de Email
    cout << "Enviando email..\n";
    bool isSent = sendEmail(
        "facujmasino@gmail.com", "Prueba VETE++",
        "<b>La recepcion de este email implica la aprobacion directa del "
        "grupo 10.</b>");

    if (isSent) {
        cout << "\n EMAIL ENVIADO!.\n";
    } else {
        cout << "Ocurrio un error :(\n";
    }
    system("pause");
}

int main() {
    Menu test;

    test.addOption("1. Gestion de Clientes", funcSubMenu);
    test.addOption("2. Gestion de Turnos", funcSubMenu);
    test.addOption("3. Gestion de Inventarios", funcSubMenu);
    test.addOption("4. Enviar email", sendTestEmail);
    test.showMenu();
    system("pause");
    return 0;
}