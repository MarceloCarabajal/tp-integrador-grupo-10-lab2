#ifndef SUBMENUS_INCLUDED
#define SUBMENUS_INCLUDED

#include "AppointmentsManager.h"
#include "BuysManager.h"
#include "ClientsManager.h"
#include "ExpenseManager.h"
#include "IncomeManager.h"
#include "Menu.h"
#include "PetRelations.h"
#include "PetsManager.h"
#include "ProdCategoryManager.h"
#include "ProductsManager.h"
#include "RelationsManager.h"
#include "ReportsManager.h"
#include "SalesManager.h"
#include "VaccinationManager.h"
#include "VetVisitsManager.h"
#include "VetsManager.h"
#include "VppConfigManager.h"

/**
 * @class SubMenus
 * @brief Clase que representa los submenús del sistema.
 *
 * Esta clase contiene los submenús del sistema, cada uno con sus respectivas
 * funciones. Los submenús incluyen la gestión de clientes, citas, veterinarios,
 * mascotas, relaciones, inventario, productos, categorías de productos,
 * vacunaciones, visitas veterinarias, compras, configuración del sistema,
 * ventas, transacciones, ingresos, gastos y reportes.
 */
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
    static void deleteRel();

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
    static void sendNotif();

    static ProdCategoryManager _catprodManager;
    static void loadProdCategory();
    static void showProdCategory();
    static void editProdCategory();
    static void cancelProdCategory();
    static void clearPC();

    static IncomeManager _incomeManager;
    static void showIncomes();

    static ExpenseManager _expenseManager;
    static void showExpenses();

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

    static ReportsManager _reportsManager;
    static void showSuccessApps();

public:
    /**
     * @brief Muestra el submenú de clientes.
     */
    static void clients();

    /**
     * @brief Muestra el submenú de turnos.
     */
    static void appointments();

    /**
     * @brief Muestra el submenú de veterinarios.
     */
    static void vets();

    /**
     * @brief Muestra el submenú de mascotas.
     */
    static void pets();

    /**
     * @brief Muestra el submenú de relaciones.
     */
    static void relations();

    /**
     * @brief Muestra el submenú de inventario.
     */
    static void inventory();

    /**
     * @brief Muestra el submenú de productos.
     */
    static void products();

    /**
     * @brief Muestra el submenú de categorías de productos.
     */
    static void productcategory();

    /**
     * @brief Muestra el submenú de vacunaciones.
     */
    static void vaccination();

    /**
     * @brief Muestra el submenú de visitas veterinarias.
     */
    static void vetvisits();

    /**
     * @brief Muestra el submenú de compras.
     */
    static void buy();

    /**
     * @brief Muestra el submenú de configuración del sistema.
     */
    static void sysConfig();

    /**
     * @brief Muestra el submenú de ventas.
     */
    static void sale();

    /**
     * @brief Muestra el submenú de transacciones.
     */
    static void transactions();

    /**
     * @brief Muestra el submenú de ingresos.
     */
    static void income();

    /**
     * @brief Muestra el submenú de gastos.
     */
    static void expense();

    /**
     * @brief Muestra el submenú de reportes.
     */
    static void Reports();
};

#endif /* SUBMENUS_INCLUDED */
