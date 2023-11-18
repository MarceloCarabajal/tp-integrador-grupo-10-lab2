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
    Menu mnuClients("CLIENTES", true);
    mnuClients.addOption("1. Cargar Cliente", loadClient);
    mnuClients.addOption("2. Mostrar Clientes", showClients);
    mnuClients.addOption("3. Editar cliente", editClients);
    mnuClients.showMenu();
}

void SubMenus::appointments() {
    /* Menu subMenu("Otro Menu", true);
        subMenu.addOption("1. Cualquier cosa", funcCualquier);
        subMenu.addOption("2. Otra cualquier cosa", funcCualquier);
        subMenu.showMenu(); */
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
    Menu mnuVets("VETERINARIOS", true);

    mnuVets.addOption("1. Cargar Veterinario", loadVet);
    mnuVets.addOption("2. Mostrar Veterinarios", showVets);
    mnuVets.addOption("3. Editar Veterinario", editVets);
    mnuVets.showMenu();
}

PetsManager SubMenus::_petsManager = PetsManager();
void SubMenus::loadPet() { _petsManager.load(); }
void SubMenus::showPets() { _petsManager.show(); }
void SubMenus::editPets() { _petsManager.edit(); }

void SubMenus::pets() {
    Menu mnuPets("MASCOTAS", true);

    mnuPets.addOption("1. Cargar Mascota", loadPet);
    mnuPets.addOption("2. Mostrar Mascotas", showPets);
    mnuPets.addOption("3. Editar Mascota", editPets);
    mnuPets.showMenu();
}

RelationsManager SubMenus::_relsManager = RelationsManager();
void SubMenus::loadRel() { _relsManager.load(); }
void SubMenus::showRels() { _relsManager.show(); }
void SubMenus::editRels() { _relsManager.edit(); }

void SubMenus::relations() {
    Menu mnuRels("RELACIONES", true);

    mnuRels.addOption("1. Cargar Relacion", loadRel);
    mnuRels.addOption("2. Mostrar Relaciones", showRels);
    mnuRels.addOption("3. Editar Relacion", editRels);
    mnuRels.showMenu();
}

ProductsManager SubMenus::_productsManager = ProductsManager();
void SubMenus::loadProduct() { _productsManager.load(); }
void SubMenus::showProducts() { _productsManager.show(); }
void SubMenus::editProducts() { _productsManager.edit(); }

void SubMenus::products() {
    Menu mnuProducts("PRODUCTOS", true);

    mnuProducts.addOption("1. Cargar Producto", loadProduct);
    mnuProducts.addOption("2. Mostrar producto", showProducts);
    mnuProducts.addOption("3. Editar producto", editProducts);
    mnuProducts.showMenu();
}

VaccinationManager SubMenus::_vaccManager = VaccinationManager();
void SubMenus::loadVaccination() { _vaccManager.load(); }
void SubMenus::showVaccinations() { _vaccManager.show(); }
void SubMenus::editVaccination() { _vaccManager.edit(); }

void SubMenus::vaccination() {
    Menu mnuVaccination("VACUNACION", true);

    mnuVaccination.addOption("1. Cargar Vacunacion", loadVaccination);
    mnuVaccination.addOption("2. Mostrar Vacunaciones", showVaccinations);
    mnuVaccination.addOption("3. Editar Vacunacion", editVaccination);
    mnuVaccination.showMenu();
}