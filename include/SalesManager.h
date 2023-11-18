#include "Sale.h"
#include "VppFile.h"

class SalesManager {
private:
    VppFile<Sale> _salesFile = VppFile<Sale>("sales.vpp");
    const int _salesFields = 7;  // total de datos de un regisro Sale
    Sale loadForm();
    Sale editForm(int regPos);

public:
    void load();
    void edit();
    void show();

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "SalesManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(Sale reg, int nId);
};


