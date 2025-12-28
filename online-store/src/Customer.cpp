#include "Customer.h"
#include "DatabaseConnection.h"
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>

void Customer::createOrder(std::shared_ptr<DatabaseConnection<std::string>> db) {
    
    try {
        db->beginTransaction();
        std::string call = "CALL createOrder(" + std::to_string(getId()) + ", '[]');";
        db->executeNonQuery(call);

        
        auto res = db->executeQuery("SELECT currval('orders_order_id_seq');");
        if (!res.empty()) {
            int order_id = std::stoi(res[0][0]);
            auto order = std::make_shared<Order>(order_id, getId(), "pending", 0.0);
            orders_.push_back(order);
            std::cout << "Empty order created with ID: " << order_id << "\n";
        }
        db->commitTransaction();
    } catch (const std::exception& e) {
        db->rollbackTransaction();
        std::cerr << "Failed to create order: " << e.what() << "\n";
        
        db->executeNonQuery(
            "INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, performed_at) "
            "VALUES ('order', -1, 'error', " + std::to_string(getId()) + ", NOW());"
        );
    }
}

void Customer::viewOrderStatus(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) {
    
    auto res = db->executeQuery(
        "SELECT o.status FROM orders o WHERE o.order_id = " + std::to_string(order_id) +
        " AND o.user_id = " + std::to_string(getId()) + ";"
    );
    if (!res.empty()) {
        std::cout << "Order " << order_id << " status: " << res[0][0] << "\n";
    } else {
        std::cout << "Order not found or access denied.\n";
    }
}

void Customer::cancelOrder(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) {
    try {
        db->beginTransaction();
        db->executeNonQuery("CALL updateOrderStatus(" + std::to_string(order_id) + ", 'canceled', " + std::to_string(getId()) + ");");
        db->executeNonQuery("CALL logAudit('order', " + std::to_string(order_id) + ", 'update', " + std::to_string(getId()) + ");");
        db->commitTransaction();
        std::cout << "Order " << order_id << " canceled.\n";
    } catch (const std::exception& e) {
        db->rollbackTransaction();
        std::cerr << "Failed to cancel order: " << e.what() << "\n";
        db->executeNonQuery(
            "INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, performed_at) "
            "VALUES ('order', " + std::to_string(order_id) + ", 'error', " + std::to_string(getId()) + ", NOW());"
        );
    }
}

void Customer::addToOrder(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id, int product_id, int qty) {
    
    

    
    auto it = std::find_if(orders_.begin(), orders_.end(),
        [order_id](const auto& order) { return order->getId() == order_id; }
    );

    if (it == orders_.end()) {
        std::cout << "Order not found in your session.\n";
        return;
    }

    
    auto item = std::make_unique<OrderItem>(product_id, qty, 0.0); 
    (*it)->addItem(std::move(item));
    std::cout << "Item added to order (in memory).\n";
}

void Customer::removeFromOrder(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id, int item_id) {
    std::cout << "Removing individual items not supported in simplified version.\n";
    
}

void Customer::makePayment(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id, std::unique_ptr<PaymentStrategy> strategy) {
    
    auto it = std::find_if(orders_.begin(), orders_.end(),
        [order_id](const auto& order) { return order->getId() == order_id; }
    );

    if (it == orders_.end()) {
        std::cout << "Order not found.\n";
        return;
    }

    
    std::string items_json = "[";
    bool first = true;
    for (const auto& item : (*it)->items_) {
        int pid = item->getProductId();
        int qty = item->getQuantity();

        
        auto res = db->executeQuery(
            "SELECT price, stock_quantity FROM products WHERE product_id = " + std::to_string(pid) + ";"
        );
        if (res.empty()) {
            std::cerr << "Error: Product " << pid << " does not exist.\n";
            return;
        }
        int stock = std::stoi(res[0][1]);
        if (stock < qty) {
            std::cerr << "Error: Insufficient stock for product " << pid << ".\n";
            return;
        }

        if (!first) items_json += ",";
        items_json += "{\"product_id\":" + std::to_string(pid) +
                      ",\"quantity\":" + std::to_string(qty) + "}";
        first = false;
    }
    items_json += "]";

    try {
        db->beginTransaction();

        
        db->executeNonQuery("DELETE FROM orders WHERE order_id = " + std::to_string(order_id) + ";");

        
        std::string call = "CALL createOrder(" + std::to_string(getId()) + ", '" + items_json+ "');";
        db->executeNonQuery(call);

        
        auto res = db->executeQuery("SELECT order_id FROM orders WHERE user_id = " + std::to_string(getId()) + " ORDER BY order_id DESC LIMIT 1;");
        if (res.empty()) throw std::runtime_error("Order creation failed");
        int new_order_id = std::stoi(res[0][0]);

        
        res = db->executeQuery("SELECT total_price FROM orders WHERE order_id = " + std::to_string(new_order_id) + ";");
        if (res.empty()) throw std::runtime_error("Total price not found");
        double amount = std::stod(res[0][0]);

        
        Payment payment(amount, std::move(strategy));
        if (payment.execute()) {
            
            db->executeNonQuery("CALL updateOrderStatus(" + std::to_string(new_order_id) + ", 'completed', " + std::to_string(getId()) + ");");
            db->executeNonQuery("CALL logAudit('order', " + std::to_string(new_order_id) + ", 'update', " + std::to_string(getId()) + ");");
            db->commitTransaction();
            std::cout << "Payment successful. Order " << new_order_id << " completed.\n";
        } else {
            throw std::runtime_error("Payment failed");
        }
    } catch (const std::exception& e) {
        db->rollbackTransaction();
        std::cerr << "Payment failed: " << e.what() << "\n";
        db->executeNonQuery(
            "INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, performed_at) "
            "VALUES ('order', " + std::to_string(order_id) + ", 'payment_error', " + std::to_string(getId()) + ", NOW());"
        );
    }
}

