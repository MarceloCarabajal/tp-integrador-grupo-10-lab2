#ifndef INPUTFORM_INCLUDED
#define INPUTFORM_INCLUDED

#include <iostream>
#include <vector>

class InputForm {
private:
    // enum para los mensajes de error de askToRetry()
    enum fieldType { strField = 0, intField = 1, alnField = 3, emailField = 4 };
    // vector con los nombres de los campos
    std::vector<std::string> _strFields;
    std::vector<std::string> _intFields;
    std::vector<std::string> _alphanumFields;
    // vector de punteros a las variables que deben ser asignadas
    std::vector<std::string *> _strVars;
    std::vector<int *> _intVars;
    std::vector<std::string *> _alphanumVars;
    std::string *_emailVar = NULL;

    bool requestStrFields();
    bool requestEmailField();
    bool requestIntFields();
    // bool requestAlphanumFields(); //TODO: metodo para alfanumericos
    // bool requestIntRangeFields(); //TODO: hacer metodo para rangos
    bool askToRetry(fieldType fType);

public:
    void setStrField(std::string fieldName, std::string &strDestination);
    void setIntField(std::string fieldName, int &intDestination);
    void setAlphanumeric(std::string fieldName, std::string &strDestination);
    void setEmailField(std::string &strDestination);
    bool fill();
};

#endif /* INPUTFORM_INCLUDED */
