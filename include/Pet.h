#pragma once
#include <string>

#include "Date.h"

class Pet {
private:
    int _petId, _ownerId;
    char _name[30], _specie[15], _breed[30], _currentDiagnosis[45];
    Date _birthDate;

public:
     Pet();

     Pet(int petId, int ownerId, std::string name, std::string specie,
           std::string breed, std::string currentDiagnosis, Date birthDate);


    void setPetId(int petId);
    void setOwnerId(int ownerId);
    void setName(std::string name);
    void setSpecie(std::string specie);
    void setBreed(std::string breed);
    void setCurrentDiagnosis(std::string currentDiagnosis);
    void setBirthDate(Date birthdate);

    int getPetId();
    int getOwnerId();
    const char* getName();
    const char* getSpecie();
    const char* getBreed();
    const char* getCurrentDiagnosis();
    Date getBirthDate();

    void addAppoinment();
    void loadPet();
    void recordVaccination();

    void toVecString(std::string vStr[7]);
};
