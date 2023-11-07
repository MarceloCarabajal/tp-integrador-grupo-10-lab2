#include <iostream>
#include <string>

#include "Menu.h"

// #include "VppFile.h"

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

int main() {
    Menu test;

    // TODO: verificar que exista la carpeta data antes de iniciar todo

    /*     test.addOption("1. Gestion de Clientes", funcSubMenu);
        test.addOption("2. Gestion de Turnos", funcSubMenu);
        test.addOption("3. Gestion de Inventarios", funcSubMenu);
        test.addOption("4. Enviar email", sendTestEmail);
        test.showMenu(); */

    system("pause");
    return 0;
}