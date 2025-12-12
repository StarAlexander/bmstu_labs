#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>
#include <iostream>
#include <memory>

class Database {

public:
    std::unique_ptr<pqxx::connection> conn;

    Database(const std::string& conn_str = "dbname=postgres password=Sashalife20050709 user=postgres")
        : conn(std::make_unique<pqxx::connection>(conn_str)) {
            if (!conn->is_open()) {
                throw std::runtime_error("Can't connect to database");
            }
        }

    pqxx::connection& getConnection() {return *conn; }
};


#endif