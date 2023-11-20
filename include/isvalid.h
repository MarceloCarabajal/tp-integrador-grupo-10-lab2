#ifndef ISVALID_INCLUDED
#define ISVALID_INCLUDED
#include <iostream>
#include <string>

// #include "utils.h" // no se incluye porque provoca una dependencia circular
// Solucion:
// Declarar el espacio de nombres utils y la funcion solamente
namespace utils {
    // Declaración forward de strLower utilizada por isvalid::boolean
    std::string strLower(std::string str);
}  // namespace utils

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
        size_t atPos = str.find('@');
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

    inline bool alphanumeric(char c) {
        if (!letter(c) && !number(c)) return false;
        return true;
    }

    inline bool alphanumeric(std::string str) {
        std::string temp = removeSpaces(str);
        if (str.length() == 0) return false;  // si la cadena esta vacia
        for (size_t i = 0; i < temp.length(); i++) {
            // Si no es ni letra ni numero, es invalido
            if (!letter(temp[i]) && !number(temp[i])) return false;
        }
        return true;
    }

    // Verificar que una cadena solo contenga letras
    inline bool onlyLetters(std::string str) {
        str = removeSpaces(str);              // quitar espacios
        if (str.length() == 0) return false;  // si esta vacia, es invalida
        for (size_t i = 0; i < str.length(); i++) {
            if (!letter(str[i])) return false;
        }
        return true;
    }

    // Verifica que una cadena solo contenga numeros enteros
    inline bool onlyIntegers(std::string str) {
        if (str.length() == 0) return false;
        for (size_t i = 0; i < str.length(); i++) {
            if (!number(str[i])) return false;
        }
        return true;
    }
    // Verifica que una cadena solo contenga si o no
    inline bool boolean(std::string cad) {
        cad = utils::strLower(cad);
        if (cad.length() == 0) return false;
        if (cad == "si" || cad == "sí" || cad == "no") return true;
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

    // Intenta convertir una cadena a float
    inline bool tryStof(std::string str) {
        try {
            std::stof(str);
            return true;
        } catch (...) {
            // si por cualquier razon falla, devuelve false
            return false;
        }
    }

    inline bool dateFormat(std::string str) {
        if (str.length() < 10) return false;
        if (str[2] != '/' || str[5] != '/') return false;
        for (size_t i = 0; i < str.length(); i++) {
            // pos 2||5 son las /
            if (i == 2 || i == 5) continue;
            if (!number(str[i])) return false;
        }
        if (std::stoi(str.substr(0, 2)) > 31) return false;
        if (std::stoi(str.substr(3, 2)) > 12) return false;
        if (std::stoi(str.substr(6, 4)) < 1900) return false;
        return true;
    }

}  // namespace isvalid

#endif /* ISVALID_INCLUDED */
