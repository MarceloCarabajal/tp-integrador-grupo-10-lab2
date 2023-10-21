#include "Menu.h"

#include <iostream>
#include <vector>

#include "functions.h"

Menu::Menu() {
    _totalOptions = 0;
    _currentOption = 0;
}

void Menu::addOption(std::string option, void (*optFunc)()) {
    _options.push_back(option);
    _functions.push_back(optFunc);
    _totalOptions++;
}

void Menu::showMenu() {
    int usrKey = -1;
    int currentSelect = 1, maxSelect = _totalOptions;

    printLogo();
    printMenu(currentSelect);

    while (usrKey != 0) {
        usrKey = rlutil::getkey();
        switch (usrKey) {
            case 14:
                if (currentSelect > 1) currentSelect--;
                printMenu(currentSelect);
                break;
            case 15:
                if (currentSelect < maxSelect) currentSelect++;
                printMenu(currentSelect);
                break;
            case 1:
                // std::cout << "toca enter\n";
                rlutil::cls();
                (_functions[currentSelect - 1])();
                rlutil::cls();
                printLogo();
                printMenu(currentSelect);
                break;
        }
    }
}

void Menu::printMenu(int selected) {
    for (int i = 0; i < _totalOptions; i++) {
        printHighlighted(_options[i], i + 1 == selected, 5, 1, 7 + i);
    }
    std::cout
        << "\n\nElija una opcion y presione enter o escape para salir.\n ";
}

void Menu::printHighlighted(std::string text, bool highlight, int color, int x,
                            int y) {
    if (highlight) {
        rlutil::setBackgroundColor(color);
        if (x + y != 0) rlutil::locate(x, y);
        std::cout << text;
        rlutil::setBackgroundColor(DEFAULT_BG);
        std::cout << std::endl;
    } else {
        rlutil::setBackgroundColor(DEFAULT_BG);
        if (x + y != 0) rlutil::locate(x, y);
        std::cout << text << std::endl;
    }
}
