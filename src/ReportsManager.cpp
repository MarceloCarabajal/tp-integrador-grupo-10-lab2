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


/*
///Estadísticas de atención medica por periodo
//primero buscar archivo de consultas y contar los Registros
for con esa cantidad para Leer cada Registro.
contador que sume si el getfecha.mes de la consulta es == al ingresado por usuario

void ReportsManager::showStadisticsVetVisits(){
utils::coutCenter("---------------------------------------------------------");
    utils::coutCenter("Reporte de Cantidad de Consultas en periodo Solicitado");
    utils::coutCenter("------------------------------------------------------");

int vetVisitsCount = _vetVisitsManager.getActiveVetVisitsCount();
VetVisits* visits = _vetVisitsManager.getActiveVetVisits();
    if (visits == -1 || visits == NULL) {
        std::cout << "Ocurrió un error al obtener las consultas.\n";
        utils::pause();
        return;
    }
    if (visits == 0) {
        std::cout << "No hay turnos registrados para mostrar.\n";
        utils::pause();
        return;
    }
int AttendedApps = countVetsVisits(visits, vetVisitsCount );
}



int ReportsManager::countVetsVisits(VetVisits* vetvisits, int appsCount) {
    int assisted = 0;
    for (int i = 0; i < appsCount; i++) {
        if (apps[i].getAttended()) {
            assisted++;
        }
    }
    return assisted;
}*/