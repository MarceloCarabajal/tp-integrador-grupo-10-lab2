#include "SubMenus.h"

void SubMenus::clients() {
    Menu subMenu("CLIENTES", true);

    subMenu.addOption("1. Cargar Cliente", _clientsManager.load);
    subMenu.addOption("2. Mostrar Clientes", _clientsManager.show);
    subMenu.addOption("3. Editar cliente", _clientsManager.edit);
    subMenu.showMenu();
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

void SubMenus::vets() {
    Menu subMenu("VETERINARIOS", true);

    subMenu.addOption("1. Cargar Veterinario", _vetsManager.load);
    subMenu.addOption("2. Mostrar Veterinarios", _vetsManager.show);
    subMenu.addOption("3. Editar Veterinario", _vetsManager.edit);
    subMenu.showMenu();
}

void SubMenus::pets() {
    Menu subMenu("MASCOTAS", true);

    subMenu.addOption("1. Cargar Mascota", _petsManager.load);
    subMenu.addOption("2. Mostrar Mascotas", _petsManager.show);
    subMenu.addOption("3. Editar Mascota", _petsManager.edit);
    subMenu.showMenu();
}

void SubMenus::relations() {
    Menu subMenu("RELACIONES", true);

    subMenu.addOption("1. Cargar Relacion", _relationsManager.load);
    subMenu.addOption("2. Mostrar Mascotas", _relationsManager.show);
    subMenu.addOption("3. Editar Mascota", _relationsManager.edit);
    subMenu.showMenu();
}

void SubMenus::products() {
    Menu subMenu("PRODUCTOS", true);

    subMenu.addOption("1. Cargar Producto", _productManager.load);
    subMenu.addOption("2. Mostrar producto", _productManager.show);
    subMenu.addOption("3. Editar producto", _productManager.edit);
    subMenu.showMenu();
}
