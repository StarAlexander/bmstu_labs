CREATE OR REPLACE FUNCTION getOrderStatus(order_id_param INTEGER)
RETURNS VARCHAR AS $$
    SELECT status FROM orders WHERE order_id = order_id_param;
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION getUserOrderCount(user_id_param INTEGER)
RETURNS INTEGER AS $$
    SELECT COUNT(*) FROM orders WHERE user_id = user_id_param;
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION getTotalSpentByUser(user_id_param INTEGER)
RETURNS DECIMAL(10, 2) AS $$
    SELECT COALESCE(SUM(total_price), 0) FROM orders
    WHERE user_id = user_id_param AND status = 'completed';
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION canReturnOrder(order_id_param INTEGER)
RETURNS BOOLEAN AS $$
    SELECT
        status = 'completed' AND
        order_date >= NOW() - INTERVAL '30 days'
    FROM orders
    WHERE order_id = order_id_param;
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION getOrderStatusHistory(order_id_param INTEGER)
RETURNS TABLE (
    history_id INTEGER,
    old_status VARCHAR,
    new_status VARCHAR,
    changed_at TIMESTAMP,
    changed_by_name VARCHAR
) AS $$
    SELECT h.history_id, h.old_status, h.new_status, h.changed_at, u.name
    FROM order_status_history h
    JOIN users u ON h.changed_by = u.user_id
    WHERE h.order_id = order_id_param
    ORDER BY h.changed_at;
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION getAuditLogByUser(user_id_param INTEGER)
RETURNS TABLE (
    log_id INTEGER,
    entity_type VARCHAR,
    entity_id INTEGER,
    operation VARCHAR,
    performed_at TIMESTAMP
) AS $$
    SELECT log_id, entity_type, entity_id, operation, performed_at
    FROM audit_log
    WHERE performed_by = user_id_param
    ORDER BY performed_at DESC;
$$ LANGUAGE sql;