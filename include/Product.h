#pragma once

#include<string>
#include "ProductCategory.h"

class Product{
private:
    int _productID, _quantity, _stock;
    float _price;
    std::string _productName, _description, _brand, _productType;
    ProductCategory _productCategory;
public:
    void setProductId(int productId);
    void setProductName(std::string productName);
    void setDescription(std::string description);
    void setQuantity(int quantity);
    void setStock(int stock);
    void setPrice(float price);
    void setBrand(std::string brand);
    void setProductType(std::string productType);
    void setProductCategory(ProductCategory category);

    int getProductId();
    std::string getProductName();
    int getQuantity();
    int getStock();
    float getPrice();
    std::string getBrand();
    std::string getProductType();
    ProductCategory getProductCategory();

    void addProduct();
    void deleteProduct();
    void updateStock();
};