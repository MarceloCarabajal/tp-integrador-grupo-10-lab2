#pragma once

#include "Buy.h"
#include "VppConfigManager.h"
#include "VppFile.h"

class BuysManager {
private:
    const std::string _folderPath = VppConfigManager().getDataPath();
    const std::string _filePath = _folderPath + "Buys.vpp";
    VppFile<Buy> _buysFile = VppFile<Buy>(_filePath);
    const int _buysFields = 7;  // total de datos de un regisro Buy

    /**
     * @brief Formulario de carga de una nueva compra.
     *
     * Esta función configura y muestra un formulario para cargar una nueva
     * compra. El usuario ingresa los datos de la compra, y la función devuelve
     * la compra creada.
     *
     * @return Nueva compra creada.
     */
    Buy loadForm();

    /**
     * @brief Formulario de edición de una compra existente.
     *
     * Esta función configura y muestra un formulario para editar una compra
     * existente. El usuario puede modificar los datos de la compra, y la
     * función devuelve la compra editada.
     *
     * @param regPos Posición del registro en el archivo de compras.
     * @return Compra editada.
     */
    Buy editForm(int regPos);

    /**
     * @brief Reintentar si el ID no existe.
     *
     * Esta función muestra un mensaje indicando que el ID ingresado no existe.
     * Ofrece al usuario la opción de reintentar ingresando un nuevo ID o salir.
     *
     * @param exists Indica si el ID existe o no.
     * @return true si se debe reintentar, false si se elige salir.
     */
    bool retryIfIdNotExists(bool exists);

    /**
     * @brief Validar la fecha de la compra.
     *
     * Esta función compara la fecha proporcionada con la fecha actual.
     *
     * @param date Fecha a validar.
     * @return true si la fecha es anterior o igual a la fecha actual, false si
     * es posterior.
     */
    bool validBuyDate(Date date);

    /**
     * @brief Reintentar si la fecha ingresada no es válida.
     *
     * Esta función muestra un mensaje si la fecha ingresada no es válida,
     * solicitando al usuario que presione una tecla para reintentar o ESC para
     * salir.
     *
     * @param valid Indica si la fecha ingresada es válida.
     * @return true si se debe reintentar, false si se debe salir.
     */
    bool retryInvalidDate(bool valid);

public:
    /**
     * @brief Cargar una compra.
     *
     * Esta función solicita al usuario el ID de la compra, verifica su
     * existencia y carga la compra utilizando el formulario de carga. Luego,
     * guarda la compra en el archivo de compras. Muestra mensajes de error o
     * éxito según corresponda.
     */
    void load();

    /**
     * @brief Función para editar una compra en el gestor de compras.
     *
     * La función solicita al usuario el ID de la compra a modificar, busca la
     * compra correspondiente en el archivo de compras, y permite la edición de
     * sus datos.
     *
     * @note La función utiliza clases como InputForm, Buy y utils para realizar
     * operaciones.
     *
     * @see InputForm, Buy, utils
     */
    void edit();

    /**
     * @brief Muestra la lista de compras almacenadas y opcionalmente pausa la
     * ejecución.
     *
     * La función obtiene y formatea los registros de compras, mostrándolos en
     * una lista.
     *
     * @param showAndPause Indica si se debe pausar la ejecución después de
     * mostrar la lista.
     *
     * @note Utiliza las clases Buy, utils y ListView.
     *
     * @see Buy, utils, ListView
     */
    void show(bool showAndPause = true);

    /**
     * @brief Elimina definitivamente las compras marcadas como dadas de baja.
     *
     * Solicita confirmación al usuario antes de realizar la operación.
     *
     * @note Utiliza las clases InputForm, utils y funciones de _buysFile.
     *
     * @see InputForm, utils, _buysFile
     */
    void clearDeleted();

    /**
     * @brief Cancela una compra marcándola como dada de baja de manera
     * provisoria.
     *
     * Muestra la lista de compras, solicita al usuario el ID de la compra a
     * cancelar, y confirma la acción antes de realizarla.
     *
     * @note Utiliza las clases InputForm, utils y funciones de _buysFile.
     *
     * @see InputForm, utils, _buysFile
     */
    void cancel();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "BuysManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile

    /**
     * @brief Función de búsqueda para encontrar una compra por su ID.
     *
     * @param reg Objeto de la clase Buy a comparar con el ID proporcionado.
     * @param nId ID de compra a buscar.
     * @return true si el ID de la compra coincide, false en caso contrario.
     */
    static bool searchById(Buy reg, int nId);

    /**
     * @brief Verifica si un ID de compra existe en el archivo de compras.
     *
     * @param nId ID de compra a verificar.
     * @return true si el ID existe, false en caso contrario.
     *
     * @note Utiliza la función de búsqueda searchById en _buysFile.
     *
     * @see searchById, _buysFile
     */
    bool idExists(int nId);
};
