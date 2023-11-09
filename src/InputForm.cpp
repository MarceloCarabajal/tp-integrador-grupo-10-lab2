#include "InputForm.h"

#include <iostream>

#include "isvalid.h"
#include "rlutil.h"

// TODO: Crear documentacion para las funciones

void InputForm::setStrField(std::string fieldName,
                            std::string& strDestination) {
    _strFields.push_back(fieldName);
    _strVars.push_back(&strDestination);
}

void InputForm::setIntField(std::string fieldName, int& intDestination) {
    _intFields.push_back(fieldName);
    _intVars.push_back(&intDestination);
}

void InputForm::setAlphanumeric(std::string fieldName,
                                std::string& strDestination) {
    _alphanumFields.push_back(fieldName);
    _alphanumVars.push_back(&strDestination);
}

void InputForm::setEmailField(std::string& strDestination) {
    _emailVar = &strDestination;
}

bool InputForm::requestStrFields() {
    for (size_t i = 0; i < _strFields.size(); i++) {
        int attempts = 0;  // lleva la cuenta de los intentos
        do {
            if (attempts > 0) {
                if (!askToRetry(strField)) return false;
            }
            std::cout << "Ingrese " << _strFields[i] << ": ";
            std::getline(std::cin, *_strVars[i]);
            attempts++;  // se suma un intento
        } while (!isvalid::onlyLetters(*_strVars[i]));
    }
    return true;
}

bool InputForm::requestIntFields() {
    for (size_t i = 0; i < _intFields.size(); i++) {
        int attempts = 0;  // lleva la cuenta de los intentos
        std::string tempStr;
        do {
            if (attempts > 0) {
                if (!askToRetry(intField)) return false;
            }
            std::cout << "Ingrese " << _intFields[i] << ": ";
            std::getline(std::cin, tempStr);
            attempts++;  // se suma un intento
        } while (!isvalid::onlyIntegers(tempStr));
        *_intVars[i] = stoi(tempStr);
    }
    return true;
}

bool InputForm::requestEmailField() {
    int attempts = 0;  // lleva la cuenta de los intentos
    do {
        if (attempts > 0) {
            if (!askToRetry(emailField)) return false;
        }
        std::cout << "Ingrese Email: ";
        std::getline(std::cin, *_emailVar);
        attempts++;  // se suma un intento
    } while (!isvalid::email(*_emailVar));
    return true;
}

bool InputForm::requestAlphanumFields() {
    int attempts = 0;  // lleva la cuenta de los intentos
    for (size_t i = 0; i < _alphanumFields.size(); i++) {
        do {
            if (attempts > 0) {
                if (!askToRetry(alnField)) return false;
            }
            std::cout << "Ingrese " << _alphanumFields[i] << ": ";
            std::getline(std::cin, *_alphanumVars[i]);
            attempts++;  // se suma un intento
        } while (!isvalid::alphanumeric(*_alphanumVars[i]));
    }
    return true;
}

bool InputForm::askToRetry(fieldType fType) {
    std::cout << "El ingreso es invalido, debe tener el formato de: ";
    switch (fType) {
        case strField:
            std::cout << "solo letras.\n";
            break;
        case intField:
            std::cout << "solo numeros enteros.\n";
            break;
        case alnField:
            std::cout << "solo numeros y letras.\n";
            break;
        case emailField:
            std::cout << "tuemail@email.com || tu_email@email.com || "
                         "tu.email@email.com\n";
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
    if (_emailVar != NULL) {
        if (!requestEmailField()) return false;
    }
    return true;
}
