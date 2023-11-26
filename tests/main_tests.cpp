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

#include "TimeCls.h"
#include "isvalid.h"

using namespace std;
using namespace isvalid;

void testTimeFormat() {
    // Valid time format
    assert(timeFormat("12:34") == true);
    assert(timeFormat("00:00") == true);
    assert(timeFormat("23:59") == true);

    // Invalid time format
    assert(timeFormat("123:45") == false);    // Length is not 5
    assert(timeFormat("12:345") == false);    // Length is not 5
    assert(timeFormat("12-34") == false);     // Separator is not ':'
    assert(timeFormat("12:34:56") == false);  // Length is not 5
    assert(timeFormat("24:00") == false);     // Hour is greater than 23
    assert(timeFormat("12:60") == false);     // Minute is greater than 59
    assert(timeFormat("-1:30") == false);     // Hour is negative
    assert(timeFormat("12:-30") == false);    // Minute is negative
}

int main() {
    testTimeFormat();
    return 0;
}