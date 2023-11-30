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

    
    bool retryIfIdNotExists(bool exists);
    bool validAppDate(Date date);
    bool retryInvalidDate(bool valid);

public:
    void load();
    void edit();
    void show(bool showAndPause = true);
    void clearDeleted();
    void cancel();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "BuysManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(Buy reg, int nId);

    bool idExists(int nId);
};
