/**
 * @file main_tests.cpp
 * @authors Bertello Ana, Carabajal Marcelo, Masino Facundo, Tola Lucas
 * @brief Usar este archivo para hacer pruebas
 *
 * Compilar usando el script compile_tests.bat
 *
 * @version 0.1
 * @date 2023-10-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>

#include "Menu.h"
#include "VppFile.h"
// #include "functions.h"

using namespace std;

class Prueba {
private:
    int numero;

public:
    void setNumero(int n) { numero = n; }
    int getNumero() { return numero; }
};

void hola() {
    cout << "hola" << endl;
    system("pause");
}
void chau() {
    cout << "chau" << endl;
    system("pause");
}

int main() {
    // handleMenu();
    /*     Prueba ppp;
        ppp.setNumero(101);

        VppFile test("test.vpp");

        test.writeFile(ppp);

        cout << test.readFile<Prueba>(0).getNumero();

        cout << endl << test.getTotalRegisters<Prueba>();

        cout << endl;
        cout << endl; */

    Menu test;

    test.addOption("1. Hola", hola);
    test.addOption("2. Chau", chau);
    test.addOption("3. Otro chau", chau);
    test.showMenu();

    system("pause");
    return 0;
}