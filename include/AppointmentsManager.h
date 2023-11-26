#pragma once

#include "Appointment.h"
#include "VppFile.h"

class AppointmentsManager {
private:
    VppFile<Appointment> _appsFile = VppFile<Appointment>("Appointments.vpp");
    const int _appsFields = 7;  // total de datos de un regisro Appointment
    Appointment loadForm();
    Appointment editForm(int regPos);
    bool retryIfIdExists(bool exists);
    bool retryIfIdNotExists(bool exists);
    bool retryInvalidTime(bool invalid);
    bool validAppDate(Date date);
    bool validAppTime(const Date& date, const Time& time);
    int getExpiredApps();
    int deleteAllExpired();

public:
    void load();
    void edit();
    void show();
    void clearExpired();
    void clearDeleted();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "AppointmentsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(Appointment reg, int nId);
    bool idExists(int nId);
};
