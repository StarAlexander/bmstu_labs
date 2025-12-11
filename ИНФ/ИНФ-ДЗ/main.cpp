#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <iomanip>
#include <ctime>
#include <pqxx/pqxx>


struct Sale {
    int sale_id;
    std::string sale_date; 
    int product_id;
    int customer_id;
    int quantity;
    double amount;
};

struct Product {
    int product_id;
    std::string product_name;
    std::string category;
    double price;
};

struct Customer {
    int customer_id;
    std::string customer_name;
    std::string region;
};


std::vector<std::string> splitCSV(const std::string& line) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;
    while (std::getline(ss, field, ',')) {
        size_t start = field.find_first_not_of(" \t");
        size_t end = field.find_last_not_of(" \t");
        if (start == std::string::npos) {
            fields.emplace_back("");
        } else {
            fields.emplace_back(field.substr(start, end - start + 1));
        }
    }
    return fields;
}

std::string validateDate(const std::string& date_str) {
    std::tm tm = {};
    std::istringstream ss(date_str);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    if (ss.fail()) {
        std::cerr << "Invalid date: " << date_str << std::endl;
        return "";
    }
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}


std::vector<Sale> loadSalesData(const std::string& filename) {
    std::vector<Sale> sales;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open " << filename << std::endl;
        return sales;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto fields = splitCSV(line);
        if (fields.size() != 6) continue;
        try {
            Sale s;
            s.sale_id = std::stoi(fields[0]);
            s.sale_date = validateDate(fields[1]);
            if (s.sale_date.empty()) continue;
            s.product_id = std::stoi(fields[2]);
            s.customer_id = std::stoi(fields[3]);
            s.quantity = std::stoi(fields[4]);
            s.amount = std::stod(fields[5]);
            sales.push_back(s);
        } catch (const std::exception& e) {
            std::cerr << "Parse error in sales: " << line << " (" << e.what() << ")\n";
        }
    }
    return sales;
}

std::vector<Product> loadProducts(const std::string& filename) {
    std::vector<Product> prods;
    std::ifstream file(filename);
    if (!file.is_open()) return prods;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto fields = splitCSV(line);
        if (fields.size() != 4) continue;
        try {
            Product p;
            p.product_id = std::stoi(fields[0]);
            p.product_name = fields[1];
            p.category = fields[2];
            p.price = std::stod(fields[3]);
            prods.push_back(p);
        } catch (const std::exception& e) {
            std::cerr << "Parse error in products: " << line << "\n";
        }
    }
    return prods;
}

std::vector<Customer> loadCustomers(const std::string& filename) {
    std::vector<Customer> custs;
    std::ifstream file(filename);
    if (!file.is_open()) return custs;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto fields = splitCSV(line);
        if (fields.size() != 3) continue;
        try {
            Customer c;
            c.customer_id = std::stoi(fields[0]);
            c.customer_name = fields[1];
            c.region = fields[2];
            custs.push_back(c);
        } catch (const std::exception& e) {
            std::cerr << "Parse error in customers: " << line << "\n";
        }
    }
    return custs;
}



void runAnalyticalQueries(pqxx::connection& conn) {
    pqxx::work txn{conn};

    std::cout << "\n=== Analytical Query Results ===\n\n";

    std::cout << "1. Total Sales by Category:\n";
    std::cout << "Category\t\tTotal Sales\n";
    std::cout << "----------------------------------------\n";
    auto q1 = txn.exec(
        "SELECT p.category, SUM(s.amount) AS total_sales "
        "FROM sales_fact s "
        "JOIN products_dim p ON s.product_id = p.product_id "
        "GROUP BY p.category "
        "ORDER BY total_sales DESC;"
    );
    for (const auto& row : q1) {
        std::cout << row["category"].c_str() << "\t\t"
                  << row["total_sales"].c_str() << "\n";
    }

    std::cout << "\n";


    std::cout << "2. Number of Sales by Region:\n";
    std::cout << "Region\t\t\tSales Count\n";
    std::cout << "----------------------------------------\n";
    auto q2 = txn.exec(
        "SELECT c.region, COUNT(s.sale_id) AS number_of_sales "
        "FROM sales_fact s "
        "JOIN customers_dim c ON s.customer_id = c.customer_id "
        "GROUP BY c.region "
        "ORDER BY number_of_sales DESC;"
    );
    for (const auto& row : q2) {
        std::cout << row["region"].c_str() << "\t\t"
                  << row["number_of_sales"].c_str() << "\n";
    }

    std::cout << "\n";

    std::cout << "3. Average Ticket by Month:\n";
    std::cout << "Year\tMonth\tAverage Ticket\n";
    std::cout << "----------------------------------------\n";
    auto q3 = txn.exec(
        "SELECT t.year, t.month, AVG(s.amount) AS average_ticket "
        "FROM sales_fact s "
        "JOIN time_dim t ON s.sale_date = t.date "
        "GROUP BY t.year, t.month "
        "ORDER BY t.year, t.month;"
    );
    for (const auto& row : q3) {
        std::cout << row["year"].c_str() << "\t"
                  << row["month"].c_str() << "\t"
                  << row["average_ticket"].c_str() << "\n";
    }

}

int main() {
    try {
        
        pqxx::connection c("dbname=postgres user=postgres password=postgres host=localhost port=5432");
        pqxx::work txn{c};

        std::cout << "Connected. Loading data...\n";

        auto sales = loadSalesData("sales.csv");
        auto products = loadProducts("products.csv");
        auto customers = loadCustomers("customers.csv");

        
        for (const auto& p : products) {
            txn.exec_params(
                "INSERT INTO products_dim (product_id, product_name, category, price) VALUES ($1, $2, $3, $4)",
                p.product_id, p.product_name, p.category, p.price
            );
        }

        
        for (const auto& c : customers) {
            txn.exec_params(
                "INSERT INTO customers_dim (customer_id, customer_name, region) VALUES ($1, $2, $3)",
                c.customer_id, c.customer_name, c.region
            );
        }

        
        std::set<std::string> unique_dates;
        for (const auto& s : sales) {
            unique_dates.insert(s.sale_date);
        }

        const char* weekdays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

        for (const std::string& date_str : unique_dates) {
            std::tm tm = {};
            std::istringstream ss(date_str);
            ss >> std::get_time(&tm, "%Y-%m-%d");

            int year = tm.tm_year + 1900;
            int month = tm.tm_mon + 1;
            int day = tm.tm_mday;
            int dow = tm.tm_wday;
            int quarter = (month - 1) / 3 + 1;

            txn.exec_params(
                "INSERT INTO time_dim (date, year, quarter, month, day, day_of_week) "
                "VALUES ($1, $2, $3, $4, $5, $6) ON CONFLICT (date) DO NOTHING",
                date_str, year, quarter, month, day, weekdays[dow]
            );
        }

        
        for (const auto& s : sales) {
            txn.exec_params(
                "INSERT INTO sales_fact (sale_id, sale_date, product_id, customer_id, quantity, amount) "
                "VALUES ($1, $2, $3, $4, $5, $6)",
                s.sale_id, s.sale_date, s.product_id, s.customer_id, s.quantity, s.amount
            );
        }

        txn.commit();
        std::cout << "Data loaded successfully!\n";

        runAnalyticalQueries(c);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}