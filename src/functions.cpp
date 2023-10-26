#include "functions.h"

#include <iomanip>
#include <iostream>

#include "quickmail.h"
#include "rlutil.h"

using namespace std;

// Credenciales SMTP
#define SMTP_HOST "smtp-relay.brevo.com"
#define SMTP_PORT 587
#define SMTP_USR "joaqfm@gmail.com"
#define SMTP_PWD "GPX8Z3Wh964TLAtw"

bool sendEmail(string to, string subject, string body) {
    quickmail_initialize();
    quickmail mailObj =
        quickmail_create("facujmasino@gmail.com", subject.c_str());

    quickmail_set_body(mailObj, body.c_str());
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
