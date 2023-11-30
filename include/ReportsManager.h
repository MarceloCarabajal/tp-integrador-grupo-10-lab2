#ifndef REPORTSMANAGER_INCLUDED
#define REPORTSMANAGER_INCLUDED

#include "AppointmentsManager.h"
#include "VetVisitsManager.h"
#include "utils.h"

class ReportsManager {
private:
    AppointmentsManager _appsManager = AppointmentsManager();
    int countAttendedApps(Appointment* apps, int appsCount);

    VetVisitsManager _vetVisitsManager = VetVisitsManager();
    int countVetVisits (VetVisits* visits, int vetVisitsCount);


public:
    void showSuccessApps();
    void showStadisticsVetVisits();
};

#endif /* REPORTSMANAGER_INCLUDED */
