#include "ProdCategoryManager.h"

#include <iostream>

#include "InputForm.h"
#include "ListView.h"
#include "rlutil.h"
#include "utils.h"

void ProdCategoryManager::load() {
    InputForm idForm;
    ProductCategory auxProdCategory;
    int nId = 0;
    bool alreadyExists = false;

    // pedir y buscar si el id ingresado existe
    do {
        if (alreadyExists) {
            std::cout << "El ID de la categoria ya existe, presione cualquier tecla "
                         "para reintentar o ESC para salir.\n";
            if (rlutil::getkey() == rlutil::KEY_ESCAPE) return;
            rlutil::cls();
        }
        idForm.setIntField("ID Categoria de Producto", nId, 4);
        // si no completa el form, salir
        if (!idForm.fill()) return;
        alreadyExists =
            _prodcategoryFile.searchReg(searchById, nId) >= 0 ? true : false;
        idForm.clearAll();  // limpiar form
    } while (alreadyExists);

    auxProdCategory = loadForm();
    // Si no se completo el form, salir
    if (strcmp (auxProdCategory.getCatName(), " ") == 0) return;

    auxProdCategory.setCatId(nId);  // set del Id ingresado anteriormente
    if (_prodcategoryFile.writeFile(auxProdCategory)) {
        std::cout << "Categoria guardada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar la categoria.\n";
    }
}

ProductCategory ProdCategoryManager::loadForm() {
    InputForm productCategForm;
    ProductCategory auxProdCategory;
    std::string name;

productCategForm.setStrField("Nombre", name, 45);


    if (!productCategForm.fill()) return auxProdCategory;

    auxProdCategory.setCatName(name);


    return auxProdCategory;
}

// Solo compara si coincide el id
bool ProdCategoryManager::searchById(ProductCategory reg, int nId) {
    if (reg.getCatId() == nId) return true;
    return false;
}

ProductCategory ProdCategoryManager::editForm(int regPos) {
    InputForm productCategForm;
    ProductCategory auxProdCategory;
     std::string name;
    int  nId;


    auxProdCategory = _prodcategoryFile.readFile(regPos);
    if (auxProdCategory.getCatId() == 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        return auxProdCategory;
    }
    // Se cargan los datos para mostrarlas en el form.

    name = auxProdCategory.getCatName();
    nId = auxProdCategory.getCatId();


    std::cout << "Editando Categoria #" << nId << std::endl;
    // configurar form
    productCategForm.setEditMode(true);  // modo edicion

    productCategForm.setStrField("Nombre", name, 45);

    // completar form
    bool success = productCategForm.fill();
    if (success) {  // si se completa
        auxProdCategory.setCatName(name);
     
        return auxProdCategory;
    }
    // si no se completa, devolver Ingreso vacio
    return auxProdCategory;
}

void ProdCategoryManager::edit() {
    InputForm search;
    int nId;
    show();
    std::cout << "\nIngrese el ID de la categoria a modificar.\n";
    search.setIntField("ID Categoria", nId, 4);
    if (!search.fill()) return;  // si no se completa, salir
    int regPos = _prodcategoryFile.searchReg(searchById, nId);
    if (regPos == -1) {
        std::cout << "No se encontraron resultados.\n";
        utils::pause();
        return;
    }
    // Si se encontro, pedir datos
    ProductCategory auxProdCategory = editForm(regPos);
    // Si no se completo el formulario, salir
    if (auxProdCategory.getCatId() == 0) {
        std::cout << "No se realizara la edicion.\n";
        utils::pause();
        return;
    }

    // guardar ingreso actualizado
    if (_prodcategoryFile.updateFile(auxProdCategory, regPos)) {
        std::cout << "Categoria editada con exito!\n";
    } else {
        std::cout << "Ocurrio un error al guardar el registro.\n";
    }
    utils::pause();
}

void ProdCategoryManager::show() {
    int totalRegs = _prodcategoryFile.getTotalRegisters();
    // calcular el total de celdas de nuestra lista, segun la cantidad de datos
    // que contiene 1 registro
    int totalCells = totalRegs * _productscategoryFields;

    if (totalRegs < 0) {
        std::cout << "Ocurrio un error al leer los registros.\n";
        utils::pause();  // TODO: usar rlutil ?
        return;
    }
    // Se crea la variable que va a contener todas las celdas, segun la cantidad
    // de registros
    std::string *cells = new std::string[totalCells];
    if (cells == NULL) {
        std::cout
            << "No hay memoria suficiente para mostrar las categorias de producto.\n";
        return;
    }
    int cellPos = 0;  // acumula la posicion actual a asignar
    for (int i = 0; i < totalRegs; i++) {
        ProductCategory auxProdCategory = _prodcategoryFile.readFile(i);
        // Obtener todas las propiedades del cliente
        // Guardarlas en un vector de string
        std::string vecStr[7];
        auxProdCategory.toVecString(vecStr);
        for (int cell = 0; cell < _productscategoryFields; cell++) {
            cells[cellPos + cell] = vecStr[cell];
        }
        // se incrementa la posicion de la celda segun la cantidad de datos que
        // contiene el registro, que equivale a una fila de la lista
        cellPos += _productscategoryFields;
    }
    // Vector que contiene las columnas de nuestra lista
    std::string columns[2] = {"ID Categoria", "Nombre"};

    ListView expensesList;
    expensesList.addCells(cells, totalCells);
    expensesList.addCols(columns, 2);
    expensesList.setTitle("CATEGORIAS DE PRODUCTOS");
    expensesList.show();

    delete[] cells;  // liberar memoria!
}