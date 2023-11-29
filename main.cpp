#include <iostream>

#include "MainManager.h"

using namespace std;

// TODO: Eliminar
/// std::string GLOBAL_PATH = "data\\";

int main() {
    MainManager _mainManager;

    // TODO: verificar que exista la carpeta data antes de iniciar todo

    _mainManager.start();

    return 0;
}
