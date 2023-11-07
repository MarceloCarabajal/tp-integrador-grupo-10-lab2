#pragma once
#include <iostream>

namespace isvalid {

    // Validar que un caracter perteneza al alfabeto
    bool letter(char l) {
        if (l < 'A' || (l > 'Z' && l < 'a')) return false;
        if (l > 'z') return false;
        return true;
    }

    // Validar que un caracter sea un numero
    bool number(char n) {
        if (n >= 0 && n <= 9) return true;
        return false;
    }

    // Validar un email (validacion basica)
    bool email(std::string str) {
        // Validar que la primer letra sea del alfabeto
        char c0 = str[0];
        int atPos = str.find('@');
        if (!letter(c0)) return false;
        // Validar que el @ y . existan
        if (atPos == -1) return false;
        // Obtner la cadena despues del @
        std::string afterAt = str.substr(atPos, str.length());
        // size_type y size_t evitan warning
        std::string::size_type dotPos = afterAt.find('.');
        // Validad que el . exista y no este al final de la cadena
        if (dotPos == (size_t)-1 || dotPos == afterAt.length() - 1)
            return false;
        return true;
    }

    // Verificar que una cadena solo contenga letras
    bool onlyLetters(std::string str) {
        for (size_t i = 0; i < str.length(); i++) {
            if (!letter(str[i])) return false;
        }
        return true;
    }
}  // namespace isvalid