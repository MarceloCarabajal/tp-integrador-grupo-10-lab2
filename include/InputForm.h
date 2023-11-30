#ifndef INPUTFORM_INCLUDED
#define INPUTFORM_INCLUDED

#include <iostream>
#include <vector>

#include "Date.h"
#include "TimeCls.h"

/**
 * @class InputForm
 * @brief Clase que representa un formulario de entrada.
 *
 */
class InputForm {
private:
    /**
     * @brief Enumeración que representa los diferentes tipos de campos,
     * utilizado or askToRetry() para informar un error.
     *
     * Los tipos de campos disponibles son:
     * - strField: Campo de texto.
     * - intField: Campo numérico entero.
     * - alnField: Campo alfanumérico.
     * - emailField: Campo de correo electrónico.
     * - phoneField: Campo de número de teléfono.
     * - boolField: Campo booleano.
     * - floatField: Campo numérico de punto flotante.
     * - dateField: Campo de fecha.
     * - rangeField: Campo de rango.
     * - timeField: Campo de tiempo.
     * - srvField: Campo de servidor.
     */
    enum fieldType {
        strField = 0,
        intField = 1,
        alnField = 3,
        emailField = 4,
        phoneField = 5,
        boolField = 6,
        floatField = 7,
        dateField = 8,
        rangeField = 9,
        timeField = 10,
        srvField = 11  // server field
    };
    // vector con los nombres de los campos
    std::vector<std::string> _strFields;
    std::vector<std::string> _intFields;
    std::vector<std::string> _alphanumFields;
    std::vector<std::string> _boolFields;
    std::vector<std::string> _floatFields;
    std::vector<std::string> _dateFields;
    std::vector<std::string> _rangeFields;
    std::vector<std::string> _timeFields;
    std::string _emailField;  // nombre del campo email
    std::string _srvField;    // nombre del campo server

    // vector con los limites de digitos/caracteres para los campos
    std::vector<int> _strLimit;
    std::vector<int> _intLimit;
    std::vector<int> _alnLimit;
    std::vector<std::vector<int>> _rangeLimits;  // [0] = min, [1] = max
    int _emailLimit;  // solo se pide 1 email, no hace falta un vector
    int _phoneLimit;  // solo se pide 1 telefono
    int _srvLimit;    // solo se pide 1 server

    // vector de punteros a las variables que deben ser asignadas
    std::vector<std::string *> _strVars;
    std::vector<int *> _intVars;
    std::vector<std::string *> _alphanumVars;
    std::vector<bool *> _boolVars;
    std::vector<float *> _floatVars;
    std::vector<Date *> _dateVars;
    std::vector<int *> _rangeVars;
    std::vector<Time *> _timeVars;
    std::string *_emailVar = NULL;
    std::string *_phoneVar = NULL;
    std::string *_srvVar = NULL;

    bool _editing, _showEditingMsg;

    /**
     * @brief Solicita campos de tipo cadena de caracteres al usuario.
     *
     * Esta función se utiliza para solicitar al usuario que ingrese valores
     * para campos de tipo cadena de caracteres.
     *
     * @return true si se solicitaron los campos correctamente, false en caso
     * contrario.
     */
    bool requestStrFields();

    /**
     * @brief Solicita el campo de correo electrónico.
     *
     * @return true si se llena correctamente, false de lo contrario.
     */
    bool requestEmailField();

    /**
     * @brief Solicita los campos de tipo entero.
     *
     * Esta función se encarga de solicitar al usuario los campos de tipo entero
     * necesarios para completar un formulario.
     *
     * @return true si se pudieron solicitar los campos correctamente, false en
     * caso contrario.
     */
    bool requestIntFields();

    /**
     * @brief Solicita el campo de teléfono.
     *
     * @return true si se completa el campo correctamente, false de lo
     * contrario.
     */
    bool requestPhoneField();

    /**
     * @brief Solicita campos alfanuméricos.
     *
     * Esta función se utiliza para solicitar campos alfanuméricos al usuario.
     *
     * @return true si se solicitaron los campos correctamente, false en caso
     * contrario.
     */
    bool requestAlphanumFields();

