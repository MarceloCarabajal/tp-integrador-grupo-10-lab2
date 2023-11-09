#include <iostream>

#include "InputForm.h"

using namespace std;

void inputFormTest() {
    InputForm formTest;
    std::string nombre, apellido, email, dir;
    int edad, dni;
    formTest.setStrField("Nombre", nombre, 30);
    formTest.setStrField("Apellido", apellido, 30);
    formTest.setAlphanumeric("Direccion", dir, 45);
    formTest.setIntField("Edad", edad, 2);
    formTest.setIntField("DNI", dni, 8);
    formTest.setEmailField(email, 45);
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