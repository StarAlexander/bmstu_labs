#include "Manager.h"
#include "DatabaseConnection.h"
#include <iostream>
#include <algorithm>

void Manager::viewOrderStatus(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) {
    auto res = db->executeQuery("SELECT status FROM orders WHERE order_id = " + std::to_string(order_id) + ";");
    if (!res.empty()) {
        std::cout << "Status: " << res[0][0] << "\n";
    }
}

void Manager::cancelOrder(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) {
    std::cout << "Managers cannot cancel orders.\n";
}

void Manager::approveOrder(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) {
    try {
        db->beginTransaction();
        db->executeNonQuery("CALL updateOrderStatus(" + std::to_string(order_id) + ", 'completed', " + std::to_string(getId()) + ");");
        db->executeNonQuery("CALL logAudit('order', " + std::to_string(order_id) + ", 'update', " + std::to_string(getId()) + ");");
        db->commitTransaction();
        std::cout << "Order approved.\n";
    } catch (...) {
        db->rollbackTransaction();
        std::cerr << "Failed to approve order.\n";
    }
}

void Manager::updateStock(std::shared_ptr<DatabaseConnection<std::string>> db, int product_id, int new_quantity) {
    try {
        db->beginTransaction();
        std::string q = "UPDATE products SET stock_quantity = " + std::to_string(new_quantity) +
                        " WHERE product_id = " + std::to_string(product_id) + ";";
        db->executeNonQuery(q);
        db->executeNonQuery("CALL logAudit('product', " + std::to_string(product_id) + ", 'update', " + std::to_string(getId()) + ");");
        db->commitTransaction();
        std::cout << "Stock updated.\n";
    } catch (...) {
        db->rollbackTransaction();
        std::cerr << "Failed to update stock.\n";
    }
}

void Manager::viewPendingOrders(std::shared_ptr<DatabaseConnection<std::string>> db) {
    auto res = db->executeQuery("SELECT order_id, user_id, total_price FROM orders WHERE status = 'pending';");
    for (const auto& r : res) {
        std::cout << "Order " << r[0] << " by user " << r[1] << ", total: " << r[2] << "\n";
    }
}

void Manager::updateOrderStatus(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id, const std::string& new_status) {
    if (new_status != "completed" && new_status != "canceled") {
        std::cout << "Managers can only set 'completed' or 'canceled'.\n";
        return;
    }
    try {
        db->beginTransaction();
        db->executeNonQuery("CALL updateOrderStatus(" + std::to_string(order_id) + ", '" + new_status + "', " + std::to_string(getId()) + ");");
        db->executeNonQuery("CALL logAudit('order', " + std::to_string(order_id) + ", 'update', " + std::to_string(getId()) + ");");
        db->commitTransaction();
        std::cout << "Status updated.\n";
    } catch (...) {
        db->rollbackTransaction();
        std::cerr << "Failed to update status.\n";
    }
}

void Manager::viewOrderDetails(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) {
    auto res = db->executeQuery("SELECT order_id, user_id, status, total_price FROM orders WHERE order_id = " + std::to_string(order_id) + ";");
    if (!res.empty()) {
        auto& r = res[0];
        std::cout << "Order " << r[0] << " | User: " << r[1] << " | Status: " << r[2] << " | Total: " << r[3] << "\n";
    }
}

void Manager::viewApprovedOrderHistory(std::shared_ptr<DatabaseConnection<std::string>> db) {
    auto res = db->executeQuery("SELECT order_id FROM order_status_history WHERE changed_by = " + std::to_string(getId()) + ";");
    for (const auto& r : res) {
        std::cout << "Order " << r[0] << " handled by you.\n";
    }
}

void Manager::viewOrderStatusHistory(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) {
    auto res = db->executeQuery("SELECT * FROM getOrderStatusHistory(" + std::to_string(order_id) + ");");
    for (const auto& r : res) {
        std::cout << "From " << r[1] << " → " << r[2] << " at " << r[3] << " by " << r[4] << "\n";
    }
}

void Manager::viewAuditLogForOrders(std::shared_ptr<DatabaseConnection<std::string>> db) {
    auto res = db->executeQuery("SELECT * FROM audit_log WHERE entity_type = 'order' AND performed_by = " + std::to_string(getId()) + ";");
    for (const auto& r : res) {
        std::cout << "Audit: " << r[1] << " " << r[2] << " " << r[3] << " at " << r[5] << "\n";
    }
}

void Manager::runMenu(std::shared_ptr<DatabaseConnection<std::string>> db) {
    int choice;
    while (true) {
        std::cout << "\nManager Menu:\n"
                  << "1. View Pending Orders\n2. Approve Order\n3. Update Stock\n"
                  << "4. View Order Details\n5. Update Order Status\n6. View My Orders\n"
                  << "7. View Order History\n8. View My Audit Log\n9. Exit\n> ";
        std::cin >> choice;
        if (choice == 9) break;

        switch (choice) {
            case 1: viewPendingOrders(db); break;
            case 2: {
                int id; std::cout << "Order ID: "; std::cin >> id;
                approveOrder(db, id); break;
            }
            case 3: {
                int pid, qty;
                std::cout << "Product ID: "; std::cin >> pid;
                std::cout << "New stock: "; std::cin >> qty;
                updateStock(db, pid, qty); break;
            }
            case 4: {
                int id; std::cout << "Order ID: "; std::cin >> id;
                viewOrderDetails(db, id); break;
            }
            case 5: {
                int id; std::string s;
                std::cout << "Order ID: "; std::cin >> id;
                std::cout << "Status (completed/canceled): "; std::cin >> s;
                updateOrderStatus(db, id, s); break;
            }
            case 6: viewApprovedOrderHistory(db); break;
            case 7: {
                int id; std::cout << "Order ID: "; std::cin >> id;
                viewOrderStatusHistory(db, id); break;
            }
            case 8: viewAuditLogForOrders(db); break;
            default: std::cout << "Invalid\n";
        }
    }
}