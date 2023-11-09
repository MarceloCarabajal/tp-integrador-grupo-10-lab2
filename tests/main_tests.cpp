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

#include "InputForm_tests.cpp"
#include "isvalid_tests.cpp"
#include "listview_tests.cpp"

int main() {
    // isvalidEmailTest();
    inputFormTest();
    // listviewTest();

    cout << endl;
    system("pause");

    return 0;
}