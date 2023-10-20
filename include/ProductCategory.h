#pragma once
#include <string>


class ProductCategory {

private: 

int _catId;
std:: string _catName; 


public: 

void setCatId(int id );
void setCatName(std:: string name );

int getCatId();
std::string getCatName();

void load();

};