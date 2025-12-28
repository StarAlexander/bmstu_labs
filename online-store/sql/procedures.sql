CREATE OR REPLACE PROCEDURE createOrder(
    p_user_id INTEGER,
    p_items JSON,
    OUT p_order_id INTEGER
)
LANGUAGE plpgsql
AS $$
DECLARE
    item JSON;
    prod RECORD;
    item_price DECIMAL(10, 2);
    total DECIMAL(10, 2) := 0;
BEGIN

    INSERT INTO orders (user_id) VALUES (p_user_id) RETURNING order_id INTO p_order_id;


    FOR item IN SELECT * FROM json_array_elements(p_items)
    LOOP
        SELECT price, stock_quantity INTO prod
        FROM products
        WHERE product_id = (item->>'product_id')::INTEGER;

        IF prod.stock_quantity < (item->>'quantity')::INTEGER THEN
            RAISE EXCEPTION 'Insufficient stock for product %', (item->>'product_id')::INTEGER;
        END IF;

        item_price := prod.price * (item->>'quantity')::INTEGER;
        total := total + item_price;


        INSERT INTO order_items (order_id, product_id, quantity, price)
        VALUES (p_order_id, (item->>'product_id')::INTEGER, (item->>'quantity')::INTEGER, item_price);


        UPDATE products
        SET stock_quantity = stock_quantity - (item->>'quantity')::INTEGER
        WHERE product_id = (item->>'product_id')::INTEGER;
    END LOOP;


    UPDATE orders SET total_price = total WHERE order_id = p_order_id;
END $$;


CREATE OR REPLACE PROCEDURE updateOrderStatus(
    p_order_id INTEGER,
    p_new_status VARCHAR,
    p_changed_by INTEGER
)
LANGUAGE plpgsql
AS $$
DECLARE
    old_stat VARCHAR;
BEGIN
    SELECT status INTO old_stat FROM orders WHERE order_id = p_order_id;
    IF NOT FOUND THEN RAISE EXCEPTION 'Order % not found', p_order_id; END IF;
    IF old_stat = p_new_status THEN RETURN; END IF;

    UPDATE orders SET status = p_new_status WHERE order_id = p_order_id;
    INSERT INTO order_status_history (order_id, old_status, new_status, changed_by)
    VALUES (p_order_id, old_stat, p_new_status, p_changed_by);
END $$;


CREATE OR REPLACE PROCEDURE logAudit(
    p_entity_type VARCHAR,
    p_entity_id INTEGER,
    p_operation VARCHAR,
    p_performed_by INTEGER
)
LANGUAGE sql
AS $$
    INSERT INTO audit_log (entity_id, entity_type, operation, performed_by)
    VALUES (p_entity_id, p_entity_type, p_operation, p_performed_by);
$$;