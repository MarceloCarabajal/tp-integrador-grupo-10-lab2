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
    std::string barText;
    rlutil::locate(0, 0);
    rlutil::setColor(rlutil::MAGENTA);
    std::cout << std::setfill('-') << std::setw(rlutil::tcols()) << ""
              << std::setfill(' ') << std::endl;
    rlutil::setColor(rlutil::GREY);
    barText = _veteName + " || Notificaciones pendientes: " +
              std::to_string(_pendingNotif) +
              " || Turnos Pendientes: " + std::to_string(_pendingApps);
    utils::coutCenter(barText);
    rlutil::setColor(rlutil::MAGENTA);
    std::cout << std::setfill('-') << std::setw(rlutil::tcols()) << ""
              << std::setfill(' ') << std::endl;
    rlutil::setColor(rlutil::GREY);
}