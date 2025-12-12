#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <memory>
#include "database.h"
#include "logger.h"

class Product {

protected:
    int id;
    std::string name;
    double price;
    static Logger logger;
    static Database db;


public:
    Product(const std::string& n, double p): name(n), price(p) {}

    virtual ~Product() = default;

    virtual void save() {
        pqxx::work txn(db.getConnection());

        auto res = txn.exec(
            "INSERT INTO products (name,price) VALUES (" +
            txn.quote(name) + ", " + txn.quote(price) + ") RETURNING id"
        );

        id = res[0][0].as<int>();

        txn.commit();
        logger.log("Added product: " + name);
    }


    virtual std::string getType() const {return "Product"; }

    int getId() const {return id; }

    std::string getName() const {return name; }

    double getPrice() const {return price; }



};


Logger Product::logger;
Database Product::db;


class DigitalProduct : public Product {
    std::string downloadLink;

public:
    DigitalProduct(const std::string& n, double p, const std::string& link) : 
        Product(n,p), downloadLink(link) {}

    std::string getType() const override {return "DigitalProduct"; }

    void save() override {
        Product::save();

        logger.log("Digital product saved: " + name + " | Link: " + downloadLink);
    }
};



class PhysicalProduct : public Product {
    double weight;

public:
    PhysicalProduct(const std::string& n, double p, double w) :
        Product(n,p), weight(w) {}

    
    std::string getType() const override {return "PhysicalProduct";}

    void save() override {
        Product::save();
        logger.log("Physical product saved: " + name + " | Weight: " + std::to_string(weight) + " kg");
    }
};



#endif