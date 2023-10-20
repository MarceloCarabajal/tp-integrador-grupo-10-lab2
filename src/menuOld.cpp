#include "menuOld.h"

#include "functions.h"

using namespace std;

void handleMenu() {
    int usrKey = 0;
    int currentSelect = 1, maxSelect = 2;

    printMenu(currentSelect);
    while (usrKey != 1) {
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
        }
    }
}

void printMenu(int selected) {
    rlutil::cls();
    printLogo();
    printHighlighted("Opcion 1\n", 1 == selected, 5);
    printHighlighted("Opcion 2\n", 2 == selected, 5);
}

void printHighlighted(string text, bool highlight, int color, int x, int y) {
    if (highlight) {
        rlutil::setBackgroundColor(color);
        if (x + y != 0) rlutil::locate(x, y);
        std::cout << text;
        rlutil::setBackgroundColor(DEFAULT_BG);
    } else {
        rlutil::setBackgroundColor(DEFAULT_BG);
        if (x + y != 0) rlutil::locate(x, y);
        std::cout << text;
        rlutil::setBackgroundColor(DEFAULT_BG);
    }
}