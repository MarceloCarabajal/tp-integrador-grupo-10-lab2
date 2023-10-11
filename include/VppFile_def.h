/**
 * @file VppFile_def.h
 * @authors Bertello Ana, Carabajal Marcelo, Masino Facundo, Tola Lucas
 * @brief Definiciones de VppFile
 *	Van dentro de un .h porque en C++ no es posible separar los
 *  prototipos de las definiciones en .h y .cpp cuando se utilizan templates
 * @version 0.1
 * @date 2023-10-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <string>

#include "VppFile.h"

VppFile::VppFile(std::string fileName) { _fileName = fileName; }

template <class vppClass>
int VppFile::getTotalRegisters() {
    FILE *pFile = fopen(_fileName.c_str(), "rb");
    if (pFile == NULL) return -1;
    // Posicionarnos al final del archivo desde el inicio
    fseek(pFile, 0, SEEK_END);
    // Obtener la cantidad de bytes leidos con fseek
    int totalBytes = ftell(pFile);
    fclose(pFile);
    // Devolver cantidad de registros calculados
    // Obtiene el tamanio del tipo instanciado al llamar
    // a la funcion getTotalRegisters<Tipo>()
    return totalBytes / sizeof(vppClass);
}

/** @brief Lee 1 registro y lo devuelve, segun el nro pasado por parametro
 *	@tparam vppClass
 *	@param regNumber Nro de registro a leer
 *	@return Registro leido, del tipo que se instancia
 */
template <class vppClass>
vppClass VppFile::readFile(int regNumber) {
    vppClass reg;  // Se crea un registro del tipo instanciado
    FILE *pFile = fopen(_fileName.c_str(), "rb");  // abrir en modo lectura
    if (pFile == NULL) return reg;  // si no se pudo abrir, devolver reg vacio
    // posicionar el puntero pFile en regNumber, moviendolo la cantidad de bytes
    // que ocupe reg x regNumber
    fseek(pFile, sizeof(reg) * regNumber, SEEK_SET);
    fread(&reg, sizeof(reg), 1, pFile);
    fclose(pFile);
    return reg;
}

template <class vppClass>
bool VppFile::readFile(vppClass *reg, int totalToRead) {
    FILE *pFile = fopen(_fileName.c_str(), "rb");
    if (pFile == NULL) return false;
    bool success = fread(reg, sizeof(vppClass), totalToRead, pFile);
    fclose(pFile);
    return success;
}

template <class vppClass>
bool VppFile::writeFile(vppClass reg) {
    FILE *pFile = fopen(_fileName.c_str(), "ab");
    if (pFile == NULL) return false;
    bool success = fwrite(&reg, sizeof(vppClass), 1, pFile);
    fclose(pFile);
    return success;
}