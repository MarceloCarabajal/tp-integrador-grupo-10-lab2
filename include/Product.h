#pragma once
#include <string>
#include "ProductCategory.h"

class Product{
private:
    int _productID, _quantity, _stock;
    float _price;
    char _productName[30], _description[45], _brand[15];
    ProductCategory _productCategory;

public:
Product();
Product (int productid, int quantity, int stock,float price, std::string productname,
 std::string description, std::string brand, ProductCategory productcategory);


 
    void setProductId(int productId);
    void setProductName(std::string productName);
    void setDescription(std::string description);
    void setQuantity(int quantity);
    void setStock(int stock);
    void setPrice(float price);
    void setBrand(std::string brand);
    void setProductCategory(ProductCategory category);

    int getProductId();
    const char * getProductName();
    const char * getDescription ();
    int getQuantity();
    int getStock();
    float getPrice();
    const char * getBrand();
    ProductCategory getProductCategory();

    void addProduct();
    void deleteProduct();
    void updateStock();


        void toVecString(std::string vStr[8]);
};