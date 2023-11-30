#ifndef VPPCONFIGMANAGER_INCLUDED
#define VPPCONFIGMANAGER_INCLUDED
#include "VppConfig.h"
#include "VppFile.h"

/**
 * @class VppConfigManager
 * @brief Clase que gestiona la configuración del programa.
 *
 * La clase VppConfigManager se encarga de administrar la configuración de V++,
 * incluyendo la carga, edición y actualización de la configuración.
 * También proporciona métodos para obtener y establecer el nombre de la
 * veterinaria, así como para obtener las credenciales de acceso para el envio
 * de emails. Además, permite cambiar entre el modo de prueba y el modo de
 * producción.
 */
class VppConfigManager {
private:
    VppFile<VppConfig> _confFile = VppFile<VppConfig>("VppConfig.vpp");
    static VppConfig _vppConfig;
    static std::string _veteName;
    static bool _testMode;
    /**
     * @brief Imprime el título.
     */
    void printTitle();
    /**
     * @brief Imprime el texto de verificacion del ancho de pantalla.
     */
    void checkText();
    /**
     * @brief Reinicia el sistema.
     *
     * Esta función reinicia el sistema para que sea efectivo el cambio de modo
     */
    void restart();

public:
    VppConfigManager();

    /**
     * @brief Inicializa la configuracion.
     *
     * @return true si la inicialización fue exitosa, false en caso contrario.
     */
    bool init();

    /**
     * @brief Verifica el ancho de la pantalla.
     *
     * Si el ancho de la pantalla es menor a 100, imprime un mensaje de error
     * y espera a que el usuario agrande la ventana.
     */
    void checkWidth();

    /**
     * @brief Pide al usuari la carga de la configuración.
     *
     * @return true si la carga fue exitosa, false en caso contrario.
     */
    bool load();

    /**
     * @brief Pide al usuario la edición de la configuración.
     *
     * @return true si la edición fue exitosa, false en caso contrario.
     */
    void edit();

    /**
     * @brief Cambia el modo a produccion/prueba.
     *
     * Esta función cambia el modo de funcionamiento del sistema.
     */
    void toggleMode();

    /**
     * @brief Variable que indica si todo está en orden.
     *
     * Esta variable indica si la configuración
     * se pudo leer y cargar correctamente
     */
    static bool isOk;

    /**
     * @brief Obtiene el nombre de la veterinaria.
     *
     * @return El nombre de la veterinaria como un objeto de tipo std::string.
     */
    std::string getVeteName();

    /**
     * @brief Obtiene las credenciales para el servidor SMTP
     *
     * @param vc Referencia a un objeto VppConfig donde se almacenarán las
     * credenciales.
     */
    void getCredentials(VppConfig &vc);

    /**
     * @brief Establece la configuración obtenida del objeto VppConfigManager.
     *
     * @param vc La configuración a establecer.
     * @return true si la configuración se estableció correctamente, false en
     * caso contrario.
     */
    bool setConfig(const VppConfig &vc);

    /**
     * @brief Actualiza la configuración con los valores proporcionados.
     *
     * @param vc La configuración actualizada.
     * @return true si la actualización fue exitosa, false de lo contrario.
     */
    bool updateConfig(const VppConfig &vc);

    /**
     * @brief Verifica si el archivo de configuración existe.
     *
     * @return true si el archivo existe, false en caso contrario.
     */
    bool exists();

    /**
     * @brief Verifica si el programa está en modo de prueba.
     *
     * @return true si el programa está en modo de prueba, false en caso
     * contrario.
     */
    bool isTesting();

    /**
     * @brief Obtiene la ruta de los datos.
     *
     * @return La ruta de los datos como un objeto de tipo std::string.
     */
    static std::string getDataPath();

    // posible idea: encriptar los datos de vppconfig.vpp
    // bool getCredentials(std::string passkey, VppConfig &vc);
};

#endif /* VPPCONFIGMANAGER_INCLUDED */
