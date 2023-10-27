#include "functions.h"

#include <windows.h>  // playSound()

#include <iomanip>
#include <iostream>

#pragma comment(lib, "winmm.lib")  // playSound()

#include "quickmail.h"
#include "rlutil.h"

using namespace std;

// Credenciales SMTP
#include "Credentials.h"

void notifSound() {
    PlaySound("notification.wav", NULL, SND_FILENAME | SND_ASYNC);
}

bool sendEmail(string to, string subject, string body, bool isHTML) {
    quickmail_initialize();
    quickmail mailObj =
        quickmail_create("info@facundomasino.com", subject.c_str());

    char *cBody = &body[0];

    // HEADERS:
    quickmail_add_header(mailObj, "Reply-To: Vete++ <info@facundomasino.com");
    quickmail_add_header(mailObj,
                         "Organization: Vete++ <info@facundomasino.com");
    quickmail_add_header(mailObj, "MIME-Version: 1.0");
    quickmail_add_header(mailObj, "X-Priority: 3");

    // Prueba html
    quickmail_add_body_memory(mailObj, "text/html", cBody, body.length(), 0);
    quickmail_add_attachment_file(mailObj, "C:\\pdf.pdf", "application/pdf");
    // quickmail_set_body(mailObj, body.c_str());
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

// Imprimir un texto centrado
void coutCentered(string str) {
    // Si es un string multilinea, calcular la linea mas larga
    int lTexto = getLongestLine(str);
    cout << setw(rlutil::tcols() / 2 - lTexto / 2) << "";
    for (int i = 0; i < (int)str.length(); i++) {
        if (str[i] == '\n') {
            cout << str[i];
            cout << setw(rlutil::tcols() / 2 - lTexto / 2) << "";
        } else {
            cout << str[i];
        }
    }
    cout << setw(rlutil::tcols() / 2 - lTexto / 2 - lTexto % 2) << "";
}

// Obtiene la linea mas larga de un string multilinea
// Para poder centrarlo con coutCentered
int getLongestLine(string str) {
    int maxLength = 0, charCount = 0;
    for (int i = 0; i < (int)str.length(); i++) {
        if (str[i] == '\n') {
            if (charCount > maxLength) maxLength = charCount;
            charCount = 0;
        }
        charCount++;
    }
    return maxLength;
}

void printLogo() {
    coutCentered(R"(
  _   __    __        __    __ 
 | | / /__ / /____ __/ /___/ /_
 | |/ / -_) __/ -_)_  __/_  __/
 |___/\__/\__/\__/ /_/   /_/   
                               )");
}
