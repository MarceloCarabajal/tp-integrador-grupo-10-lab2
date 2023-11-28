#pragma once
#include <string>


class ProductCategory {

private: 

int _catId;
char _catName[30]; 
bool _status;

public: 

ProductCategory();
ProductCategory(int catid, std::string catname,bool status);


void setCatId(int id );
void setCatName(std::string name );
void setStatus(bool status);

int getCatId();
const char* getCatName();
bool getStatus();

void load();


void toVecString(std::string vStr[2]);

};