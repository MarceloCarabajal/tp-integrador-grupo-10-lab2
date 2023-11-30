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

    /**
     * @brief Verifica si un carácter pertenece al alfabeto.
     * @param l El carácter a verificar.
     * @return true si es una letra, false en caso contrario.
     */
    inline bool letter(char l) {
        if (l < 'A' || (l > 'Z' && l < 'a')) return false;
        if (l > 'z') return false;
        return true;
    }

    /**
     * @brief Verifica si un carácter es un número.
     * @param n El carácter a verificar.
     * @return true si es un número, false en caso contrario.
     */
    inline bool number(char n) {
        if (n >= '0' && n <= '9') return true;
        return false;
    }

    /**
     * @brief Verifica si un número está en un rango dado.
     * @param n El número a verificar.
     * @param start El inicio del rango.
     * @param end El final del rango.
     * @return true si está en el rango, false en caso contrario.
     */
    inline bool range(int n, int start, int end) {
        if (n >= start && n <= end) return true;
        return false;
    }

    /**
     * @brief Verifica si una cadena tiene un formato de correo electrónico
     * básico.
     * @param str La cadena a verificar.
     * @return true si es un formato de correo electrónico válido, false en caso
     * contrario.
     */
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
        // si al final posee un caracter que no es una letra, es invalido
        if (!letter(str[str.length() - 1])) return false;
        return true;
    }

    /**
     * @brief Elimina los espacios de una cadena.
     * @param str La cadena de la cual se eliminarán los espacios.
     * @return La cadena sin espacios.
     */
    inline std::string removeSpaces(std::string str) {
        std::string temp;
        for (size_t i = 0; i < str.length(); i++) {
            if (str[i] != ' ') temp += str[i];
        }
        return temp;
    }

    /**
     * @brief Verifica si un carácter es alfanumérico.
     * @param c El carácter a verificar.
     * @return true si es alfanumérico, false en caso contrario.
     */
    inline bool alphanumeric(char c) {
        if (!letter(c) && !number(c)) return false;
        return true;
    }

    /**
     * @brief Verifica si una cadena es completamente alfanumérica.
     * @param str La cadena a verificar.
     * @return true si es alfanumérica, false en caso contrario.
     */
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
    /**
     * @brief Verifica si una cadena de texto contiene únicamente letras.
     *
     * @param str La cadena de texto a verificar.
     * @return true si la cadena de texto contiene únicamente letras, false de
     * lo contrario.
     */
    inline bool onlyLetters(std::string str) {
        str = removeSpaces(str);              // quitar espacios
        if (str.length() == 0) return false;  // si esta vacia, es invalida
        for (size_t i = 0; i < str.length(); i++) {
            if (!letter(str[i])) return false;
        }
        return true;
    }

    /**
     * @brief Verifica si una cadena de caracteres contiene únicamente números
     * enteros.
     *
     * @param str La cadena de caracteres a verificar.
     * @return true si la cadena contiene únicamente números enteros, false en
     * caso contrario.
     */
    inline bool onlyIntegers(std::string str) {
        if (str.length() == 0) return false;
        for (size_t i = 0; i < str.length(); i++) {
            if (!number(str[i])) return false;
        }
        return true;
    }

    /**
     * @brief Verifica si una cadena de texto es un valor booleano válido.
     *
     * @param cad La cadena de texto a verificar.
     * @return true si la cadena es un valor booleano válido, false en caso
     * contrario.
     */
    inline bool boolean(std::string cad) {
        cad = utils::strLower(cad);
        if (cad.length() == 0) return false;
        if (cad == "si" || cad == "sí" || cad == "no") return true;
        return false;
    }

    /**
     * @brief Verifica si una cadena de caracteres representa un número de tipo
     * float.
     *
     * @param str La cadena de caracteres a verificar.
     * @return true si la cadena de caracteres representa un número de tipo
     * float, false de lo contrario.
     */
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

    /**
     * @brief Intenta convertir una cadena de caracteres en un número de punto
     * flotante.
     *
     * @param str La cadena de caracteres a convertir.
     * @return true si la conversión es exitosa, false en caso contrario.
     */
    inline bool tryStof(std::string str) {
        try {
            std::stof(str);
            return true;
        } catch (...) {
            // si por cualquier razon falla, devuelve false
            return false;
        }
    }

    /**
     * @brief Intenta convertir una cadena de caracteres en un entero utilizando
     * std::stoi.
     *
     * @param str La cadena de caracteres a convertir.
     * @return true si la conversión fue exitosa, false en caso contrario.
     */
    inline bool tryStoi(std::string str) {
        try {
            std::stoi(str);
            return true;
        } catch (...) {
            return false;
        }
    }

    /**
     * @brief Verifica si un número entero se encuentra dentro de un rango dado.
     *
     * @param str El número en formato de cadena de caracteres.
     * @param start El valor mínimo del rango.
     * @param end El valor máximo del rango.
     * @return true si el número está dentro del rango, false en caso contrario.
     */
    inline bool range(std::string str, int start, int end) {
        if (!tryStoi(str)) return false;
        int n = std::stoi(str);
        if (n >= start && n <= end) return true;
        return false;
    }

    /**
     * @brief Verifica si una cadena de caracteres tiene el formato de fecha
     * válido (dd/mm/yyyy).
     *
     * @param str La cadena de caracteres a verificar.
     * @return true si la cadena tiene el formato de fecha válido, false de lo
     * contrario.
     */
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

    /**
     * @brief Verifica si una cadena de texto tiene el formato de hora válido
     * (HH:MM).
     *
     * @param str La cadena de texto a verificar.
     * @return true si la cadena tiene el formato de hora válido, false de lo
     * contrario.
     */
    inline bool timeFormat(std::string str) {
        if (str.length() != 5) return false;
        std::string hr = str.substr(0, 2), min = str.substr(3, 2);
        if (str[2] != ':') return false;
        if (!onlyIntegers(hr)) return false;
        if (!onlyIntegers(min)) return false;
        int nHr = std::stoi(hr), nMin = std::stoi(min);
        if (nHr > 23 || nHr < 0) return false;
        if (nMin > 59 || nMin < 0) return false;
        return true;
    }

    /**
     * @brief Verifica si el nombre de un servidor SMTP es válido.
     *
     * @param str El nombre del servidor a verificar.
     * @return true si el nombre del servidor es válido, false de lo contrario.
     */
    inline bool srvName(std::string str) {
        int dotFounds = 0;
        if (str.length() < 5) return false;
        for (size_t i = 0; i < str.length(); i++) {
            // Si no es letra, numero o punto, es invalido
            if (!alphanumeric(str[i]) && str[i] != '.') return false;
            if (str[i] == '.') dotFounds++;
        }
        if (dotFounds < 2) return false;
        return true;
    }

}  // namespace isvalid

#endif /* ISVALID_INCLUDED */
