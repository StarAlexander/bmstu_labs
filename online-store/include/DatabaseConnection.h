#pragma once
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <memory>

template<typename T>
class DatabaseConnection {
private:
    std::unique_ptr<pqxx::connection> conn_;
    std::unique_ptr<pqxx::work> txn_;

public:
    explicit DatabaseConnection(const T& conn_str)
        : conn_(std::make_unique<pqxx::connection>(conn_str)) {}

    std::vector<std::vector<std::string>> executeQuery(const std::string& query);
    void executeNonQuery(const std::string& query);
    void beginTransaction();
    void commitTransaction();
    void rollbackTransaction();
    bool getTransactionStatus() const { return static_cast<bool>(txn_); }
    void createFunction(const std::string& sql);
    void createTrigger(const std::string& sql);

    ~DatabaseConnection() = default;
};