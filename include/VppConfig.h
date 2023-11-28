#ifndef VPPCONFIG_INCLUDED
#define VPPCONFIG_INCLUDED

#include <iostream>

class VppConfig {
private:
    char _veteName[30];
    char _SMTPServer[45];
    char _SMTPUser[45];
    char _SMTPPass[30];
    int _SMTPPort;

public:
    VppConfig();
    void setVeteName(std::string vtN);
    void setSMTPServer(std::string srv);
    void setSMTPUser(std::string usr);
    void setSMTPPass(std::string pass);
    void setSMTPPort(int p);

    const char* getVeteName();
    const char* getSMTPServer();
    const char* getSMTPUser();
    const char* getSMTPPass();
    int getSMTPPort();
};

#endif /* VPPCONFIG_INCLUDED */
