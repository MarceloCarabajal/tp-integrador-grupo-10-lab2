#ifndef CLIENTSMANAGER_INCLUDED
#define CLIENTSMANAGER_INCLUDED

#include "Client.h"
#include "VppConfigManager.h"
#include "VppFile.h"

/**
 * @class ClientsManager
 * @brief Gestor de clientes.
 * Esta clase se encarga de gestionar los clientes del sistema. Permite cargar
 * nuevos clientes, modificar clientes existentes, mostrar la lista de clientes,
 * eliminar clientes y realizar consultas sobre los clientes almacenados.
 */
class ClientsManager {
private:
    const std::string _folderPath =
        VppConfigManager()
            .getDataPath(); /**< Ruta de la carpeta donde se almacenan los datos
                               de los clientes. */
    const std::string _filePath =
        _folderPath + "Clients.vpp"; /**< Ruta del archivo que contiene los
                                        datos de los clientes. */
    VppFile<Client> _clientsFile = VppFile<Client>(
        _filePath); /**< Archivo que almacena los registros de los clientes. */
    const int _clientsFields =
        7; /**< Número total de campos en un registro de cliente. */

    /**
     * @brief Cargar datos para un nuevo cliente.
     * Solicita y valida los datos necesarios para crear un nuevo cliente.
     * @return Objeto `Client` con los datos del nuevo cliente.
     */
    Client loadForm();

    /**
     * @brief Editar un cliente existente.
     * Permite editar un cliente existente, solicitando y validando los datos
     * necesarios.
     * @param regPos Posición del cliente en los registros.
     * @return Objeto `Client` con los datos del cliente editado, o un objeto
     * vacío si no se completa el formulario.
     */

    Client editForm(int regPos);

public:
    /**
     * @brief Cargar un nuevo cliente en el sistema.
     * Solicita al usuario ingresar un ID de cliente único, verifica su
     * existencia y carga el resto de los datos necesarios para crear un nuevo
     * cliente. Si la operación se completa exitosamente, guarda el cliente en
     * el archivo.
     * Utiliza la función auxiliar `loadForm()` para obtener los detalles del
     * cliente.
     */
    void load();

    /**
     * @brief Modificar un cliente existente en el sistema.
     * Muestra la lista de clientes disponibles, solicita al usuario ingresar el
     * ID del cliente a modificar y, si existe, permite editar los detalles del
     * cliente. Guarda los cambios en el archivo de clientes si la operación es
     * exitosa.
     */
    void edit();

    /**
     * @brief Mostrar la lista de clientes.
     * Muestra en una lista los detalles de los clientes almacenados.
     * Los datos se presentan en columnas, incluyendo ID, nombre, apellido, DNI,
     * dirección, teléfono y correo electrónico.
     * @param showAndPause Indica si después de mostrar la lista se debe pausar
     * la ejecución.
     */
    void show(bool showAndPause = true);

    void clearSearched();

    /**
     * @brief Eliminar definitivamente los clientes marcados para eliminación.
     * Busca y muestra los clientes marcados para eliminación, solicitando
     * confirmación al usuario antes de realizar la eliminación definitiva.
     * Muestra el resultado de la operación, indicando si se eliminaron con
     * éxito, no se encontraron clientes marcados o si ocurrió un error durante
     * la eliminación.
     */
    void clearDeleted();

    /**
     * @brief Cancelar el registro de un cliente de forma provisoria.
     * Muestra la lista de clientes y solicita al usuario que ingrese el ID del
     * cliente que desea dar de baja de forma provisoria. Proporciona una
     * confirmación antes de realizar la cancelación. Muestra el resultado de la
     * operación, indicando si la baja provisoria se realizó con éxito, si no se
     * llevó a cabo o si ocurrió un error durante el proceso.
     */
    void cancel();

    /**
     * @brief Obtener el nombre completo de un cliente mediante su ID.
     * Busca el cliente con el ID proporcionado y devuelve su nombre completo
     * concatenando el nombre y apellido. Retorna "ERROR" si no se encuentra el
     * cliente.
     * @param nId El ID del cliente.
     * @return El nombre completo del cliente o "ERROR" en caso de no
     * encontrarlo.
     */
    std::string getFullNameById(int nId);

    /**
     * @brief Obtiene un cliente por su ID.
     *
     * @param nId El ID del cliente a buscar.
     * @return El cliente correspondiente al ID especificado.
     */
    Client getClientById(int nId);

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "ClientsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile

    /**
     * @brief Función de búsqueda por ID para la búsqueda en registros de
     * clientes.
     * Compara el ID de un cliente con un ID proporcionado y devuelve verdadero
     * si coinciden.
     * @param reg Objeto Cliente a comparar.
     * @param nId ID a comparar.
     * @return Verdadero si los IDs coinciden, falso en caso contrario.
     */
    static bool searchById(Client reg, int nId);

    /**
     * @brief Verificar la existencia de un ID en los registros de clientes.
     * Busca un ID en los registros y devuelve verdadero si existe, falso en
     * caso contrario.
     * @param nId ID a verificar.
     * @return Verdadero si el ID existe, falso en caso contrario.
     */
    bool idExists(int nId);

    /**
     * @brief Verificar si un ID de cliente está activo.
     * Busca un ID en los registros y devuelve verdadero si está activo, falso
     * en caso contrario.
     * @param nId ID a verificar.
     * @return Verdadero si el ID está activo, falso en caso contrario.
     */
    bool isActiveId(int nId);
};

#endif /* CLIENTSMANAGER_INCLUDED */
