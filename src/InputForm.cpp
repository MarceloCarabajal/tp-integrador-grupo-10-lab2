#include "InputForm.h"

#include <iostream>

#include "Date.h"
#include "isvalid.h"
#include "rlutil.h"
#include "utils.h"

// TODO: Crear documentacion para las funciones

InputForm::InputForm(bool isEditing, bool showEditingMsg) {
    _editing = isEditing;
    _showEditingMsg = showEditingMsg;
}

void InputForm::setEditMode(bool editMode, bool showEditingMsg) {
    _editing = editMode;
    _showEditingMsg = showEditingMsg;
}

void InputForm::setTimeField(std::string fieldName, Time& timeDestination) {
    _timeFields.push_back(fieldName);
    _timeVars.push_back(&timeDestination);
}

void InputForm::setStrField(std::string fieldName, std::string& strDestination,
                            int maxLength) {
    _strFields.push_back(fieldName);
    _strVars.push_back(&strDestination);
    _strLimit.push_back(maxLength);
}

void InputForm::setIntField(std::string fieldName, int& intDestination,
                            int maxLength) {
    _intFields.push_back(fieldName);
    _intVars.push_back(&intDestination);
    _intLimit.push_back(maxLength);
}

void InputForm::setAlphanumeric(std::string fieldName,
                                std::string& strDestination, int maxLength) {
    _alphanumFields.push_back(fieldName);
    _alphanumVars.push_back(&strDestination);
    _alnLimit.push_back(maxLength);
}

void InputForm::setEmailField(std::string& strDestination, int maxLength,
                              std::string fieldName) {
    _emailVar = &strDestination;
    _emailLimit = maxLength;
    _emailField = fieldName;
}

void InputForm::setPhoneField(std::string& strDestination, int maxLength) {
    _phoneVar = &strDestination;
    _phoneLimit = maxLength;
}

void InputForm::setBoolField(std::string fieldName, bool& boolDestination) {
    _boolFields.push_back(fieldName);
    _boolVars.push_back(&boolDestination);
}

void InputForm::setFloatField(std::string fieldName, float& floatDestination) {
    _floatFields.push_back(fieldName);
    _floatVars.push_back(&floatDestination);
}

void InputForm::setRangeField(std::string fieldName, int& intDestination,
                              int min, int max) {
    _rangeFields.push_back(fieldName);
    _rangeVars.push_back(&intDestination);
    _rangeLimits.push_back(std::vector<int>{min, max});
}

void InputForm::setDateField(std::string fieldName, Date& dateDestination) {
    _dateFields.push_back(fieldName);
    _dateVars.push_back(&dateDestination);
}

void InputForm::setSrvField(std::string fieldName, std::string& strDestination,
                            int maxLength) {
    _srvField = fieldName;
    _srvVar = &strDestination;
    _srvLimit = maxLength;
}

bool InputForm::requestStrFields() {
    for (size_t i = 0; i < _strFields.size(); i++) {
        int attempts = 0;  // lleva la cuenta de los intentos
        bool valid;
        std::string temp = "";
        do {
            if (attempts > 0) {
                if (!askToRetry(strField, _strLimit[i])) return false;
            }
            if (_editing) {
                std::cout << _strFields[i] << " actual: " << *_strVars[i];
            }
            std::cout << (_editing ? "\nNuevo/a " : "Ingrese ") << _strFields[i]
                      << ": ";
            std::getline(std::cin, temp);
            attempts++;                // se suma un intento
            temp = utils::trim(temp);  // quitar espacios al inicio y final
            valid = isvalid::onlyLetters(temp) &&
                    (size_t)_strLimit[i] >= temp.length();
            // si esta en edicion y deja en blanco, es valido
            if (_editing && temp.empty()) valid = true;
        } while (!valid);
        // si esta en modo edicion, y deja vacio, no se reasigna
        if (!temp.empty()) *_strVars[i] = temp;
    }
    return true;
}

