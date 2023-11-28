#ifndef VPPCONFIGMANAGER_INCLUDED
#define VPPCONFIGMANAGER_INCLUDED
#include "VppConfig.h"
#include "VppFile.h"

class VppConfigManager {
private:
    VppFile<VppConfig> _confFile = VppFile<VppConfig>("VppConfig.vpp");
    static VppConfig _vppConfig;
    static std::string _veteName;

public:
    bool init();
    bool load();

    std::string getVeteName();
    void getCredentials(VppConfig &vc);
    bool setConfig(const VppConfig &vc);
    bool exists();

    // posible idea: encriptar los datos de vppconfig.vpp
    // bool getCredentials(std::string passkey, VppConfig &vc);
};

#endif /* VPPCONFIGMANAGER_INCLUDED */
