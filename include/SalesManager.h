#include "Sale.h"
#include "VppConfigManager.h"
#include "VppFile.h"

/**
 * @class SalesManager
 * @brief Clase que representa un administrador de ventas.
 *
 * Esta clase se encarga de administrar las ventas, cargar, editar y mostrar
 * información relacionada con las ventas. También proporciona métodos para
 * buscar ventas por ID y verificar la existencia de un ID en las ventas.
 */
class SalesManager {
private:
    const std::string _folderPath =
        VppConfigManager().getDataPath(); /**< Ruta de la carpeta de datos. */
    const std::string _filePath =
        _folderPath + "Sales.vpp"; /**< Ruta del archivo de ventas. */
    VppFile<Sale> _salesFile =
        VppFile<Sale>(_filePath); /**< Archivo de ventas. */
    const int _salesFields =
        6; /**< Número total de datos de un registro de venta. */

    /**
     * @brief Carga los datos de una venta desde un formulario.
     * @return La venta cargada.
     */
    Sale loadForm();

    /**
     * @brief Permite editar los datos de una venta existente.
     * @param regPos La posición del registro de venta a editar.
     * @return La venta editada.
     */
    Sale editForm(int regPos);

    /**
     * @brief Verifica si una fecha de aplicación es válida.
     * @param date La fecha a verificar.
     * @return true si la fecha es válida, false en caso contrario.
     */
    bool validAppDate(Date date);

    /**
     * @brief Permite reintentar una fecha inválida.
     * @param valid Indica si la fecha es válida.
     * @return true si se debe reintentar, false en caso contrario.
     */
    bool retryInvalidDate(bool valid);

public:
    /**
     * @brief Carga los datos de las ventas desde un archivo.
     */
    void load();

    /**
     * @brief Permite editar los datos de una venta existente.
     */
    void edit();

    /**
     * @brief Muestra la información de las ventas.
     * @param showAndPause Indica si se debe mostrar y pausar la ejecución.
     */
    void show(bool showAndPause = true);

    /**
     * @brief Busca una venta por su ID.
     * @param reg La venta a buscar.
     * @param nId El ID de la venta a buscar.
     * @return true si se encuentra la venta, false en caso contrario.
     *
     * Esta función es estática y puede ser utilizada sin necesidad de
     * instanciar un objeto de tipo "SalesManager". Esto permite que se pueda
     * pasar por parámetro un puntero a esta función, lo que es necesario para
     * la búsqueda de registros con VppFile.
     */
    static bool searchById(Sale reg, int nId);

    /**
     * @brief Verifica si un ID de venta existe.
     * @param nId El ID de la venta a verificar.
     * @return true si el ID existe, false en caso contrario.
     */
    bool idExists(int nId);
};
