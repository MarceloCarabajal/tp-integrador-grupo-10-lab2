#include <iostream>
#include "ProductCategory.h"

using namespace std;

void ProductCategory::setCatId(int id ){_catId=id;}
void ProductCategory::setCatName(std:: string name ){_catName=name;   }

int ProductCategory::getCatId(){return _catId;}
std::string ProductCategory::getCatName(){return _catName;}

void ProductCategory::load(){
int catId;
std:: string catName;

cout <<"Ingrese ID de categoria:";
cin>>catId;
setCatId (catId);

cout<<"Ingrese nombre de la categoria:";
cin>>catName;
setCatName(catName);

}