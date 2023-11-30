#ifndef EMAILTEMPLATE_INCLUDED
#define EMAILTEMPLATE_INCLUDED

#include <iostream>

#include "Date.h"

/**
 * @class EmailTemplate
 * @brief Clase que representa una plantilla de correo electrónico.
 *
 * Esta clase se utiliza para cargar una plantilla de correo electrónico desde
 * un archivo, reemplazar los parámetros de la plantilla con valores específicos
 * y obtener el contenido HTML resultante.
 */
class EmailTemplate {
private:
    std::string _templateFile;  /**< Ruta del archivo de plantilla */
    std::string _HTMLData = ""; /**< Contenido HTML de la plantilla */

    /**
     * @brief Carga la plantilla HTML desde el archivo.
     */
    void getHTMlTemplate();

    /**
     * @brief Reemplaza un parámetro de la plantilla con un nuevo valor.
     * @param paramKey La clave del parámetro a reemplazar.
     * @param newValue El nuevo valor del parámetro.
     * @return true si el reemplazo fue exitoso, false en caso contrario.
     */
    bool replaceParameter(std::string paramKey, std::string newValue);

public:
    /**
     * @brief Constructor de la clase EmailTemplate.
     * @param templateFile Ruta del archivo de plantilla.
     */
    EmailTemplate(std::string templateFile);

    /**
     * @brief Establece los datos del correo electrónico.
     * @param recipientName El nombre del destinatario.
     * @param bodyTitle El título del cuerpo del correo.
     * @param expDate La fecha de expiración.
     * @param veteName El nombre de la veterinaria.
     * @return true si los datos se establecieron correctamente, false en caso
     * contrario.
     */
    bool setEmailData(std::string recipientName, std::string bodyTitle,
                      Date expDate, std::string veteName);

    /**
     * @brief Obtiene el contenido HTML de la plantilla.
     * @return El contenido HTML de la plantilla.
     */
    std::string getHTML();
};

#endif /* EMAILTEMPLATE_INCLUDED */
