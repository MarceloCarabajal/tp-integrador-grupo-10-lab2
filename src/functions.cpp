#include "functions.h"

#include <iomanip>
#include <iostream>

#include "rlutil.h"

using namespace std;

void coutCentered(string str) {
    // Si es un string multilinea, calcular la linea mas larga
    int lTexto = getLongestLine(str);
    cout << setw(rlutil::tcols() / 2 - lTexto / 2) << "";
    for (int i = 0; i < (int)str.length(); i++) {
        if (str[i] == '\n') {
            cout << str[i];
            cout << setw(rlutil::tcols() / 2 - lTexto / 2) << "";
        } else {
            cout << str[i];
        }
    }
    cout << setw(rlutil::tcols() / 2 - lTexto / 2 - lTexto % 2) << "";
}

int getLongestLine(string str) {
    int maxLength = 0, charCount = 0;
    for (int i = 0; i < (int)str.length(); i++) {
        if (str[i] == '\n') {
            if (charCount > maxLength) maxLength = charCount;
            charCount = 0;
        }
        charCount++;
    }
    return maxLength;
}

void printLogo() {
    coutCentered(R"(
  _   __    __        __    __ 
 | | / /__ / /____ __/ /___/ /_
 | |/ / -_) __/ -_)_  __/_  __/
 |___/\__/\__/\__/ /_/   /_/   
                               )");
}
