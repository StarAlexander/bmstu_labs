#pragma once


class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual bool pay(double amount) = 0;
};

class CreditCardPayment : public PaymentStrategy {
public:
    bool pay(double amount) override;
};

class EWalletPayment : public PaymentStrategy {
public:
    bool pay(double amount) override;
};

class SBPPayment : public PaymentStrategy {
public:
    bool pay(double amount) override;
};