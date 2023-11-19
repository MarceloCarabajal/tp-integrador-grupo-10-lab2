#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

#include <rlutil.h>

#include <iostream>

// #include "isvalid.h", evita la dependencia circular
//  Declaración forward de isvalid::alphanumeric
namespace isvalid {
    bool alphanumeric(char c);
}

namespace utils {

    inline void pause() {
        std::cout << "Presione cualquier tecla para continuar..." << std::endl;
        rlutil::hidecursor();
        rlutil::anykey();
    }

    inline std::string removeEmoji(std::string str) {
        size_t firstPos = str.find(':');
        size_t secondPos = str.find(':', firstPos + 1);
        if (firstPos == std::string::npos) return str;
        if (secondPos == std::string::npos) return str;
        std::string temp = str.substr(0, firstPos - 1) +
                           str.substr(secondPos + 1, str.length());
        return temp + "  ";  // suma 2 espacios ocupados por el emoji
    }

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

    inline std::string strLower(std::string str) {
        for (size_t i = 0; i < str.length(); i++) {
            str[i] = tolower(str[i]);
        }
        return str;
    }

    inline bool strToBool(std::string str) {
        if (strLower(str) == "si") return true;
        if (strLower(str) == "sí") return true;
        return false;
    }

    inline std::string boolToStr(bool b) {
        if (b) return "Sí";
        return "No";
    }

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

}  // namespace utils

#endif /* UTILS_INCLUDED */
