#pragma once

class OrderItem {
private:
    int product_id_;
    int quantity_;
    double price_;

public:
    OrderItem(int product_id, int quantity, double price);
    ~OrderItem() = default;

    double getLineTotal() const;
    int getProductId() const { return product_id_; }
    int getQuantity() const { return quantity_; }
    double getPrice() const { return price_; }
};