CREATE OR REPLACE FUNCTION update_orders_on_price_change()
RETURNS TRIGGER AS $$
BEGIN
    UPDATE order_items
    SET price = NEW.price * quantity
    WHERE product_id = NEW.product_id;

    UPDATE orders o
    SET total_price = (SELECT SUM(price) FROM order_items WHERE order_id = o.order_id)
    WHERE order_id IN (SELECT DISTINCT order_id FROM order_items WHERE product_id = NEW.product_id);
    RETURN NEW;
END $$ LANGUAGE plpgsql;

CREATE TRIGGER trg_price_update
AFTER UPDATE OF price ON products
FOR EACH ROW EXECUTE FUNCTION update_orders_on_price_change();