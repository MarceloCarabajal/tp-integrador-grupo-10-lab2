#include <iostream>

#include "../unused/listview.h"

void listviewTest() {
    std::string columns[3] = {"Nombre", "Apellido", "ID"};
    std::string cells[6] = {"cliente1", "apellido1", "1",
                            "cliente2", "apellido2", "2"};
    int colsWidth[3] = {15, 15, 4};
    listview::printAll("CLIENTES", columns, cells, 6, 3, colsWidth);
}