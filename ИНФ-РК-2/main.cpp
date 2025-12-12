#include <iostream>
#include <string>

class BankAccount {
protected:
    std::string accountNumber;
    std::string ownerName;
    double balance;

public:
    BankAccount(const std::string& accNum, const std::string& name, double initialBalance = 0.0)
        : accountNumber(accNum), ownerName(name), balance(initialBalance) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited " << amount << ". New balance: " << balance << "\n";
        } else {
            std::cout << "Invalid deposit amount.\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Withdrew " << amount << ". New balance: " << balance << "\n";
        } else {
            std::cout << "Insufficient funds or invalid amount.\n";
        }
    }

    void display() const {
        std::cout << "Account: " << accountNumber
                  << ", Owner: " << ownerName
                  << ", Balance: " << balance << "\n";
    }
};

class SavingsAccount : public BankAccount {
private:
    double interestRate; 

public:
    SavingsAccount(const std::string& accNum, const std::string& name, double initialBalance, double rate)
        : BankAccount(accNum, name, initialBalance), interestRate(rate) {}

    void applyInterest() {
        double interest = balance * (interestRate / 100.0);
        balance += interest;
        std::cout << "Applied interest: " << interest << ". New balance: " << balance << "\n";
    }
};

int main() {
    
    BankAccount acc1("BA001", "Ivan Ivanov", 1000.0);
    acc1.display();
    acc1.deposit(200.0);
    acc1.withdraw(150.0);

    std::cout << "\n";

    
    SavingsAccount acc2("SA001", "Anna Petrova", 2000.0, 5.0); 
    acc2.display();
    acc2.deposit(500.0);
    acc2.applyInterest();

    return 0;
}