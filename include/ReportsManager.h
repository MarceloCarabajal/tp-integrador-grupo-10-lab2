#ifndef REPORTSMANAGER_INCLUDED
#define REPORTSMANAGER_INCLUDED

#include "AppointmentsManager.h"
#include "utils.h"

class ReportsManager {
private:
    AppointmentsManager _appsManager = AppointmentsManager();
    int countAttendedApps(Appointment* apps, int appsCount);

public:
    void showSuccessApps();
};

#endif /* REPORTSMANAGER_INCLUDED */
