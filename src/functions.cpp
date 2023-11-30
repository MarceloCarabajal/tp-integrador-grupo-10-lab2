#include "functions.h"

#include <windows.h>  // playSound()

#include <iomanip>
#include <iostream>
#include <string>

#include "EmailTemplate.h"
#include "utils.h"

#pragma comment(lib, "winmm.lib")  // playSound()

#include "quickmail.h"
#include "rlutil.h"

using namespace std;

// Credenciales SMTP
// Ya no son necesarias, se configuran en VppConfig.vpp
// #include "Credentials.h"

std::string getCurrentDirectory() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}
// TODO: quizas sea necesaria esta funcion
void setWorkingDirectory() {
    std::string strPath = getCurrentDirectory();
    TCHAR *Tpath = new TCHAR[strPath.size() + 1];
    Tpath[strPath.size()] = 0;

    std::copy(strPath.begin(), strPath.end(), Tpath);
    SetCurrentDirectory(Tpath);
}

void notifSound() {
    PlaySound("notification.wav", NULL, SND_FILENAME | SND_ASYNC);
}

/* void sendTestEmail() {
    std::string emailTo;
    EmailTemplate emailHTML("data\\notification.html");
    bool successFormat = emailHTML.setEmailData("Facundo", "Nueva notificacion",
                                                Date(2, 11, 2023));
    if (!successFormat) {
        cout << "Error al crear email\n";
        utils::pause();
        return;
    }

    cout << "Destinatario: ";
    cin >> emailTo;
    cout << "Enviando email..\n";
    bool isSent =
        sendEmail(emailTo.c_str(), "Nueva notificacion", emailHTML.getHTML());

    if (isSent) {
        notifSound();
        cout << "\n EMAIL ENVIADO!.\n";
    } else {
        cout << "Ocurrio un error :(\n";
    }
    utils::pause();
} */