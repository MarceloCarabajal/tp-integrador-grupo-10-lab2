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
    ProductCategory loadForm();
    ProductCategory editForm(int regPos);

public:
    void load();
    void edit();
    void show(bool showAndPause = true);
    void clearDeleted();
    void cancel();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "ProdCategoryManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(ProductCategory reg, int nId);

    bool idExists(int nId);
};
