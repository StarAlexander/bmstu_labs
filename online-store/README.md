# Система интернет-магазина

## 3.1 Описание задачи

**Цель работы**: Реализация многоуровневой системы интернет-магазина на C++ с использованием PostgreSQL, отвечающей требованиям безопасности, целостности данных и объектно-ориентированного проектирования.

**Описание системы**:  
Система поддерживает три роли пользователей: **администратор**, **менеджер**, **покупатель**. Предусмотрены операции: создание/отмена/возврат заказов, управление товарами, оплата через разные стратегии, логирование изменений, транзакционная безопасность и генерация отчётов.

**Используемые технологии**:
- Язык программирования: **C++20**
- База данных: **PostgreSQL 14+**
- Библиотека для работы с БД: **libpqxx**
- Сборка: **CMake**

---

## 3.2 Архитектура проекта

### Классы и отношения
- **`User`** — абстрактный базовый класс с чисто виртуальными методами (`createOrder`, `viewOrderStatus`, `cancelOrder`).
- **Наследование**:
  - `Admin` — полный доступ.
  - `Manager` — управление заказами и складом.
  - `Customer` — работа со своими заказами.
- **Композиция**:
  - `Order` содержит `std::vector<std::unique_ptr<OrderItem>>` — элементы удаляются вместе с заказом.
  - `Order` владеет `std::unique_ptr<Payment>`.
- **Агрегация**:
  - `User` хранит `std::vector<std::shared_ptr<Order>>` — заказы могут существовать независимо.

### Шаблонный класс
- `DatabaseConnection<T>` — универсальный интерфейс к PostgreSQL через `libpqxx`, поддерживающий транзакции, процедуры, триггеры.

---

## 3.3 Работа с базой данных

### Таблицы
1. `users` — пользователи с ролями и loyalty-уровнем.
2. `products` — товары с ценой и остатком.
3. `orders` — заказы со статусами.
4. `order_items` — состав заказов.
5. `order_status_history` — история изменений статусов.
6. `audit_log` — журнал аудита.

### Ограничения
- `CHECK (price > 0)`, `CHECK (stock_quantity >= 0)`
- `UNIQUE (email)`

### Хранимые объекты
- **Процедуры**: `createOrder`, `updateOrderStatus`, `logAudit`
- **Функции**: `getOrderStatus`, `canReturnOrder`, `getAuditLogByUser`, `generate_audit_report`
- **Триггеры**:
  - Обновление `order_date` при смене статуса.
  - Обновление `total_price` при смене цены товара.
  - Логирование в `order_status_history` через процедуру (без триггера, т.к. нужен `changed_by`).

### Транзакции
Все критические операции (создание заказа, оплата, возврат) выполняются в транзакциях. При ошибке — `ROLLBACK` + запись в `audit_log`.

---

## 3.4 Умные указатели и STL

### Умные указатели
- `std::unique_ptr<OrderItem>` — композиция, автоматическое удаление.
- `std::unique_ptr<PaymentStrategy>` — стратегия оплаты.
- `std::shared_ptr<Order>` — агрегация, заказы могут использоваться в нескольких контекстах.

### STL и лямбды
- **Фильтрация заказов**:
  ```cpp
  std::vector<std::shared_ptr<Order>> pending;
  std::copy_if(orders_.begin(), orders_.end(), std::back_inserter(pending),
      [](const auto& o) { return o->getStatus() == "pending"; });
  ```

- **Агрегация**:
  ```cpp
  double total = std::accumulate(orders_.begin(), orders_.end(), 0.0,
  [](double sum, const auto& o) { return sum + o->getTotalPrice(); });
  ```

- **Проверка прав**:
  ```cpp
  auto canEdit = [](const User& u) { return u.getRole() == "admin" || u.getRole() == "manager"; };
  ```

## 3.5 Логика ролей и прав доступа

| Роль        | Возможности              | Ограничения                   |
| ----------- | ------------------------ | ----------------------------- |
| Admin       | Полный доступ            | -                             |
| Manager     | Работа со складом        | Аудит                         |
| Customer    | Работа с заказами        | Доступ только к своим заказам |


## 3.6 Аудит и история изменений


# Таблицы

- **order_status_history**: фиксирует все смены статусов с указанием пользователя.
- **audit_log**:логирует **insert**/**update**/**delete** для **order**,**product**,**user**.

# Механизм

- Запись в **audit_log** выполняется через процедуру **logAudit()**, вызываемую из C++.
- История статусов - через **updateOrderStatus()**.


## 3.7 Сборка и запуск проекта

# Требования

- Компилятор: GCC 11+ или CLang 14+
- БД: PostgreSQL 14+
- Библиотека: libpqxx
- Система: Linux,Windows (MSYS2), macOS


# Установка зависимостей (Ubuntu/Debian)

```bash
sudo apt install postgresql libpqxx-dev build-essential cmake
```

# Сборка

```bash
git clone https://github.com/StarAlexander/bmstu_labs.git
cd bmstu_labs/online-store
cmake -S . -B build
cmake --build build
```

# Пример работы

```bash
Role:
1. Admin
2. Manager
3. Customer
4. Exit
> 3
Enter User ID: 3

--- Customer Menu ---
1. Create Order
...
> 6
Order ID: 3
Payment method:
1. Card
2. E-Wallet
3. SBP
> 1
[PAY] Paid 800 via Credit Card
Payment successful. Order 3 completed.
```
