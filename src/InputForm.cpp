#include "InputForm.h"

#include <iostream>

#include "isvalid.h"
#include "rlutil.h"

// TODO: Crear documentacion para las funciones
// TODO: Agregar posibilidad de limite de caracteres en los campos
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
        do {
            if (attempts > 0) {
                if (!askToRetry(strField, _strLimit[i])) return false;
            }
            std::cout << "Ingrese " << _strFields[i] << ": ";
            std::getline(std::cin, *_strVars[i]);
            attempts++;  // se suma un intento
            valid = isvalid::onlyLetters(*_strVars[i]) &&
                    (size_t)_strLimit[i] >= (*_strVars[i]).length();
        } while (!valid);
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
            std::cout << "Ingrese " << _intFields[i] << ": ";
            std::getline(std::cin, tempStr);
            attempts++;  // se suma un intento
            valid = isvalid::onlyIntegers(tempStr) &&
                    (size_t)_intLimit[i] >= tempStr.length();
        } while (!valid);
        *_intVars[i] = stoi(tempStr);
    }
    return true;
}

bool InputForm::requestPhoneField() {
    int attempts = 0;  // lleva la cuenta de los intentos
    bool valid;
    do {
        if (attempts > 0) {
            if (!askToRetry(phoneField, _phoneLimit)) return false;
        }
        std::cout << "Ingrese Telefono: ";
        std::getline(std::cin, *_phoneVar);
        attempts++;  // se suma un intento
        valid = isvalid::onlyIntegers(*_phoneVar) &&
                (size_t)_phoneLimit >= (*_phoneVar).length();
    } while (!valid);
    return true;
}

bool InputForm::requestEmailField() {
    int attempts = 0;  // lleva la cuenta de los intentos
    bool valid;
    do {
        if (attempts > 0) {
            if (!askToRetry(emailField, _emailLimit)) return false;
        }
        std::cout << "Ingrese Email: ";
        std::getline(std::cin, *_emailVar);
        attempts++;  // se suma un intento
        valid = isvalid::email(*_emailVar) &&
                (size_t)_emailLimit >= (*_emailVar).length();
    } while (!valid);
    return true;
}

bool InputForm::requestAlphanumFields() {
    for (size_t i = 0; i < _alphanumFields.size(); i++) {
        int attempts = 0;  // lleva la cuenta de los intentos
        bool valid;
        do {
            if (attempts > 0) {
                if (!askToRetry(alnField, _alnLimit[i])) return false;
            }
            std::cout << "Ingrese " << _alphanumFields[i] << ": ";
            std::getline(std::cin, *_alphanumVars[i]);
            attempts++;  // se suma un intento
            valid = isvalid::alphanumeric(*_alphanumVars[i]) &&
                    (size_t)_alnLimit[i] >= (*_alphanumVars[i]).length();
        } while (!valid);
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
