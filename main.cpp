#include <iostream>

#include "Menu.h"
// #include "VppFile.h"

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
    std::string emailTo;
    // TODO: Probar cuerpo HTML de Email

    cout << "Destinatario: ";
    cin >> emailTo;
    cout << "Enviando email..\n";
    bool isSent = sendEmail(
        emailTo.c_str(), "VETE++ - Notificacion Recibida",
        "<h1>Vete++ - Sistema de gestion</h1>"
        "<p>Texto de prueba... 1 2 3</p>"
        "<i>La recepcion de este email implica la aprobacion directa del "
        "grupo 10.</i>");

    if (isSent) {
        notifSound();
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