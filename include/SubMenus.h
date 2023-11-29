#ifndef SUBMENUS_INCLUDED
#define SUBMENUS_INCLUDED

#include "AppointmentsManager.h"
#include "ClientsManager.h"
#include "Menu.h"
#include "PetRelations.h"
#include "PetsManager.h"
#include "ProdCategoryManager.h"
#include "ProductsManager.h"
#include "RelationsManager.h"
#include "VaccinationManager.h"
#include "VetVisitsManager.h"
#include "VetsManager.h"
#include "BuysManager.h"
#include "SalesManager.h"
#include "VppConfigManager.h"

class SubMenus {
private:
    static ClientsManager _clientsManager;
    static void loadClient();
    static void showClients();
    static void editClients();
    static void cancelClients();
    static void clear();

    static AppointmentsManager _appsManager;
    static void loadAppointment();
    static void showAppointment();
    static void editAppointment();
    static void cancelAppointment();
    static void clearAppointments();
    static void clearDeleted();

    static VetsManager _vetsManager;
    static void loadVet();
    static void showVets();
    static void editVets();
    static void cancelVet();
    static void clearVet();

    static PetsManager _petsManager;
    static void loadPet();
    static void showPets();
    static void editPets();
    static void cancelPets();
    static void clearp();

    static RelationsManager _relsManager;
    static void loadRel();
    static void showRels();
    static void editRels();
    static void cancelRel();
    static void clearRels();

    static ProductsManager _productsManager;
    static void loadProduct();
    static void showProducts();
    static void editProducts();
    static void cancelProduct();
    static void clearProd();

    static VaccinationManager _vaccManager;
    static void loadVaccination();
    static void showVaccinations();
    static void editVaccination();
    static void cancelVaccination();
    static void clearV();

    static ProdCategoryManager _catprodManager;
    static void loadProdCategory();
    static void showProdCategory();
    static void editProdCategory();
    static void cancelProdCategory();
    static void clearPC();

    static VetVisitsManager _vetvisitsManager;
    static void loadvetvisit();
    static void showvetvisits();
    static void editvetvisit();
    static void cancelvetvisit();
    static void clearvv();


    static BuysManager _buysManager;
    static void loadbuy();
    static void showbuy();
    static void editbuy();
    static void cancelbuy();
    static void clearbuy();

    static SalesManager _salesManager;
    static void loadsale();
    static void showsale();
    static void editsale();
   

    static VppConfigManager _vppConfigManager;
    static void editConfig();
    static void toggleMode();

public:
    static void clients();
    static void appointments();
    static void inventory();
    static void vets();
    static void pets();
    static void relations();
    static void products();
    static void vaccination();
    static void productcategory();
    static void vetvisits();
    static void buy();
    static void sysConfig();
    static void sale();
};

#endif /* SUBMENUS_INCLUDED */