    /**
     * @brief Solicita campos booleanos al usuario.
     *
     * Esta función solicita al usuario que ingrese valores booleanos para los
     * campos especificados.
     *
     * @return true si se ingresaron correctamente los valores booleanos, false
     * en caso contrario.
     */
    bool requestBoolFields();

    /**
     * @brief Solicita los campos de tipo float.
     *
     * @return true si se completaron los campos correctamente, false en caso
     * contrario.
     */
    bool requestFloatFields();

    /**
     * @brief Solicita los campos de fecha.
     *
     * Esta función se utiliza para solicitar los campos de fecha al usuario.
     *
     * @return true si se completaron los campos de fecha correctamente, false
     * en caso contrario.
     */
    bool requestDateFields();

    /**
     * @brief Solicita los campos de rango.
     *
     * Esta función se utiliza para solicitar los campos de rango al usuario.
     *
     * @return true si se ingresaron los campos de rango correctamente, false en
     * caso contrario.
     */
    bool requestRangeFields();

    /**
     * @brief Solicita los campos de hora.
     *
     * Esta función se utiliza para solicitar los campos de hora al usuario.
     *
     * @return true si se ingresaron los campos correctamente, false en caso
     * contrario.
     */
    bool requestTimeFields();

    /**
     * @brief Solicita el campo del servidor.
     *
     * @return true si se solicita correctamente el campo del servidor.
     * @return false si ocurre un error al solicitar el campo del servidor.
     */
    bool requestSrvField();

    /**
     * @brief Pregunta al usuario si desea volver a intentar.
     *
     * @param fType El tipo de campo que se está validando.
     * @param maxLimit El límite máximo permitido para el campo.
     * @param min El valor mínimo permitido para el campo.
     * @param max El valor máximo permitido para el campo.
     * @return true si el usuario desea volver a intentar, false de lo
     * contrario.
     */
    bool askToRetry(fieldType fType, int maxLimit = 0, int min = 0,
                    int max = 0);

public:
    /**
     * @brief Constructor de la clase InputForm.
     *
     * @param isEditing Indica si se está editando un formulario existente.
     * @param showEditingMsg Indica si se debe mostrar un mensaje de edición.
     */
    InputForm(bool isEditing = false, bool showEditingMsg = false);

