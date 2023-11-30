#pragma once
#include "Income.h"
#include "VppConfigManager.h"
#include "VppFile.h"

class IncomeManager {
private:
    const std::string _folderPath = VppConfigManager().getDataPath();
    const std::string _filePath = _folderPath + "Incomes.vpp";
    VppFile<Income> _incomeFile = VppFile<Income>(_filePath);
    const int _incomesFields = 7;  // total de datos de un registro Income

    /**
     * @brief Carga los detalles de un formulario de ingreso.
     * Esta función crea un formulario de entrada para cargar los detalles de un
     * ingreso, como la descripción, el método de pago, la fecha, la hora, el ID
     * de venta y el total. Si el usuario completa el formulario, se crea un
     * objeto de ingreso con la información proporcionada.
     * @return Un objeto de tipo Income con los detalles del ingreso cargados
     * desde el formulario. Si el usuario no completa el formulario, se devuelve
     * un objeto Income vacío.
     */
    Income loadForm();

    /**
     * @brief Permite la edición de los detalles de un ingreso existente
     * mediante un formulario.
     * Lee un registro de ingreso desde el archivo, muestra los datos en un
     * formulario de edición, permite al usuario modificar la información y
     * devuelve un objeto de ingreso editado.
     * @param regPos La posición del registro a editar en el archivo.
     * @return Objeto de tipo Income con los detalles del ingreso editados desde
     * el formulario. Si el usuario no completa el formulario, se devuelve un
     * objeto Income vacío.
     */
    Income editForm(int regPos);

public:
    /**
     * @brief Carga y guarda un nuevo ingreso después de solicitar y verificar
     * un ID único.
     * Muestra un formulario para ingresar un ID de ingreso único, verifica su
     * disponibilidad en el archivo, y luego carga y guarda los detalles del
     * nuevo ingreso utilizando otro formulario.
     * Si el usuario cancela el ingreso o hay errores, la función se interrumpe.
     */
    void load();

    /**
     * @brief Permite la edición de los detalles de un ingreso existente
     * solicitando el ID de la transacción.
     * Muestra la lista de ingresos existentes, solicita al usuario el ID de la
     * transacción a modificar y luego permite la edición de los detalles del
     * ingreso utilizando un formulario.
     * Si el usuario cancela la edición o hay errores, la función se interrumpe.
     */
    void edit();

    /**
     * @brief Muestra una lista de ingresos en forma de tabla.
     * Calcula y muestra en formato de tabla los ingresos almacenados en el
     * archivo. Utiliza una clase ListView para la presentación.
     * @param showAndPause Si es verdadero, muestra la lista y pausa la
     * ejecución. Si es falso, solo realiza la presentación.
     */
    void show(bool showAndPause = true);

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "IncomeManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile

    /**
     * @brief Función de búsqueda por ID para ser utilizada en la búsqueda en el
     * archivo de ingresos.
     * Compara el ID de una transacción con un ID proporcionado.
     * @param reg Objeto de tipo Income que representa un registro de ingreso.
     * @param nId ID de transacción a comparar.
     * @return Verdadero si el ID de la transacción coincide con el ID
     * proporcionado, falso de lo contrario.
     */
    static bool searchById(Income reg, int nId);

    /**
     * @brief Verifica la existencia de un ID en el archivo de ingresos.
     * Utiliza la función de búsqueda por ID para determinar si un ID de
     * transacción ya existe en el archivo.
     * @param nId ID de transacción a verificar.
     * @return Verdadero si el ID existe en el archivo, falso de lo contrario.
     */
    bool idExists(int nId);
};
