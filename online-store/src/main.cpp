#include <iostream>
#include <memory>
#include "DatabaseConnection.h"
#include "Admin.h"
#include "Manager.h"
#include "Customer.h"

std::unique_ptr<User> loadUser(std::shared_ptr<DatabaseConnection<std::string>> db, int user_id) {
    auto res = db->executeQuery("SELECT name, email, role, loyalty_level FROM users WHERE user_id = " + std::to_string(user_id) + ";");
    if (res.empty()) return nullptr;
    auto& r = res[0];
    if (r[2] == "admin") {
        return std::make_unique<Admin>(user_id, r[0], r[1], r[2], std::stoi(r[3]));
    } else if (r[2] == "manager") {
        return std::make_unique<Manager>(user_id, r[0], r[1], r[2], std::stoi(r[3]));
    } else if (r[2] == "customer") {
        return std::make_unique<Customer>(user_id, r[0], r[1], r[2], std::stoi(r[3]));
    }
    return nullptr;
}

int main() {
    std::string conn_str = "dbname=postgres password=Sashalife20050709 user=postgres";
    auto db = std::make_shared<DatabaseConnection<std::string>>(conn_str);

    int choice, uid;
    while (true) {
        std::cout << "\n1. Admin\n2. Manager\n3. Customer\n4. Exit\n> ";
        std::cin >> choice;
        if (choice == 4) break;
        std::cout << "Enter User ID: "; std::cin >> uid;

        auto user = loadUser(db, uid);
        if (!user) {
            std::cout << "User not found.\n";
            continue;
        }

        if (user->getRole() == "admin") {
            static_cast<Admin*>(user.get())->runMenu(db);
        } else if (user->getRole() == "manager") {
            static_cast<Manager*>(user.get())->runMenu(db);
        } else if (user->getRole() == "customer") {
            static_cast<Customer*>(user.get())->runMenu(db);
        }
    }
    return 0;
}