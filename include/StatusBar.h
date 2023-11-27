#ifndef STATUSBAR_INCLUDED
#define STATUSBAR_INCLUDED

class StatusBar {
private:
    static int _pendingNotif;
    static int _pendingApps;

public:
    StatusBar();
    void update();
    static void show();
};

#endif /* STATUSBAR_INCLUDED */
