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

#include <cassert>
#include <iostream>
#include <string>

#include "isvalid.h"

using namespace std;

inline bool number(char n) {
    if (n >= '0' && n <= '9') return true;
    return false;
}

inline bool floatType(std::string str) {
    int dotFounds = 0;
    if (str.length() == 0) return false;
    for (size_t i = 0; i < str.length(); i++) {
        if (!number(str[i]) && str[i] != '.') return false;
        if (str[i] == '.') dotFounds++;
        if (str[i] == '.' && i == str.length() - 1) return false;
        if (str[i] == '.' && i == 0) return false;
    }
    if (dotFounds > 1) return false;
    return true;
}

void testFloatType() {
    // Test 1: Empty string
    assert(floatType("") == false);

    // Test 2: String with only digits
    assert(floatType("12345") == true);

    // Test 3: String with only a dot
    assert(floatType(".") == false);

    // Test 4: String with multiple dots
    assert(floatType("12.34.56") == false);

    // Test 5: String with a dot at the beginning
    assert(floatType(".123") == false);

    // Test 6: String with a dot at the end
    assert(floatType("123.") == false);

    // Test 7: Valid float number
    assert(floatType("3.14") == true);

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    // isvalidEmailTest();
    // inputFormTest();
    // listviewTest();
    /*     ClientsManager clients;
        clients.load();
        clients.show();
        cout << endl; */
    testFloatType();
    system("pause");

    return 0;
}