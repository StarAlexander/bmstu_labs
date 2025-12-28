#include "DatabaseConnection.h"
#include <stdexcept>

template<typename T>
std::vector<std::vector<std::string>> DatabaseConnection<T>::executeQuery(const std::string& query) {
    pqxx::nontransaction w(*conn_);
    pqxx::result r = w.exec(query);
    std::vector<std::vector<std::string>> result;
    for (const auto& row : r) {
        std::vector<std::string> row_vec;
        for (const auto& field : row) {
            row_vec.push_back(std::string(field.c_str()));
        }
        result.push_back(row_vec);
    }
    return result;
}

template<typename T>
void DatabaseConnection<T>::executeNonQuery(const std::string& query) {
    if (txn_) {
        txn_->exec(query);
    } else {
        pqxx::nontransaction w(*conn_);
        w.exec(query);
    }
}

template<typename T>
void DatabaseConnection<T>::beginTransaction() {
    if (!txn_) {
        txn_ = std::make_unique<pqxx::work>(*conn_);
    }
}

template<typename T>
void DatabaseConnection<T>::commitTransaction() {
    if (txn_) {
        txn_->commit();
        txn_.reset();
    }
}

template<typename T>
void DatabaseConnection<T>::rollbackTransaction() {
    if (txn_) {
        txn_->abort();
        txn_.reset();
    }
}

template<typename T>
void DatabaseConnection<T>::createFunction(const std::string& sql) {
    executeNonQuery(sql);
}

template<typename T>
void DatabaseConnection<T>::createTrigger(const std::string& sql) {
    executeNonQuery(sql);
}

template class DatabaseConnection<std::string>;