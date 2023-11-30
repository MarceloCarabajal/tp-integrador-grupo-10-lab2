#include "SubMenus.h"

#include "utils.h"

ClientsManager SubMenus::_clientsManager = ClientsManager();
void SubMenus::loadClient() {
    _clientsManager.load();
    utils::pause();
}
void SubMenus::editClients() { _clientsManager.edit(); }
void SubMenus::showClients() { _clientsManager.show(); }
void SubMenus::cancelClients() {
    _clientsManager.cancel();
    utils::pause();
}
void SubMenus::clear() {
    _clientsManager.clearDeleted();
    utils::pause();
}

void SubMenus::clients() {
    Menu mnuClients("CLIENTES:busts_in_silhouette:", true);
    mnuClients.addOption("1. Cargar Cliente :arrow_up_small:", loadClient);
    mnuClients.addOption("2. Mostrar Clientes :page_facing_up:", showClients);
    mnuClients.addOption("3. Editar cliente :pencil2:", editClients);
    mnuClients.addOption("4. Baja del cliente :x:", cancelClients);
    mnuClients.addOption("5. Limpiar registros :white_check_mark:", clear);
    mnuClients.showMenu();
}

VetVisitsManager SubMenus::_vetvisitsManager = VetVisitsManager();
void SubMenus::loadvetvisit() {
    _vetvisitsManager.load();
    utils::pause();
}
void SubMenus::editvetvisit() { _vetvisitsManager.edit(); }
void SubMenus::showvetvisits() {
    _vetvisitsManager.show();
    utils::pause();
}
void SubMenus::cancelvetvisit() { _vetvisitsManager.cancel(); }
void SubMenus::clearvv() { _vetvisitsManager.clearDeleted(); }

void SubMenus::vetvisits() {
    Menu mnuClients("CONSULTAS VETERINARIAS:busts_in_silhouette:", true);
    mnuClients.addOption("1. Cargar Consulta :arrow_up_small:", loadvetvisit);
    mnuClients.addOption("2. Mostrar Consulta :page_facing_up:", showvetvisits);
    mnuClients.addOption("3. Editar Consulta:pencil2:", editvetvisit);
    mnuClients.addOption("4. Baja de consulta :x:", cancelvetvisit);
    mnuClients.addOption("5. Limpiar registros :white_check_mark:", clearvv);
    mnuClients.showMenu();
}

AppointmentsManager SubMenus::_appsManager = AppointmentsManager();
void SubMenus::loadAppointment() { _appsManager.load(); }
void SubMenus::showAppointment() { _appsManager.show(); }
void SubMenus::editAppointment() { _appsManager.edit(); }
void SubMenus::cancelAppointment() { _appsManager.cancel(); }
void SubMenus::clearAppointments() { _appsManager.clearExpired(); }
void SubMenus::clearDeleted() { _appsManager.clearDeleted(); }
void SubMenus::appointments() {
    Menu mnuAppoint("TURNOS :busts_in_silhouette:", true);
    mnuAppoint.addOption("1. Cargar Turno :arrow_up_small:", loadAppointment);
    mnuAppoint.addOption("2. Mostrar Turnos :page_facing_up:", showAppointment);
    mnuAppoint.addOption("3. Editar Turno :pencil2:", editAppointment);
    mnuAppoint.addOption("4. Cancelar Turno :x:", cancelAppointment);
    mnuAppoint.addOption("5. Eliminar expirados :x:", clearAppointments);
    mnuAppoint.addOption("6. Limpiar registros :white_check_mark:",
                         clearDeleted);
    mnuAppoint.showMenu();
}

/*
AppointmentsManager SubMenus::_appsManager = AppointmentsManager();
void SubMenus::loadAppointment() { _appsManager.load(); }
void SubMenus::showAppointment() { _appsManager.show(); utils::pause(); }
void SubMenus::editAppointment() { _appsManager.edit(); }*/

/*/
        mnuInventory.addOption("1. Cargar productos", loadProduct);
        mnuInventory.addOption("2. Edita productos", editProducts);
        mnuInventory.addOption("3. Mostrar productos", showProducts);
        mnuInventory.addOption("4. Cargar categoria ", loadProdCategory);
        mnuInventory.addOption("5. Editar categoria ", editProdCategory);
        mnuInventory.addOption("6. Mostrar categoria ", showProdCategory);
        mnuInventory.showMenu();
}*/

VetsManager SubMenus::_vetsManager = VetsManager();
void SubMenus::loadVet() {
    _vetsManager.load();
    utils::pause();
}
void SubMenus::showVets() {
    _vetsManager.show();
    utils::pause();
}
void SubMenus::editVets() { _vetsManager.edit(); }
void SubMenus::cancelVet() { _vetsManager.cancel(); }
void SubMenus::clearVet() { _vetsManager.clearDeleted(); }

