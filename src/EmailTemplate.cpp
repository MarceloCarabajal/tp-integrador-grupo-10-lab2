#include "EmailTemplate.h"

/**
 * @brief Constructor de la clase EmailTemplate.
 *
 * Este constructor crea una instancia de la clase EmailTemplate y especifica el
 * archivo de plantilla de correo electrónico.
 *
 * @param templateFile El nombre del archivo de plantilla de correo electrónico.
 */
EmailTemplate::EmailTemplate(std::string templateFile) {
    _templateFile = templateFile;
    getHTMlTemplate();
}

/**
 * @brief Establece los datos del correo electrónico.
 *
 * Esta función permite establecer los datos del correo electrónico, como el
 * nombre del destinatario, el título del cuerpo del mensaje y la fecha de
 * vencimiento.
 *
 * @param recipientName El nombre del destinatario.
 * @param bodyTitle El título del cuerpo del mensaje.
 * @param expDate La fecha de vencimiento del mensaje.
 * @return `true` si se establecen los datos con éxito, de lo contrario,
 * `false`.
 */
bool EmailTemplate::setEmailData(std::string recipientName,
                                 std::string bodyTitle, Date expDate) {
    bool success;
    success = replaceParameter("{recipientName}", recipientName);
    success += replaceParameter("{bodyTitle}", bodyTitle);
    success += replaceParameter("{expDate}", expDate.toString());
    return success;
}

/**
 * @brief Obtiene el contenido HTML del correo electrónico.
 *
 * Esta función devuelve el contenido HTML del correo electrónico después de
 * haber establecido los datos del correo.
 *
 * @return El contenido HTML del correo electrónico.
 */
std::string EmailTemplate::getHTML() { return _HTMLData; }

/**
 * @brief Obtiene el contenido de la plantilla HTML.
 *
 * Esta función abre el archivo de plantilla HTML, lee su contenido y lo
 * almacena internamente en la instancia de EmailTemplate.
 */
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

/**
 * @brief Reemplaza un parámetro en el contenido HTML del correo electrónico.
 *
 * Esta función reemplaza un parámetro específico en el contenido HTML del
 * correo electrónico con un nuevo valor.
 *
 * @param paramKey La clave del parámetro que se desea reemplazar.
 * @param newValue El nuevo valor que se utilizará para reemplazar el parámetro.
 * @return `true` si el reemplazo se realiza con éxito, de lo contrario,
 * `false`.
 */
bool EmailTemplate::replaceParameter(std::string paramKey,
                                     std::string newValue) {
    int paramPos = 0;
    paramPos = _HTMLData.find(paramKey);
    if (paramPos == 0) return false;
    _HTMLData.replace(paramPos, paramKey.length(), newValue);
    return true;
}
