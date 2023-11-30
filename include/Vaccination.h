#pragma once
#include <string>

#include "Date.h"

class Vaccination {
private:
    int _aplicationId, _petId;
    Date _dateAplication, _dateRevaccination;
    char _nameVaccine[15];
    bool _notified;

    bool _status;

public:
    Vaccination();

    Vaccination(int petId, int aplicationId, std::string nameVaccine,
                Date dateAplication, Date dateRevaccination, bool notified,
                bool status);

    void setAplicationId(int apli);
    void setPetId(int Idp);
    void setDateAplication(Date Apli);
    void setDateRevaccination(Date Revacci);
    void setNameVaccine(std::string name);
    void setNotified(bool noti);
    void setStatus(bool status);

    int getAplicationId();
    int getPetId();
    Date getDateAplication();
    Date getDateRevaccination();
    const char* getNameVaccine();
    bool getNotified();
    bool getStatus();

    void toVecString(std::string vStr[6]);
};
