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

/**
 * @brief Actualiza un registro en el archivo.
 *
 * Esta función permite actualizar un registro en un archivo binario en una
 * posición específica.
 *
 * @tparam VppClass El tipo de datos del registro.
 * @param reg El registro que se desea actualizar.
 * @param regPos La posición del registro que se desea actualizar.
 * @return `true` si la actualización se realiza con éxito, de lo contrario,
 * `false`.
 */
template <class VppClass>
bool VppFile<VppClass>::updateFile(VppClass reg, int regPos) {
    FILE *pFile = fopen(_fileName.c_str(), "rb+");
    if (pFile == NULL) return false;
    fseek(pFile, sizeof(reg) * regPos, SEEK_SET);
    bool success = fwrite(&reg, sizeof(reg), 1, pFile);
    fclose(pFile);
    return success;
}

template <class VppClass>
bool VppFile<VppClass>::deleteReg(int regNumber) {
    int total = getTotalRegisters();
    if (total <= 0) return false;
    VppClass *regs = new VppClass[total];
    if (regs == NULL) return false;
    bool okRead = readFile(regs, total);
    if (!okRead) return false;
    FILE *pFile = fopen(_fileName.c_str(), "wb");
    if (pFile == NULL) return false;
    for (int i = 0; i < total; i++) {
        if (i == regNumber) continue;
        bool success = fwrite(&regs[i], sizeof(VppClass), 1, pFile);
        if (!success) {
            fclose(pFile);
            return false;
        }
    }
    fclose(pFile);
    return true;
}

template <class VppClass>
bool VppFile<VppClass>::markForDelete(int regNumber) {
    VppClass reg = readFile(regNumber);
    if (!reg.getStatus()) return false;
    reg.setStatus(false);
    bool success = updateFile(reg, regNumber);
    return success;
}

template <class VppClass>
int VppFile<VppClass>::deleteAllMarked() {
    int written = 0;  // acumulador registros escritos
    int total = getTotalRegisters();
    if (total <= 0) return -1;
    VppClass *regs = new VppClass[total];
    if (regs == NULL) return -1;
    bool okRead = readFile(regs, total);
    if (!okRead) return false;
    FILE *pFile = fopen(_fileName.c_str(), "wb");
    if (pFile == NULL) return -1;
    for (int i = 0; i < total; i++) {
        // si el registro esta marcado para eliminar, no escribirlo
        if (!regs[i].getStatus()) continue;
        // si esta activo, escribirlo de nuevo
        bool success = fwrite(&regs[i], sizeof(VppClass), 1, pFile);
        if (!success) return -1;
        written++;
    }
    // devolver el total de registros eliminados
    return total - written;
}

/**
 * @brief Busca un registro en el archivo.
 *
 * Esta función busca un registro en un archivo binario y utiliza una función de
 * callback para determinar si se encuentra el registro deseado.
 *
 * @tparam VppClass El tipo de datos del registro.
 * @param fCallback Un puntero a una función de callback que se utiliza para
 * evaluar si se ha encontrado el registro deseado.
 * @return La posición del registro si se encuentra, de lo contrario, retorna
 * -1.
 *
 * @see getTotalRegisters() para obtener el número total de registros en el
 * archivo.
 */
template <class VppClass>
template <typename AnyType>
int VppFile<VppClass>::searchReg(bool (*fCallback)(VppClass reg, AnyType value),
                                 AnyType value) {
    VppClass auxReg;
    int totalToRead = getTotalRegisters();
    FILE *pFile = fopen(_fileName.c_str(), "rb");
    if (pFile == NULL) return -1;
    for (int i = 0; i < totalToRead; i++) {
        // Si ocurre un error al leer, devuelve -1
        if (!fread(&auxReg, sizeof(auxReg), 1, pFile)) {
            fclose(pFile);
            return -1;
        }
        // Si la funcion callback devuelve true, se encontro
        // lo buscado en el registro y se devuelve la posicion
        if ((fCallback)(auxReg, value)) {
            fclose(pFile);
            return i;
        }
    }
    fclose(pFile);
    return -1;
}