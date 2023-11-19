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

using namespace std;

inline bool number(char n) {
    if (n >= '0' && n <= '9') return true;
    return false;
}

inline bool dateFormat(std::string str) {
    if (str.length() < 10) return false;
    if (str[2] != '/' || str[5] != '/') return false;
    for (size_t i = 0; i < str.length(); i++) {
        // pos 2||5 son las /
        if (i == 2 || i == 5) continue;
        if (!number(str[i])) return false;
    }
    if (stoi(str.substr(0, 2)) > 31) return false;
    if (stoi(str.substr(3, 2)) > 12) return false;
    if (stoi(str.substr(6, 4)) < 1900) return false;
    return true;
}

void testDateFormat() {
    // Test valid date format
    assert(dateFormat("01/01/2022") == true);
    assert(dateFormat("31/12/2022") == true);

    // Test invalid date format
    assert(dateFormat("1/1/2022") == false);    // Invalid length
    assert(dateFormat("01-01-2022") == false);  // Invalid delimiter
    assert(dateFormat("01/13/2022") == false);  // Invalid month
    assert(dateFormat("01/01/1020") == false);  // Invalid year
}

int main() {
    // isvalidEmailTest();
    // inputFormTest();
    // listviewTest();
    /*     ClientsManager clients;
        clients.load();
        clients.show();
        cout << endl; */
    testDateFormat();
    std::cout << "All tests passed!" << std::endl;
    system("pause");

    return 0;
}