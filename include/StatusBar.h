#ifndef STATUSBAR_INCLUDED
#define STATUSBAR_INCLUDED

#include <iostream>

class StatusBar {
private:
    static int _pendingNotif;
    static int _pendingApps;
    static std::string _veteName;

public:
    StatusBar();
    void update();
    static void show();
};

#endif /* STATUSBAR_INCLUDED */
