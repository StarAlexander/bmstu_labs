#include <iostream>
#include <string>
#include <vector>
#include "product.h"
#include "order.h"
#include "order_item.h"
#include "logger.h"
#include <pqxx/pqxx>


void addProductMenu();
void addOrder();
void addItemToOrder();
void viewAllProducts();
void viewAllOrders();
void runAnalytics();


Database globalDb;
Logger globalLogger;

int main() {
    try {
        int choice;

        do {
            std::cout << "\n=== Sales Management System ===\n";
            std::cout << "1. Add product\n";
            std::cout << "2. Add order\n";
            std::cout << "3. Add item to order\n";
            std::cout << "4. View all products\n";
            std::cout << "5. View all orders\n";
            std::cout << "6. Run analytics\n";
            std::cout << "0. Exit\n";
            std::cout << "Choose an option: ";
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
                case 1: addProductMenu(); break;
                case 2: addOrder(); break;
                case 3: addItemToOrder(); break;
                case 4: viewAllProducts(); break;
                case 5: viewAllOrders(); break;
                case 6: runAnalytics(); break;
                case 0: std::cout << "Exit...\n"; break;
                default: std::cout << "Wrong option.\n";
            }
        } while (choice != 0);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        globalLogger.log("Critical error: " + std::string(e.what()));
    }
    return 0;
}


void addProductMenu() {
    std::cout << "1. Physical product\n 2. Digital product\n Choice: ";

    int type; std::cin >> type;

    std::cin.ignore();

    std::string name; double price;
    std::cout << "Name: "; std::getline(std::cin,name);
    std::cout << "Price: "; std::cin >> price;

    if (type == 1) {
        double weight;
        std::cout << "Weight (kg): "; std::cin >> weight;
        PhysicalProduct p(name,price,weight);
        p.save();
    } else if (type == 2) {
        std::string link;
        std::cout << "Download link: "; std::getline(std::cin,link);
        DigitalProduct p(name,price,link);
        p.save();
    }
}

void addOrder() {
    std::string date;

    std::cout << "Order date (YYYY-MM-DD, leave empty for current date): ";
    std::getline(std::cin,date);
    Order order(date);
    order.save();
}

void addItemToOrder() {
    int orderId, productId, qty;

    double price;
    std::cout << "order ID: "; std::cin >> orderId;
    std::cout << "product ID: "; std::cin >> productId;
    std::cout << "quantity: "; std::cin >> qty;
    std::cout << "unit price: "; std::cin >> price;
    OrderItem item(orderId,productId,qty,price);

    item.save();
}


void viewAllProducts() {
    pqxx::work txn(globalDb.getConnection());

    auto res = txn.exec("SELECT id, name, price FROM products");

    std::cout << "\n--- All products ---\n";
    for (const auto& row : res) {
        std::cout << "ID: " << row["id"].as<int>()
        << " | Name: " << row["name"].c_str()
        << " | Price: " << row["price"].as<double>() << "\n";
    }

    globalLogger.log("Viewed all products.");
}


void viewAllOrders() {
    pqxx::work txn (globalDb.getConnection());

    auto res = txn.exec("SELECT order_id, order_date FROM orders");

    std::cout << "\n--- All orders ---\n";

    for (const auto& row: res) {
        std::cout << "ID: " << row["order_id"].as<int>()
        << " | date: " << row["order_date"].c_str() << "\n";

    }
    globalLogger.log("Viewed all orders");
}


void runAnalytics() {
    pqxx::work txn (globalDb.getConnection());
    globalLogger.log("Running analytics...");

    std::cout << "\n=== Analytics ===\n";

    std::cout << "\n1. Total revenue by products: \n";
    auto res1 = txn.exec(R"(
        SELECT p.name, SUM(oi.total_price) AS revenue
        FROM products p
        JOIN order_items oi ON p.id = oi.product_id
        GROUP BY p.id,p.name
        ORDER BY revenue DESC
        )");

    for (const auto& row: res1) {
        std::cout << row["name"].c_str() << ": " << row["revenue"].as<double>() << "\n";
    }

    std::cout << "\n2. Top 3 best selling products.";
    auto res2 = txn.exec(R"(
        SELECT p.name, SUm(oi.quantity) AS total
        FROM products p
        JOIN order_items oi ON p.id = oi.product_id
        GROUP BY p.id, p.name
        ORDER BY total DESC
        LIMIT 3
        )");

    for (const auto& row: res2) {
        std::cout << row["name"].c_str() << ": " << row["total"].as<int>() << " units.\n";
    }

    std::cout << "\n3. Average order price: \n";

    auto res3 = txn.exec(R"(
        SELECT AVG(total_per_order) AS avg_order
        FROM (
            SELECT SUM(oi.total_price) AS total_per_order
            FROM orders o
            JOIN order_items oi ON o.order_id = oi.order_id
            GROUP BY o.order_id
        ) as order_totals
        )");
    
    if (!res3.empty() && !res3[0]["avg_order"].is_null()) {
        std::cout << res3[0]["avg_order"].as<double>() << "\n";
    } else {
        std::cout << "No data.\n";
    }


    std::cout << "\n4. Number of orders per product:\n";

    auto res4 = txn.exec(R"(
        SELECT p.name, COUNT(DISTINCT oi.order_id) AS num_orders
        FROM products p
        JOIN order_items oi ON p.id = oi.product_id
        GROUP BY p.id, p.name
        ORDER BY num_orders DESC
        
        )");
    
    for (const auto& row: res4) {
        std::cout << row["name"].c_str() << ": " << row["num_orders"].as<int>() << " order(s)\n";
    }
}