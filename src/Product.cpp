#include <cstring>
#include "Product.h"


void Product::setProductId(int productId){_productID=productId;   }
void Product::setProductName(std::string productName){strcpy(_productName,productName.c_str());}
void Product::setDescription(std::string description){strcpy(_description,description.c_str());}
void Product::setQuantity(int quantity){_quantity=quantity;}
void Product::setStock(int stock){_stock=stock;}
void Product::setPrice(float price){_price=price;}
void Product::setBrand(std::string brand){strcpy(_brand,brand.c_str());}
void Product::setProductType(std::string productType){strcpy(_productType,productType.c_str());}
void Product::setProductCategory(ProductCategory category){_productCategory=category;}

int Product::getProductId(){return _productID;}
const char * Product::getProductName(){return _productName;  }
const char * Product::getDescription (){return _description;}
int Product::getQuantity(){return  _quantity;}
int Product::getStock(){return _stock;}
float Product::getPrice(){return _price;}
const char * Product::getBrand(){return _brand; }
const char * Product::getProductType(){return _productType ;}
ProductCategory Product::getProductCategory(){return _productCategory;}

//TODO Completar metodos restantes
void addProduct(){
    
}
void deleteProduct(){
    
}
void updateStock(){
    
}