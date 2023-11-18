#include "MainManager.h"

// eliminar esto
void funcSubMenutest() { system("pause"); }

void MainManager::start() {
    std::cout << "Iniciando..." << std::endl;
    mainMenu();
}

void MainManager::mainMenu() {
    _mainMenu.addOption("1. Gestion de Clientes", _subMenus.clients);
    _mainMenu.addOption("2. Gestion de Turnos", _subMenus.appointments);
    _mainMenu.addOption("3. Gestion de Inventarios", _subMenus.inventory);
    _mainMenu.addOption("4. Enviar email", funcSubMenutest);
    _mainMenu.addOption("5. Gestion de Veterinarios", _subMenus.vets);
    _mainMenu.addOption("6. Gestion de Mascotas", _subMenus.pets);
    _mainMenu.addOption("7. Gestion de Relaciones", _subMenus.relations);
    _mainMenu.addOption("8. Gestion de Productos", _subMenus.products);
    _mainMenu.showMenu();
}
