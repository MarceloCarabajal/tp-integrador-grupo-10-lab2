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
    ItemSale loadForm();
    ItemSale editForm(int regPos);
    bool retryIfIdNotExists(bool exists);

public:
    void load();
    void edit();
    void show(bool showAndPause = true);
    void clearDeleted();
    void cancel();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "itemSalemanager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(ItemSale reg, int nId);

    bool idExists(int nId);
};
