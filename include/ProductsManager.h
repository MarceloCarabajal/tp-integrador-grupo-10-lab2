#pragma once

#include "Product.h"
#include "VppConfigManager.h"
#include "VppFile.h"

class ProductsManager {
private:
    const std::string _folderPath = VppConfigManager().getDataPath();
    const std::string _filePath = _folderPath + "Products.vpp";
    VppFile<Product> _productsFile = VppFile<Product>(_filePath);
    const int _productFields = 8;  // total de datos de un regisro Product

    /**
     * @brief Formulario de carga de un nuevo producto.
     *
     * Esta función configura y muestra un formulario para cargar un nuevo
     * producto. El usuario ingresa los datos del producto, y la función
     * devuelve el producto creado.
     *
     * @return Nuevo producto creado.
     */
    Product loadForm();

    /**
     * @brief Formulario de edición de un producto.
     *
     * Esta función configura y muestra un formulario de edición para un
     * producto existente. Carga los datos actuales del producto y permite al
     * usuario modificarlos. Luego, devuelve el producto modificado.
     *
     * @param regPos Posición del registro en el archivo.
     * @return Producto modificado.
     */
    Product editForm(int regPos);

public:
    /**
     * @brief Cargar un nuevo producto.
     *
     * Esta función solicita al usuario los datos para crear un nuevo producto.
     * Pide el ID del producto y verifica su existencia. Luego, carga el
     * formulario para ingresar los datos del producto y lo guarda en el
     * archivo.
     */
    void load();

    /**
     * @brief Editar un producto.
     *
     * Esta función permite al usuario editar un producto existente. Muestra la
     * lista de productos, solicita el ID del producto a modificar y luego pide
     * los datos actualizados. Finalmente, guarda el producto actualizado en el
     * archivo.
     */
    void edit();

    /**
     * @brief Mostrar lista de productos.
     *
     * Esta función muestra la lista de productos, permitiendo al usuario
     * visualizar información detallada. Si se proporciona `true` a
     * `showAndPause`, se pausará después de mostrar la lista.
     *
     * @param showAndPause Indica si se debe pausar después de mostrar la lista.
     */
    void show(bool showAndPause = true);

    /**
     * @brief Borrar definitivamente productos eliminados.
     *
     * Esta función busca productos marcados como eliminados y los elimina
     * definitivamente después de solicitar confirmación al usuario.
     */
    void clearDeleted();

    /**
     * @brief Baja logica productos.
     *
     * Permite dar de baja  logica un producto solicitando el ID al usuario.
     * Muestra una confirmación y realiza la acción de baja si es confirmada.
     */
    void cancel();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "ProductManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile

    /**
     * @brief Función de búsqueda por ID para productos.
     *
     * Compara el ID de un producto con el ID proporcionado para determinar si
     * coinciden.
     *
     * @param reg El objeto de producto a comparar.
     * @param nId El ID a comparar.
     * @return true si los IDs coinciden, false de lo contrario.
     */
    static bool searchById(Product reg, int nId);
    /**
     * @brief Verifica la existencia de un producto mediante su ID.
     *
     * Utiliza la función de búsqueda por ID para determinar si hay un producto
     * con el ID proporcionado en el archivo de productos.
     *
     * @param nId El ID del producto a verificar.
     * @return true si el producto existe, false de lo contrario.
     */
    bool idExists(int nId);
};
