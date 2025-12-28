#include "Admin.h"
#include "DatabaseConnection.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <filesystem>

void Admin::viewOrderStatus(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) {
    auto res = db->executeQuery("SELECT * FROM getOrderStatus(" + std::to_string(order_id) + ");");
    if (!res.empty()) {
        std::cout << "Order " << order_id << " status: " << res[0][0] << "\n";
    } else {
        std::cout << "Order not found.\n";
    }
}

void Admin::cancelOrder(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) {
    try {
        db->beginTransaction();
        db->executeNonQuery("CALL updateOrderStatus(" + std::to_string(order_id) + ", 'canceled', " + std::to_string(getId()) + ");");
        db->executeNonQuery("CALL logAudit('order', " + std::to_string(order_id) + ", 'update', " + std::to_string(getId()) + ");");
        db->commitTransaction();
        std::cout << "Order " << order_id << " canceled.\n";
    } catch (...) {
        db->rollbackTransaction();
        std::cerr << "Failed to cancel order.\n";
    }
}

void Admin::addProduct(std::shared_ptr<DatabaseConnection<std::string>> db) {
    std::string name; double price; int qty;
    std::cout << "Name: "; std::cin >> name;
    std::cout << "Price: "; std::cin >> price;
    std::cout << "Stock: "; std::cin >> qty;
    try {
        db->beginTransaction();
        std::string q = "INSERT INTO products (name, price, stock_quantity) VALUES ('" +
                        name + "', " + std::to_string(price) + ", " + std::to_string(qty) + ");";
        db->executeNonQuery(q);
        db->executeNonQuery("CALL logAudit('product', (SELECT currval('products_product_id_seq')), 'insert', " + std::to_string(getId()) + ");");
        db->commitTransaction();
        std::cout << "Product added.\n";
    } catch (...) {
        db->rollbackTransaction();
        std::cerr << "Failed to add product.\n";
    }
}

void Admin::updateProduct(std::shared_ptr<DatabaseConnection<std::string>> db, int prod_id) {
    double new_price; int new_qty;
    std::cout << "New price: "; std::cin >> new_price;
    std::cout << "New stock: "; std::cin >> new_qty;
    try {
        db->beginTransaction();
        std::string q = "UPDATE products SET price = " + std::to_string(new_price) +
                        ", stock_quantity = " + std::to_string(new_qty) +
                        " WHERE product_id = " + std::to_string(prod_id) + ";";
        db->executeNonQuery(q);
        db->executeNonQuery("CALL logAudit('product', " + std::to_string(prod_id) + ", 'update', " + std::to_string(getId()) + ");");
        db->commitTransaction();
        std::cout << "Product updated.\n";
    } catch (...) {
        db->rollbackTransaction();
        std::cerr << "Failed to update product.\n";
    }
}

void Admin::deleteProduct(std::shared_ptr<DatabaseConnection<std::string>> db, int prod_id) {
    try {
        db->beginTransaction();
        db->executeNonQuery("DELETE FROM products WHERE product_id = " + std::to_string(prod_id) + ";");
        db->executeNonQuery("CALL logAudit('product', " + std::to_string(prod_id) + ", 'delete', " + std::to_string(getId()) + ");");
        db->commitTransaction();
        std::cout << "Product deleted.\n";
    } catch (...) {
        db->rollbackTransaction();
        std::cerr << "Failed to delete product.\n";
    }
}

void Admin::viewAllOrders(std::shared_ptr<DatabaseConnection<std::string>> db) {
    auto res = db->executeQuery("SELECT order_id, user_id, status, total_price FROM orders;");
    for (const auto& r : res) {
        std::cout << "ID: " << r[0] << ", User: " << r[1] << ", Status: " << r[2] << ", Total: " << r[3] << "\n";
    }
}

