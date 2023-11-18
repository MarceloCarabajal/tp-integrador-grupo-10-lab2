#ifndef INPUTFORM_INCLUDED
#define INPUTFORM_INCLUDED

#include <iostream>
#include <vector>

class InputForm {
private:
    // enum para los mensajes de error de askToRetry()
    enum fieldType {
        strField = 0,
        intField = 1,
        alnField = 3,
        emailField = 4,
        phoneField = 5,
        boolField =6
    };
    // vector con los nombres de los campos
    std::vector<std::string> _strFields;
    std::vector<std::string> _intFields;
    std::vector<std::string> _alphanumFields;
    std::vector<std::string> _boolFields; 

    // vector con los limites de digitos/caracteres para los campos
    std::vector<int> _strLimit;
    std::vector<int> _intLimit;
    std::vector<int> _alnLimit; 
    int _emailLimit;  // solo se pide 1 email, no hace falta un vector
    int _phoneLimit;  // solo se pide 1 telefono

    // vector de punteros a las variables que deben ser asignadas
    std::vector<std::string *> _strVars;
    std::vector<int *> _intVars;
    std::vector<std::string *> _alphanumVars;
    std::vector <bool *>_boolVars;
    std::string *_emailVar = NULL;
    std::string *_phoneVar = NULL;
    

    bool _editing;

    bool requestStrFields();
    bool requestEmailField();
    bool requestIntFields();
    bool requestPhoneField();
    bool requestAlphanumFields();
    bool requestBoolFields();
    // bool requestIntRangeFields(); //TODO: hacer metodo para rangos
    bool askToRetry(fieldType fType, int maxLimit);

    // utils
    std::string trim(std::string str);

public:
    InputForm(bool isEditing = false);

    void setStrField(std::string fieldName, std::string &strDestination,
                     int maxLength);
    void setIntField(std::string fieldName, int &intDestination, int maxLength);
    void setAlphanumeric(std::string fieldName, std::string &strDestination,
                         int maxLength);
    void setEmailField(std::string &strDestination, int maxLength);
    void setPhoneField(std::string &strDestination, int maxLength);
    void setBoolField (std::string &strDestination);

    void setEditMode(bool editMode);

    
    bool fill();
    void clearAll();
};

#endif /* INPUTFORM_INCLUDED */
