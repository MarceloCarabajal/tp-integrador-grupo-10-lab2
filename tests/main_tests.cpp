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
using namespace std;

#include "InputForm.h"
#include "isvalid_tests.cpp"

int main() {
    // isvalidEmailTest();
    InputForm formTest;
    std::string nombre, apellido, email;
    int edad, dni;
    formTest.setStrField("Nombre", nombre);
    formTest.setStrField("Apellido", apellido);
    formTest.setIntField("Edad", edad);
    formTest.setIntField("DNI", dni);
    formTest.setEmailField(email);
    if (formTest.fill()) {
        cout << nombre << endl;
        cout << apellido << endl;
        cout << email << endl;
        cout << edad << endl;
    }
    system("pause");

    return 0;
}