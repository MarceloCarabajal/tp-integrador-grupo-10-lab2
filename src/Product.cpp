#include "Product.h"
#include <cstring>

Product::Product(){
    _productID=-1;
     _quantity=0;
    _stock=-1;
    _price=0.00;
    strcpy(_productName, " ");
    strcpy(_description, " ");
    strcpy(_brand, " ");
   _productCategory= ProductCategory();
    _status = false;

}
Product::Product (int productid, int quantity, int stock,float price, std::string productname,
 std::string description, std::string brand,  ProductCategory productcategory,bool status){

    _productID=productid;
    _quantity=quantity;
    _stock=stock;
    _price=price;
   strcpy(_productName,productname.c_str());
   strcpy( _description, description.c_str());
   strcpy( _brand, brand.c_str());
   _productCategory=productcategory;
     _status = status;

 }

void Product::setProductId(int productId) { _productID = productId; }
void Product::setProductName(std::string productName) {
    strcpy(_productName, productName.c_str());
}
void Product::setDescription(std::string description) {
    strcpy(_description, description.c_str());
}
void Product::setQuantity(int quantity) { _quantity = quantity; }
void Product::setStock(int stock) { _stock = stock; }
void Product::setPrice(float price) { _price = price; }
void Product::setBrand(std::string brand) { strcpy(_brand, brand.c_str()); }
void Product::setProductCategory(ProductCategory category) {
    _productCategory = category;
}
void Product::setStatus(bool status) { _status = status; }

int Product::getProductId() { return _productID; }
const char* Product::getProductName() { return _productName; }
const char* Product::getDescription() { return _description; }
int Product::getQuantity() { return _quantity; }
int Product::getStock() { return _stock; }
float Product::getPrice() { return _price; }
const char* Product::getBrand() { return _brand; }
ProductCategory Product::getProductCategory() { return _productCategory; }
bool Product::getStatus() { return _status; }

// TODO Completar metodos restantes
void addProduct() {}
void deleteProduct() {}
void updateStock() {}

void Product::toVecString(std::string vStr[9]) {
    vStr[0] = std::to_string(_productID);
    vStr[1] = _productName;
    vStr[2] = _description;
    vStr[3] = _brand;
    vStr[4] = std::to_string(_quantity);
    vStr[5] = std::to_string(_price);
    vStr[6] = std::to_string(_stock);
    vStr[7] = _productCategory.getCatName();
}
