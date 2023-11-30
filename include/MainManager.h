#ifndef MAINMANAGER_INCLUDED
#define MAINMANAGER_INCLUDED

#include "ClientsManager.h"
#include "Menu.h"
#include "SubMenus.h"

/**
 * @brief Clase que representa el administrador principal del programa.
 *
 * Esta clase se encarga de gestionar el menú principal y los submenús del
 * programa. También verifica la configuración antes de iniciar el programa.
 */
class MainManager {
private:
    Menu _mainMenu = Menu("MENU PRINCIPAL:house:");
    SubMenus _subMenus;

    /**
     * @brief Verifica la configuración del programa.
     * @return true si la configuración es válida, false en caso contrario.
     */
    bool checkConfig();

public:
    /**
     * @brief Inicia el programa.
     */
    void start();

    /**
     * @brief Muestra el menú principal.
     */
    void mainMenu();
};

#endif /* MAINMANAGER_INCLUDED */
