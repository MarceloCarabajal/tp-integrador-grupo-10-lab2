#include "ListView.h"

#include <codecvt>
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
    int emptyCells = 0;                           // acumula celdas vacías
    for (size_t i = 0; i < nRows; i++) {
        locateCenter();
        for (size_t j = 0; j < _cols.size(); j++) {
            int colW = _colsW[j];  // ancho maximo
            int cellW = (int)_cells[curCell].length() + 1;
            // Si el ancho de columna maximo es el de la palabra de la columna
            // +1 para el espacio, la palabra podria contener caracteres
            // especiales que calcularian mal la longitud real
            if (colW == (int)_cols[j].length() + 1) {
                // recalcular ancho por si tiene caracteres especiales
                // solo si el ancho de la celda es menor al de la columna
                if (cellW < colW) colW = getUTF8Length(_cols[j]) + 1;
            }
            // solo imprimir celda si no está vacía
            if (!_cells[curCell].empty()) {
                std::cout << std::setw(colW) << _cells[curCell];
            }
            if (_cells[curCell].empty()) emptyCells++;
            curCell++;
        }
        // si todas las celdas estaban vacías, no producir salto de linea
        if (emptyCells != (int)_cols.size()) std::cout << std::endl;
        // descontar 1 posicion de Y ya que esta fila no se imprime si está
        // vacía
        if (emptyCells == (int)_cols.size()) _curY--;
        emptyCells = 0;  // reset
    }
}

void ListView::setMaxWidths() {
    size_t nRows = _cells.size() / _cols.size();  // calcular cuantas filas hay
    // recorrrer cada columna
    for (size_t i = 0; i < _cols.size(); i++) {
        // setear ancho del nombre de la columna actual
        // +1 para la separacion
        _colsW.push_back(_cols[i].length() + 1);
        size_t cellPos = i;  // posicion de la celda = columna actual
        // recorrer para cada fila, la celda correlativa a la columna
        for (size_t j = 0; j < nRows; j++) {
            // setear ancho de celda
            int cellW = _cells[cellPos].length() + 1;  // +1 para separarlas
            // comparar ancho de celda con ancho de columna
            // si es mayor, se reasigna el ancho de columna
            if (cellW > _colsW[i]) _colsW[i] = cellW;
            // moverse nCeldas segun cantidad de columnas
            // para ir a la prox. fila y a la celda correlativa con la columna
            cellPos += _cols.size();
        }
        // printf("Width Col #%d: %d\n", (int)i, (int)_colsW[i]);
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

int ListView::getUTF8Length(std::string utf8) {
    // the UTF-8 - UTF-32 standard conversion facet
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cvt;

    // UTF-8 to UTF-32
    std::u32string utf32 = cvt.from_bytes(utf8);
    return utf32.size();
}

void ListView::show() {
    setMaxWidths();  // setear maximos x columna
    calcWidth();     // calcular largo total
    printTitle();
    printColumns();
    printRows();
    printBorder();
}
