#pragma once

#include "ItemSale.h"
#include "VppConfigManager.h"
#include "VppFile.h"

class ItemSaleManager {
private:
    const std::string _folderPath = VppConfigManager().getDataPath();
    const std::string _filePath = _folderPath + "ItemSales.vpp";
    VppFile<ItemSale> _itemSaleFile = VppFile<ItemSale>(_filePath);
    const int _itemSalesFields = 4;  // total de datos de un regisro ItemSale

    /**
     * @brief Carga los detalles de un formulario para agregar un ítem a una
     * venta.
     * Esta función solicita al usuario ingresar el ID de la venta existente,
     * verifica su existencia, y luego solicita los detalles del ítem a agregar,
     * como el ID del producto, la cantidad y el precio unitario.
     * @return Objeto de tipo ItemSale con los detalles del ítem cargados desde
     * el formulario. Si el usuario no completa el formulario, se devuelve un
     * objeto ItemSale vacío.
     */
    ItemSale loadForm();

    // ItemSale editForm(int regPos);
    /**
     * @brief Permite al usuario reintentar si el ID no existe.
     * Esta función muestra un mensaje indicando que el ID ingresado no existe,
     * y permite al usuario presionar cualquier tecla para reintentar o la tecla
     * ESC para salir.
     * @param exists Valor booleano que indica si el ID existe o no.
     * @return Verdadero si el usuario elige reintentar, falso si elige salir.
     */
    bool retryIfIdNotExists(bool exists);

public:
    /**
     * @brief Carga y guarda un nuevo ítem de venta después de solicitar los
     * detalles mediante un formulario.
     * Muestra un formulario para ingresar los detalles de un nuevo ítem de
     * venta y lo guarda en el archivo.
     * Si el usuario cancela la operación o hay errores en el formulario, la
     * función se interrumpe.
     */
    void load();

    void edit();
    
    // void show(bool showAndPause = true);
    /*void clearDeleted();
    void cancel();*/

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "itemSalemanager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile

    /*
    static bool searchById(ItemSale reg, int nId);
    bool idExists(int nId);*/
};
