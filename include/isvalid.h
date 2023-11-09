#pragma once
#include <iostream>

namespace isvalid {
    /*NOTA: se usa la palabra clave inline en cada funcion para evitar multiples
     * definiciones al ser incluido el archivo .h, inline indica al compilador
     * que debe insertar el contenido de la funcion directamente desde donde se
     * llama
     */

    // Validar que un caracter perteneza al alfabeto
    inline bool letter(char l) {
        if (l < 'A' || (l > 'Z' && l < 'a')) return false;
        if (l > 'z') return false;
        return true;
    }

    // Validar que un caracter sea un numero
    inline bool number(char n) {
        if (n >= '0' && n <= '9') return true;
        return false;
    }

    inline bool range(int n, int start, int end) {
        if (n >= start && n <= end) return true;
        return false;
    }

    // Validar un email (validacion basica)
    inline bool email(std::string str) {
        // Validar que la primer letra sea del alfabeto
        char c0 = str[0];
        int atPos = str.find('@');
        if (!letter(c0)) return false;
        // Validar que el @ exista
        if (atPos == std::string::npos) return false;
        // No puede contener espacios
        if (str.find(' ') != std::string::npos) return false;
        // Obtner la cadena despues del @
        std::string afterAt = str.substr(atPos, str.length());
        // size_type y size_t evitan warning
        std::string::size_type dotPos = afterAt.find('.');
        // Validad que el . exista y no este al final de la cadena
        if (dotPos == (size_t)-1 || dotPos == afterAt.length() - 1) {
            return false;
        }
        return true;
    }

    inline std::string removeSpaces(std::string str) {
        std::string temp;
        for (size_t i = 0; i < str.length(); i++) {
            if (str[i] != ' ') temp += str[i];
        }
        return temp;
    }

    inline bool alphanumeric(std::string str) {
        std::string temp = removeSpaces(str);
        for (size_t i = 0; i < temp.length(); i++) {
            // Si no es ni letra ni numero, es invalido
            if (!letter(temp[i]) && !number(temp[i])) return false;
        }
        return true;
    }

    // Verificar que una cadena solo contenga letras
    inline bool onlyLetters(std::string str) {
        for (size_t i = 0; i < str.length(); i++) {
            if (!letter(str[i])) return false;
        }
        return true;
    }

    // Verifica que una cadena solo contenga numeros enteros
    inline bool onlyIntegers(std::string str) {
        for (size_t i = 0; i < str.length(); i++) {
            if (!number(str[i])) return false;
        }
        return true;
    }
}  // namespace isvalid