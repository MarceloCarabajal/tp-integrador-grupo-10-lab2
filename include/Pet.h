#pragma once
#include<string>

class Pet {

private: 
int _petId, _ownerId;
std::string _name, _specie,_breed, _currentDiagnosis;
Date _birthDate;

public: 
 Pet();
        void setPetId(int petId);
        void setOwnerId (int ownerId)
        void setName(std::string name);
        void setSpecie(std::string specie);
        void setBreed(std::string breed);
        void setCurrentDiagnosis(std::string currentDiagnosis);
        void setBirthDate (Date birthdate);
     

        int getPetId ();
        int getOwnerId ();
        std::string getName();
        std::string getSpecie();
        std::string getBreed();
        std::string getCurrentDiagnosis();
        Date getBirthDate ();

        void addAppoinment ();
        void loadPet ();
        void recordVaccination ();

};