void SubMenus::vets() {
    Menu mnuVets("VETERINARIOS:briefcase:", true);

    mnuVets.addOption("1. Cargar Veterinario :arrow_up_small:", loadVet);
    mnuVets.addOption("2. Mostrar Veterinarios :page_facing_up:", showVets);
    mnuVets.addOption("3. Editar Veterinario :pencil2:", editVets);
    mnuVets.addOption("4. Baja de Veterinario:x:", cancelVet);
    mnuVets.addOption("5. Limpiar registros :white_check_mark:", clearVet);
    mnuVets.showMenu();
}

PetsManager SubMenus::_petsManager = PetsManager();
void SubMenus::loadPet() {
    _petsManager.load();
    utils::pause();
}
void SubMenus::showPets() { _petsManager.show(); }
void SubMenus::editPets() { _petsManager.edit(); }
void SubMenus::cancelPets() { _petsManager.cancel(); }
void SubMenus::clearp() {
    _petsManager.clearDeleted();
    utils::pause();
}

void SubMenus::pets() {
    Menu mnuPets("MASCOTAS:dog:", true);

    mnuPets.addOption("1. Cargar Mascota :arrow_up_small:", loadPet);
    mnuPets.addOption("2. Mostrar Mascotas :page_facing_up:", showPets);
    mnuPets.addOption("3. Editar Mascota :pencil2:", editPets);
    mnuPets.addOption("4. Baja de mascota:x:", cancelPets);
    mnuPets.addOption("5. Limpiar registros :white_check_mark:", clearp);
    mnuPets.showMenu();
}

RelationsManager SubMenus::_relsManager = RelationsManager();
void SubMenus::loadRel() {
    _relsManager.load();
    utils::pause();
}
void SubMenus::showRels() { _relsManager.show(); }
void SubMenus::editRels() { _relsManager.edit(); }
void SubMenus::deleteRel() { _relsManager.deleteRel(); }

void SubMenus::relations() {
    Menu mnuRels("RELACIONES:couple_with_heart:", true);

    mnuRels.addOption("1. Cargar Relación :arrow_up_small:", loadRel);
    mnuRels.addOption("2. Mostrar Relaciones :page_facing_up:", showRels);
    mnuRels.addOption("3. Editar Relación :pencil2:", editRels);
    mnuRels.addOption("4. Baja de Relación :x:", deleteRel);
    mnuRels.showMenu();
}

VaccinationManager SubMenus::_vaccManager = VaccinationManager();
void SubMenus::loadVaccination() {
    _vaccManager.load();
    utils::pause();
}
void SubMenus::showVaccinations() { _vaccManager.show(); }
void SubMenus::editVaccination() { _vaccManager.edit(); }
void SubMenus::cancelVaccination() { _vaccManager.cancel(); }
void SubMenus::clearV() { _vaccManager.clearDeleted(); }
void SubMenus::sendNotif() { _vaccManager.configAndSendNotif(); }
void SubMenus::vaccination() {
    Menu mnuVaccination("VACUNACIÓN:syringe:", true);

    mnuVaccination.addOption("1. Cargar Vacunación :arrow_up_small:",
                             loadVaccination);
    mnuVaccination.addOption("2. Mostrar Vacunaciones :page_facing_up:",
                             showVaccinations);
    mnuVaccination.addOption("3. Editar Vacunación :pencil2:", editVaccination);
    mnuVaccination.addOption("4. Baja Vacunación :x:", cancelVaccination);
    mnuVaccination.addOption("5. Limpiar registros :white_check_mark:", clearV);
    mnuVaccination.addOption("6. Enviar notificaciones pendientes :mailbox:",
                             sendNotif);
    mnuVaccination.showMenu();
}

ProductsManager SubMenus::_productsManager = ProductsManager();
void SubMenus::loadProduct() {
    _productsManager.load();
    utils::pause();
}
void SubMenus::showProducts() { _productsManager.show(); }
void SubMenus::editProducts() { _productsManager.edit(); }
void SubMenus::cancelProduct() { _productsManager.cancel(); }
void SubMenus::clearProd() { _productsManager.clearDeleted(); }

void SubMenus::products() {
    Menu mnuProducts("PRODUCTOS:package:", true);

    mnuProducts.addOption("1. Cargar Producto :arrow_up_small:", loadProduct);
    mnuProducts.addOption("2. Mostrar producto :page_facing_up:", showProducts);
    mnuProducts.addOption("3. Editar producto :pencil2:", editProducts);
    mnuProducts.addOption("4. Baja Producto :x:", cancelProduct);
    mnuProducts.addOption("5. Limpiar Registros :white_check_mark:", clearProd);
    mnuProducts.showMenu();
}

