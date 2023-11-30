#pragma once

#include "PetRelations.h"
#include "VppConfigManager.h"
#include "VppFile.h"

/**
 * @class RelationsManager
 * @brief Clase para gestionar las relaciones entre mascotas y clientes.
 *
 * La clase RelationsManager se encarga de cargar, editar, mostrar y guardar las
 * relaciones entre mascotas y clientes. Permite crear nuevas relaciones, editar
 * relaciones existentes, buscar relaciones por ID de mascota y cliente, y
 * verificar la existencia de una relación específica.
 */
class RelationsManager {
private:
    const std::string _folderPath = VppConfigManager().getDataPath();
    const std::string _filePath = _folderPath + "PetRelations.vpp";
    VppFile<PetRelations> _petRelationsFile = VppFile<PetRelations>(_filePath);
    // relId, petId, clientId, owner?, clientName, petName = 6
    const int _petRelationsFields = 6;  // total de datos a mostrar en ListView

    /**
     * @brief Método para cargar y gestionar formularios de relaciones entre
     * mascotas y clientes.
     * Este método solicita información del usuario, como IDs de mascota y
     * cliente, y verifica la existencia de dichos IDs en los respectivos
     * Managers. También se encarga de manejar la creación de nuevas relaciones,
     * verificando si ya existe una relación entre la mascota y el cliente
     * ingresados.
     * @return Objeto PetRelations que representa la nueva relación creada o una
     * relación existente. Si la creación o carga del formulario es
     * interrumpida, se retorna una instancia vacía de PetRelations.
     */
    PetRelations loadForm();

    /**
     * @brief Método para editar relaciones entre mascotas y clientes.
     * Permite la edición de una relación existente, solicitando nuevos valores
     * y verificando la existencia de IDs.
     * @param regPos Posición del registro a editar.
     * @return Objeto PetRelations que representa la relación editada. Retorna
     * instancia vacía si hay errores.
     */
    PetRelations editForm(int regPos);

    /**
     * @brief Método para reintentar si un ID ya existe.
     * Muestra un mensaje indicando que el ID ya existe y permite al usuario
     * reintentar o salir.
     * @param exists Indica si el ID ya existe.
     * @return Devuelve true si se elige reintentar, false si se elige salir.
     */
    bool retryIfIdExists(bool exists);

    /**
     * @brief Método para reintentar si un ID no existe.
     * Muestra un mensaje indicando que el ID no existe y permite al usuario
     * reintentar o salir.
     * @param exists Indica si el ID no existe.
     * @return Devuelve true si se elige reintentar, false si se elige salir.
     */
    bool retryIfIdNotExists(bool exists);

    /**
     * @brief Método para asignar un nuevo propietario a una mascota.
     * Solicita confirmación al usuario para cambiar el propietario de la
     * mascota. Si se confirma, actualiza el registro de mascotas con el nuevo
     * propietario.
     * @param petId ID de la mascota.
     * @param clientId ID del nuevo propietario.
     * @return Devuelve true si se realiza con éxito, false en caso de error o
     * si se elige no cambiar el propietario.
     */
    bool newOwner(int petId, int clientId);

public:
    /**
     * @brief Método para cargar y guardar relaciones entre mascotas y clientes.
     * Solicita al usuario un ID de relación, verifica su existencia y carga los
     * datos de la relación. Luego, guarda la relación en el archivo
     * correspondiente.
     */
    void load();

    /**
     * @brief Método para editar relaciones existentes entre mascotas y
     * clientes.
     * Muestra las relaciones disponibles, solicita al usuario el ID de la
     * relación a modificar, y luego permite la edición de dicha relación.
     * Actualiza el archivo de relaciones con los cambios.
     */
    void edit();

    /**
     * @brief Método para mostrar relaciones entre mascotas y clientes.
     * Muestra una lista de relaciones, incluyendo ID, ID de mascota y cliente,
     * indicación de propietario, nombre del cliente y nombre de la mascota.
     * Permite pausar después de mostrar si se especifica.
     * @param showAndPause Indica si se debe pausar después de mostrar la lista.
     */
    void show(bool showAndPause = true);

    /**
     * @brief Método para actualizar una relación existente entre mascotas y
     * clientes.
     * Actualiza el archivo de relaciones con la nueva información de la
     * relación en la posición especificada.
     * @param petR Objeto PetRelations con la información actualizada.
     * @param regPos Posición de la relación en el archivo.
     * @return Devuelve true si la actualización es exitosa, false en caso
     * contrario.
     */
    bool updateRelation(PetRelations petR, int regPos);

    /**
     * @brief Método para dar de baja una relación existente entre mascotas y
     * clientes.
     * Muestra la lista de relaciones, solicita al usuario el ID de la relación
     * a dar de baja, y confirma la acción antes de realizarla. La baja es
     * irreversible.
     */
    void deleteRel();

    /**
     * @brief Función para generar automáticamente una nueva relación.
     * Se utiliza internamente desde PetsManager. Crea una nueva relación con el
     * ID más bajo disponible o el siguiente disponible si ya existen
     * relaciones. Devuelve el nuevo ID asignado o -1 en caso de error.
     * @param clientId ID del cliente asociado a la nueva relación.
     * @param petId ID de la mascota asociada a la nueva relación.
     * @return Devuelve el nuevo ID de la relación generada o -1 en caso de
     * error.
     */
    int autogenerateNew(int clientId, int petId);

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "RelationsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(PetRelations reg, int nId);

    /**
     * @brief Función para buscar una relación específica entre mascotas y
     * clientes.
     * Compara el ID de mascota y cliente en la relación con los proporcionados.
     * @param reg Objeto PetRelations a comparar.
     * @param petId ID de la mascota a buscar.
     * @param clientId ID del cliente a buscar.
     * @return Devuelve true si la relación coincide con los IDs proporcionados,
     * false en caso contrario.
     */
    static bool searchRelation(PetRelations reg, int petId, int clientId);

    /**
     * @brief Método para verificar la existencia de una relación entre mascotas
     * y clientes.
     * Busca la relación con los IDs de mascota y cliente proporcionados.
     * @param petId ID de la mascota a buscar.
     * @param clientId ID del cliente a buscar.
     * @return Devuelve true si la relación existe, false en caso contrario.
     */
    bool relationExists(int petId, int clientId);

    /**
     * @brief Método para buscar y obtener una relación específica entre
     * mascotas y clientes.
     * Busca la relación con los IDs de mascota y cliente proporcionados.
     * Devuelve un objeto PetRelations con la información de la relación
     * encontrada, o un objeto vacío si no se encuentra.
     *
     * @param petId ID de la mascota a buscar.
     * @param clientId ID del cliente a buscar.
     * @return Objeto PetRelations con la información de la relación encontrada
     * o un objeto vacío si no se encuentra.
     */
    PetRelations searchGetRelation(int petId, int clientId);

    /**
     * @brief Método para verificar la existencia de un ID de relación.
     * Busca el ID de relación proporcionado en el archivo de relaciones.
     * @param nId ID de la relación a verificar.
     * @return Devuelve true si el ID de relación existe, false en caso
     * contrario.
     */
    bool idExists(int nId);
};
