#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <cctype>


class Vehicle {
protected:
    std::string brand;
    std::string model;
    int year;
    std::vector<std::string> serviceRecords; 

public:
    Vehicle(std::string b, std::string m, int y, std::vector<std::string> records = {})
        : brand(std::move(b)), model(std::move(m)), year(y), serviceRecords(std::move(records)) {}

    virtual ~Vehicle() = default;

    virtual void display() const = 0;
    virtual std::string toFileString() const = 0;

    
    const std::string& getBrand() const { return brand; }
    const std::string& getModel() const { return model; }
    int getYear() const { return year; }
    const std::vector<std::string>& getServiceRecords() const { return serviceRecords; }

    
    void setBrand(const std::string& b) { brand = b; }
    void setModel(const std::string& m) { model = m; }
    void setYear(int y) { year = y; }
    void addServiceRecord(const std::string& record) { serviceRecords.push_back(record); }
};


class Car : public Vehicle {
    std::string transmission;
    int numDoors;

public:
    Car(std::string b, std::string m, int y, std::string trans, int doors, std::vector<std::string> records = {})
        : Vehicle(std::move(b), std::move(m), y, std::move(records)),
          transmission(std::move(trans)), numDoors(doors) {}

    void display() const override {
        std::cout << "Car [Brand: " << brand << ", Model: " << model
                  << ", Year: " << year << ", Transmission: " << transmission
                  << ", Doors: " << numDoors << "]\n";
        if (!serviceRecords.empty()) {
            std::cout << "  Service records: ";
            for (size_t i = 0; i < serviceRecords.size(); ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << serviceRecords[i];
            }
            std::cout << "\n";
        }
    }

    const std::string& getTransmission() const { return transmission; }
    int getNumDoors() const { return numDoors; }

    std::string toFileString() const override {
        std::ostringstream oss;
        oss << "Car;" << brand << ";" << model << ";" << year << ";" << transmission << "-" << numDoors << ";";
        for (size_t i = 0; i < serviceRecords.size(); ++i) {
            if (i > 0) oss << "\\|";
            oss << serviceRecords[i];
        }
        return oss.str();
    }
};


class Motorcycle : public Vehicle {
    std::string type;
    int power; 

public:
    Motorcycle(std::string b, std::string m, int y, std::string t, int p, std::vector<std::string> records = {})
        : Vehicle(std::move(b), std::move(m), y, std::move(records)), type(std::move(t)), power(p) {}

    void display() const override {
        std::cout << "Motorcycle [Brand: " << brand << ", Model: " << model
                  << ", Year: " << year << ", Type: " << type << ", Power: " << power << " HP]\n";
        if (!serviceRecords.empty()) {
            std::cout << "  Service records: ";
            for (size_t i = 0; i < serviceRecords.size(); ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << serviceRecords[i];
            }
            std::cout << "\n";
        }
    }

    const std::string& getType() const { return type; }
    int getPower() const { return power; }

    std::string toFileString() const override {
        std::ostringstream oss;
        oss << "Motorcycle;" << brand << ";" << model << ";" << year << ";" << type << "-" << power << ";";
        for (size_t i = 0; i < serviceRecords.size(); ++i) {
            if (i > 0) oss << "\\|";
            oss << serviceRecords[i];
        }
        return oss.str();
    }
};


std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}


std::unique_ptr<Vehicle> parseVehicle(const std::string& line) {
    auto parts = split(line, ';');
    if (parts.size() < 6) return nullptr;

    std::string type = parts[0];
    std::string brand = parts[1];
    std::string model = parts[2];
    int year = std::stoi(parts[3]);

    
    std::string servicePart = parts[5];
    std::vector<std::string> serviceRecords;
    size_t pos = 0;
    std::string token;
    const std::string delim = "\\|";
    while ((pos = servicePart.find(delim)) != std::string::npos) {
        token = servicePart.substr(0, pos);
        if (!token.empty()) serviceRecords.push_back(token);
        servicePart.erase(0, pos + delim.length());
    }
    if (!servicePart.empty()) serviceRecords.push_back(servicePart);

    if (type == "Car") {
        auto param = split(parts[4], '-');
        if (param.size() < 2) return nullptr;
        std::string trans = param[0];
        int doors = std::stoi(param[1]);
        return std::make_unique<Car>(brand, model, year, trans, doors, serviceRecords);
    } else if (type == "Motorcycle") {
        auto param = split(parts[4], '-');
        if (param.size() < 2) return nullptr;
        std::string bikeType = param[0];
        int power = std::stoi(param[1]);
        return std::make_unique<Motorcycle>(brand, model, year, bikeType, power, serviceRecords);
    }
    return nullptr;
}


