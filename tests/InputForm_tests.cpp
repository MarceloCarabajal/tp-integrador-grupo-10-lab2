#include <iostream>

#include "InputForm.h"


using namespace std;

void inputFormTest() {
    InputForm formTest;
    std::string nombre, apellido, email;
    int edad, dni;
    formTest.setStrField("Nombre", nombre);
    formTest.setStrField("Apellido", apellido);
    formTest.setIntField("Edad", edad);
    formTest.setIntField("DNI", dni);
    formTest.setEmailField(email);
    if (formTest.fill()) {
        cout << "Datos ingresados\n:";
        cout << nombre << endl;
        cout << apellido << endl;
        cout << email << endl;
        cout << edad << endl;
    }
}