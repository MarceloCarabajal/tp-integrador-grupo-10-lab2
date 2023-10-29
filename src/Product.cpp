#include "Product.h"


void Product::setProductId(int productId){_productID=productId;   }
void Product::setProductName(std::string productName){_productName=productName;}
void Product::setDescription(std::string description){_description=description;}
void Product::setQuantity(int quantity){_quantity=quantity;}
void Product::setStock(int stock){_stock=stock;}
void Product::setPrice(float price){_price=price;}
void Product::setBrand(std::string brand){_brand=brand;}
void Product::setProductType(std::string productType){_productType=productType;}
void Product::setProductCategory(ProductCategory category){_productCategory=category;}

int Product::getProductId(){return _productID;}
std::string Product::getProductName(){return _productName;  }
 std::string Product::getDescription (){return _description;}
int Product::getQuantity(){return  _quantity;}
int Product::getStock(){return _stock;}
float Product::getPrice(){return _price;}
std::string Product::getBrand(){return _brand; }
std::string Product::getProductType(){return _productType ;}
ProductCategory Product::getProductCategory(){return _productCategory;}

//TODO Completar metodos restantes
void addProduct(){
    
}
void deleteProduct(){
    
}
void updateStock(){
    
}