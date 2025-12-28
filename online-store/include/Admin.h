#pragma once
#include "User.h"

class Admin : public User {
public:
    using User::User;
    void createOrder(std::shared_ptr<DatabaseConnection<std::string>> db) override {}
    void viewOrderStatus(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) override;
    void cancelOrder(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) override;

    void addProduct(std::shared_ptr<DatabaseConnection<std::string>> db);
    void updateProduct(std::shared_ptr<DatabaseConnection<std::string>> db, int prod_id);
    void deleteProduct(std::shared_ptr<DatabaseConnection<std::string>> db, int prod_id);
    void viewAllOrders(std::shared_ptr<DatabaseConnection<std::string>> db);
    void updateOrderStatus(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id, const std::string& status);
    void viewOrderHistory(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id);
    void viewAuditLog(std::shared_ptr<DatabaseConnection<std::string>> db);
    void generateReport(std::shared_ptr<DatabaseConnection<std::string>> db);

    void runMenu(std::shared_ptr<DatabaseConnection<std::string>> db);
};