void Customer::returnOrder(std::shared_ptr<DatabaseConnection<std::string>> db, int order_id) {
    
    auto res = db->executeQuery("SELECT canReturnOrder(" + std::to_string(order_id) + ");");
    if (res.empty() || res[0][0] != "t") {
        std::cout << "Return not allowed: order must be 'completed' and within 30 days.\n";
        return;
    }

    try {
        db->beginTransaction();
        db->executeNonQuery("CALL updateOrderStatus(" + std::to_string(order_id) + ", 'returned', " + std::to_string(getId()) + ");");
        db->executeNonQuery("CALL logAudit('order', " + std::to_string(order_id) + ", 'update', " + std::to_string(getId()) + ");");
        db->commitTransaction();
        std::cout << "Order " << order_id << " returned successfully.\n";
    } catch (const std::exception& e) {
        db->rollbackTransaction();
        std::cerr << "Failed to return order: " << e.what() << "\n";
        db->executeNonQuery(
            "INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, performed_at) "
            "VALUES ('order', " + std::to_string(order_id) + ", 'return_error', " + std::to_string(getId()) + ", NOW());"
        );
    }
}

void Customer::runMenu(std::shared_ptr<DatabaseConnection<std::string>> db) {
    int choice;
    while (true) {
        std::cout << "\n--- Customer Menu ---\n"
                  << "1. Create Order\n"
                  << "2. Add Item to Order\n"
                  << "3. Remove Item from Order\n"
                  << "4. View My Orders\n"
                  << "5. View Order Status\n"
                  << "6. Pay Order\n"
                  << "7. Return Order\n"
                  << "8. View Order Status History\n"
                  << "9. Exit\n> ";
        std::cin >> choice;

        if (choice == 9) break;

        switch (choice) {
            case 1: createOrder(db); break;

            case 2: {
                int oid, pid, qty;
                std::cout << "Order ID: "; std::cin >> oid;
                std::cout << "Product ID: "; std::cin >> pid;
                std::cout << "Quantity: "; std::cin >> qty;
                addToOrder(db, oid, pid, qty);
                break;
            }

            case 3: {
                int oid, iid;
                std::cout << "Order ID: "; std::cin >> oid;
                std::cout << "Item ID (ignored): "; std::cin >> iid;
                removeFromOrder(db, oid, iid);
                break;
            }

            case 4: {
                auto res = db->executeQuery(
                    "SELECT order_id, status, total_price FROM orders WHERE user_id = " + std::to_string(getId()) + ";"
                );
                if (res.empty()) {
                    std::cout << "No orders found.\n";
                } else {
                    for (const auto& r : res) {
                        std::cout << "Order " << r[0] << " | Status: " << r[1] << " | Total: " << r[2] << "\n";
                    }
                }
                break;
            }

            case 5: {
                int oid;
                std::cout << "Order ID: "; std::cin >> oid;
                viewOrderStatus(db, oid);
                break;
            }

            case 6: {
                int oid, strat;
                std::cout << "Order ID: "; std::cin >> oid;
                std::cout << "Payment method:\n1. Card\n2. E-Wallet\n3. SBP\n> ";
                std::cin >> strat;

                std::unique_ptr<PaymentStrategy> ps;
                if (strat == 1) ps = std::make_unique<CreditCardPayment>();
                else if (strat == 2) ps = std::make_unique<EWalletPayment>();
                else if (strat == 3) ps = std::make_unique<SBPPayment>();
                else {
                    std::cout << "Invalid payment method.\n";
                    break;
                }

                makePayment(db, oid, std::move(ps));
                break;
            }

            case 7: {
                int oid;
                std::cout << "Order ID: "; std::cin >> oid;
                returnOrder(db, oid);
                break;
            }

            case 8: {
                int oid;
                std::cout << "Order ID: "; std::cin >> oid;
                
                auto res = db->executeQuery(
                    "SELECT 1 FROM orders WHERE order_id = " + std::to_string(oid) +
                    " AND user_id = " + std::to_string(getId()) + ";"
                );
                if (res.empty()) {
                    std::cout << "Access denied.\n";
                    break;
                }
                auto hist = db->executeQuery(
                    "SELECT * FROM getOrderStatusHistory(" + std::to_string(oid) + ");"
                );
                if (hist.empty()) {
                    std::cout << "No history found.\n";
                } else {
                    for (const auto& h : hist) {
                        std::cout << "Status: " << h[1] << " → " << h[2] << " at " << h[3] << " by " << h[4] << "\n";
                    }
                }
                break;
            }

            default:
                std::cout << "Invalid option.\n";
        }
    }
}