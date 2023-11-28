#include "StatusBar.h"

#include <iomanip>

#include "AppointmentsManager.h"
#include "VppConfigManager.h"
#include "rlutil.h"
#include "utils.h"

int StatusBar::_pendingNotif;  // inicializar variable estática
int StatusBar::_pendingApps;
std::string StatusBar::_veteName;
StatusBar::StatusBar() { _pendingNotif = 0; }

void StatusBar::update() {
    VppConfigManager configMgr;
    AppointmentsManager appsManager;

    _veteName = configMgr.getVeteName();
    _pendingApps = appsManager.getPendingApps();
    if (_pendingApps == -1) _pendingApps = 0;
    _pendingNotif++;  // TODO: implementar conteo notificaciones
}

void StatusBar::show() {
    VppConfigManager configMgr;
    std::string barText;
    std::string testMode = "";
    rlutil::locate(0, 0);
    rlutil::setColor(rlutil::MAGENTA);
    std::cout << " " << std::setfill('-') << std::setw(rlutil::tcols() - 2)
              << "" << std::setfill(' ') << std::endl;
    rlutil::setColor(rlutil::GREY);
    if (configMgr.isTesting()) testMode = " | MODO DE PRUEBA ACTIVO";

    barText = _veteName +
              " | Notificaciones pendientes: " + std::to_string(_pendingNotif) +
              " | Turnos Pendientes: " + std::to_string(_pendingApps) +
              testMode;

    utils::coutCenter(barText);
    rlutil::setColor(rlutil::MAGENTA);
    std::cout << " " << std::setfill('-') << std::setw(rlutil::tcols() - 2)
              << "" << std::setfill(' ') << std::endl;
    rlutil::setColor(rlutil::GREY);
}