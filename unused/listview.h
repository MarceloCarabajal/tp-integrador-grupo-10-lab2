/**
 * @file listview.h
 * @brief Un conjunto de funciones para mostrar una vista de lista.
 */
#ifndef LISTVIEW_INCLUDED
#define LISTVIEW_INCLUDED

#include <iomanip>
#include <iostream>

#include "rlutil.h"

namespace listview {

    inline void locateCenter(int w) {
        int center = rlutil::tcols() / 2 - (w / 2) - (w % 2);
        rlutil::locate(center, 1);
    }

    /**
     * @brief Imprime un borde horizontal con el ancho especificado.
     * @param w El ancho del borde.
     */
    inline void printBorderW(int w) {
        locateCenter(w);
        std::cout << std::left;
        std::cout << std::setfill('-') << std::setw(w) << ""
                  << std::setfill(' ') << std::endl;
    }

    /**
     * @brief Imprime un título centrado dentro de un borde horizontal.
     * @param title El título que se imprimirá.
     * @param w El ancho del borde.
     */
    inline void printTitle(std::string title, int w) {
        // calcular la posicion de inicio de titulo
        int startPos = (w / 2) - title.length() / 2 - (title.length() % 2);
        printBorderW(w);
        locateCenter(w);
        std::cout << std::setw(startPos) << "";
        std::cout << title << std::endl;
        printBorderW(w);
    }

    /**
     * @brief Calcula el ancho total de las columnas.
     * @param colsW Un array de anchos de columna.
     * @param total El número total de columnas.
     * @return El ancho total de todas las columnas.
     */
    inline int calcWidth(int *colsW, int total) {
        int listW = 0;
        for (int i = 0; i < total; i++) {
            listW += colsW[i] + 1;  // se le suma 1 para separarlas
        }
        return listW;
    }

    /**
     * @brief Imprime un conjunto de columnas con anchos especificados.
     * @param cols Un array de nombres de columna.
     * @param colsW Un array de anchos de columna.
     * @param total El número total de columnas.
     */
    inline void printColumns(std::string *cols, int *colsW, int total) {
        int listW = calcWidth(colsW, total);
        locateCenter(listW);
        for (int i = 0; i < total; i++) {
            // colsW + 1 para la separacion
            std::cout << std::setw(colsW[i] + 1) << cols[i];
        }
        std::cout << std::endl;
        printBorderW(listW);
    }

    /**
     * @brief Imprime filas de datos en columnas con anchos especificados.
     * @param cells Un array de valores de celda.
     * @param nCells El número total de celdas.
     * @param nCols El número de columnas.
     * @param colsW Un array de anchos de columna.
     */
    inline void printRows(std::string *cells, int nCells, int nCols, int *colsW,
                          int listW) {
        int nRows = nCells / nCols;  // calc numero de filas
        int curCell = 0;             // current cell acumulador
        locateCenter(listW);
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
                // colsW + 1 para la separacion
                std::cout << std::setw(colsW[j] + 1) << cells[curCell];
                curCell++;
            }
            std::cout << std::endl;
        }
    }

    inline void setMaxWidths(std::string *cells, std::string *cols, int nCells,
                             int *colsW, int nCols) {
        int nRows = nCells / nCols;  // calcular cuantas filas hay
        // recorrrer para cada columna, todas las celdas
        for (int i = 0; i < nCols; i++) {
            colsW[i] = cols[i].length();  // guarda ancho del nombre de columna
                                          // para luego comparar si es el mayor
            int cellPos = i;              // posicion de la celda
            for (int j = 0; j < nRows; j++) {
                cellPos += j;
                int cellW = cells[cellPos].length();
                if (cellW > colsW[i]) colsW[i] = cellW;
                cellPos += nCols;  // moverse a la fila de abajo
            }
        }
    }

    /**
     * @brief Imprime una vista de lista completa con título, columnas y filas.
     * @param title El título de la vista de lista.
     * @param cols Un array de nombres de columna.
     * @param cells Un array de valores de celda.
     * @param nCells El número total de celdas.
     * @param nCols El número de columnas.
     * @param colsW Un array de anchos de columna.
     */
    inline void printAll(std::string title, std::string *cols,
                         std::string *cells, int nCells, int nCols,
                         int *colsW) {
        setMaxWidths(cells, cols, nCells, colsW, nCols);
        int listW = calcWidth(colsW, nCols);
        printTitle(title, listW);
        printColumns(cols, colsW, nCols);
        printRows(cells, nCells, nCols, colsW, listW);
        printBorderW(listW);
    }
}  // namespace listview

#endif /* LISTVIEW_INCLUDED */
