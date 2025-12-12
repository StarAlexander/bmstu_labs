#ifndef ORDERITEM_H
#define ORDERITEM_H

#include "database.h"
#include "logger.h"

class OrderItem {

    int orderItemId;
    int orderId;
    int productId;
    int quantity;
    double totalPrice;
    static Logger logger;
    static Database db;


public:
    OrderItem(int oid, int pid, int qty, double price) 
    : orderId(oid), productId(pid), quantity(qty), totalPrice(price) {}
    
    
    void save() {
        pqxx::work txn(db.getConnection());

        txn.exec(
            "INSERT INTO order_items (order_id,product_id,quantity,total_price) VALUES (" +
            txn.quote(orderId) + ", " + txn.quote(productId) + ", " + txn.quote(quantity) + 
            ", " + txn.quote(totalPrice) + ")"
        );

        txn.commit();

        logger.log("Added order item: order=" + std::to_string(orderId) + 
                    ", product=" + std::to_string(productId) + 
                    ", quantity=" + std::to_string(quantity));

        
    }

};

Logger OrderItem::logger;
Database OrderItem::db;


#endif