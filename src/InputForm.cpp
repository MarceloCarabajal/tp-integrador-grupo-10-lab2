#include "InputForm.h"

#include <iostream>

#include "isvalid.h"
#include "rlutil.h"

// TODO: Crear documentacion para las funciones

InputForm::InputForm(bool isEditing) { _editing = isEditing; }

void InputForm::setEditMode(bool editMode) { _editing = editMode; }

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

void InputForm::setEmailField(std::string& strDestination, int maxLength) {
    _emailVar = &strDestination;
    _emailLimit = maxLength;
}

void InputForm::setPhoneField(std::string& strDestination, int maxLength) {
    _phoneVar = &strDestination;
    _phoneLimit = maxLength;
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
            if (_editing)
                std::cout << _strFields[i] << " actual: " << *_strVars[i];
            std::cout << (_editing ? "\nNuevo/a " : "Ingrese ") << _strFields[i]
                      << ": ";
            std::getline(std::cin, temp);
            attempts++;         // se suma un intento
            temp = trim(temp);  // quitar espacios al inicio y final
            valid = isvalid::onlyLetters(temp) &&
                    (size_t)_strLimit[i] >= temp.length();
            // si esta en edicion y deja en blanco, es valido
            if (_editing && temp.length() == 0) valid = true;
        } while (!valid);
        // si esta en modo edicion, y deja vacio, no se reasigna
        if (temp.length() > 0) *_strVars[i] = temp;
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
            if (_editing)
                std::cout << _intFields[i] << " actual: " << *_intVars[i];
            std::cout << (_editing ? "\nNuevo/a " : "Ingrese ") << _intFields[i]
                      << ": ";
            std::getline(std::cin, tempStr);
            attempts++;  // se suma un intento
            tempStr = trim(tempStr);
            valid = isvalid::onlyIntegers(tempStr) &&
                    (size_t)_intLimit[i] >= tempStr.length();
            // si esta en edicion y deja en blanco, es valido
            if (_editing && tempStr.length() == 0) valid = true;
        } while (!valid);
        // si esta en modo edicion, y deja vacio, no se reasigna
        if (tempStr.length() > 0) *_intVars[i] = stoi(tempStr);
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
        temp = trim(temp);
        valid =
            isvalid::onlyIntegers(temp) && (size_t)_phoneLimit >= temp.length();
        // si esta en edicion y deja en blanco, es valido
        if (_editing && temp.length() == 0) valid = true;
    } while (!valid);
    // si esta en modo edicion, y deja vacio, no se reasigna
    if (temp.length() > 0) *_phoneVar = temp;
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
        if (_editing) std::cout << "Email actual: " << *_emailVar;
        std::cout << (_editing ? "\nNuevo/a " : "Ingrese ") << "Email: ";
        std::getline(std::cin, temp);
        attempts++;  // se suma un intento
        temp = trim(temp);
        valid = isvalid::email(temp) && (size_t)_emailLimit >= temp.length();
        // si esta en edicion y deja en blanco, es valido
        if (_editing && temp.length() == 0) valid = true;
    } while (!valid);
    // si esta en modo edicion, y deja vacio, no se reasigna
    if (temp.length() > 0) *_emailVar = temp;
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
            if (_editing)
                std::cout << _alphanumFields[i]
                          << " actual: " << *_alphanumVars[i];
            std::cout << (_editing ? "\nNuevo/a " : "Ingrese ")
                      << _alphanumFields[i] << ": ";
            std::getline(std::cin, temp);
            attempts++;  // se suma un intento
            temp = trim(temp);
            valid = isvalid::alphanumeric(temp) &&
                    (size_t)_alnLimit[i] >= temp.length();
            // si esta en edicion y deja en blanco, es valido
            if (_editing && temp.length() == 0) valid = true;
        } while (!valid);
        // si esta en modo edicion, y deja vacio, no se reasigna
        if (temp.length() > 0) *_alphanumVars[i] = temp;
    }
    return true;
}

bool InputForm::askToRetry(fieldType fType, int maxLimit) {
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
        case phoneField:
            std::cout << "solo numeros, hasta " << maxLimit << " digitos. \n";
        default:
            break;
    }
    std::cout << "Presione cualquier tecla para reintentar o ESC para volver "
                 "al menu.\n";
    if (rlutil::getkey() == rlutil::KEY_ESCAPE) {
        rlutil::cls();
        return false;  // no reintentar
    }
    rlutil::cls();
    return true;
}

bool InputForm::fill() {
    if (_editing) {
        std::cout << "*Dejar los campos en blanco para mantener el valor "
                     "actual.\n";
    }
    if (!requestStrFields()) return false;
    if (!requestAlphanumFields()) return false;
    if (!requestIntFields()) return false;
    // Si se asigno la variable, pedir campo
    if (_emailVar != NULL) {
        if (!requestEmailField()) return false;
    }
    if (_phoneVar != NULL) {
        if (!requestPhoneField()) return false;
    }
    return true;
}

// limpia todos los vectores
void InputForm::clearAll() {
    _strFields.clear();
    _intFields.clear();
    _alphanumFields.clear();
    _strLimit.clear();
    _intLimit.clear();
    _alnLimit.clear();
    _strVars.clear();
    _intVars.clear();
    _alphanumVars.clear();
}

std::string InputForm::trim(std::string str) {
    size_t lSpaces = 0, rSpaces = 0, strEnd = 0;
    std::string temp;
    // contar espacios desde la izquierda
    for (size_t i = 0; i < str.length(); i++) {
        // si es una letra, salir del for
        if (isvalid::alphanumeric(str[i])) break;
        if (str[i] == char(32)) lSpaces++;
    }
    // contar espacios desde la derecha
    // se convierte length() a (int) porque i no puede ser de tipo size_t debido
    // a que se usa decremento y al llegar a 0 y decrementar, un tipo size_t no
    // puede ser negativo y vuelve a su valor maximo, generando un loop infinito
    for (int i = (int)str.length(); i >= 0; i--) {
        // si es una letra, salir del for
        if (isvalid::alphanumeric(str[i - 1])) break;
        if (str[i - 1] == char(32)) rSpaces++;
    }
    // Calcular tamanio total sin espacios L y R
    strEnd = str.length() - rSpaces;
    // copiar str desde lSpaces hasta strEnd
    for (size_t i = lSpaces; i < strEnd; i++) {
        temp += str[i];
    }
    // si no se detectaron espacios, devolver str
    if (lSpaces + rSpaces == 0) return str;
    // sino devolver str trimeado
    return temp;
}
