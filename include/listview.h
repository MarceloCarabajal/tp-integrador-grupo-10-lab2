#pragma once

#include <iostream>
#include <vector>

/**
 * @class ListView
 * @brief Clase que representa una vista de lista.
 *
 * La clase ListView se utiliza para mostrar una lista de elementos en una
 * interfaz de usuario. Permite agregar celdas, columnas y un título, y luego
 * mostrar la lista en pantalla.
 */
class ListView {
private:
    int _width, _curY = 1;  // posicion Y actual
    std::string _title;
    std::vector<std::string> _cells, _cols;
    std::vector<int> _colsW;

    /**
     * @brief Imprime el borde de la lista.
     */
    void printBorder();
    /**
     * @brief Imprime el título de la lista.
     */
    void printTitle();
    /**
     * @brief Calcula el ancho de la lista.
     */
    void calcWidth();
    /**
     * @brief Imprime las columnas de la lista.
     */
    void printColumns();
    /**
     * @brief Imprime las filas de la lista.
     */
    void printRows();
    /**
     * @brief Establece el ancho máximo de las columnas en la vista de lista.
     */
    void setMaxWidths();
    /**
     * @brief Ubica la lista en el centro de la pantalla.
     */
    void locateCenter();

    /**
     * @brief Obtiene la longitud en caracteres de una cadena UTF-8.
     *
     * @param utf8 La cadena UTF-8 de la cual se desea obtener la longitud.
     * @return La longitud en caracteres de la cadena UTF-8.
     */
    int getUTF8Length(std::string utf8);

public:
    /**
     * @brief Agrega celdas a la lista.
     *
     * @param cells Puntero al arreglo de cadenas de caracteres que representan
     * las celdas.
     * @param total Cantidad total de celdas a agregar.
     */
    void addCells(std::string *cells, int total);

    /**
     * @brief Agrega columnas a la lista.
     *
     * @param cols Puntero al arreglo de cadenas de caracteres que representan
     * las columnas.
     * @param total Cantidad total de columnas a agregar.
     */
    void addCols(std::string *cols, int total);

    /**
     * @brief Establece el título de la lista.
     *
     * @param title Cadena de caracteres que representa el título.
     */
    void setTitle(std::string title);

    /**
     * @brief Muestra la lista en pantalla.
     */
    void show();
};