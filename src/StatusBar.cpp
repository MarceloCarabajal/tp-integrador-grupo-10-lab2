#include "StatusBar.h"

#include <iomanip>

#include "AppointmentsManager.h"
#include "VaccinationManager.h"
#include "VppConfigManager.h"
#include "rlutil.h"
#include "utils.h"

int StatusBar::_pendingVacc;  // inicializar variable estática
int StatusBar::_pendingApps;
std::string StatusBar::_veteName;

void StatusBar::update() {
    VppConfigManager configMgr;
    AppointmentsManager appsManager;
    VaccinationManager vaccManager;

    _veteName = configMgr.getVeteName();
    _pendingApps = appsManager.getPendingApps();
    if (_pendingApps == -1) _pendingApps = 0;
    _pendingVacc = vaccManager.pendingCount();
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
              " | Vacunaciones Pendientes: " + std::to_string(_pendingVacc) +
              " | Turnos Pendientes: " + std::to_string(_pendingApps) +
              testMode;

    utils::coutCenter(barText);
    rlutil::setColor(rlutil::MAGENTA);
    std::cout << " " << std::setfill('-') << std::setw(rlutil::tcols() - 2)
              << "" << std::setfill(' ') << std::endl;
    rlutil::setColor(rlutil::GREY);
}