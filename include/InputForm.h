#ifndef INPUTFORM_INCLUDED
#define INPUTFORM_INCLUDED

#include <iostream>
#include <vector>

#include "Date.h"
#include "TimeCls.h"

class InputForm {
private:
    // enum para los mensajes de error de askToRetry()
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

    bool requestStrFields();
    bool requestEmailField();
    bool requestIntFields();
    bool requestPhoneField();
    bool requestAlphanumFields();
    bool requestBoolFields();
    bool requestFloatFields();
    bool requestDateFields();
    bool requestRangeFields();
    bool requestTimeFields();
    bool requestSrvField();
    bool askToRetry(fieldType fType, int maxLimit = 0, int min = 0,
                    int max = 0);

public:
    InputForm(bool isEditing = false, bool showEditingMsg = false);

    void setStrField(std::string fieldName, std::string &strDestination,
                     int maxLength);
    void setIntField(std::string fieldName, int &intDestination, int maxLength);
    void setAlphanumeric(std::string fieldName, std::string &strDestination,
                         int maxLength);
    void setEmailField(std::string &strDestination, int maxLength,
                       std::string fieldName = "Email");
    void setPhoneField(std::string &strDestination, int maxLength);
    void setBoolField(std::string fieldName, bool &boolDestination);
    void setFloatField(std::string fieldName, float &floatDestination);
    void setDateField(std::string fieldName, Date &dateDestination);
    void setRangeField(std::string fieldName, int &intDestination, int min,
                       int max);
    void setTimeField(std::string fieldName, Time &timeDestination);
    void setSrvField(std::string fieldName, std::string &strDestination,
                     int maxLength);

    void setEditMode(bool editMode, bool showEditingMsg = true);

    bool fill();
    void clearAll();
};

#endif /* INPUTFORM_INCLUDED */