std::list<std::unique_ptr<Vehicle>> loadFromFile(const std::string& filename) {
    std::list<std::unique_ptr<Vehicle>> vehicles;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return vehicles;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto v = parseVehicle(line);
        if (v) vehicles.push_back(std::move(v));
    }
    file.close();
    return vehicles;
}


void saveToFile(const std::list<std::unique_ptr<Vehicle>>& vehicles, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not write to file " << filename << "\n";
        return;
    }
    for (const auto& v : vehicles) {
        file << v->toFileString() << "\n";
    }
    file.close();
}


void sortByYear(std::list<std::unique_ptr<Vehicle>>& vehicles) {
    vehicles.sort([](const auto& a, const auto& b) {
        return a->getYear() < b->getYear();
    });
}


int countAutomaticCars(const std::list<std::unique_ptr<Vehicle>>& vehicles) {
    return std::count_if(vehicles.begin(), vehicles.end(), [](const auto& v) {
        if (auto car = dynamic_cast<const Car*>(v.get())) {
            return car->getTransmission().find("Automatic") != std::string::npos;
        }
        return false;
    });
}


Motorcycle* findMostPowerfulMotorcycle(std::list<std::unique_ptr<Vehicle>>& vehicles) {
    Motorcycle* best = nullptr;
    for (auto& v : vehicles) {
        if (auto moto = dynamic_cast<Motorcycle*>(v.get())) {
            if (!best || moto->getPower() > best->getPower()) {
                best = moto;
            }
        }
    }
    return best;
}


void groupAndSave(const std::list<std::unique_ptr<Vehicle>>& vehicles) {
    std::ofstream carsFile("cars.txt");
    std::ofstream bikesFile("motorcycles.txt");

    for (const auto& v : vehicles) {
        if (dynamic_cast<const Car*>(v.get())) {
            carsFile << v->toFileString() << "\n";
        } else if (dynamic_cast<const Motorcycle*>(v.get())) {
            bikesFile << v->toFileString() << "\n";
        }
    }
    carsFile.close(); bikesFile.close();
}


double averageCarYear(const std::list<std::unique_ptr<Vehicle>>& vehicles) {
    std::vector<int> years;
    std::for_each(vehicles.begin(), vehicles.end(), [&years](const auto& v) {
        if (dynamic_cast<const Car*>(v.get())) {
            years.push_back(v->getYear());
        }
    });
    if (years.empty()) return 0.0;
    return std::accumulate(years.begin(), years.end(), 0.0) / static_cast<double>(years.size());
}


void findVehiclesWithService(const std::list<std::unique_ptr<Vehicle>>& vehicles, const std::string& keyword) {
    for (const auto& v : vehicles) {
        const auto& records = v->getServiceRecords();
        bool found = std::any_of(records.begin(), records.end(), [&keyword](const std::string& r) {
            return r.find(keyword) != std::string::npos;
        });
        if (found) {
            v->display();
        }
    }
}


void addNewVehicle(std::list<std::unique_ptr<Vehicle>>& vehicles) {
    std::cout << "Enter type (Car / Motorcycle): ";
    std::string type;
    std::getline(std::cin, type);

    std::cout << "Brand: ";
    std::string brand;
    std::getline(std::cin, brand);

    std::cout << "Model: ";
    std::string model;
    std::getline(std::cin, model);

    std::cout << "Year: ";
    std::string yearStr;
    std::getline(std::cin, yearStr);
    int year = std::stoi(yearStr);

    if (type == "Car") {
        std::cout << "Transmission (e.g., Automatic): ";
        std::string trans;
        std::getline(std::cin, trans);
        std::cout << "Number of doors: ";
        std::string doorsStr;
        std::getline(std::cin, doorsStr);
        int doors = std::stoi(doorsStr);
        vehicles.push_back(std::make_unique<Car>(brand, model, year, trans, doors));
    } else if (type == "Motorcycle") {
        std::cout << "Type (e.g., Sport): ";
        std::string bikeType;
        std::getline(std::cin, bikeType);
        std::cout << "Power (HP): ";
        std::string powerStr;
        std::getline(std::cin, powerStr);
        int power = std::stoi(powerStr);
        vehicles.push_back(std::make_unique<Motorcycle>(brand, model, year, bikeType, power));
    } else {
        std::cout << "Unknown type!\n";
    }
    std::cout << "Vehicle added.\n";
}