bool InputForm::requestIntFields() {
    for (size_t i = 0; i < _intFields.size(); i++) {
        int attempts = 0;  // lleva la cuenta de los intentos
        bool valid;
        std::string tempStr;
        do {
            if (attempts > 0) {
                if (!askToRetry(intField, _intLimit[i])) return false;
            }
            if (_editing) {
                std::cout << _intFields[i] << " actual: " << *_intVars[i];
            }
            std::cout << (_editing ? "\nNuevo/a " : "Ingrese ") << _intFields[i]
                      << ": ";
            std::getline(std::cin, tempStr);
            attempts++;  // se suma un intento
            tempStr = utils::trim(tempStr);
            valid = isvalid::onlyIntegers(tempStr) &&
                    (size_t)_intLimit[i] >= tempStr.length();
            // si esta en edicion y deja en blanco, es valido
            if (_editing && tempStr.empty()) valid = true;
        } while (!valid);
        // si esta en modo edicion, y deja vacio, no se reasigna
        if (!tempStr.empty()) *_intVars[i] = stoi(tempStr);
    }
    return true;
}

bool InputForm::requestPhoneField() {
    int attempts = 0;  // lleva la cuenta de los intentos
    bool valid;
    std::string temp;
    do {
        if (attempts > 0) {
            if (!askToRetry(phoneField, _phoneLimit)) return false;
        }
        if (_editing) std::cout << "Telefono actual: " << *_phoneVar;
        std::cout << (_editing ? "\nNuevo/a " : "Ingrese ") << "Telefono: ";
        std::getline(std::cin, temp);
        attempts++;  // se suma un intento
        temp = utils::trim(temp);
        valid =
            isvalid::onlyIntegers(temp) && (size_t)_phoneLimit >= temp.length();
        // si esta en edicion y deja en blanco, es valido
        if (_editing && temp.empty()) valid = true;
    } while (!valid);
    // si esta en modo edicion, y deja vacio, no se reasigna
    if (!temp.empty()) *_phoneVar = temp;
    return true;
}

bool InputForm::requestEmailField() {
    int attempts = 0;  // lleva la cuenta de los intentos
    bool valid;
    std::string temp;
    do {
        if (attempts > 0) {
            if (!askToRetry(emailField, _emailLimit)) return false;
        }
        if (_editing) std::cout << _emailField << " actual: " << *_emailVar;
        std::cout << (_editing ? "\nNuevo/a " : "Ingrese ") << _emailField
                  << ": ";
        std::getline(std::cin, temp);
        attempts++;  // se suma un intento
        temp = utils::trim(temp);
        valid = isvalid::email(temp) && (size_t)_emailLimit >= temp.length();
        // si esta en edicion y deja en blanco, es valido
        if (_editing && temp.empty()) valid = true;
    } while (!valid);
    // si esta en modo edicion, y deja vacio, no se reasigna
    if (!temp.empty()) *_emailVar = temp;
    return true;
}

bool InputForm::requestAlphanumFields() {
    for (size_t i = 0; i < _alphanumFields.size(); i++) {
        int attempts = 0;  // lleva la cuenta de los intentos
        bool valid;
        std::string temp;
        do {
            if (attempts > 0) {
                if (!askToRetry(alnField, _alnLimit[i])) return false;
            }
            if (_editing) {
                std::cout << _alphanumFields[i]
                          << " actual: " << *_alphanumVars[i];
            }
            std::cout << (_editing ? "\nNuevo/a " : "Ingrese ")
                      << _alphanumFields[i] << ": ";
            std::getline(std::cin, temp);
            attempts++;  // se suma un intento
            temp = utils::trim(temp);
            valid = isvalid::alphanumeric(temp) &&
                    (size_t)_alnLimit[i] >= temp.length();
            // si esta en edicion y deja en blanco, es valido
            if (_editing && temp.empty()) valid = true;
        } while (!valid);
        // si esta en modo edicion, y deja vacio, no se reasigna
        if (!temp.empty()) *_alphanumVars[i] = temp;
    }
    return true;
}

bool InputForm::requestDateFields() {
    for (size_t i = 0; i < _dateFields.size(); i++) {
        int attempts = 0;  // lleva la cuenta de los intentos
        bool valid;
        std::string temp;
        do {
            if (attempts > 0) {
                if (!askToRetry(dateField)) return false;
            }
            if (_editing) {
                std::cout << _dateFields[i]
                          << " actual: " << (*_dateVars[i]).toString();
            }
            std::cout << (_editing ? "\nNuevo/a " : "Ingrese ")
                      << _dateFields[i] << ": ";
            std::getline(std::cin, temp);
            attempts++;  // se suma un intento
            temp = utils::trim(temp);
            valid = isvalid::dateFormat(temp);
            // si esta en edicion y deja en blanco, es valido
            if (_editing && temp.empty()) valid = true;
        } while (!valid);
        // si esta en modo edicion, y deja vacio, no se reasigna
        if (!temp.empty()) {
            *_dateVars[i] =
                Date(stoi(temp.substr(0, 2)), stoi(temp.substr(3, 2)),
                     stoi(temp.substr(6, 4)));
        }
    }
    return true;
}

