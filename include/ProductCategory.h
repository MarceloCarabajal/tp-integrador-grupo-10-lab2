#pragma once
#include <string>


class ProductCategory {

private: 

int _catId;
char _catName[30]; 


public: 

void setCatId(int id );
void setCatName(const char* name );

int getCatId();
const char* getCatName();

void load();

};