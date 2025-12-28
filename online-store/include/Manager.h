#pragma once
#include "User.h"
#include <memory>
#include <vector>

class Manager : public User {

public:
    using User::User;

    void createOrder(std::shared_ptr<DatabaseConnection<std::string>> db) override {}
    void viewOrderStatus(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) override;
    void cancelOrder(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) override;

    void approveOrder(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id);
    void updateStock(std::shared_ptr<DatabaseConnection<std::string>> db, int product_id, int new_quantity);
    void viewPendingOrders(std::shared_ptr<DatabaseConnection<std::string>> db);
    void updateOrderStatus(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id, const std::string& new_status);
    void viewOrderDetails(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id);
    void viewApprovedOrderHistory(std::shared_ptr<DatabaseConnection<std::string>> db);
    void viewOrderStatusHistory(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id);
    void viewAuditLogForOrders(std::shared_ptr<DatabaseConnection<std::string>> db);

    void runMenu(std::shared_ptr<DatabaseConnection<std::string>> db);
};