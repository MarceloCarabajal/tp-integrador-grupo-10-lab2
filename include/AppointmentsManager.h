#pragma once

#include "Appointment.h"
#include "VppConfigManager.h"
#include "VppFile.h"

class AppointmentsManager {
private:
    const std::string _folderPath = VppConfigManager().getDataPath();
    const std::string _filePath = _folderPath + "Appointments.vpp";
    VppFile<Appointment> _appsFile = VppFile<Appointment>(_filePath);
    const int _appsFields = 7;  // total de datos de un registro Appointment
    /**
     * @brief Cargar datos para un nuevo turno.
     *
     * Esta función solicita y valida los datos necesarios para crear un nuevo
     * turno.
     *
     * @return Objeto Appointment con los datos del nuevo turno.
     */
    Appointment loadForm();
    /**
     * @brief Editar un turno existente.
     *
     * Esta función permite editar un turno existente, solicitando y validando
     * los datos necesarios.
     *
     * @param regPos Posición del turno en los registros.
     * @return Objeto Appointment con los datos del turno editado, o un objeto
     * vacío si no se completa el formulario.
     */
    Appointment editForm(int regPos);
    /**
     * @brief Reintentar si el ID ya existe.
     *
     * Esta función muestra un mensaje indicando que el ID ingresado ya existe y
     * da la opción de reintentar ingresando un nuevo ID o salir presionando
     * ESC.
     *
     * @param exists Indica si el ID ya existe.
     * @return Devuelve `true` para reintentar o `false` para salir.
     */
    bool retryIfIdExists(bool exists);
    /**
     * @brief Reintentar si el ID no existe.
     *
     * Esta función muestra un mensaje indicando que el ID ingresado no existe y
     * ofrece la opción de reintentar ingresando un nuevo ID o salir presionando
     * la tecla ESC.
     *
     * @param exists Indica si el ID existe.
     * @return Devuelve `true` para reintentar o `false` para salir.
     */
    bool retryIfIdNotExists(bool exists);
    /**
     * @brief Reintentar operación si la fecha ingresada no es válida.
     *
     * Muestra mensaje de error si la fecha no es válida (debe ser mayor o igual
     * a la actual). Permite al usuario reintentar ingresando una nueva fecha o
     * salir con ESC.
     *
     * @param valid Indica si la fecha es válida (true) o no (false).
     * @return Devuelve true si se elige reintentar, false si se elige salir.
     */
    bool retryInvalidDate(bool valid);
    /**
     * @brief Reintentar operación si la hora ingresada no es válida.
     *
     * Muestra mensaje de error si la hora no es válida o ya existe un turno con
     * el mismo horario. Permite al usuario reintentar ingresando una nueva hora
     * o salir con ESC.
     *
     * @param valid Indica si la hora es válida (true) o no (false).
     * @return Devuelve true si se elige reintentar, false si se elige salir.
     */
    bool retryInvalidTime(bool invalid);
    /**
     * @brief Validar si la fecha proporcionada es válida.
     *
     * Compara la fecha proporcionada con la fecha actual.
     * Devuelve true si la fecha es mayor o igual a la actual, false en caso
     * contrario.
     *
     * @param date La fecha a validar.
     * @return Devuelve true si la fecha es válida, false si es anterior a la
     * actual.
     */
    bool validAppDate(Date date);
    /**
     * @brief Validar la hora del turno.
     *
     * Esta función verifica si la hora del turno es válida y no está duplicada
     * con otros turnos. Además, verifica que no sea un horario pasado si la
     * fecha es el mismo día.
     *
     * @param date Fecha del turno.
     * @param time Hora del turno.
     * @return Devuelve `true` si la hora es válida, no duplicada y no es un
     * horario pasado; `false` en caso contrario.
     */
    bool validAppTime(const Date& date, const Time& time);
    /**
     * @brief Obtener el número de citas vencidas.
     *
     * Calcula y devuelve la cantidad de citas activas que han vencido hasta la
     * fecha actual.
     *
     * @return El número de citas vencidas, o -1 si hay un error o no hay citas
     * registradas.
     */
    int getExpiredApps();
    /**
     * @brief Eliminar todas las citas vencidas.
     *
     * Busca y elimina todas las citas activas que han vencido hasta la fecha
     * actual. Marca los registros a eliminar y realiza la eliminación física en
     * el archivo.
     *
     * @return La cantidad de citas eliminadas o 0 si hay un error o no hay
     * citas registradas.
     */
    int deleteAllExpired();

public:
    /**
     * @brief Cargar un nuevo turno en el sistema.
     *
     * Solicita al usuario ingresar un ID de turno único, verifica su
     * existencia, y luego carga el resto de los datos necesarios para crear un
     * nuevo turno. Si la operación se completa exitosamente, guarda el turno en
     * el archivo.
     *
     * Utiliza la función auxiliar loadForm() para obtener los detalles del
     * turno.
     */
    void load();
    /**
     * @brief Modificar un turno existente en el sistema.
     *
     * Muestra la lista de turnos disponibles, solicita al usuario ingresar el
     * ID del turno a modificar y, si existe, permite editar los detalles del
     * turno. Guarda los cambios en el archivo de turnos si la operación es
     * exitosa.
     */
    void edit();
    /**
     * @brief Mostrar la lista de turnos veterinarios.
     *
     * Muestra en una lista los detalles de los turnos veterinarios almacenados.
     * Los datos se presentan en columnas, incluyendo ID, ID de mascota, fecha,
     * hora, motivo, estado de asistencia y ID de cliente.
     *
     * @param showAndPause Indica si después de mostrar la lista se debe pausar
     * la ejecución.
     */
    void show(bool showAndPause = true);
    /**
     * @brief Limpiar los turnos expirados del sistema.
     *
     * Busca y muestra la cantidad de turnos expirados. Solicita confirmación
     * al usuario antes de eliminarlos de forma irreversible. Realiza la
     * eliminación y muestra el resultado. La eliminación puede resultar en
     * errores, no eliminar ningún turno o eliminarlos con éxito.
     */
    void clearExpired();
    /**
     * @brief Eliminar definitivamente los turnos marcados para eliminación.
     *
     * Busca y muestra los turnos con eliminación pendiente, solicitando
     * confirmación al usuario antes de realizar la eliminación definitiva.
     * Muestra el resultado de la operación, indicando si se eliminaron con
     * éxito, no se encontraron turnos marcados o si ocurrió un error durante la
     * eliminación.
     */
    void clearDeleted();
    /**
     * @brief Cancelar un turno veterinario.
     *
     * Muestra la lista de turnos y solicita al usuario que ingrese el ID del
     * turno que desea cancelar. Proporciona una confirmación antes de realizar
     * la cancelación irreversible. Muestra el resultado de la operación,
     * indicando si el turno se canceló con éxito, si no se realizó la
     * cancelación o si ocurrió un error durante el proceso.
     */
    void cancel();
    /**
     * @brief Obtener la cantidad de turnos veterinarios activos.
     *
     * Calcula y devuelve la cantidad de turnos veterinarios activos en el
     * sistema, basándose en el estado de activación de cada registro.
     *
     * @return La cantidad de turnos veterinarios activos o -1 en caso de error.
     */
    int getActiveAppsCount();
    /**
     * @brief Obtener los turnos veterinarios activos.
     *
     * Retorna un arreglo dinámico de objetos `Appointment` que representan los
     * turnos veterinarios activos en el sistema. La memoria asignada para el
     * arreglo debe ser gestionada adecuadamente por el llamante.
     *
     * @note El llamante es responsable de liberar la memoria asignada a través
     * de `delete[]`.
     *
     * @return Un puntero al arreglo de turnos activos o NULL en caso de error.
     */
    Appointment* getActiveApps();
    /**
     * @brief Obtener la cantidad de turnos veterinarios pendientes.
     *
     * Calcula y devuelve la cantidad de turnos veterinarios pendientes en el
     * sistema, basándose en la fecha y el estado de activación de cada
     * registro.
     *
     * @return La cantidad de turnos veterinarios pendientes o -1 en caso de
     * error.
     */
    int getPendingApps();
    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "AppointmentsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    /**
     * @brief Función de búsqueda por ID para la búsqueda en registros de turnos
     * veterinarios.
     *
     * Compara el ID de un turno con un ID proporcionado y devuelve verdadero si
     * coinciden.
     *
     * @param reg Objeto Appointment a comparar.
     * @param nId ID a comparar.
     * @return Verdadero si los IDs coinciden, falso en caso contrario.
     */
    static bool searchById(Appointment reg, int nId);
    /**
     * @brief Verificar la existencia de un ID en los registros de turnos
     * veterinarios.
     *
     * Busca un ID en los registros y devuelve verdadero si existe, falso en
     * caso contrario.
     *
     * @param nId ID a verificar.
     * @return Verdadero si el ID existe, falso en caso contrario.
     */
    bool idExists(int nId);
};
