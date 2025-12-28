
DELETE FROM audit_log;
DELETE FROM order_status_history;
DELETE FROM order_items;
DELETE FROM orders;
DELETE FROM products;
DELETE FROM users;


ALTER SEQUENCE users_user_id_seq RESTART WITH 1;
ALTER SEQUENCE products_product_id_seq RESTART WITH 1;
ALTER SEQUENCE orders_order_id_seq RESTART WITH 1;
ALTER SEQUENCE order_items_order_item_id_seq RESTART WITH 1;
ALTER SEQUENCE order_status_history_history_id_seq RESTART WITH 1;
ALTER SEQUENCE audit_log_log_id_seq RESTART WITH 1;


INSERT INTO users (name, email, role, password_hash, loyalty_level) VALUES
('Админ Иван', 'admin@shop.ru', 'admin', 'hash_admin_123', 1),
('Менеджер Ольга', 'manager@shop.ru', 'manager', 'hash_manager_456', 0),
('Покупатель Алексей', 'customer1@shop.ru', 'customer', 'hash_cust_789', 0),
('Покупатель Мария', 'customer2@shop.ru', 'customer', 'hash_cust_101', 1);


INSERT INTO products (name, price, stock_quantity) VALUES
('Ноутбук ASUS', 65000.00, 10),
('Мышь Logitech', 1200.50, 50),
('Клавиатура механическая', 3500.00, 30),
('Монитор 27" 4K', 25000.00, 5),
('USB-флешка 64 ГБ', 800.00, 100);



INSERT INTO orders (user_id, status, total_price, order_date) VALUES
(3, 'pending', 66200.50, NOW() - INTERVAL '2 days');


INSERT INTO orders (user_id, status, total_price, order_date) VALUES
(4, 'completed', 28500.00, NOW() - INTERVAL '10 days');


INSERT INTO orders (user_id, status, total_price, order_date) VALUES
(3, 'completed', 800.00, NOW() - INTERVAL '5 days');


INSERT INTO orders (user_id, status, total_price, order_date) VALUES
(4, 'canceled', 3500.00, NOW() - INTERVAL '15 days');



INSERT INTO order_items (order_id, product_id, quantity, price) VALUES
(1, 1, 1, 65000.00),
(1, 2, 1, 1200.50);


INSERT INTO order_items (order_id, product_id, quantity, price) VALUES
(2, 4, 1, 25000.00),
(2, 3, 1, 3500.00);


INSERT INTO order_items (order_id, product_id, quantity, price) VALUES
(3, 5, 1, 800.00);


INSERT INTO order_items (order_id, product_id, quantity, price) VALUES
(4, 3, 1, 3500.00);



INSERT INTO order_status_history (order_id, old_status, new_status, changed_at, changed_by) VALUES
(2, 'pending', 'completed', NOW() - INTERVAL '10 days', 2); 


INSERT INTO order_status_history (order_id, old_status, new_status, changed_at, changed_by) VALUES
(3, 'pending', 'completed', NOW() - INTERVAL '5 days', 2);


INSERT INTO order_status_history (order_id, old_status, new_status, changed_at, changed_by) VALUES
(4, 'pending', 'canceled', NOW() - INTERVAL '15 days', 4); 



INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, performed_at) VALUES
('product', 1, 'insert', 1, NOW() - INTERVAL '30 days'),
('product', 2, 'insert', 1, NOW() - INTERVAL '30 days'),
('product', 3, 'insert', 1, NOW() - INTERVAL '30 days'),
('product', 4, 'insert', 1, NOW() - INTERVAL '30 days'),
('product', 5, 'insert', 1, NOW() - INTERVAL '30 days');


INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, performed_at) VALUES
('order', 2, 'update', 2, NOW() - INTERVAL '10 days'),
('order', 3, 'update', 2, NOW() - INTERVAL '5 days');


INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, performed_at) VALUES
('order', 1, 'insert', 3, NOW() - INTERVAL '2 days'),
('order', 3, 'insert', 3, NOW() - INTERVAL '5 days'),
('order', 4, 'insert', 4, NOW() - INTERVAL '15 days'),
('order', 4, 'update', 4, NOW() - INTERVAL '15 days'); 



UPDATE products SET price = 66000.00 WHERE product_id = 1;