void Admin::updateOrderStatus(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id, const std::string& status) {
    try {
        db->beginTransaction();
        db->executeNonQuery("CALL updateOrderStatus(" + std::to_string(order_id) + ", '" + status + "', " + std::to_string(getId()) + ");");
        db->executeNonQuery("CALL logAudit('order', " + std::to_string(order_id) + ", 'update', " + std::to_string(getId()) + ");");
        db->commitTransaction();
        std::cout << "Status updated.\n";
    } catch (...) {
        db->rollbackTransaction();
        std::cerr << "Failed to update status.\n";
    }
}

void Admin::viewOrderHistory(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) {
    auto res = db->executeQuery("SELECT * FROM getOrderStatusHistory(" + std::to_string(order_id) + ");");
    for (const auto& r : res) {
        std::cout << "From " << r[1] << " → " << r[2] << " at " << r[3] << " by " << r[4] << "\n";
    }
}

void Admin::viewAuditLog(std::shared_ptr<DatabaseConnection<std::string>> db) {
    auto res = db->executeQuery("SELECT * FROM getAuditLogByUser(" + std::to_string(getId()) + ");");
    for (const auto& r : res) {
        std::cout << "Log: " << r[0] << " | " << r[1] << " " << r[2] << " " << r[3] << " at " << r[4] << "\n";
    }
}

void Admin::generateReport(std::shared_ptr<DatabaseConnection<std::string>> db) {
    std::filesystem::create_directories("reports");
    std::string query = R"(
        SELECT
            h.order_id,
            h.old_status,
            h.new_status,
            h.changed_at,
            u.name AS changed_by_user,
            a.entity_type,
            a.operation,
            a.performed_at
        FROM order_status_history h
        JOIN users u ON h.changed_by = u.user_id
        LEFT JOIN audit_log a ON a.entity_id = h.order_id AND a.entity_type = 'order'
        ORDER BY h.changed_at;
    )";

    auto result = db->executeQuery(query);

    std::ofstream file("reports/audit.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Cannot create reports/audit.csv\n";
        return;
    }
    file << "order_id,old_status,new_status,status_changed_at,changed_by_user,audit_entity_type,audit_operation,audit_performed_at\n";
    for (const auto& row : result) {
        for (size_t i = 0; i < row.size(); ++i) {
            if (i > 0) file << ",";
            file << "\"" << row[i] << "\"";
        }
        file << "\n";
    }

    file.close();
    std::cout << "CSV report saved to reports/audit.csv\n";
}

void Admin::runMenu(std::shared_ptr<DatabaseConnection<std::string>> db) {
    int choice;
    while (true) {
        std::cout << "\nAdmin Menu:\n"
                  << "1. Add Product\n2. Update Product\n3. Delete Product\n4. View All Orders\n"
                  << "5. View Order Details\n6. Update Order Status\n7. View Order History\n"
                  << "8. View Audit Log\n9. Generate CSV Report\n10. Exit\n> ";
        std::cin >> choice;
        if (choice == 10) break;

        switch (choice) {
            case 1: addProduct(db); break;
            case 2: {
                int id; std::cout << "Product ID: "; std::cin >> id;
                updateProduct(db, id); break;
            }
            case 3: {
                int id; std::cout << "Product ID: "; std::cin >> id;
                deleteProduct(db, id); break;
            }
            case 4: viewAllOrders(db); break;
            case 5: {
                int id; std::cout << "Order ID: "; std::cin >> id;
                viewOrderStatus(db, id); break;
            }
            case 6: {
                int id; std::string s;
                std::cout << "Order ID: "; std::cin >> id;
                std::cout << "Status (pending/completed/canceled/returned): "; std::cin >> s;
                updateOrderStatus(db, id, s); break;
            }
            case 7: {
                int id; std::cout << "Order ID: "; std::cin >> id;
                viewOrderHistory(db, id); break;
            }
            case 8: viewAuditLog(db); break;
            case 9: generateReport(db); break;
            default: std::cout << "Invalid\n";
        }
    }
}