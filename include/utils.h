/**
 * @file utils.h
 * @brief Contiene funciones de utilidad para el programa.
 *
 * @note Este archivo depende de la biblioteca rlutil.h y fileapi.h.
 */
#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

#include <rlutil.h>
// API de archivos de Windows
#include <fileapi.h>  // necesario para la funcion GetFileAttributes

#include <iomanip>
#include <iostream>

// #include "isvalid.h", evita la dependencia circular
//  Declaración forward de isvalid::alphanumeric
namespace isvalid {
    bool alphanumeric(char c);
}

namespace utils {

    /**
     * @brief Pausa la ejecución del programa y espera a que el usuario presione
     * cualquier tecla.
     *
     * Esta función muestra un mensaje en pantalla indicando al usuario que
     * presione cualquier tecla para continuar. Luego, oculta el cursor y espera
     * a que el usuario presione una tecla utilizando la biblioteca rlutil.
     */
    inline void pause() {
        std::cout << "Presione cualquier tecla para continuar..." << std::endl;
        rlutil::hidecursor();
        rlutil::anykey();
    }

    /**
     * @brief Elimina los emojis de una cadena de texto.
     *
     * @param str La cadena de texto de la cual se eliminarán los emojis.
     * @return La cadena de texto sin emojis.
     */
    inline std::string removeEmoji(std::string str) {
        size_t firstPos = str.find(':');
        size_t secondPos = str.find(':', firstPos + 1);
        if (firstPos == std::string::npos) return str;
        if (secondPos == std::string::npos) return str;
        std::string temp = str.substr(0, firstPos - 1) +
                           str.substr(secondPos + 1, str.length());
        return temp + "  ";  // suma 2 espacios ocupados por el emoji
    }

    /**
     * @brief Elimina los espacios en blanco al inicio y al final de una cadena
     * de texto.
     *
     * @param str La cadena de texto a la que se le eliminarán los espacios en
     * blanco.
     * @return La cadena de texto sin los espacios en blanco al inicio y al
     * final.
     */
    inline std::string trim(std::string str) {
        size_t lSpaces = 0, rSpaces = 0, strEnd = 0;
        std::string temp;
        // contar espacios desde la izquierda
        for (size_t i = 0; i < str.length(); i++) {
            // si es una letra, salir del for
            if (::isvalid::alphanumeric(str[i])) break;
            if (str[i] == char(32)) lSpaces++;
        }
        // contar espacios desde la derecha
        // se convierte length() a (int) porque i no puede ser de tipo size_t
        // debido a que se usa decremento y al llegar a 0 y decrementar, un tipo
        // size_t no puede ser negativo y vuelve a su valor maximo, generando un
        // loop infinito
        for (int i = (int)str.length(); i >= 0; i--) {
            // si es una letra, salir del for
            if (::isvalid::alphanumeric(str[i - 1])) break;
            if (str[i - 1] == char(32)) rSpaces++;
        }
        // Calcular tamanio total sin espacios L y R
        strEnd = str.length() - rSpaces;
        // copiar str desde lSpaces hasta strEnd
        for (size_t i = lSpaces; i < strEnd; i++) {
            temp += str[i];
        }
        // si no se detectaron espacios, devolver str
        if (lSpaces + rSpaces == 0) return str;
        // sino devolver str trimeado
        return temp;
    }

    /**
     * @brief Convierte una cadena de caracteres a minúsculas.
     *
     * @param str La cadena de caracteres a convertir.
     * @return La cadena de caracteres convertida a minúsculas.
     */
    inline std::string strLower(std::string str) {
        for (size_t i = 0; i < str.length(); i++) {
            str[i] = tolower(str[i]);
        }
        return str;
    }

    /**
     * @brief Convierte una cadena de texto en un valor booleano.
     *
     * @param str La cadena de texto a convertir.
     * @return true si la cadena es "si" o "sí", false en caso contrario.
     */
    inline bool strToBool(std::string str) {
        if (strLower(str) == "si") return true;
        if (strLower(str) == "sí") return true;
        return false;
    }