void editVehicle(std::list<std::unique_ptr<Vehicle>>& vehicles) {
    if (vehicles.empty()) {
        std::cout << "No vehicles to edit.\n";
        return;
    }

    std::cout << "Enter index (starting from 0): ";
    std::string idxStr;
    std::getline(std::cin, idxStr);
    size_t idx = std::stoul(idxStr);

    auto it = vehicles.begin();
    std::advance(it, idx);
    if (it == vehicles.end()) {
        std::cout << "Invalid index.\n";
        return;
    }

    Vehicle* v = it->get();

    std::cout << "New brand: ";
    std::string brand;
    std::getline(std::cin, brand);
    v->setBrand(brand);

    std::cout << "New model: ";
    std::string model;
    std::getline(std::cin, model);
    v->setModel(model);

    std::cout << "New year: ";
    std::string yearStr;
    std::getline(std::cin, yearStr);
    v->setYear(std::stoi(yearStr));

    std::cout << "Add service record? (y/n): ";
    char choice;
    std::cin >> choice;
    std::cin.ignore();
    if (choice == 'y' || choice == 'Y') {
        std::cout << "Record: ";
        std::string record;
        std::getline(std::cin, record);
        v->addServiceRecord(record);
    }

    std::cout << "Vehicle updated.\n";
}


void deleteVehicle(std::list<std::unique_ptr<Vehicle>>& vehicles) {
    if (vehicles.empty()) {
        std::cout << "No vehicles to delete.\n";
        return;
    }

    std::cout << "Enter index (starting from 0): ";
    std::string idxStr;
    std::getline(std::cin, idxStr);
    size_t idx = std::stoul(idxStr);

    auto it = vehicles.begin();
    std::advance(it, idx);
    if (it == vehicles.end()) {
        std::cout << "Invalid index.\n";
        return;
    }

    vehicles.erase(it);
    std::cout << "Vehicle deleted.\n";
}


int main() {
    std::list<std::unique_ptr<Vehicle>> vehicles;
    int choice;

    do {
        std::cout << "\n--- Vehicle Management System ---\n";
        std::cout << "1. Load data from file\n";
        std::cout << "2. Display all vehicles\n";
        std::cout << "3. Search vehicles by service keyword (e.g., 'engine')\n";
        std::cout << "4. Sort by year\n";
        std::cout << "5. Count cars with automatic transmission\n";
        std::cout << "6. Find most powerful motorcycle\n";
        std::cout << "7. Group and save to cars.txt / motorcycles.txt\n";
        std::cout << "8. Average car manufacturing year\n";
        std::cout << "9. Add new vehicle manually\n";
        std::cout << "10. Edit vehicle\n";
        std::cout << "11. Delete vehicle\n";
        std::cout << "12. Save to file\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;
        std::cin.ignore(); 

        switch (choice) {
            case 1: {
                vehicles = loadFromFile("vehicles.txt");
                std::cout << "Data loaded.\n";
                break;
            }
            case 2: {
                for (const auto& v : vehicles) {
                    v->display();
                }
                break;
            }
            case 3: {
                std::cout << "Enter service keyword: ";
                std::string word;
                std::getline(std::cin, word);
                findVehiclesWithService(vehicles, word);
                break;
            }
            case 4: {
                sortByYear(vehicles);
                std::cout << "Sorted by year.\n";
                break;
            }
            case 5: {
                int cnt = countAutomaticCars(vehicles);
                std::cout << "Cars with automatic transmission: " << cnt << "\n";
                break;
            }
            case 6: {
                if (auto* moto = findMostPowerfulMotorcycle(vehicles)) {
                    std::cout << "Most powerful motorcycle:\n";
                    moto->display();
                } else {
                    std::cout << "No motorcycles found.\n";
                }
                break;
            }
            case 7: {
                groupAndSave(vehicles);
                std::cout << "Saved to cars.txt and motorcycles.txt\n";
                break;
            }
            case 8: {
                double avg = averageCarYear(vehicles);
                std::cout << "Average car year: " << avg << "\n";
                break;
            }
            case 9: {
                addNewVehicle(vehicles);
                break;
            }
            case 10: {
                editVehicle(vehicles);
                break;
            }
            case 11: {
                deleteVehicle(vehicles);
                break;
            }
            case 12: {
                saveToFile(vehicles, "vehicles_output.txt");
                std::cout << "Saved to vehicles_output.txt\n";
                break;
            }
            case 0:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}