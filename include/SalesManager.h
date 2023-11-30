#include "Sale.h"
#include "VppConfigManager.h"
#include "VppFile.h"

class SalesManager {
private:
    const std::string _folderPath = VppConfigManager().getDataPath();
    const std::string _filePath = _folderPath + "Sales.vpp";
    VppFile<Sale> _salesFile = VppFile<Sale>(_filePath);
    const int _salesFields = 6;  // total de datos de un regisro Sale
    Sale loadForm();
    Sale editForm(int regPos);
    bool validAppDate(Date date);
    bool retryInvalidDate(bool valid);

public:
    void load();
    void edit();
    void show(bool showAndPause = true);

    // Al ser una funcion estatica se puede usar sin necesaidad de instanciar un
    // objeto de tipo "SalesManager", eso permite que se pueda pasar por
    // parametro un puntero a esta funcion, lo que es necesario para la busqueda
    // de registros con VppFile
    static bool searchById(Sale reg, int nId);

    bool idExists(int nId);
};
