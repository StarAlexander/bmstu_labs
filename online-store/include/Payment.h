#pragma once
#include <memory>
#include "PaymentStrategy.h"

class Payment {
private:
    double amount_;
    std::unique_ptr<PaymentStrategy> strategy_;

public:
    Payment(double amount, std::unique_ptr<PaymentStrategy> strategy)
        : amount_(amount), strategy_(std::move(strategy)) {}

    bool execute() {
        if (strategy_) {
            return strategy_->pay(amount_);
        }
        return false;
    }

    double getAmount() const { return amount_; }
};