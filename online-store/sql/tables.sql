CREATE TABLE IF NOT EXISTS users (
    user_id SERIAL PRIMARY KEY,
    name VARCHAR NOT NULL,
    email VARCHAR NOT NULL UNIQUE,
    role VARCHAR NOT NULL CHECK (role IN ('admin', 'manager', 'customer')),
    password_hash VARCHAR NOT NULL,
    loyalty_level INTEGER DEFAULT 0 CHECK (loyalty_level IN (0, 1))
);

CREATE TABLE IF NOT EXISTS products (
    product_id SERIAL PRIMARY KEY,
    name VARCHAR NOT NULL,
    price DECIMAL(10, 2) CHECK (price > 0),
    stock_quantity INTEGER CHECK (stock_quantity >= 0)
);

CREATE TABLE IF NOT EXISTS orders (
    order_id SERIAL PRIMARY KEY,
    user_id INTEGER REFERENCES users(user_id) ON DELETE CASCADE,
    status VARCHAR DEFAULT 'pending' CHECK (status IN ('pending', 'completed', 'canceled', 'returned')),
    total_price DECIMAL(10, 2),
    order_date TIMESTAMP DEFAULT NOW()
);

CREATE TABLE IF NOT EXISTS order_items (
    order_item_id SERIAL PRIMARY KEY,
    order_id INTEGER REFERENCES orders(order_id) ON DELETE CASCADE,
    product_id INTEGER REFERENCES products(product_id),
    quantity INTEGER,
    price DECIMAL(10, 2)
);

CREATE TABLE IF NOT EXISTS order_status_history (
    history_id SERIAL PRIMARY KEY,
    order_id INTEGER REFERENCES orders(order_id),
    old_status VARCHAR,
    new_status VARCHAR,
    changed_at TIMESTAMP DEFAULT NOW(),
    changed_by INTEGER REFERENCES users(user_id)
);

CREATE TABLE IF NOT EXISTS audit_log (
    log_id SERIAL PRIMARY KEY,
    entity_type VARCHAR NOT NULL CHECK (entity_type IN ('order', 'product', 'user')),
    entity_id INTEGER NOT NULL,
    operation VARCHAR NOT NULL CHECK (operation IN ('insert', 'update', 'delete')),
    performed_by INTEGER REFERENCES users(user_id),
    performed_at TIMESTAMP DEFAULT NOW()
);