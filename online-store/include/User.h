#pragma once
#include <string>
#include <vector>
#include <memory>
#include "DatabaseConnection.h"
#include "Order.h"

class User {
protected:
    int user_id_;
    std::string name_, email_, role_;
    int loyalty_level_;

public:
    User(int id, std::string name, std::string email, std::string role, int level = 0)
        : user_id_(id), name_(std::move(name)), email_(std::move(email)), role_(std::move(role)), loyalty_level_(level) {}

    virtual ~User() = default;

    virtual void createOrder(std::shared_ptr<DatabaseConnection<std::string>> db) = 0;
    virtual void viewOrderStatus(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) = 0;
    virtual void cancelOrder(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) = 0;

    int getId() const { return user_id_; }
    const std::string& getRole() const { return role_; }
};