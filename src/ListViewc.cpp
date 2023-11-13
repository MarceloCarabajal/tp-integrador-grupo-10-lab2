#include "ListViewc.h"

#include <iomanip>

#include "rlutil.h"

void ListView::locateCenter() {
    int center = rlutil::tcols() / 2 - (_width / 2) - (_width % 2);
    rlutil::locate(center, _curY);
    _curY++;
}

void ListView::printBorder() {
    locateCenter();
    std::cout << std::left;
    std::cout << std::setfill('-') << std::setw(_width) << ""
              << std::setfill(' ') << std::endl;
}

void ListView::printTitle() {
    int startPos = (_width / 2) - _title.length() / 2 - (_title.length() % 2);
    printBorder();
    locateCenter();
    std::cout << std::setw(startPos) << "";
    std::cout << _title << std::endl;
    printBorder();
}

void ListView::calcWidth() {
    int listW = 0;
    for (size_t i = 0; i < _cols.size(); i++) {
        listW += _colsW[i];
    }
    _width = listW;
}

void ListView::printColumns() {
    locateCenter();
    for (size_t i = 0; i < _cols.size(); i++) {
        // colsW + 1 para la separacion
        std::cout << std::setw(_colsW[i]) << _cols[i];
    }
    std::cout << std::endl;
    printBorder();
}

void ListView::printRows() {
    size_t nRows = _cells.size() / _cols.size();  // calc numero de filas
    int curCell = 0;                              // current cell acumulador
    for (size_t i = 0; i < nRows; i++) {
        locateCenter();
        for (size_t j = 0; j < _cols.size(); j++) {
            std::cout << std::setw(_colsW[j]) << _cells[curCell];
            curCell++;
        }
        std::cout << std::endl;
    }
}

void ListView::setMaxWidths() {
    size_t nRows = _cells.size() / _cols.size();  // calcular cuantas filas hay
    // recorrrer para cada columna, todas las celdas
    for (size_t i = 0; i < _cols.size(); i++) {
        // setear ancho del nombre de la columna actual
        // +1 para la separacion
        _colsW.push_back(_cols[i].length() + 1);
        size_t cellPos = i;  // posicion de la celda
        for (size_t j = 0; j < nRows; j++) {
            cellPos += j;
            int cellW = _cells[cellPos].length() + 1;  // +1 para separarlas
            if (cellW > _colsW[i]) _colsW[i] = cellW;
            cellPos += _cols.size();  // moverse a la fila de abajo
        }
    }
}

void ListView::addCells(std::string* cells, int total) {
    for (int i = 0; i < total; i++) {
        _cells.push_back(cells[i]);
    }
}

void ListView::addCols(std::string* cols, int total) {
    for (int i = 0; i < total; i++) {
        _cols.push_back(cols[i]);
    }
}

void ListView::setTitle(std::string title) { _title = title; }

void ListView::show() {
    setMaxWidths();  // setear maximos x columna
    calcWidth();     // calcular largo total
    printTitle();
    printColumns();
    printRows();
    printBorder();
}
