#pragma once
#include <vector>
#include <memory>
#include "OrderItem.h"
#include "Payment.h"

class Order {
    int order_id_;
    int user_id_;
    std::string status_;
    double total_price_;
    std::unique_ptr<Payment> payment_;

public:
    std::vector<std::unique_ptr<OrderItem>> items_;
    Order(int id, int uid, std::string status, double total)
        : order_id_(id), user_id_(uid), status_(std::move(status)), total_price_(total) {}

    void addItem(std::unique_ptr<OrderItem> item) { items_.push_back(std::move(item)); }
    void setPayment(std::unique_ptr<Payment> p) { payment_ = std::move(p); }
    int getId() const { return order_id_; }
    double getTotalPrice() const { return total_price_; }
    const std::string& getStatus() const { return status_; }
};