#include "VppConfig.h"

#include <cstring>

VppConfig::VppConfig() {
    strcpy(_veteName, "");
    strcpy(_SMTPPass, "");
    strcpy(_SMTPServer, "");
    strcpy(_SMTPUser, "");
    _SMTPPort = 0;
    _testMode = false;
}

void VppConfig::setVeteName(std::string vtN) { strcpy(_veteName, vtN.c_str()); }
void VppConfig::setSMTPServer(std::string srv) {
    strcpy(_SMTPServer, srv.c_str());
}
void VppConfig::setSMTPUser(std::string usr) { strcpy(_SMTPUser, usr.c_str()); }
void VppConfig::setSMTPPass(std::string pass) {
    strcpy(_SMTPPass, pass.c_str());
}
void VppConfig::setSMTPPort(int p) { _SMTPPort = p; }
void VppConfig::setTestMode(bool testMode) { _testMode = testMode; }

const char* VppConfig::getVeteName() { return _veteName; }
const char* VppConfig::getSMTPServer() { return _SMTPServer; }
const char* VppConfig::getSMTPUser() { return _SMTPUser; }
const char* VppConfig::getSMTPPass() { return _SMTPPass; }
int VppConfig::getSMTPPort() { return _SMTPPort; }
bool VppConfig::getTestMode() { return _testMode; }