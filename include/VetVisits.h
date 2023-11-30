#pragma once
#include <string>

#include "Date.h"

class VetVisits {
private:
    int _visitId, _vetId, _clientId, _petId, _saleId;
    Date _date;
    char _reason[30], _diagnosis[240];
    bool _status;

public:
    VetVisits();
    VetVisits(int visitid, int vetid, int clientid, int petid, int saleid,
              Date date, std::string reason, std::string diagnosis,
              bool status);
    void setVisitId(int id);
    void setVetId(int id);
    void setClientId(int id);
    void setPetId(int id);
    void setSaleId(int id);
    void setDate(Date dat);
    void setReason(std::string reason);
    void setDiagnosis(std::string diagnosis);
    void setStatus(bool status);

    int getVisitId();
    Date getDate();
    const char* getReason();
    const char* getDiagnosis();
    int getVetId();
    int getClientId();
    int getPetId();
    int getSaleId();
    bool getStatus();

    bool isValidRelation();

    void toVecString(std::string vStr[8]);
};