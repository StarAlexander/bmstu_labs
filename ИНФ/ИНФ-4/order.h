#ifndef ORDER_H
#define ORDER_H


#include <string>
#include "database.h"
#include "logger.h"

class Order {

protected:
    int orderId;
    std::string orderDate;
    static Logger logger;
    static Database db;


public:
    Order(const std::string& date = "") : orderDate(date.empty() ? getCurrentDate() : date) {}


    void save() {
        pqxx::work txn(db.getConnection());
        auto res = txn.exec(
            "INSERT INTO orders(order_date) VALUES (" + txn.quote(orderDate) + ") RETURNING order_id" 
        );

        orderId = res[0][0].as<int>();

        txn.commit();

        logger.log("Created order with ID: " + std::to_string(orderId) + " on " + orderDate);
    }

    int getId() const {return orderId; }

    std::string getDate() const {return orderDate; }

private:

    std::string getCurrentDate() {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        char buf[11];
        std::strftime(buf,sizeof(buf),"%Y-%m-%d",&tm);
        return std::string(buf);
    }
};


Logger Order::logger;
Database Order::db;


#endif