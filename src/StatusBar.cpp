#include "StatusBar.h"

#include <iomanip>
#include <iostream>

#include "AppointmentsManager.h"
#include "rlutil.h"

int StatusBar::_pendingNotif;  // inicializar variable estática
int StatusBar::_pendingApps;
StatusBar::StatusBar() { _pendingNotif = 0; }

void StatusBar::update() {
    AppointmentsManager appsManager;
    _pendingApps = appsManager.getPendingApps();
    _pendingNotif++;
}

void StatusBar::show() {
    rlutil::locate(0, 0);
    rlutil::setColor(rlutil::MAGENTA);
    std::cout << std::setfill('-') << std::setw(rlutil::tcols()) << ""
              << std::endl;
    rlutil::setColor(rlutil::GREY);
    std::cout << "Notificaciones pendientes: " << _pendingNotif;
    std::cout << " || Turnos Pendientes: " << _pendingApps << std::endl;
    rlutil::setColor(rlutil::MAGENTA);
    std::cout << std::setfill('-') << std::setw(rlutil::tcols()) << ""
              << std::setfill(' ') << std::endl;
    rlutil::setColor(rlutil::GREY);
}