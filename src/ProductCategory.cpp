#include <iostream>
#include <cstring>
#include "ProductCategory.h"

using namespace std;

void ProductCategory::setCatId(int id ){_catId=id;}
void ProductCategory::setCatName(std::string name ){strcpy(_catName,name.c_str());   }

int ProductCategory::getCatId(){return _catId;}
const char * ProductCategory::getCatName(){return _catName;}


void ProductCategory::toVecString(std::string vStr[2]) {
    vStr[0] = std::to_string(_catId);
    vStr[1] = _catName;
 
}
/*
void ProductCategory::load(){
int catId;
std:: string catName;

cout <<"Ingrese ID de categoria:";
cin>>catId;
setCatId (catId);

cout<<"Ingrese nombre de la categoria:";
cin>>catName;
setCatName(catName);

}*/