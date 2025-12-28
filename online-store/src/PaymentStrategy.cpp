#include "PaymentStrategy.h"
#include <iostream>

bool CreditCardPayment::pay(double amount) {
    std::cout << "[PAY] Paid " << amount << " via Credit Card\n";
    return true;
}

bool EWalletPayment::pay(double amount) {
    std::cout << "[PAY] Paid " << amount << " via E-Wallet\n";
    return true;
}

bool SBPPayment::pay(double amount) {
    std::cout << "[PAY] Paid " << amount << " via SBP\n";
    return true;
}