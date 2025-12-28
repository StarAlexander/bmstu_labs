#pragma once
#include <string>

class Product {
private:
    int product_id_;
    std::string name_;
    double price_;
    int stock_quantity_;

public:
    Product(int id, std::string name, double price, int stock) : product_id_(id), name_(name),price_(price),stock_quantity_(stock) {};
    ~Product() = default;

    int getId() const { return product_id_; }
    const std::string& getName() const { return name_; }
    double getPrice() const { return price_; }
    int getStock() const { return stock_quantity_; }
    void setPrice(double p) { price_ = p; }
    void setStock(int qty) { stock_quantity_ = qty; }
};