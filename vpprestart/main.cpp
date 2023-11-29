#include <tchar.h>
#include <windows.h>

#include "..\include\rlutil.h"

int main() {
    std::cout << "REINICIANDO VETE++..." << std::endl;
    rlutil::msleep(2000);
    ShellExecute(NULL, _T("open"), _T("vetepp.exe"), NULL, NULL,
                 SW_SHOWDEFAULT);
    return 0;
}