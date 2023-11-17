#ifndef SUBMENUS_INCLUDED
#define SUBMENUS_INCLUDED

#include "ClientsManager.h"
#include "Menu.h"
#include "PetRelations.h"
#include "PetsManager.h"
#include "ProductManager.h"
#include "RelationsManager.h"
#include "VetsManager.h"


class SubMenus {
private:
    static ClientsManager _clientsManager;
    static VetsManager _vetsManager;
    static RelationsManager _relationsManager;
    static PetsManager _petsManager;
    static PetRelations _petsRelations;
    static ProductManager _productManager;

public:
    static void clients();
    static void appointments();
    static void inventory();
    static void vets();
    static void pets();
    static void relations();
    static void products();
};

#endif /* SUBMENUS_INCLUDED */