ProdCategoryManager SubMenus::_catprodManager = ProdCategoryManager();
void SubMenus::loadProdCategory() {
    _catprodManager.load();
    utils::pause();
}
void SubMenus::showProdCategory() { _catprodManager.show(); }
void SubMenus::editProdCategory() { _catprodManager.edit(); }
void SubMenus::cancelProdCategory() { _catprodManager.cancel(); }
void SubMenus::clearPC() { _catprodManager.clearDeleted(); }

void SubMenus::productcategory() {
    Menu mnuCatProd("CATEGORIA DE PRODUCTOS:syringe:", true);

    mnuCatProd.addOption("1. Cargar Categoria :arrow_up_small:",
                         loadProdCategory);
    mnuCatProd.addOption("2. Mostrar Categorias :page_facing_up:",
                         showProdCategory);
    mnuCatProd.addOption("3. Editar Categoria :pencil2:", editProdCategory);
    mnuCatProd.addOption("4. Baja Categoria :x:", cancelProdCategory);
    mnuCatProd.addOption("5. Limpiar Registros :white_check_mark:", clearPC);
    mnuCatProd.showMenu();
}

void SubMenus::inventory() {
    Menu mnuInventory("INVENTARIO", true);
    mnuInventory.addOption("1. Gestionar Productos", products);
    mnuInventory.addOption("2. Gestionar Categorías", productcategory);
    mnuInventory.showMenu();
}

IncomeManager SubMenus::_incomeManager = IncomeManager();
void SubMenus::showIncomes() {
    _incomeManager.show();
    utils::pause();
}

ExpenseManager SubMenus::_expenseManager = ExpenseManager();
void SubMenus::showExpenses() {
    _expenseManager.show();
    utils::pause();
}

void SubMenus::transactions() {
    Menu mnuTransac("INGRESOS/EGRESOS", true);
    mnuTransac.addOption("1. Mostrar Ingresos", showIncomes);
    mnuTransac.addOption("2. Mostrar Egresos ", showExpenses);
    mnuTransac.showMenu();
}

SalesManager SubMenus::_salesManager = SalesManager();
void SubMenus::loadsale() {
    _salesManager.load();
    utils::pause();
}
void SubMenus::showsale() {
    _salesManager.show();
    utils::pause();
}
void SubMenus::editsale() { _salesManager.edit(); }

void SubMenus::sale() {
    Menu mnuBuy("VENTAS:syringe:", true);

    mnuBuy.addOption("1. Cargar Venta :arrow_up_small:", loadsale);
    mnuBuy.addOption("2. Mostrar Ventas  :page_facing_up:", showsale);
    mnuBuy.addOption("3. Editar VentaS  :pencil2:", editsale);

    mnuBuy.showMenu();
}

BuysManager SubMenus::_buysManager = BuysManager();
void SubMenus::loadbuy() {
    _buysManager.load();
    utils::pause();
}
void SubMenus::showbuy() { _buysManager.show(); }
void SubMenus::editbuy() { _buysManager.edit(); }
void SubMenus::cancelbuy() { _buysManager.cancel(); }
void SubMenus::clearbuy() { _buysManager.clearDeleted(); }

void SubMenus::buy() {
    Menu mnuBuy("COMPRAS:syringe:", true);

    mnuBuy.addOption("1. Cargar Compra :arrow_up_small:", loadbuy);
    mnuBuy.addOption("2. Mostrar Compras  :page_facing_up:", showbuy);
    mnuBuy.addOption("3. Editar Compra  :pencil2:", editbuy);
    mnuBuy.addOption("4. Baja Compra  :x:", cancelbuy);
    mnuBuy.addOption("5. Limpiar Registros :white_check_mark:", clearbuy);
    mnuBuy.showMenu();
}

VppConfigManager SubMenus::_vppConfigManager = VppConfigManager();
void SubMenus::editConfig() { _vppConfigManager.edit(); }
void SubMenus::toggleMode() { _vppConfigManager.toggleMode(); }

void SubMenus::sysConfig() {
    Menu mnuConfig("CONFIGURACIÓN:gear:", true);

    mnuConfig.addOption("1. Editar configuración :pencil2:", editConfig);
    mnuConfig.addOption(
        "2. Cambiar modo de ejecución :arrows_counterclockwise:", toggleMode);
    mnuConfig.showMenu();
}

ReportsManager SubMenus::_reportsManager = ReportsManager();
void SubMenus::showSuccessApps() { _reportsManager.showSuccessApps(); }

void SubMenus::Reports() {
    Menu mnuReports("REPORTES:bar_chart:", true);

    mnuReports.addOption("1. Turnos exitosos :white_check_mark:",
                         showSuccessApps);
    mnuReports.showMenu();
}