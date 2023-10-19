/**
 * @file VppFile.h
 * @authors Bertello Ana, Carabajal Marcelo, Masino Facundo, Tola Lucas
 * @brief VppFile contiene metodos para el manejo basico de archivos.
 * Contiene todos los metodos basicos, necesarios y recurrentes que
 * se utilizan a la hora de realizar operaciones con los archivos de datos .vpp
 * Cada vez que una clase necesite crear o manipular un archivo .vpp, se
 * debera crear un objeto de tipo VppFile
 * @version 0.1
 * @date 2023-10-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <string>

class VppFile {
public:
    VppFile(std::string fileName);

    template <class vppClass>
    int getTotalRegisters();
    template <class vppClass>
    vppClass readFile(int regNumber);
    template <class vppClass>
    bool readFile(vppClass *reg, int totalToRead);
    template <class vppClass>
    bool writeFile(vppClass reg);
    // template <class vppClass>
    // bool updateFile(int regNumber, bool *fCallback); // TODO: desarrollo
    // pendiente

private:
    std::string _fileName;
};

#include "VppFile_def.h"