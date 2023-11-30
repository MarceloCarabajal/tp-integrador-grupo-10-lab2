#pragma once

#include "VetVisits.h"
#include "VppConfigManager.h"
#include "VppFile.h"

class VetVisitsManager {
private:
    const std::string _folderPath = VppConfigManager().getDataPath();
    const std::string _filePath = _folderPath + "VetVisits.vpp";
    VppFile<VetVisits> _vetVisitsFile = VppFile<VetVisits>(_filePath);
    const int _vetVisitsFields = 9;  // total de datos de un regisro VetVisit
    VetVisits loadForm();
    VetVisits editForm(int regPos);
    bool retryIfIdExists(bool exists);
    bool retryIfIdNotExists(bool exists, bool isActive);

public:
    /**
     * @brief Carga una nueva consulta veterinaria, solicitando información al
     * usuario y almacenándola en el archivo. La función verifica la existencia
     * del ID ingresado, evitando duplicados o el uso de IDs dados de baja.
     */
    void load();
    /**
     * @brief Edita una consulta veterinaria existente, solicitando al usuario
     * el ID y la información actualizada. La función verifica la existencia y
     * estado de la consulta antes de realizar la edición.
     */
    void edit();
    /**
     * @brief Muestra en pantalla la lista de consultas veterinarias almacenadas
     * y, opcionalmente, pausa la ejecución.
     * @param showAndPause Indica si se debe pausar la ejecución después de
     * mostrar la lista.
     */
    void show(bool showAndPause = true);
    void menu();
    /**
     * @brief Elimina definitivamente las consultas veterinarias marcadas como
     * dadas de baja. Solicita confirmación al usuario antes de realizar la
     * operación.
     */
    void clearDeleted();
    /**
     * @brief Cancela una consulta veterinaria marcándola como dada de baja de
     * manera provisoria.
     * Muestra la lista de consultas, solicita al usuario el ID de la consulta a
     * cancelar, y confirma la acción antes de realizarla.
     * @note Utiliza las clases InputForm, utils y funciones de _vetVisitsFile.
     * @see InputForm, utils, _vetVisitsFile
     */
    void cancel();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "VetVisitsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile

    /**
     * @brief Función de búsqueda para encontrar una visita veterinaria por su
     * ID.
     * @param reg Objeto de la clase VetVisits a comparar con el ID
     * proporcionado.
     * @param nId ID de visita veterinaria a buscar.
     * @return true si el ID de la visita veterinaria coincide, false en caso
     * contrario.
     */
    static bool searchById(VetVisits reg, int nId);

    /**
     * @brief Verifica si un ID de visita veterinaria existe en el archivo.
     * @param nId ID de visita veterinaria a verificar.
     * @return true si el ID existe, false en caso contrario.
     */
    bool idExists(int nId);

    /**
     * @brief Verifica si un ID de visita veterinaria está activo.
     * @param nId ID de visita veterinaria a verificar.
     * @return true si el ID está activo, false en caso contrario.
     */
    bool isActiveId(int nId);
};
