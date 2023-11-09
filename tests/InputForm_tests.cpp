#include <iostream>

#include "InputForm.h"

using namespace std;

void inputFormTest() {
    InputForm formTest;
    std::string nombre, apellido, email, dir;
    int edad, dni;
    formTest.setStrField("Nombre", nombre);
    formTest.setStrField("Apellido", apellido);
    formTest.setAlphanumeric("Direccion", dir);
    formTest.setIntField("Edad", edad);
    formTest.setIntField("DNI", dni);
    formTest.setEmailField(email);
    if (formTest.fill()) {
        cout << "Datos ingresados:\n";
        cout << nombre << endl;
        cout << apellido << endl;
        cout << dir << endl;
        cout << email << endl;
        cout << edad << endl;
        cout << dni << endl;
    }
}