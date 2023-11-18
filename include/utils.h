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
}  // namespace utils

#endif /* UTILS_INCLUDED */