    /**
     * @brief Convierte un valor booleano en una cadena de texto.
     *
     * @param b El valor booleano a convertir.
     * @return La cadena de texto "Si" si el valor es verdadero, "No" si el
     * valor es falso.
     */
    inline std::string boolToStr(bool b) {
        if (b) return "Si";
        return "No";
    }

    /**
     * @brief Reemplaza todas las comas en una cadena de texto con puntos.
     *
     * @param str La cadena de texto en la que se reemplazarán las comas.
     * @return La cadena de texto resultante después de reemplazar las comas con
     * puntos.
     */
    inline std::string replaceCommas(std::string str) {
        std::string temp;
        // si no hay comas, devolver str
        if (str.find(',') == std::string::npos) return str;
        for (size_t i = 0; i < str.length(); i++) {
            if (str[i] == ',')
                temp += '.';
            else
                temp += str[i];
        }
        return temp;
    }

    /**
     * @brief Obtiene la longitud de la línea más larga en una cadena de texto.
     *
     * @param str La cadena de texto en la que se buscará la línea más larga.
     * @return La longitud de la línea más larga encontrada. Si no hay saltos de
     * línea, se devuelve la longitud de la cadena de texto.
     */
    inline int getLongestLine(std::string str) {
        int maxLength = 0, charCount = 0;
        for (int i = 0; i < (int)str.length(); i++) {
            if (str[i] == '\n') {
                if (charCount > maxLength) maxLength = charCount;
                charCount = 0;
            }
            charCount++;
        }
        // si no hay saltos de linea, devolver la longitud del string
        if (maxLength == 0) return charCount;
        return maxLength;
    }

    /**
     * @brief Imprime una cadena de texto centrada en la consola.
     *
     * @param str La cadena de texto a imprimir.
     */
    inline void coutCenter(std::string str) {
        // Calcular la linea mas larga
        int lTexto = getLongestLine(str);
        std::cout << std::setw(rlutil::tcols() / 2 - lTexto / 2) << "";
        for (int i = 0; i < (int)str.length(); i++) {
            if (str[i] == '\n') {
                std::cout << str[i];
                std::cout << std::setw(rlutil::tcols() / 2 - lTexto / 2) << "";
            } else {
                std::cout << str[i];
            }
        }
        std::cout << std::setw(rlutil::tcols() / 2 - lTexto / 2) << "";
    }

    /**
     * @brief Imprime el logo del programa en la consola.
     *
     * Esta función imprime el logo del programa en la consola.
     * Utiliza la función coutCenter para centrar el logo en la pantalla.
     */
    inline void printLogo() {
        coutCenter(R"(
  _   __    __        __    __ 
 | | / /__ / /____ __/ /___/ /_
 | |/ / -_) __/ -_)_  __/_  __/
 |___/\__/\__/\__/ /_/   /_/   
                               )");
    }

    /**
     * @brief Limpia la pantalla.
     *
     * Esta función utiliza la biblioteca rlutil para limpiar la pantalla.
     */
    inline void cls() { rlutil::cls(); }

    /**
     * @brief Verifica si un archivo existe en la ruta especificada.
     *
     * @param filePath La ruta del archivo a verificar.
     * @return true si el archivo existe, false en caso contrario.
     */
    inline bool fileExists(std::string filePath) {
        // convertir string a TCHAR/WCHAR
        TCHAR *Tpath = new TCHAR[filePath.size() + 1];
        Tpath[filePath.size()] = 0;
        std::copy(filePath.begin(), filePath.end(), Tpath);
        // comprobar si existe el archivo
        DWORD dwAttrib = GetFileAttributes(Tpath);

        delete[] Tpath;
        // si el archivo no existe, devolver false
        return (dwAttrib != INVALID_FILE_ATTRIBUTES);
    }
}  // namespace utils

#endif /* UTILS_INCLUDED */
