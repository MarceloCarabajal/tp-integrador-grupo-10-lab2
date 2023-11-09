#include <iostream>
#include <cstring>
#include "ProductCategory.h"

using namespace std;

void ProductCategory::setCatId(int id ){_catId=id;}
void ProductCategory::setCatName(const char* name ){strcpy(_catName,name);   }

int ProductCategory::getCatId(){return _catId;}
const char * ProductCategory::getCatName(){return _catName;}
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