#include "ProductCategory.h"
#include <cstring>

#include <iostream>
using namespace std;

ProductCategory::ProductCategory(){
_catId= -1;
strcpy (_catName, " ");
_status = false;
}

ProductCategory::ProductCategory(int catid, std::string catname, bool status){
_catId=catid;
strcpy(_catName, catname.c_str());
_status = status;


}



void ProductCategory::setCatId(int id ){_catId=id;}
void ProductCategory::setCatName(std::string name ){strcpy(_catName,name.c_str());   }
void ProductCategory::setStatus(bool status) { _status = status; }



int ProductCategory::getCatId(){return _catId;}
const char * ProductCategory::getCatName(){return _catName;}
bool ProductCategory::getStatus() { return _status; }


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