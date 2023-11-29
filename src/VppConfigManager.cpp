#include "VppConfigManager.h"

// API de archivos de Windows
#include <fileapi.h>  // necesario para la funcion GetFileAttributes
#include <tchar.h>
#include <windows.h>

#include "InputForm.h"
#include "VppConfig.h"
#include "utils.h"

// declarar a nivel archivo las variable estaticas
// De esta forma una vez que se inicialize, ya no va a ser necesaria la lectura
// del archivo VppConfig.vpp cada vez que se instancie esta clase
VppConfig VppConfigManager::_vppConfig;
std::string VppConfigManager::_veteName;
bool VppConfigManager::_testMode = false;
bool VppConfigManager::isOk = false;

VppConfigManager::VppConfigManager() {
    // std::cout << "VppConfigMgr inicializado" << std::endl;
    // utils::pause();

    // Solo lee el archivo de configuraciones si no se ha leido antes
    // O si dio error por no existir
    if (_vppConfig.getSMTPPort() != 0) isOk = true;
    if (_vppConfig.getSMTPPort() == 0) {
        _vppConfig = _confFile.readFile(0);
        _veteName = _vppConfig.getVeteName();
        _testMode = _vppConfig.getTestMode();
        if (_vppConfig.getSMTPPort() == 0) {
            isOk = false;
        } else {
            isOk = true;
        }
    }
}

// cargar datos del archivo
bool VppConfigManager::init() {
    _vppConfig = _confFile.readFile(0);
    if (_vppConfig.getSMTPPort() == 0) return false;
    _veteName = _vppConfig.getVeteName();
    _testMode = _vppConfig.getTestMode();
    isOk = true;
    return true;
}

void VppConfigManager::checkText() {
    utils::cls();
    utils::coutCenter(
        "La ventana es demasiado pequeña para ejecutar el programa.");
    utils::coutCenter("Por favor, agrande/estire el ancho de la misma hasta");
    utils::coutCenter("Que la linea de abajo se vea en una sola fila.");
    std::cout << std::setfill('-') << std::setw(100) << "" << std::setfill(' ')
              << std::endl;
}

void VppConfigManager::checkWidth() {
    int actualWidth = rlutil::tcols();
    bool widthOk = false;
    int count = 0;
    if (actualWidth >= 100) return;
    while (!widthOk) {
        checkText();
        if (count == 60) {  // si pasaron 30 segundos, salir
            std::cout << "No se ha podido configurar el ancho correcto, se "
                         "usará el ancho actual pero es probable que el "
                         "programa no se visualice correctamente.\n";
            utils::pause();
            break;
        }
        rlutil::msleep(500);
        checkText();
        actualWidth = rlutil::tcols();
        if (actualWidth >= 100) {
            std::cout << std::endl;
            utils::coutCenter("Ancho configurado correctamente!");
            utils::pause();
            widthOk = true;
        }
    }
}

void VppConfigManager::printTitle() {
    utils::cls();
    utils::coutCenter("-------------------------");
    utils::coutCenter("Configuración del sistema");
    utils::coutCenter("-------------------------");
    std::cout << std::endl;
}

bool VppConfigManager::load() {
    InputForm configForm;
    VppConfig auxVc;
    std::string veteName, SMTPServer, SMTPUser, SMTPPass;
    int SMTPPort;
    printTitle();
    utils::coutCenter(
        "Deberá ingresar una serie de datos para "
        "configurar el sistema.");
    utils::coutCenter(
        "Estos serán necesarios para asegurar el correcto "
        "funcionamiento del mismo.");
    std::cout << std::endl;
    configForm.setStrField("Nombre de la veterinaria", veteName, 30);
    configForm.setSrvField("Servidor SMTP", SMTPServer, 45);
    configForm.setEmailField(SMTPUser, 45, "Usuario SMTP");
    configForm.setAlphanumeric("Contraseña SMTP", SMTPPass, 30);
    configForm.setRangeField("Puerto SMTP", SMTPPort, 0, 65535);

    if (!configForm.fill()) {
        utils::coutCenter("AVISO: No se guardó la configuración");
        utils::coutCenter(
            "la funcionalidad de envío de notificaciones estará "
            "deshabilitada.");
        utils::pause();
        utils::cls();
        return false;
    }

    auxVc.setVeteName(veteName);
    auxVc.setSMTPPass(SMTPPass);
    auxVc.setSMTPPort(SMTPPort);
    auxVc.setSMTPServer(SMTPServer);
    auxVc.setSMTPUser(SMTPUser);
    auxVc.setTestMode(_testMode);  // por defecto desactivado

    if (setConfig(auxVc)) {
        utils::coutCenter("Configuración guardada correctamente!");
        std::cout << std::endl;
        utils::pause();
        utils::cls();
        return true;
    } else {
        utils::coutCenter("Error al guardar la configuración.");
        utils::coutCenter(
            "la funcionalidad de envío de notificaciones estará "
            "deshabilitada.");
        std::cout << std::endl;
        utils::pause();
        utils::cls();
        return false;
    }
}