    /**
     * @brief Establece el valor de un campo de tipo cadena.
     *
     * Esta función permite establecer el valor de un campo de tipo cadena en un
     * objeto InputForm.
     *
     * @param fieldName El nombre del campo.
     * @param strDestination La referencia a la variable donde se almacenará el
     * valor del campo.
     * @param maxLength La longitud máxima permitida para el valor del campo.
     */
    void setStrField(std::string fieldName, std::string &strDestination,
                     int maxLength);
    /**
     * @brief Establece un campo de tipo entero en el formulario.
     *
     * Esta función permite establecer un campo de tipo entero en el formulario,
     * asignando el valor ingresado por el usuario a la variable de destino.
     *
     * @param fieldName El nombre del campo.
     * @param intDestination La variable de destino donde se almacenará el valor
     * entero ingresado.
     * @param maxLength La longitud máxima permitida para el campo.
     */
    void setIntField(std::string fieldName, int &intDestination, int maxLength);
    /**
     * @brief Establece un campo alfanumérico en el formulario de entrada.
     *
     * Esta función se utiliza para establecer un campo alfanumérico en el
     * formulario de entrada. El campo se identifica por su nombre y el valor se
     * guarda en la variable de destino proporcionada. Además, se puede
     * especificar la longitud máxima permitida para el campo.
     *
     * @param fieldName El nombre del campo alfanumérico.
     * @param strDestination La variable de destino donde se guardará el valor
     * del campo.
     * @param maxLength La longitud máxima permitida para el campo.
     */
    void setAlphanumeric(std::string fieldName, std::string &strDestination,
                         int maxLength);
    /**
     * @brief Establece el campo de correo electrónico.
     *
     * Esta función se utiliza para establecer el valor del campo de correo
     * electrónico en un formulario de entrada.
     *
     * @param strDestination Referencia a una cadena de caracteres donde se
     * almacenará el valor del campo de correo electrónico.
     * @param maxLength La longitud máxima permitida para el campo de correo
     * electrónico.
     * @param fieldName (opcional) El nombre del campo de correo electrónico.
     * Por defecto es "Email".
     */
    void setEmailField(std::string &strDestination, int maxLength,
                       std::string fieldName = "Email");
    /**
     * @brief Establece el campo de teléfono.
     *
     * Esta función se utiliza para establecer el campo de teléfono en un
     * formulario de entrada.
     *
     * @param strDestination Referencia a una cadena de caracteres donde se
     * almacenará el valor del campo de teléfono.
     * @param maxLength La longitud máxima permitida para el campo de teléfono.
     */
    void setPhoneField(std::string &strDestination, int maxLength);
    /**
     * @brief Establece un campo booleano en el formulario de entrada.
     *
     * Esta función permite establecer un campo booleano especificado por su
     * nombre. El valor se asigna a través de una referencia al parámetro
     * boolDestination.
     *
     * @param fieldName El nombre del campo booleano.
     * @param boolDestination La referencia a la variable booleana donde se
     * asignará el valor.
     */
    void setBoolField(std::string fieldName, bool &boolDestination);
    /**
     * @brief Establece el valor de un campo de tipo float en el formulario de
     * entrada.
     *
     * @param fieldName El nombre del campo.
     * @param floatDestination La variable donde se almacenará el valor del
     * campo.
     */
    void setFloatField(std::string fieldName, float &floatDestination);
    /**
     * @brief Establece el campo de fecha especificado en el formulario de
     * entrada.
     *
     * @param fieldName El nombre del campo de fecha.
     * @param dateDestination La referencia al objeto Date donde se almacenará
     * la fecha.
     */
    void setDateField(std::string fieldName, Date &dateDestination);
    /**
     * @brief Establece un campo de rango para un nombre de campo dado.
     *
     * Esta función permite establecer un campo de rango para un nombre de campo
     * específico. El campo de rango se utiliza para limitar el valor de un
     * entero dentro de un rango mínimo y máximo.
     *
     * @param fieldName El nombre del campo.
     * @param intDestination La variable entera de destino donde se almacenará
     * el valor.
     * @param min El valor mínimo permitido para el campo de rango.
     * @param max El valor máximo permitido para el campo de rango.
     */
    void setRangeField(std::string fieldName, int &intDestination, int min,
                       int max);
    /**
     * @brief Establece el campo de hora especificado en el formulario de
     * entrada.
     *
     * @param fieldName El nombre del campo de hora.
     * @param timeDestination La referencia al objeto Time donde se almacenará
     * la hora.
     */
    void setTimeField(std::string fieldName, Time &timeDestination);
    /**
     * @brief Establece el campo del servidor SMTP con el nombre especificado.
     *
     * Esta función asigna el valor de un campo del servidor a una cadena de
     * destino.
     *
     * @param fieldName El nombre del campo del servidor.
     * @param strDestination La cadena de destino donde se asignará el valor del
     * campo del servidor.
     * @param maxLength La longitud máxima permitida para la cadena de destino.
     */
    void setSrvField(std::string fieldName, std::string &strDestination,
                     int maxLength);

    /**
     * @brief Establece el modo de edición de la forma de entrada.
     *
     * @param editMode Indica si se debe activar el modo de edición.
     * @param showEditingMsg Indica si se debe mostrar un mensaje de edición.
     */
    void setEditMode(bool editMode, bool showEditingMsg = true);

    /**
     * @brief Rellena los campos del formulario.
     *
     * @return true si se pudo llenar el formulario correctamente, false en caso
     * contrario.
     */
    bool fill();
    /**
     * @brief Limpia todos los campos del formulario.
     */
    void clearAll();
};

#endif /* INPUTFORM_INCLUDED */
