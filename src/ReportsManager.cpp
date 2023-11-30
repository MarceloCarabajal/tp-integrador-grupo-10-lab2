#include "ReportsManager.h"

void ReportsManager::showSuccessApps() {
    utils::coutCenter("--------------------------");
    utils::coutCenter("Reporte de Turnos exitosos");
    utils::coutCenter("--------------------------");

    int appsCount = _appsManager.getActiveAppsCount();
    Appointment* apps = _appsManager.getActiveApps();
    if (appsCount == -1 || apps == NULL) {
        std::cout << "Ocurrió un error al obtener los turnos.\n";
        utils::pause();
        return;
    }
    if (appsCount == 0) {
        std::cout << "No hay turnos registrados para mostrar.\n";
        utils::pause();
        return;
    }

    int AttendedApps = countAttendedApps(apps, appsCount);
    std::cout << "Total de turnos: " << appsCount << std::endl;
    std::cout << "Total de turnos atendidos:" << AttendedApps << std::endl;
    std::cout << "Porcentaje de turnos atendidos: "
              << (AttendedApps * 100) / appsCount << "%\n";
    utils::pause();
    delete[] apps;
}

int ReportsManager::countAttendedApps(Appointment* apps, int appsCount) {
    int assisted = 0;
    for (int i = 0; i < appsCount; i++) {
        if (apps[i].getAttended()) {
            assisted++;
        }
    }
    return assisted;
}