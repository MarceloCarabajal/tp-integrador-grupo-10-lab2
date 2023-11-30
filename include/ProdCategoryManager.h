#pragma once
#include "ProductCategory.h"
#include "VppConfigManager.h"
#include "VppFile.h"

class ProdCategoryManager {
private:
    const std::string _folderPath = VppConfigManager().getDataPath();
    const std::string _filePath = _folderPath + "ProductCategories.vpp";
    VppFile<ProductCategory> _prodcategoryFile =
        VppFile<ProductCategory>(_filePath);
    const int _productscategoryFields =
        2;  // total de datos de un registro Income

    /**
     * @brief Carga los detalles de un formulario para una nueva categoría de
     * productos.
     * Esta función solicita al usuario ingresar el nombre de la categoría y
     * crea un objeto ProductCategory con esos detalles. Luego, establece el
     * estado de la categoría como activo y devuelve el objeto. Si el usuario no
     * completa el formulario, se devuelve un objeto ProductCategory vacío.
     * @return Objeto de tipo ProductCategory con los detalles de la nueva
     * categoría cargados desde el formulario.
     */
    ProductCategory loadForm();

    /**
     * @brief Permite la edición de los detalles de una categoría de productos
     * existente solicitando el ID de la categoría.
     * Muestra la categoría actual, solicita al usuario ingresar el nuevo nombre
     * de la categoría, y permite la edición de los detalles utilizando un
     * formulario. Si el usuario cancela la edición o hay errores en el
     * formulario, la función se interrumpe.
     * @param regPos Posición del registro en el archivo.
     * @return Objeto de tipo ProductCategory con los detalles de la categoría
     * editados desde el formulario. Si el usuario no completa el formulario, se
     * devuelve un objeto ProductCategory vacío.
     */
    ProductCategory editForm(int regPos);

public:
    /**
     * @brief Permite cargar y guardar una nueva categoría de productos con
     * detalles ingresados por el usuario.
     * Solicita al usuario ingresar un ID único para la nueva categoría y
     * verifica si ya existe. Luego, utiliza la función `loadForm` para obtener
     * los detalles de la categoría y guardarla en el archivo. Si el usuario no
     * completa el formulario, la función se interrumpe.
     */
    void load();

    /**
     * @brief Permite la modificación de los detalles de una categoría de
     * productos existente.
     * Muestra la lista de categorías, solicita al usuario ingresar el ID de la
     * categoría a modificar, y permite la edición de los detalles utilizando un
     * formulario. Si el usuario cancela la edición o hay errores en el
     * formulario, la función se interrumpe.
     */
    void edit();

    /**
     * @brief Muestra la lista de categorías de productos.
     * Calcula el total de celdas según la cantidad de datos que contiene un
     * registro y muestra una lista de categorías de productos con sus
     * respectivas columnas: "ID Categoría" y "Nombre". Si no hay registros o
     * hay un error al leerlos, se mostrará un mensaje correspondiente.
     * @param showAndPause Indica si se debe pausar la ejecución después de
     * mostrar la lista.
     */
    void show(bool showAndPause = true);

    /**
     * @brief Elimina permanentemente las categorías de productos marcadas como
     * dadas de baja.
     * Muestra un mensaje de confirmación y, en caso afirmativo, busca
     * categorías de productos marcadas como dadas de baja e intenta eliminarlas
     * definitivamente. Muestra el resultado de la operación, indicando si se
     * encontraron registros, si ocurrió un error o la cantidad de registros
     * eliminados con éxito.
     */
    void clearDeleted();

    /**
     * @brief Realiza una baja provisoria de una categoría de producto.
     * Muestra las categorías de producto, solicita al usuario el ID de la
     * categoría que desea dar de baja y, luego de confirmar la acción, realiza
     * la baja provisoria. Informa al usuario sobre el resultado de la
     * operación.
     */
    void cancel();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "ProdCategoryManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    /**
     * @brief Busca una categoría de producto por su ID.
     * Compara el ID de la categoría de producto con el ID proporcionado.
     * @param reg La categoría de producto a comparar.
     * @param nId El ID a buscar.
     * @return true si los IDs coinciden, false de lo contrario.
     */
    static bool searchById(ProductCategory reg, int nId);

    /**
     * @brief Verifica la existencia de una categoría de producto por su ID.
     * Utiliza la función de búsqueda por ID para determinar si una categoría de
     * producto con el ID proporcionado existe en el archivo.
     * @param nId El ID de la categoría de producto a verificar.
     * @return true si la categoría de producto existe, false de lo contrario.
     */
    bool idExists(int nId);
};
