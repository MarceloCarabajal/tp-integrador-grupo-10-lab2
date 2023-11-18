#ifndef MAINMANAGER_INCLUDED
#define MAINMANAGER_INCLUDED

#include "ClientsManager.h"
#include "Menu.h"
#include "SubMenus.h"

class MainManager {
private:
    Menu _mainMenu = Menu("MENU PRINCIPAL:house:");
    SubMenus _subMenus;

public:
    void start();
    void mainMenu();
};

#endif /* MAINMANAGER_INCLUDED */
