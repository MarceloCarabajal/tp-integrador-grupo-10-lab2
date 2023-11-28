#pragma once
#include "ProductCategory.h"
#include "VppFile.h"



class ProdCategoryManager {
private:
    VppFile<ProductCategory> _prodcategoryFile = VppFile<ProductCategory>("ProductCategories.vpp");
    const int _productscategoryFields = 2;  // total de datos de un registro Income
   ProductCategory loadForm();
   ProductCategory  editForm(int regPos);

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
    static bool searchById(ProductCategory  reg, int nId);

    bool idExists(int nId);
};

