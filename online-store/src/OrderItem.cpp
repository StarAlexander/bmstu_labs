#include "OrderItem.h"

OrderItem::OrderItem(int product_id, int quantity, double price)
    : product_id_(product_id), quantity_(quantity), price_(price) {}

double OrderItem::getLineTotal() const {
    return price_ * quantity_;
}