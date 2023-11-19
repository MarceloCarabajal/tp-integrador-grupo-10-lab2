#ifndef SUBMENUS_INCLUDED
#define SUBMENUS_INCLUDED

#include "ClientsManager.h"
#include "Menu.h"
#include "PetRelations.h"
#include "PetsManager.h"
#include "ProductsManager.h"
#include "RelationsManager.h"
#include "VetsManager.h"
#include "VaccinationManager.h"
#include "AppointmentsManager.h"

class SubMenus {
private:
    static ClientsManager _clientsManager;
    static void loadClient();
    static void showClients();
    static void editClients();

  static AppointmentsManager _appointmentsManager;
    static void loadAppointment();
    static void showAppointment();
    static void editAppointment();



    static VetsManager _vetsManager;
    static void loadVet();
    static void showVets();
    static void editVets();

    static PetsManager _petsManager;
    static void loadPet();
    static void showPets();
    static void editPets();

    static RelationsManager _relsManager;
    static void loadRel();
    static void showRels();
    static void editRels();

    static ProductsManager _productsManager;
    static void loadProduct();
    static void showProducts();
    static void editProducts();

    static VaccinationManager _vaccManager;
    static void loadVaccination();
    static void showVaccinations();
    static void editVaccination();

public:
    static void clients();
    static void appointments();
    static void inventory();
    static void vets();
    static void pets();
    static void relations();
    static void products();
    static void vaccination();
};

#endif /* SUBMENUS_INCLUDED */