void VppConfigManager::edit() {
    InputForm configForm(true, true);
    VppConfig auxVc;
    std::string veteName, SMTPServer, SMTPUser, SMTPPass;
    int SMTPPort;
    printTitle();
    utils::coutCenter("Editar datos");
    std::cout << std::endl;

    // cargar datos actuales
    veteName = _vppConfig.getVeteName();
    SMTPServer = _vppConfig.getSMTPServer();
    SMTPUser = _vppConfig.getSMTPUser();
    SMTPPass = _vppConfig.getSMTPPass();
    SMTPPort = _vppConfig.getSMTPPort();
    // configurar campos
    configForm.setStrField("Nombre de la veterinaria", veteName, 30);
    configForm.setAlphanumeric("Servidor SMTP", SMTPServer, 45);
    configForm.setEmailField(SMTPUser, 45, "Usuario SMTP");
    configForm.setAlphanumeric("Contraseña SMTP", SMTPPass, 30);
    configForm.setRangeField("Puerto SMTP", SMTPPort, 0, 65535);
    // pedir datos
    if (!configForm.fill()) {
        utils::coutCenter("AVISO: No se editó la configuración");
        utils::pause();
        utils::cls();
        return;
    }

    auxVc.setVeteName(veteName);
    auxVc.setSMTPPass(SMTPPass);
    auxVc.setSMTPPort(SMTPPort);
    auxVc.setSMTPServer(SMTPServer);
    auxVc.setSMTPUser(SMTPUser);
    auxVc.setTestMode(_testMode);  // conserva el valor actual

    if (updateConfig(auxVc)) {
        utils::coutCenter("Configuración guardada correctamente!");
        std::cout << std::endl;
        utils::pause();
        utils::cls();
        return;
    } else {
        utils::coutCenter("Error al guardar la configuración.");
        std::cout << std::endl;
        utils::pause();
        utils::cls();
        return;
    }
}

void VppConfigManager::toggleMode() {
    InputForm toggleForm;
    bool confirm;
    printTitle();
    utils::coutCenter("Modo de ejecución actual");
    std::cout << "Actualmente está ejecutando el programa en MODO ";
    if (_testMode) {
        std::cout << "DE PRUEBAS.\nEn este se utilizarán los datos de prueba "
                     "precargados.\n";
    } else {
        std::cout << "NORMAL.\nEn este se deben cargar manualmente todos los "
                     "datos.\n";
    }
    std::cout << "Desea cambiar el modo de ejecución? ";
    toggleForm.setBoolField("[SI/NO]", confirm);
    if (!toggleForm.fill()) return;
    if (confirm) {
        VppConfig auxVc = _vppConfig;
        auxVc.setTestMode(!_testMode);
        if (updateConfig(auxVc)) {
            utils::cls();
            utils::coutCenter("Modo de ejecución cambiado correctamente!");
            rlutil::msleep(1000);
            restart();
        } else {
            std::cout << "Ocurrió un error al guardar los cambios.\n";
        }
        utils::pause();
    }
}

void VppConfigManager::restart() {
    int count = 5;
    while (count != 0) {
        utils::coutCenter("EL PROGRAMA SE REINICIARÁ EN " +
                          std::to_string(count) + " SEGUNDOS.");
        rlutil::msleep(1000);
        count--;
        utils::cls();
    }
    ShellExecute(NULL, _T("open"), _T("vpprestart.exe"), NULL, NULL,
                 SW_SHOWDEFAULT);
    exit(0);
}

bool VppConfigManager::isTesting() { return _testMode; }

std::string VppConfigManager::getDataPath() {
    std::string path = "data\\";
    if (_testMode) path = "data_debug\\";
    return path;
}

std::string VppConfigManager::getVeteName() { return _veteName; }

void VppConfigManager::getCredentials(VppConfig &vc) { vc = _vppConfig; }

bool VppConfigManager::setConfig(const VppConfig &vc) {
    // writeFile utiliza el modo de escritura "ab" pero teniendo en cuenta que
    // solo se llama a este metodo cuando no existe VppConfig.vpp, entonces este
    // va a ser el unico registro existente
    return _confFile.writeFile(vc);
}

bool VppConfigManager::updateConfig(const VppConfig &vc) {
    bool success = _confFile.updateFile(vc, 0);
    if (success) init();  // actualizar datos
    return success;
}

bool VppConfigManager::exists() {
    // comprobar si existe VppConfig.vpp
    std::string filePath = "VppConfig.vpp";
    // convertir string a TCHAR/WCHAR
    TCHAR *Tpath = new TCHAR[filePath.size() + 1];
    Tpath[filePath.size()] = 0;
    std::copy(filePath.begin(), filePath.end(), Tpath);
    // comprobar si existe el archivo
    DWORD dwAttrib = GetFileAttributes(Tpath);

    // si el archivo no existe, devolver false
    return (dwAttrib != INVALID_FILE_ATTRIBUTES);
}