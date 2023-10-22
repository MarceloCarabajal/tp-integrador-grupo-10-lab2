#ifndef MENU_INCLUDED
#define MENU_INCLUDED

#include <iostream>
#include <vector>

#include "rlutil.h"

const int DEFAULT_BG = rlutil::BLACK;

class Menu {
private:
    int _currentOption, _maxLength, _yPos = 9;
    bool _isSubMenu;
    std::string _title;
    std::vector<std::string> _options;
    std::vector<void (*)()> _functions;

    void printMenu(int selected);
    void printBase();
    void printHighlighted(std::string text, bool highlight, int color = 14,
                          int x = 0, int y = 0);
    void updateMaxLength(std::string str);
    int getXPosCentered();

public:
    Menu(std::string title = "MENU", bool isSubMenu = false);
    void addOption(std::string option, void (*optFunc)());
    void showMenu();
};

#endif /* MENU_INCLUDED */