bool InputForm::requestBoolFields() {
    for (size_t i = 0; i < _boolFields.size(); i++) {
        int attempts = 0;  // lleva la cuenta de los intentos
        bool valid;
        std::string temp = "";
        do {
            if (attempts > 0) {
                if (!askToRetry(boolField)) return false;
            }
            if (_editing)
                std::cout << _boolFields[i]
                          << " actual: " << utils::boolToStr(*_boolVars[i]);
            std::cout << (_editing ? "\nNuevo/a " : "Ingrese ")
                      << _boolFields[i] << ": ";
            std::getline(std::cin, temp);
            attempts++;                // se suma un intento
            temp = utils::trim(temp);  // quitar espacios al inicio y final
            valid = isvalid::boolean(temp);
            // si esta en edicion y deja en blanco, es valido
            if (_editing && temp.empty()) valid = true;
        } while (!valid);
        // si esta en modo edicion, y deja vacio, no se reasigna
        if (!temp.empty()) *_boolVars[i] = utils::strToBool(temp);
    }
    return true;
}

bool InputForm::requestFloatFields() {
    for (size_t i = 0; i < _floatFields.size(); i++) {
        int attempts = 0;  // lleva la cuenta de los intentos
        bool valid;
        std::string temp;
        do {
            if (attempts > 0) {
                if (!askToRetry(floatField)) return false;
            }
            if (_editing) {
                std::cout << _floatFields[i] << " actual: " << *_floatVars[i];
            }
            std::cout << (_editing ? "\nNuevo/a " : "Ingrese ")
                      << _floatFields[i] << ": ";
            std::getline(std::cin, temp);
            attempts++;  // se suma un intento
            temp = utils::trim(temp);
            temp = utils::replaceCommas(temp);  // cambiar comas por puntos
            valid = isvalid::floatType(temp) && isvalid::tryStof(temp);
            // si esta en edicion y deja en blanco, es valido
            if (_editing && temp.empty()) valid = true;
        } while (!valid);
        // si esta en modo edicion, y deja vacio, no se reasigna
        if (!temp.empty()) *_floatVars[i] = stof(temp);
    }
    return true;
}

bool InputForm::requestRangeFields() {
    for (size_t i = 0; i < _rangeFields.size(); i++) {
        int attempts = 0;  // lleva la cuenta de los intentos
        bool valid;
        std::string temp;
        do {
            if (attempts > 0) {
                if (!askToRetry(rangeField, 0, _rangeLimits[i][0],
                                _rangeLimits[i][1]))
                    return false;
            }
            if (_editing) {
                std::cout << _rangeFields[i] << " actual: " << *_rangeVars[i];
            }
            std::cout << (_editing ? "\nNuevo/a " : "Ingrese ")
                      << _rangeFields[i] << ": ";
            std::getline(std::cin, temp);
            attempts++;  // se suma un intento
            temp = utils::trim(temp);
            valid =
                isvalid::range(temp, _rangeLimits[i][0], _rangeLimits[i][1]);
            // si esta en edicion y deja en blanco, es valido
            if (_editing && temp.empty()) valid = true;
        } while (!valid);
        // si esta en modo edicion, y deja vacio, no se reasigna
        if (!temp.empty()) *_rangeVars[i] = stoi(temp);
    }
    return true;
}

bool InputForm::requestTimeFields() {
    for (size_t i = 0; i < _timeFields.size(); i++) {
        int attempts = 0;  // lleva la cuenta de los intentos
        bool valid;
        std::string temp;
        do {
            if (attempts > 0) {
                if (!askToRetry(timeField)) return false;
            }
            if (_editing) {
                std::cout << _timeFields[i]
                          << " actual: " << (*_timeVars[i]).toString();
            }
            std::cout << (_editing ? "\nNuevo/a " : "Ingrese ")
                      << _timeFields[i] << ": ";
            std::getline(std::cin, temp);
            attempts++;  // se suma un intento
            temp = utils::trim(temp);
            valid = isvalid::timeFormat(temp);
            // si esta en edicion y deja en blanco, es valido
            if (_editing && temp.empty()) valid = true;
        } while (!valid);
        // si esta en modo edicion, y deja vacio, no se reasigna
        if (!temp.empty()) {
            int h = stoi(temp.substr(0, 2));
            int min = stoi(temp.substr(3, 2));
            *_timeVars[i] = Time(h, min, 0);
        }
    }
    return true;
}

