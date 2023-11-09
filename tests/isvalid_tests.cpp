#pragma once
#include <iostream>
using namespace std;

#include "isvalid.h"

void isvalidEmailTest() {
    cout << "Tests isvalid::email()" << endl;
    cout << "a: " << isvalid::email("a") << endl;
    cout << "z: " << isvalid::email("z") << endl;
    cout << "A: " << isvalid::email("A") << endl;
    cout << "Z: " << isvalid::email("Z") << endl;
    cout << "[: " << isvalid::email("[") << endl;
    cout << "{: " << isvalid::email("{") << endl;
    cout << "a@: " << isvalid::email("a@") << endl;
    cout << "a@.: " << isvalid::email("a@.") << endl;
    cout << "pepito@pepito.a: " << isvalid::email("pepito@pepito.a") << endl;
    cout << "pepito@pepito: " << isvalid::email("pepito@pepito") << endl;
    cout << "facu_j@gmail.: " << isvalid::email("facu_@gmail.") << endl;
    cout << "facu_j@gmail.com: " << isvalid::email("facu_j@gmail.com") << endl;
    cout << "abc 123: " << isvalid::alphanumeric("abc 123") << endl;
    cout << "abc123: " << isvalid::alphanumeric("abc123") << endl;
    cout << "abc. 123: " << isvalid::alphanumeric("abc. 123") << endl;
    cout << "abc: " << isvalid::alphanumeric("abc") << endl;
}