#include <cstring>
#include "Product.h"


void Product::setProductId(int productId){_productID=productId;   }
void Product::setProductName(const char * productName){strcpy(_productName,productName);}
void Product::setDescription(const char * description){strcpy(_description,description);}
void Product::setQuantity(int quantity){_quantity=quantity;}
void Product::setStock(int stock){_stock=stock;}
void Product::setPrice(float price){_price=price;}
void Product::setBrand(const char * brand){strcpy(_brand,brand);}
void Product::setProductType(const char * productType){strcpy(_productType,productType);}
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