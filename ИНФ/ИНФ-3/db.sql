CREATE DATABASE order_management;

\c order_management;


CREATE TABLE products (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    price NUMERIC(10, 2) NOT NULL CHECK (price >= 0)
);

CREATE TABLE orders (
    order_id SERIAL PRIMARY KEY,
    order_date DATE NOT NULL DEFAULT CURRENT_DATE
);


CREATE TABLE order_items (
    order_item_id SERIAL PRIMARY KEY,
    order_id INTEGER NOT NULL,
    product_id INTEGER NOT NULL,
    quantity INTEGER NOT NULL CHECK (quantity > 0),
    total_price NUMERIC(12, 2) NOT NULL CHECK (total_price >= 0),
    FOREIGN KEY (order_id) REFERENCES orders(order_id) ON DELETE CASCADE,
    FOREIGN KEY (product_id) REFERENCES products(id) ON DELETE RESTRICT
);




INSERT INTO products (name, price) VALUES
('Ноутбук', 59999.99),
('Мышь', 1299.00),
('Клавиатура', 3499.50),
('Монитор', 18999.00),
('Наушники', 2999.99);


INSERT INTO orders (order_date) VALUES
('2025-11-10'),
('2025-11-12'),
('2025-11-14');


INSERT INTO order_items (order_id, product_id, quantity, total_price) VALUES
(1, 1, 1, 59999.99),
(1, 2, 2, 2598.00);


INSERT INTO order_items (order_id, product_id, quantity, total_price) VALUES
(2, 3, 1, 3499.50),
(2, 5, 1, 2999.99);

INSERT INTO order_items (order_id, product_id, quantity, total_price) VALUES
(3, 4, 1, 18999.00),
(3, 2, 1, 1299.00);


SELECT id, name, price FROM products;



SELECT
    oi.order_item_id,
    p.name AS product_name,
    oi.quantity,
    oi.total_price
FROM order_items oi
JOIN products p ON oi.product_id = p.id
WHERE oi.order_id = 1;


SELECT SUM(total_price) AS total_order_cost
FROM order_items
WHERE order_id = 1;


SELECT
    o.order_id,
    o.order_date,
    SUM(oi.total_price) AS total_amount
FROM orders o
JOIN order_items oi ON o.order_id = oi.order_id
WHERE o.order_date BETWEEN '2025-11-10' AND '2025-11-14'
GROUP BY o.order_id, o.order_date
ORDER BY o.order_date;



-- Дополнительно

SELECT
    p.name AS product_name,
    COUNT(*) AS times_ordered
FROM order_items oi
JOIN products p ON oi.product_id = p.id
JOIN orders o ON oi.order_id = o.order_id
WHERE o.order_date BETWEEN '2025-11-01' AND '2025-11-30'
GROUP BY p.id, p.name
ORDER BY times_ordered DESC;


UPDATE products
SET price = 1199.00
WHERE id = 2;

-- Цена изменилась, требуется пересчет общей стоимости

UPDATE order_items oi
SET total_price = oi.quantity * p.price
FROM products p
WHERE oi.product_id = p.id;