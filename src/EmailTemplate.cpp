#include "EmailTemplate.h"

EmailTemplate::EmailTemplate(std::string templateFile) {
    _templateFile = templateFile;
    getHTMlTemplate();
}

bool EmailTemplate::setEmailData(std::string recipientName,
                                 std::string bodyTitle, Date expDate) {
    bool success;
    success = replaceParameter("{recipientName}", recipientName);
    success += replaceParameter("{bodyTitle}", bodyTitle);
    success += replaceParameter("{expDate}", expDate.toString());
    return success;
}

std::string EmailTemplate::getHTML() { return _HTMLData; }

void EmailTemplate::getHTMlTemplate() {
    std::string strHTML;
    FILE *pHTML = fopen(_templateFile.c_str(), "rb");
    if (pHTML == NULL) return;
    // Obtener el tamanio
    fseek(pHTML, 0, SEEK_END);
    int fSize = ftell(pHTML);
    // Adaptar tamanio string
    strHTML.resize(fSize);
    // Volver al inicio
    fseek(pHTML, 0, SEEK_SET);
    // leer
    int sizeRead = fread(&strHTML[0], sizeof(char), fSize, pHTML);
    fclose(pHTML);
    if (sizeRead == fSize) _HTMLData = strHTML;
}

bool EmailTemplate::replaceParameter(std::string paramKey,
                                     std::string newValue) {
    int paramPos = 0;
    paramPos = _HTMLData.find(paramKey);
    if (paramPos == 0) return false;
    _HTMLData.replace(paramPos, paramKey.length(), newValue);
    return true;
}
