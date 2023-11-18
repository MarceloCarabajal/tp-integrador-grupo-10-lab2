#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

#include <rlutil.h>

#include <iostream>

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
}  // namespace utils

#endif /* UTILS_INCLUDED */
