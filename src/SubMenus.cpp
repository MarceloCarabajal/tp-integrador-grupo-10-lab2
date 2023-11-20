#include "SubMenus.h"

#include "utils.h"

ClientsManager SubMenus::_clientsManager = ClientsManager();
void SubMenus::loadClient() { _clientsManager.load(); }
void SubMenus::editClients() { _clientsManager.edit(); }

void SubMenus::showClients() {
    _clientsManager.show();
    utils::pause();
}

void SubMenus::clients() {
    Menu mnuClients("CLIENTES:busts_in_silhouette:", true);
    mnuClients.addOption("1. Cargar Cliente :arrow_up_small:", loadClient);
    mnuClients.addOption("2. Mostrar Clientes :page_facing_up:", showClients);
    mnuClients.addOption("3. Editar cliente :pencil2:", editClients);
    mnuClients.showMenu();
}

AppointmentsManager SubMenus::_appsManager = AppointmentsManager();
void SubMenus::loadAppointment() { _appsManager.load(); }
void SubMenus::showAppointment() { _appsManager.show(); }
void SubMenus::editAppointment() { _appsManager.edit(); }

void SubMenus::appointments() {
    Menu mnuAppoint("TURNOS :busts_in_silhouette:", true);
    mnuAppoint.addOption("1. Cargar Turno :arrow_up_small:", loadAppointment);
    mnuAppoint.addOption("2. Mostrar Turnos :page_facing_up:", showAppointment);
    mnuAppoint.addOption("3. Editar Turno :pencil2:", editAppointment);
    mnuAppoint.showMenu();
}

void SubMenus::inventory() {
    /* Menu subMenu("Otro Menu", true);
        subMenu.addOption("1. Cualquier cosa", funcCualquier);
        subMenu.addOption("2. Otra cualquier cosa", funcCualquier);
        subMenu.showMenu(); */
}

VetsManager SubMenus::_vetsManager = VetsManager();
void SubMenus::loadVet() { _vetsManager.load(); }
void SubMenus::showVets() { _vetsManager.show(); }
void SubMenus::editVets() { _vetsManager.edit(); }

void SubMenus::vets() {
    Menu mnuVets("VETERINARIOS:briefcase:", true);

    mnuVets.addOption("1. Cargar Veterinario :arrow_up_small:", loadVet);
    mnuVets.addOption("2. Mostrar Veterinarios :page_facing_up:", showVets);
    mnuVets.addOption("3. Editar Veterinario :pencil2:", editVets);
    mnuVets.showMenu();
}

PetsManager SubMenus::_petsManager = PetsManager();
void SubMenus::loadPet() { _petsManager.load(); }
void SubMenus::showPets() { _petsManager.show(); }
void SubMenus::editPets() { _petsManager.edit(); }

void SubMenus::pets() {
    Menu mnuPets("MASCOTAS:dog:", true);

    mnuPets.addOption("1. Cargar Mascota :arrow_up_small:", loadPet);
    mnuPets.addOption("2. Mostrar Mascotas :page_facing_up:", showPets);
    mnuPets.addOption("3. Editar Mascota :pencil2:", editPets);
    mnuPets.showMenu();
}

RelationsManager SubMenus::_relsManager = RelationsManager();
void SubMenus::loadRel() { _relsManager.load(); }
void SubMenus::showRels() { _relsManager.show(); }
void SubMenus::editRels() { _relsManager.edit(); }

void SubMenus::relations() {
    Menu mnuRels("RELACIONES:couple_with_heart:", true);

    mnuRels.addOption("1. Cargar Relación :arrow_up_small:", loadRel);
    mnuRels.addOption("2. Mostrar Relaciones :page_facing_up:", showRels);
    mnuRels.addOption("3. Editar Relación :pencil2:", editRels);
    mnuRels.showMenu();
}

ProductsManager SubMenus::_productsManager = ProductsManager();
void SubMenus::loadProduct() { _productsManager.load(); }
void SubMenus::showProducts() { _productsManager.show(); }
void SubMenus::editProducts() { _productsManager.edit(); }

void SubMenus::products() {
    Menu mnuProducts("PRODUCTOS:package:", true);

    mnuProducts.addOption("1. Cargar Producto :arrow_up_small:", loadProduct);
    mnuProducts.addOption("2. Mostrar producto :page_facing_up:", showProducts);
    mnuProducts.addOption("3. Editar producto :pencil2:", editProducts);
    mnuProducts.showMenu();
}

VaccinationManager SubMenus::_vaccManager = VaccinationManager();
void SubMenus::loadVaccination() { _vaccManager.load(); }
void SubMenus::showVaccinations() { _vaccManager.show(); }
void SubMenus::editVaccination() { _vaccManager.edit(); }

void SubMenus::vaccination() {
    Menu mnuVaccination("VACUNACIÓN:syringe:", true);

    mnuVaccination.addOption("1. Cargar Vacunación :arrow_up_small:",
                             loadVaccination);
    mnuVaccination.addOption("2. Mostrar Vacunaciones :page_facing_up:",
                             showVaccinations);
    mnuVaccination.addOption("3. Editar Vacunación :pencil2:", editVaccination);
    mnuVaccination.showMenu();
}