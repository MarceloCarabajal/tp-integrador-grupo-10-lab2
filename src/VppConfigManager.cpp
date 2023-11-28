#include "VppConfigManager.h"

#include <fileapi.h>  // necesario para la funcion GetFileAttributes

#include "InputForm.h"
#include "VppConfig.h"
#include "utils.h"
// declarar a nivel archivo las variable estaticas
// De esta forma una vez que se inicialize, ya no va a ser necesaria la lectura
// del archivo VppConfig.vpp cada vez que se instancie esta clase
VppConfig VppConfigManager::_vppConfig;
std::string VppConfigManager::_veteName;

// cargar datos del archivo
bool VppConfigManager::init() {
    _vppConfig = _confFile.readFile(0);
    if (_vppConfig.getSMTPPort() == 0) return false;
    _veteName = _vppConfig.getVeteName();
    return true;
}

bool VppConfigManager::load() {
    InputForm configForm;
    VppConfig auxVc;
    std::string veteName, SMTPServer, SMTPUser, SMTPPass;
    int SMTPPort;
    utils::cls();
    utils::coutCenter("-------------------------");
    utils::coutCenter("Configuración del sistema");
    utils::coutCenter("-------------------------");
    std::cout << std::endl;
    utils::coutCenter(
        "Deberá ingresar una serie de datos para "
        "configurar el sistema.");
    utils::coutCenter(
        "Estos serán necesarios para asegurar el correcto "
        "funcionamiento del mismo.");
    std::cout << std::endl;
    configForm.setStrField("Nombre de la veterinaria", veteName, 30);
    configForm.setAlphanumeric("Servidor SMTP", SMTPServer, 45);
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

std::string VppConfigManager::getVeteName() { return _veteName; }

void VppConfigManager::getCredentials(VppConfig &vc) { vc = _vppConfig; }

bool VppConfigManager::setConfig(const VppConfig &vc) {
    // writeFile utiliza el modo de escritura "ab" pero teniendo en cuenta que
    // solo se llama a este metodo cuando no existe VppConfig.vpp, entonces este
    // va a ser el unico registro existente
    return _confFile.writeFile(vc);
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