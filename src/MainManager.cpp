#include "MainManager.h"

#include <windows.h>

// eliminar esto
void funcSubMenutest() { system("pause"); }

void MainManager::start() {
    std::cout << "Iniciando..." << std::endl;
    SetConsoleOutputCP(65001);  // setear pagina de codigos UTF8 para emojis
    mainMenu();
}

void MainManager::mainMenu() {
    _mainMenu.addOption("1. Gestión de Clientes :busts_in_silhouette:",
                        _subMenus.clients);
    _mainMenu.addOption("2. Gestión de Turnos :date:", _subMenus.appointments);
    _mainMenu.addOption("3. Gestión de Inventarios :file_folder:",
                        _subMenus.inventory);
    _mainMenu.addOption("4. Enviar email", funcSubMenutest);
    _mainMenu.addOption("5. Gestión de Veterinarios :briefcase:",
                        _subMenus.vets);
    _mainMenu.addOption("6. Gestión de Mascotas :dog:", _subMenus.pets);
    _mainMenu.addOption("7. Gestión de Relaciones :couple_with_heart:",
                        _subMenus.relations);
    _mainMenu.addOption("8. Gestión de Productos :package:",
                        _subMenus.products);
    _mainMenu.showMenu();
}
