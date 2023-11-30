#pragma once

#include "Client.h"
#include "Vaccination.h"
#include "VppConfigManager.h"
#include "VppFile.h"

/**
 * @class VaccinationManager
 * @brief Clase que gestiona las vacunaciones.
 *
 * La clase VaccinationManager se encarga de administrar las vacunaciones,
 * incluyendo la carga, edición, visualización y notificación de las mismas.
 * También proporciona métodos para realizar búsquedas y verificar la existencia
 * de un ID de vacunación.
 */
class VaccinationManager {
private:
    const std::string _folderPath =
        VppConfigManager().getDataPath(); /**< Ruta de la carpeta de datos */
    const std::string _filePath =
        _folderPath +
        "Vaccinations.vpp"; /**< Ruta del archivo de vacunaciones */
    VppFile<Vaccination> _vaccinationFile =
        VppFile<Vaccination>(_filePath); /**< Archivo de vacunaciones */
    const int _vaccinationFields =
        6; /**< Número total de campos de una vacunación */

    /**
     * @brief Carga los datos de una vacunación desde un formulario.
     * @return Objeto Vaccination con los datos cargados.
     */
    Vaccination loadForm();

    /**
     * @brief Edita los datos de una vacunación existente.
     * @param regPos Posición del registro a editar.
     * @return Objeto Vaccination con los datos editados.
     */
    Vaccination editForm(int regPos);

    /**
     * @brief Verifica si existe un ID de vacunación y solicita reintentar en
     * caso afirmativo.
     * @param exists Indica si el ID de vacunación existe.
     * @return true si se debe reintentar, false en caso contrario.
     */
    bool retryIfIdExists(bool exists);

    /**
     * @brief Verifica si no existe un ID de vacunación y solicita reintentar en
     * caso afirmativo.
     * @param exists Indica si el ID de vacunación no existe.
     * @return true si se debe reintentar, false en caso contrario.
     */
    bool retryIfIdNotExists(bool exists);

    /**
     * @brief Verifica si una fecha de vacunación y revacunación es válida.
     * @param dateV Fecha de vacunación.
     * @param dateR Fecha de revacunación.
     * @return true si la fecha es válida, false en caso contrario.
     */
    bool validVaccRevaccDate(Date dateV, Date dateR);

    /**
     * @brief Verifica si una fecha de aplicación es válida.
     * @param date Fecha de aplicación.
     * @return true si la fecha es válida, false en caso contrario.
     */
    bool validAplicDate(Date date);

public:
    /**
     * @brief Carga los datos de las vacunaciones desde el archivo.
     */
    void load();

    /**
     * @brief Edita los datos de una vacunación existente.
     */
    void edit();

    /**
     * @brief Muestra las vacunaciones.
     * @param showAndPause Indica si se debe mostrar y pausar la ejecución.
     */
    void show(bool showAndPause = true);

    /**
     * @brief Muestra un conjunto de vacunaciones.
     * @param regs Puntero al arreglo de vacunaciones.
     * @param totalRegs Número total de vacunaciones.
     */
    void show(Vaccination* regs, int totalRegs);

    /**
     * @brief Configura y envía notificaciones de vacunaciones pendientes.
     */
    void configAndSendNotif();

    /**
     * @brief Notifica a los clientes sobre la vacunación pendiente.
     *
     * Esta función envía una notificación a los clientes sobre la vacunación
     * pendiente,
     *
     * @param pending Puntero a la vacunación pendiente.
     * @param total Número total de vacunas pendientes.
     * @param veteEmail Correo electrónico del veterinario.
     */
    void notifyClients(Vaccination* pending, int total, std::string veteEmail);

    /**
     * @brief Actualiza el estado de notificación de una vacuna.
     *
     * @param nId El ID de la vacuna.
     * @param state El nuevo estado de notificación.
     * @return true si la actualización fue exitosa, false en caso contrario.
     */
    bool updateNotifState(int nId, bool state);

    /**
     * @brief Crea y envía un correo electrónico al cliente para recordarle la
     * fecha de revacunación.
     *
     * @param client El cliente al que se enviará el correo electrónico.
     * @param from La dirección de correo electrónico desde la cual se enviará
     * el correo.
     * @param revacc La fecha de revacunación que se incluirá en el correo
     * electrónico.
     * @return true si el correo electrónico se envió correctamente, false en
     * caso contrario.
     */
    bool CreateSendEmail(Client client, std::string from, Date revacc);

    /**
     * @brief Elimina las vacunaciones marcadas como eliminadas.
     */
    void clearDeleted();

    /**
     * @brief Cancela la operación actual.
     */
    void cancel();

    /**
     * @brief Obtiene las vacunaciones pendientes de notificar.
     * @param remainingDays Días restantes para la notificación.
     * @return Puntero al arreglo de vacunaciones pendientes.
     */
    Vaccination* getPendingToNotif(int remainingDays);

    /**
     * @brief Obtiene el número de vacunaciones pendientes.
     * @param remainingDays Días restantes para la notificación.
     * @param onlyUnnotified Indica si solo se deben contar las vacunaciones no
     * notificadas.
     * @return Número de vacunaciones pendientes.
     */
    int pendingCount(int remainingDays = 15, bool onlyUnnotified = false);

    /**
     * @brief Busca una vacunación por su ID.
     * @param reg Objeto Vaccination a buscar.
     * @param nId ID de la vacunación a buscar.
     * @return true si se encuentra la vacunación, false en caso contrario.
     */
    static bool searchById(Vaccination reg, int nId);

    /**
     * @brief Verifica si un ID de vacunación existe.
     * @param nId ID de la vacunación a verificar.
     * @return true si el ID existe, false en caso contrario.
     */
    bool idExists(int nId);
};