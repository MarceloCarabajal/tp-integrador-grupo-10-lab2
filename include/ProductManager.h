#pragma once

#include "Product.h"
#include "VppFile.h"


class ProductManager {
private:
    VppFile<Product> _productsFile = VppFile<Product>("Products.vpp");
    const int _productFields = 9;  // total de datos de un regisro Pet
  Product loadForm();
  Product editForm(int regPos);



public:
    void load();
    void edit();
    void show();
    void menu();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "ProductManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(Product reg, int nId);
};
