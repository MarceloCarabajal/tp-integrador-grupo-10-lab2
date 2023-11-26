#pragma once

#include <iostream>
#include <vector>

class ListView {
private:
    int _width, _curY = 1;  // posicion Y actual
    std::string _title;
    std::vector<std::string> _cells, _cols;
    std::vector<int> _colsW;

    void printBorder();
    void printTitle();
    void calcWidth();
    void printColumns();
    void printRows();
    void setMaxWidths();
    void locateCenter();

    int getUTF8Length(std::string utf8);

public:
    void addCells(std::string *cells, int total);
    void addCols(std::string *cols, int total);
    void setTitle(std::string title);
    void show();
};