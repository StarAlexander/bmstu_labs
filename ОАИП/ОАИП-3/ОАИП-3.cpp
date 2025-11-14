#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;


struct Product {
    string name;
    int quantity;
    double price;

    
    Product() : name(""), quantity(0), price(0.0) {}

    
    Product(const string& n, int q, double p) : name(n), quantity(q), price(p) {}
};


void createAndFillFile() {
    ofstream outFile("orders.txt", ios::app); 
    if (!outFile.is_open()) {
        cout << "Error: Cannot open file 'orders.txt' for writing." << endl;
        return;
    }

    cout << "Enter product information (press Enter with empty name to stop):" << endl;
    while (true) {
        string name;
        int quantity;
        double price;

        cout << "Product name: ";
        getline(cin, name);
        if (name.empty()) break; 

        cout << "Quantity: ";
        cin >> quantity;
        cout << "Price per unit: ";
        cin >> price;
        cin.ignore(); 

        outFile << name << "," << quantity << "," << price << endl;
        cout << "Product added successfully!" << endl;
    }

    outFile.close();
    cout << "Data saved to 'orders.txt'." << endl;
}


vector<Product> readAllProducts() {
    vector<Product> products;
    ifstream inFile("orders.txt");
    if (!inFile.is_open()) {
        cout << "Error: Cannot open file 'orders.txt' for reading." << endl;
        return products;
    }

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue; 

        stringstream ss(line);
        string name, qtyStr, priceStr;
        getline(ss, name, ',');
        getline(ss, qtyStr, ',');
        getline(ss, priceStr);

        try {
            int quantity = stoi(qtyStr);
            double price = stod(priceStr);
            products.emplace_back(name, quantity, price);
        } catch (const exception& e) {
            cout << "Warning: Invalid data format in line: " << line << endl;
        }
    }

    inFile.close();
    return products;
}


void searchProductByName(const string& targetName) {
    vector<Product> products = readAllProducts();
    bool found = false;

    cout << "\nSearch results for '" << targetName << "':" << endl;
    for (const auto& prod : products) {
        if (prod.name == targetName) {
            cout << "Found: " << prod.name << " | Quantity: " << prod.quantity 
                 << " | Price per unit: $" << fixed << setprecision(2) << prod.price << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No product found with name '" << targetName << "'." << endl;
    }
}


void sortProducts(int criterion) {
    vector<Product> products = readAllProducts();
    if (products.empty()) {
        cout << "No products to sort." << endl;
        return;
    }

    switch (criterion) {
        case 1: 
            sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
                return a.name < b.name;
            });
            cout << "Sorted by name." << endl;
            break;
        case 2: 
            sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
                return a.quantity < b.quantity;
            });
            cout << "Sorted by quantity." << endl;
            break;
        case 3: 
            sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
                return a.price < b.price;
            });
            cout << "Sorted by price." << endl;
            break;
        default:
            cout << "Invalid sorting criterion." << endl;
            return;
    }

    
    cout << "\nSorted Products:" << endl;
    for (const auto& prod : products) {
        cout << prod.name << " | Quantity: " << prod.quantity 
             << " | Price per unit: $" << fixed << setprecision(2) << prod.price << endl;
    }
}


void addNewProduct() {
    string name;
    int quantity;
    double price;

    cout << "Enter new product information:" << endl;
    cout << "Product name: ";
    getline(cin, name);
    cout << "Quantity: ";
    cin >> quantity;
    cout << "Price per unit: ";
    cin >> price;
    cin.ignore(); 

    ofstream outFile("orders.txt", ios::app); 
    if (!outFile.is_open()) {
        cout << "Error: Cannot open file 'orders.txt' for writing." << endl;
        return;
    }

    outFile << name << "," << quantity << "," << price << endl;
    outFile.close();

    cout << "New product '" << name << "' added successfully!" << endl;
}


void displayProductsByRequest() {
    vector<Product> products = readAllProducts();
    if (products.empty()) {
        cout << "No products available." << endl;
        return;
    }

    int choice;
    cout << "\nDisplay options:" << endl;
    cout << "1. Show all products" << endl;
    cout << "2. Show products with price not exceeding a certain value" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(); 

    if (choice == 1) {
        cout << "\nAll Products:" << endl;
        for (const auto& prod : products) {
            cout << prod.name << " | Quantity: " << prod.quantity 
                 << " | Price per unit: $" << fixed << setprecision(2) << prod.price << endl;
        }
    } else if (choice == 2) {
        double maxPrice;
        cout << "Enter maximum price: $";
        cin >> maxPrice;
        cin.ignore();

        cout << "\nProducts with price <= $" << fixed << setprecision(2) << maxPrice << ":" << endl;
        bool found = false;
        for (const auto& prod : products) {
            if (prod.price <= maxPrice) {
                cout << prod.name << " | Quantity: " << prod.quantity 
                     << " | Price per unit: $" << fixed << setprecision(2) << prod.price << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No products found with price <= $" << fixed << setprecision(2) << maxPrice << "." << endl;
        }
    } else {
        cout << "Invalid choice." << endl;
    }
}


void logOperation(const string& operationResult) {
    ofstream logFile("output.txt", ios::app); 
    if (logFile.is_open()) {
        logFile << "=== Operation Result ===" << endl;
        logFile << operationResult << endl;
        logFile << "========================" << endl;
        logFile.close();
        cout << "Operation result logged to 'output.txt'." << endl;
    } else {
        cout << "Warning: Could not log operation to 'output.txt'." << endl;
    }
}


int main() {
    cout << "Welcome to the Product Management System!" << endl;

    while (true) {
        cout << "\n=== Main Menu ===" << endl;
        cout << "1. Create and fill file (add products)" << endl;
        cout << "2. Search product by name" << endl;
        cout << "3. Sort products" << endl;
        cout << "4. Add new product" << endl;
        cout << "5. Display products by request" << endl;
        cout << "6. Exit" << endl;
        cout << "Choose an option (1-6): ";

        int choice;
        cin >> choice;
        cin.ignore(); 

        string logMessage = "";

        switch (choice) {
            case 1: {
                cout << "\n--- Create and Fill File ---" << endl;
                createAndFillFile();
                logMessage = "Created/Filled file 'orders.txt'.";
                break;
            }
            case 2: {
                cout << "\n--- Search Product by Name ---" << endl;
                string name;
                cout << "Enter product name to search: ";
                getline(cin, name);
                searchProductByName(name);
                logMessage = "Searched for product: " + name;
                break;
            }
            case 3: {
                cout << "\n--- Sort Products ---" << endl;
                cout << "Sort by:" << endl;
                cout << "1. Name" << endl;
                cout << "2. Quantity" << endl;
                cout << "3. Price" << endl;
                cout << "Enter criterion (1-3): ";
                int criterion;
                cin >> criterion;
                cin.ignore();
                sortProducts(criterion);
                logMessage = "Sorted products by criterion: " + to_string(criterion);
                break;
            }
            case 4: {
                cout << "\n--- Add New Product ---" << endl;
                addNewProduct();
                logMessage = "Added new product.";
                break;
            }
            case 5: {
                cout << "\n--- Display Products by Request ---" << endl;
                displayProductsByRequest();
                logMessage = "Displayed products based on user request.";
                break;
            }
            case 6: {
                cout << "Goodbye!" << endl;
                return 0;
            }
            default:
                cout << "Invalid option. Please try again." << endl;
                continue;
        }

        
        logOperation(logMessage);
    }

    return 0;
}