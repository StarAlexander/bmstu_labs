#pragma once
#include "User.h"
#include "PaymentStrategy.h"

class Customer : public User {
    std::vector<std::shared_ptr<Order>> orders_;

public:
    using User::User;

    void createOrder(std::shared_ptr<DatabaseConnection<std::string>> db) override;
    void viewOrderStatus(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) override;
    void cancelOrder(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) override;

    void addToOrder(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id, int product_id, int qty);
    void removeFromOrder(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id, int item_id);
    void makePayment(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id, std::unique_ptr<PaymentStrategy> strategy);
    void returnOrder(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id);

    void runMenu(std::shared_ptr<DatabaseConnection<std::string>> db);
};