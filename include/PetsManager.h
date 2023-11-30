#pragma once

#include "Pet.h"
#include "VppConfigManager.h"
#include "VppFile.h"

class PetsManager {
private:
    const std::string _folderPath = VppConfigManager().getDataPath();
    const std::string _filePath = _folderPath + "Pets.vpp";
    VppFile<Pet> _petsFile = VppFile<Pet>(_filePath);
    const int _petsFields = 7;  // total de datos de un regisro Pet

    /**
     * @brief Método para cargar datos de una mascota desde un formulario.
     * Solicita al usuario el ID del dueño, verifica su existencia,
     * y luego solicita y carga la información de la mascota, incluyendo nombre,
     * especie, raza, diagnóstico actual y fecha de nacimiento.
     * Si se completa el formulario, crea y devuelve un objeto Pet con la
     * información.
     * @return Objeto Pet con la información cargada desde el formulario.
     */
    Pet loadForm();

    /**
     * @brief Edita la información de una mascota mediante un formulario.
     * Lee los datos existentes desde el archivo, permite modificarlos a través
     * de un formulario, y actualiza la información de la mascota en el archivo.
     * Si se cambia el dueño, gestiona la creación o edición de relaciones.
     * Muestra mensajes de éxito, error o cancelación.
     * @param regPos Posición de registro de la mascota a editar.
     * @return Objeto Pet con la información editada o un objeto Pet vacío si la
     * edición no se completó.
     */
    Pet editForm(int regPos);

    /**
     * @brief Reintentar si el ID no existe.
     * Verifica si un ID existe y, si no, muestra un mensaje de error y da la
     * opción de reintentar ingresando un nuevo ID o salir. Devuelve verdadero
     * para reintentar y falso para salir.
     * @param exists Indica si el ID existe.
     * @return Verdadero para reintentar, falso para salir.
     */
    bool retryIfIdNotExists(bool exists);

public:
    /**
     * @brief Cargar información de una nueva mascota.
     * Solicita al usuario un ID para la nueva mascota, verifica su
     * disponibilidad, y carga la información de la mascota mediante un
     * formulario. Guarda la información en el archivo de registros y crea una
     * nueva relación si la carga es exitosa. Muestra mensajes de éxito, error o
     * cancelación.
     */
    void load();

    /**
     * @brief Modifica la información de una mascota existente.
     * Muestra la lista de mascotas, solicita al usuario el ID de la mascota a
     * modificar, verifica su existencia y estado, y permite la edición de la
     * información de la mascota mediante un formulario. Guarda la información
     * actualizada en el archivo de registros. Muestra mensajes de éxito, error
     * o cancelación.
     */
    void edit();

    /**
     * @brief Muestra una lista de mascotas y, opcionalmente, pausa la
     * ejecución.
     * Obtiene la información de todas las mascotas desde el archivo de
     * registros, la organiza en un formato de lista y la muestra en la consola.
     * Si se solicita, pausa la ejecución para que el usuario pueda revisar la
     * información.
     * @param showAndPause Indica si se debe pausar la ejecución después de
     * mostrar la lista.
     */
    void show(bool showAndPause = true);

    /**
     * @brief Elimina definitivamente las mascotas marcadas como dadas de baja.
     * Solicita confirmación al usuario antes de buscar y eliminar las mascotas
     * que han sido marcadas como dadas de baja. Muestra mensajes de éxito,
     * error o la ausencia de registros para eliminar.
     */
    void clearDeleted();

    /**
     * @brief Realiza la baja provisoria de una mascota seleccionada por el
     * usuario.
     * Solicita al usuario el ID de la mascota a
     * dar de baja, verifica su existencia y permite confirmar o cancelar la
     * baja provisoria. Realiza la operación y muestra mensajes de éxito, error
     * o cancelación.
     */
    void cancel();

    /**
     * @brief Actualiza el dueño de una mascota específica.
     * Busca la mascota por su ID, verifica su existencia, actualiza el ID del
     * dueño con el nuevo valor proporcionado y guarda la información
     * actualizada en el archivo de registros. Retorna verdadero si la operación
     * es exitosa, falso en caso contrario.
     * @param ownerId Nuevo ID del dueño para la mascota.
     * @param petId ID de la mascota a actualizar.
     * @return Verdadero si la actualización fue exitosa, falso si falló.
     */
    bool updateOwner(int ownerId, int petId);

    /**
     * @brief Obtiene el nombre de una mascota mediante su ID.
     * Busca la mascota por su ID, verifica su existencia y retorna su nombre.
     * Si la búsqueda falla, devuelve "ERROR".
     * @param nId ID de la mascota para obtener el nombre.
     * @return Nombre de la mascota o "ERROR" en caso de fallo.
     */
    std::string getNameById(int nId);

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "PetsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile

    /**
     * @brief Busca una mascota por su ID.
     * Compara el ID proporcionado con el ID de la mascota dada y retorna
     * verdadero si son iguales; de lo contrario, retorna falso.
     * @param reg Mascota a comparar.
     * @param nId ID de la mascota a buscar.
     * @return Verdadero si el ID coincide, falso si no.
     */
    static bool searchById(Pet reg, int nId);

    /**
     * @brief Verifica la existencia de una mascota por su ID.
     * Busca la mascota por su ID en el archivo de registros y devuelve
     * verdadero si se encuentra; de lo contrario, devuelve falso.
     * @param nId ID de la mascota a verificar.
     * @return Verdadero si la mascota existe, falso si no.
     */
    bool idExists(int nId);

    /**
     * @brief Verifica la existencia de una mascota por su ID.
     * Busca la mascota por su ID en el archivo de registros y devuelve
     * verdadero si se encuentra; de lo contrario, devuelve falso.
     * @param nId ID de la mascota a verificar.
     * @return Verdadero si la mascota existe, falso si no.
     */
    bool isActiveId(int nId);
};
