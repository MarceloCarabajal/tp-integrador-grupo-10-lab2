#pragma once

#include "Expense.h"
#include "VppConfigManager.h"
#include "VppFile.h"

class ExpenseManager {
private:
    const std::string _folderPath = VppConfigManager().getDataPath();
    const std::string _filePath = _folderPath + "Expenses.vpp";
    VppFile<Expense> _expenseFile = VppFile<Expense>(_filePath);
    const int _expenseFields = 7;  // total de datos de un registro Expense

    /**
     * @brief Carga los detalles de un gasto desde un formulario de entrada.
     *
     * Crea un formulario para capturar información como descripción, método de
     * pago, fecha, hora, ID de compra y total. Retorna un objeto Expense con
     * los datos del formulario o un objeto vacío si no se completa.
     *
     * @return Objeto Expense con detalles del gasto o un objeto vacío si no se
     * completa el formulario.
     */
    Expense loadForm();

    /**
     * @brief Edita los detalles de un gasto cargando y modificando la
     * información desde un formulario.
     *
     * Lee un registro de gasto desde el archivo, muestra los datos en un
     * formulario de edición, permite al usuario modificar la información y
     * devuelve un objeto Expense editado.
     *
     * @param regPos La posición del registro a editar en el archivo.
     * @return Objeto Expense editado o un objeto vacío si hay errores al leer
     * el registro o el formulario no se completa.
     */
    Expense editForm(int regPos);

public:
    /**
     * @brief Carga y guarda un nuevo gasto después de solicitar y verificar un
     * ID único.
     *
     * Muestra un formulario para ingresar un ID de gasto único, verifica su
     * disponibilidad en el archivo, y luego carga y guarda los detalles del
     * nuevo gasto utilizando otro formulario.
     *
     * Si el usuario cancela el ingreso o hay errores, la función se interrumpe.
     */
    void load();

    /**
     * @brief Permite la edición de un gasto existente solicitando el ID de la
     * transacción.
     *
     * Muestra la lista de gastos existentes, solicita al usuario el ID de la
     * transacción a modificar y luego permite la edición de los detalles del
     * gasto utilizando un formulario.
     *
     * Si el usuario cancela la edición o hay errores, la función se interrumpe.
     */
    void edit();

    /**
     * @brief Muestra una lista de gastos en forma de tabla.
     *
     * Calcula y muestra en formato de tabla los gastos almacenados en el
     * archivo. Se utiliza una clase ListView para la presentación.
     *
     * @param showAndPause Si es verdadero, muestra la lista y pausa la
     * ejecución. Si es falso, solo realiza la presentación.
     */
    void show(bool showAndPause = true);

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "ExpenseManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile

    /**
     * @brief Función de búsqueda por ID para ser utilizada en la búsqueda en el
     * archivo de gastos.
     *
     * Compara el ID de una transacción con un ID proporcionado.
     *
     * @param reg Objeto de tipo Expense que representa un registro de gasto.
     * @param nId ID de transacción a comparar.
     * @return Verdadero si el ID de la transacción coincide con el ID
     * proporcionado, falso de lo contrario.
     */
    static bool searchById(Expense reg, int nId);

    /**
     * @brief Verifica la existencia de un ID en el archivo de gastos.
     *
     * Utiliza la función de búsqueda por ID para determinar si un ID de
     * transacción ya existe en el archivo.
     *
     * @param nId ID de transacción a verificar.
     * @return Verdadero si el ID existe en el archivo, falso de lo contrario.
     */
    bool idExists(int nId);
};
