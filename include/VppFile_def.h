/**
 * @file VppFile_def.h
 * @authors Bertello Ana, Carabajal Marcelo, Masino Facundo
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

/**
 * @brief Constructor de la clase VppFile.
 * @param fileName Nombre del archivo a manejar.
 */
template <class VppClass>
VppFile<VppClass>::VppFile(std::string fileName) {
    _fileName = fileName;
}

/**
 * @brief Obtiene el número total de registros en el archivo.
 * @tparam VppClass Tipo de registro a considerar.
 * @return Número total de registros en el archivo.
 */
template <class VppClass>
int VppFile<VppClass>::getTotalRegisters() {
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
    return totalBytes / sizeof(VppClass);
}

/** @brief Lee 1 registro y lo devuelve, segun el nro pasado por parametro
 *	@tparam VppClass
 *	@param regNumber Nro de registro a leer
 *	@return Registro leido, del tipo que se instancia
 */
template <class VppClass>
VppClass VppFile<VppClass>::readFile(int regNumber) {
    VppClass reg;  // Se crea un registro del tipo instanciado
    FILE *pFile = fopen(_fileName.c_str(), "rb");  // abrir en modo lectura
    if (pFile == NULL) return reg;  // si no se pudo abrir, devolver reg vacio
    // posicionar el puntero pFile en regNumber, moviendolo la cantidad de bytes
    // que ocupe reg x regNumber
    fseek(pFile, sizeof(reg) * regNumber, SEEK_SET);
    fread(&reg, sizeof(reg), 1, pFile);
    fclose(pFile);
    return reg;
}

/**
 * @brief Lee múltiples registros del archivo y los almacena en un vector.
 * @tparam VppClass Tipo de registro a leer.
 * @param reg Puntero al vector en el que se almacenarán los registros leídos.
 * @param totalToRead Cantidad de registros a leer.
 * @return `true` si la lectura fue exitosa, `false` en caso contrario.
 */
template <class VppClass>
bool VppFile<VppClass>::readFile(VppClass *reg, int totalToRead) {
    FILE *pFile = fopen(_fileName.c_str(), "rb");
    if (pFile == NULL) return false;
    bool success = fread(reg, sizeof(VppClass), totalToRead, pFile);
    fclose(pFile);
    return success;
}

/**
 * @brief Escribe un registro en el archivo.
 * @tparam VppClass Tipo de registro a escribir.
 * @param reg Registro a escribir en el archivo.
 * @return `true` si la escritura fue exitosa, `false` en caso contrario.
 */
template <class VppClass>
bool VppFile<VppClass>::writeFile(VppClass reg) {
    FILE *pFile = fopen(_fileName.c_str(), "ab");
    if (pFile == NULL) return false;
    bool success = fwrite(&reg, sizeof(VppClass), 1, pFile);
    fclose(pFile);
    return success;
}