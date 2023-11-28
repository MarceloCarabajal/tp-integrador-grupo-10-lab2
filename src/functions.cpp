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
#include "Credentials.h"

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

bool sendEmail(string to, string subject, string body) {
    quickmail_initialize();
    quickmail mailObj =
        quickmail_create("notificacion@vetegestion.com.ar", subject.c_str());

    char *cBody = &body[0];

    // HEADERS:
    quickmail_add_header(mailObj,
                         "From: veteName <notificacion@vetegestion.com.ar>");
    quickmail_add_header(
        mailObj, "Reply-To: veteName <notificacion@vetegestion.com.ar>");
    quickmail_add_header(
        mailObj, "Organization: veteName <notificacion@vetegestion.com.ar>");
    quickmail_add_header(mailObj, "MIME-Version: 1.0");
    quickmail_add_header(mailObj, "X-Priority: 3");

    quickmail_add_body_memory(mailObj, "text/html", cBody, body.length(), 0);
    // quickmail_add_attachment_file(mailObj, "C:\\pdf.pdf", "application/pdf");
    quickmail_add_to(mailObj, to.c_str());
    const char *errmsg =
        quickmail_send(mailObj, SMTP_HOST, SMTP_PORT, SMTP_USR, SMTP_PWD);
    if (errmsg != NULL) {
        cout << "Error al enviar e-mailj:\n" << errmsg;
        return false;
    }
    quickmail_destroy(mailObj);
    return true;
}

void sendTestEmail() {
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
}