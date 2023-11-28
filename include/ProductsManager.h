#pragma once

#include "Product.h"
#include "VppFile.h"

class ProductsManager {
private:
    VppFile<Product> _productsFile = VppFile<Product>("Products.vpp");
    const int _productFields = 8;  // total de datos de un regisro Product
    Product loadForm();
    Product editForm(int regPos);

public:
    void load();
    void edit();
    void show(bool showAndPause = true);
    void clearDeleted();
    void cancel();
    

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "ProductManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(Product reg, int nId);

    bool idExists(int nId);
};
