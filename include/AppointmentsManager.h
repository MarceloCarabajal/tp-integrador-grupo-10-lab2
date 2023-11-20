#pragma once

#include "Appointment.h"
#include "VppFile.h"

class AppointmentsManager {
private:
    VppFile<Appointment> _appointmentsFile = VppFile<Appointment>("Appointments.vpp");
    const int _AppointmentsFields = 7;  // total de datos de un regisro Appointment
  Appointment loadForm();
  Appointment  editForm(int regPos);



public:
    void load();
    void edit();
    void show();
    void menu();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "AppointmentsManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(Appointment reg, int nId);
};
