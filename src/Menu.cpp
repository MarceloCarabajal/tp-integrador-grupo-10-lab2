#include "Menu.h"

#include <iomanip>
#include <iostream>
#include <vector>

#include "StatusBar.h"
#include "emoji.h"
#include "utils.h"

Menu::Menu(std::string title, bool isSubMenu) {
    _currentOption = 0;
    _maxLength = (int)utils::removeEmoji(title).size() + 2;
    _title = " " + title + " ";
    _isSubMenu = isSubMenu;
}

void Menu::addOption(std::string option, void (*optFunc)()) {
    _options.push_back(option);
    _functions.push_back(optFunc);
    updateMaxLength(utils::removeEmoji(option));
}

void Menu::updateMaxLength(std::string str) {
    if ((int)str.size() > _maxLength) _maxLength = str.size();
}

void Menu::showMenu() {
    int usrKey = -1;
    int currentSelect = 1, maxSelect;

    if (_isSubMenu) {
        _options.push_back("0. VOLVER (ESC) :arrow_backward:");
    } else {
        _options.push_back("0. SALIR (ESC) :end:");
    }

    maxSelect = _options.size();
    printBase();
    printMenu(currentSelect);

    while (usrKey != 0) {
        usrKey = rlutil::getkey();
        switch (usrKey) {
            case 14:  // Flecha Arriba
                if (currentSelect > 1) currentSelect--;
                printMenu(currentSelect);
                break;
            case 15:  // Flecha Abajo
                if (currentSelect < maxSelect) currentSelect++;
                printMenu(currentSelect);
                break;
            case 1:  // ENTER
                if (currentSelect == maxSelect) return;
                rlutil::cls();
                rlutil::showcursor();  // volver a mostrar cursor
                (_functions[currentSelect - 1])();
                printBase();
                printMenu(currentSelect);
                break;
        }
    }
}

void Menu::printBase() {
    int remainingWidth = 0, sidesWidth, xPos;
    int titleSize = (int)utils::removeEmoji(_title).size();
    xPos = getXPosCentered();
    sidesWidth = (_maxLength / 2) - titleSize / 2;
    sidesWidth -= titleSize % 2;
    if ((sidesWidth * 2) + titleSize < _maxLength) {
        remainingWidth = 1;
    }
    // Limpiar todo
    rlutil::cls();
    // Barra de estado
    StatusBar::show();
    //  Logo
    utils::printLogo();
    // Titulo del menu
    rlutil::locate(xPos, _yPos - 1);
    std::cout << std::setfill('#') << std::setw(sidesWidth) << ""
              << emojicpp::emojize(_title)
              << std::setw(sidesWidth + remainingWidth) << "";
    std::cout << std::setfill(' ');
    // Linea base del menu
    rlutil::locate(xPos, _yPos + _options.size());
    std::cout << std::setfill('#') << std::setw(_maxLength) << "";
    std::cout << std::setfill(' ');
}

void Menu::printMenu(int selected) {
    bool isSelected;
    for (int i = 0; i < (int)_options.size(); i++) {
        isSelected = i + 1 == selected;  // ver si es la opcion seleccionada
        printHighlighted(_options[i], isSelected, rlutil::MAGENTA,
                         getXPosCentered(), _yPos + i);
    }
    std::cout << "\n\nElija una opcion y presione enter, o ESC para salir.\n ";
    rlutil::hidecursor();  // ocultar cursor de consola
}

int Menu::getXPosCentered() {
    int consoleWidth = rlutil::tcols();
    return (consoleWidth / 2) - _maxLength / 2;
}

void Menu::printHighlighted(std::string text, bool highlight, int color, int x,
                            int y) {
    if (highlight) {
        rlutil::setBackgroundColor(color);
        if (x + y != 0) rlutil::locate(x, y);
        std::cout << emojicpp::emojize(text);
        rlutil::setBackgroundColor(DEFAULT_BG);
        // La linea nueva se imprime despues de setear el
        // color de fondo para evitar el bug de cuando se borra la
        // pantalla y que quede toda la linea vacia con color
        std::cout << std::endl;
    } else {
        rlutil::setBackgroundColor(DEFAULT_BG);
        if (x + y != 0) rlutil::locate(x, y);
        std::cout << emojicpp::emojize(text) << std::endl;
    }
}