bool InputForm::requestSrvField() {
    int attempts = 0;  // lleva la cuenta de los intentos
    bool valid;
    std::string temp;
    do {
        if (attempts > 0) {
            if (!askToRetry(srvField)) return false;
        }
        if (_editing) std::cout << _srvField << " actual: " << *_srvVar;
        std::cout << (_editing ? "\nNuevo/a " : "Ingrese ") << _srvField
                  << ": ";
        std::getline(std::cin, temp);
        attempts++;  // se suma un intento
        temp = utils::trim(temp);
        valid = isvalid::srvName(temp) && (size_t)_srvLimit >= temp.length();
        // si esta en edicion y deja en blanco, es valido
        if (_editing && temp.empty()) valid = true;
    } while (!valid);
    // si esta en modo edicion, y deja vacio, no se reasigna
    if (!temp.empty()) *_srvVar = temp;
    return true;
}

bool InputForm::askToRetry(fieldType fType, int maxLimit, int min, int max) {
    std::cout << "El ingreso es invalido, debe tener el formato de: ";
    switch (fType) {
        case strField:
            std::cout << "solo letras, hasta " << maxLimit << " caracteres.\n";
            break;
        case intField:
            std::cout << "solo numeros enteros, hasta " << maxLimit
                      << " digitos. \n";
            break;
        case alnField:
            std::cout << "solo numeros y letras, hasta " << maxLimit
                      << " caracteres.\n";
            break;
        case emailField:
            std::cout << "tuemail@email.com || tu_email@email.com || "
                         "tu.email@email.com hasta "
                      << maxLimit << " caracteres.\n";
            break;
        case phoneField:
            std::cout << "solo numeros, hasta " << maxLimit << " digitos. \n";
            break;
        case boolField:
            std::cout << "solo Si o No.\n";
            break;
        case floatField:
            std::cout
                << "solo números enteros o decimales del tipo 0.00 / 0,00.\n";
            break;
        case dateField:
            std::cout << "solo fechas del tipo dd/mm/aaaa.\n";
            break;
        case rangeField:
            std::cout << "Solo numeros enteros entre " << min << " y " << max
                      << ".\n";
            break;
        case timeField:
            std::cout << "Solo formato 24hs del tipo hs:min. Ej: 17:00.\n";
            break;
        case srvField:
            std::cout << "nombre de servidor SMTP. Hasta " << maxLimit
                      << " caracteres.\n"
                      << "Ejemplo: smtp.gmail.com.\n";
            break;
        default:
            break;
    }
    std::cout << "Presione cualquier tecla para reintentar o ESC para volver "
                 "al menu.\n";
    if (rlutil::getkey() == rlutil::KEY_ESCAPE) {
        rlutil::cls();
        std::cout << "Se ha cancelado la acción actual.\n";
        return false;  // no reintentar
    }
    rlutil::cls();
    return true;
}

bool InputForm::fill() {
    if (_editing && _showEditingMsg) {
        std::cout << "* Dejar los campos en blanco para mantener el valor "
                     "actual.\n\n";
    }
    if (!requestStrFields()) return false;
    if (!requestAlphanumFields()) return false;
    if (!requestIntFields()) return false;
    if (!requestBoolFields()) return false;
    if (!requestFloatFields()) return false;
    if (!requestDateFields()) return false;
    if (!requestRangeFields()) return false;
    if (!requestTimeFields()) return false;

    // Si se asigno la variable, pedir campo
    if (_emailVar != NULL) {
        if (!requestEmailField()) return false;
    }
    if (_phoneVar != NULL) {
        if (!requestPhoneField()) return false;
    }
    if (_srvVar != NULL) {
        if (!requestSrvField()) return false;
    }

    return true;
}

// limpia todos los vectores
void InputForm::clearAll() {
    _strFields.clear();
    _intFields.clear();
    _alphanumFields.clear();
    _boolFields.clear();
    _floatFields.clear();
    _dateFields.clear();

    _strLimit.clear();
    _intLimit.clear();
    _alnLimit.clear();
    _rangeLimits.clear();

    _strVars.clear();
    _intVars.clear();
    _alphanumVars.clear();
    _boolVars.clear();
    _floatVars.clear();
    _dateVars.clear();
    _rangeVars.clear();
    _timeVars.clear();
}
