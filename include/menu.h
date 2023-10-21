#ifndef MENU_INCLUDED
#define MENU_INCLUDED

#include <iostream>
#include <vector>

#include "rlutil.h"

const int DEFAULT_BG = rlutil::BLACK;

class Menu {
private:
    int _totalOptions, _currentOption;
    std::vector<std::string> _options;
    std::vector<void (*)()> _functions;

    void printMenu(int selected);
    void printHighlighted(std::string text, bool highlight, int color = 14,
                          int x = 0, int y = 0);

public:
    Menu();
    void addOption(std::string option, void (*optFunc)());
    void showMenu();
};

#endif /* MENU_INCLUDED */
