#ifndef VPPCONFIGMANAGER_INCLUDED
#define VPPCONFIGMANAGER_INCLUDED
#include "VppConfig.h"
#include "VppFile.h"

class VppConfigManager {
private:
    VppFile<VppConfig> _confFile = VppFile<VppConfig>("VppConfig.vpp");
    static VppConfig _vppConfig;
    static std::string _veteName;
    static bool _testMode;
    void printTitle();
    void checkText();

public:
    bool init();
    void checkWidth();
    bool load();
    void edit();
    void toggleMode();
    void setDebugMode(bool debugMode);

    std::string getVeteName();
    void getCredentials(VppConfig &vc);
    bool setConfig(const VppConfig &vc);
    bool updateConfig(const VppConfig &vc);
    bool exists();
    bool isTesting();
    static std::string getDataPath();
    // posible idea: encriptar los datos de vppconfig.vpp
    // bool getCredentials(std::string passkey, VppConfig &vc);
};

#endif /* VPPCONFIGMANAGER_INCLUDED */
