#pragma once

#include "Vet.h"
#include "VppConfigManager.h"
#include "VppFile.h"

class VetsManager {
private:
    const std::string _folderPath = VppConfigManager().getDataPath();
    const std::string _filePath = _folderPath + "Vets.vpp";
    VppFile<Vet> _vetsFile = VppFile<Vet>(_filePath);
    const int _vetsFields = 5;  // total de datos de un registro Vet

    /**
     * @brief Método para cargar datos de un veterinario desde un formulario.
     *
     * Crea un formulario de entrada (InputForm) para capturar información del
     * veterinario. Solicita al usuario que ingrese nombre, apellido,
     * especialidad y DNI. Si el usuario no completa el formulario, devuelve un
     * objeto Vet vacío. Si se completó el formulario, crea un objeto Vet con la
     * información proporcionada y lo devuelve.
     *
     * @return Objeto Vet con la información del veterinario cargada desde el
     * formulario.
     */
    Vet loadForm();

    /**
     * @brief Edita la información de un veterinario mediante un formulario.
     *
     * Lee los datos del veterinario desde un archivo en la posición de registro
     * especificada, carga la información en un formulario para su edición, y
     * actualiza el objeto Vet con los nuevos datos si la edición se completa;
     * de lo contrario, devuelve un objeto Vet vacío.
     *
     * @param regPos Posición de registro del veterinario a editar.
     * @return Objeto Vet con la información editada o un objeto Vet vacío si la
     * edición no se completó.
     */
    Vet editForm(int regPos);

public:
    /**
     * @brief Método para cargar y guardar información de un veterinario.
     *
     * Solicita al usuario un ID de veterinario único, verifica su
     * disponibilidad, carga la información del veterinario mediante un
     * formulario y la guarda en un archivo. Si el ID ya existe, permite
     * reintentar o salir. Si no se completa el formulario, se sale.
     *
     * El método finaliza mostrando mensajes de éxito o error según el resultado
     * de la operación.
     */
    void load();

    /**
     * @brief Método para editar la información de un veterinario.
     *
     * Muestra la lista de veterinarios, solicita al usuario el ID del
     * veterinario a modificar, y permite editar sus datos a través de un
     * formulario. Luego, actualiza la información en el archivo de registros.
     * Muestra mensajes de éxito o error según el resultado.
     */
    void edit();

    /**
     * @brief Método para mostrar la lista de veterinarios.
     *
     * Calcula y presenta una lista de veterinarios obtenida desde el archivo de
     * registros. Muestra mensajes de error si ocurren problemas al leer los
     * registros o si no hay registros.
     *
     * @param showAndPause Indica si se debe mostrar la lista y pausar después.
     */
    void show(bool showAndPause = true);

    /**
     * @brief Método para eliminar definitivamente veterinarios marcados como
     * dados de baja.
     *
     * Solicita confirmación al usuario antes de buscar y eliminar los registros
     * de veterinarios marcados como dados de baja. Muestra mensajes de éxito,
     * error o la ausencia de registros eliminados.
     */
    void clearDeleted();

    /**
     * @brief Método para dar de baja provisoria a un veterinario.
     *
     * Muestra la lista de veterinarios, solicita al usuario el ID del
     * veterinario a dar de baja, y solicita confirmación antes de marcar al
     * veterinario para la baja provisoria. Muestra mensajes de éxito, error o
     * cancelación según el resultado.
     */
    void cancel();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "VetsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile

    /**
     * @brief Función para buscar un veterinario por su ID.
     *
     * Compara el ID del veterinario con un ID proporcionado y devuelve
     * verdadero si son iguales; de lo contrario, devuelve falso.
     *
     * @param reg Objeto Vet a comparar.
     * @param nId ID a comparar con el ID del veterinario.
     * @return Verdadero si los IDs son iguales, falso de lo contrario.
     */
    static bool searchById(Vet reg, int nId);

    /**
     * @brief Verifica la existencia de un ID de veterinario en los registros.
     *
     * Busca un ID de veterinario en los registros y devuelve verdadero si
     * existe; de lo contrario, devuelve falso.
     *
     * @param nId ID del veterinario a verificar.
     * @return Verdadero si el ID existe, falso de lo contrario.
     */
    bool idExists(int nId);

    /**
     * @brief Verifica si un ID de veterinario está activo en los registros.
     *
     * Busca un ID de veterinario en los registros y devuelve verdadero si está
     * activo; de lo contrario, devuelve falso.
     *
     * @param nId ID del veterinario a verificar.
     * @return Verdadero si el ID está activo, falso de lo contrario.
     */
    bool isActiveId(int nId);
};
