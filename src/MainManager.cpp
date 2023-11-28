#include "MainManager.h"

#include <windows.h>

#include "StatusBar.h"
#include "VppConfigManager.h"
#include "utils.h"
// eliminar esto
void funcSubMenutest() { system("pause"); }

bool MainManager::checkConfig() {
    VppConfigManager vppConfigMgr;
    // Si existe archivo de configuración, cargar configuración
    if (vppConfigMgr.exists()) return vppConfigMgr.init();
    // Si no existe, crearlo y tratar de cargarlo
    if (vppConfigMgr.load()) return vppConfigMgr.init();
    // si se llega a este punto, ocurrió un error en la carga y el usuario ya
    // fue informado
    return true;
}

void MainManager::start() {
    StatusBar statusBar;  // inicializa StatusBar
    std::cout << "Iniciando sistema...\n";
    SetConsoleOutputCP(65001);  // setear pagina de codigos UTF8 para emojis
    if (!checkConfig()) {
        utils::coutCenter(
            "Ocurrió un error al cargar la configuración del sistema.");
        utils::coutCenter(
            "la funcionalidad de envío de notificaciones estará "
            "deshabilitada.");
        utils::pause();
    }
    statusBar.update();
    mainMenu();
}

void MainManager::mainMenu() {
    _mainMenu.addOption("1. Gestión de Clientes :busts_in_silhouette:",
                        _subMenus.clients);
    _mainMenu.addOption("2. Gestión de Mascotas :dog:", _subMenus.pets);
    _mainMenu.addOption("3. Gestión de Relaciones :couple_with_heart:",
                        _subMenus.relations);
    _mainMenu.addOption("4. Gestión de Turnos :date:", _subMenus.appointments);
    _mainMenu.addOption("5. Gestión de Consultas :file_folder:",
                        _subMenus.vetvisits);
    _mainMenu.addOption("6. Gestión de Vacunación :syringe:",
                        _subMenus.vaccination);
    _mainMenu.addOption("7. Gestión de Inventarios :file_folder:",
                        _subMenus.inventory);
    _mainMenu.addOption("8. Gestión de Veterinarios :briefcase:",
                        _subMenus.vets);
    _mainMenu.addOption("9. Enviar email", funcSubMenutest);

    _mainMenu.showMenu();
}
