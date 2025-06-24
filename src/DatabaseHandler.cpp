#include "DatabaseHandler.h"
#include <iostream>

DatabaseHandler::DatabaseHandler(const std::string& dbName) : db(nullptr), dbName(dbName) {}
DatabaseHandler::~DatabaseHandler() { close(); }

bool DatabaseHandler::open() {
    return sqlite3_open(dbName.c_str(), &db) == SQLITE_OK;
}

void DatabaseHandler::close() {
    if (db) sqlite3_close(db);
}

bool DatabaseHandler::createTable() {
    const char* sql = "CREATE TABLE IF NOT EXISTS items ("
                      "id INTEGER PRIMARY KEY, "
                      "name TEXT, "
                      "quantity INTEGER, "
                      "price REAL, "
                      "category TEXT);";
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool DatabaseHandler::addItem(const Item& item) {
    const char* sql = "INSERT INTO items (id, name, quantity, price, category) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) return false;
    sqlite3_bind_int(stmt, 1, item.getId());
    sqlite3_bind_text(stmt, 2, item.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, item.getQuantity());
    sqlite3_bind_double(stmt, 4, item.getPrice());
    sqlite3_bind_text(stmt, 5, item.getCategory().c_str(), -1, SQLITE_TRANSIENT);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool DatabaseHandler::updateItem(const Item& item) {
    const char* sql = "UPDATE items SET name=?, quantity=?, price=?, category=? WHERE id=?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, item.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, item.getQuantity());
    sqlite3_bind_double(stmt, 3, item.getPrice());
    sqlite3_bind_text(stmt, 4, item.getCategory().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 5, item.getId());
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool DatabaseHandler::deleteItem(int id) {
    const char* sql = "DELETE FROM items WHERE id=?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) return false;
    sqlite3_bind_int(stmt, 1, id);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

std::vector<Item> DatabaseHandler::getAllItems() {
    std::vector<Item> items;
    const char* sql = "SELECT id, name, quantity, price, category FROM items;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) return items;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string name = (const char*)sqlite3_column_text(stmt, 1);
        int qty = sqlite3_column_int(stmt, 2);
        double price = sqlite3_column_double(stmt, 3);
        std::string cat = (const char*)sqlite3_column_text(stmt, 4);
        items.push_back(Item(id, name, qty, price, cat));
    }
    sqlite3_finalize(stmt);
    return items;
}

std::vector<Item> DatabaseHandler::searchByName(const std::string& name) {
    std::vector<Item> items;
    const char* sql = "SELECT id, name, quantity, price, category FROM items WHERE name LIKE ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) return items;
    std::string pattern = "%" + name + "%";
    sqlite3_bind_text(stmt, 1, pattern.c_str(), -1, SQLITE_TRANSIENT);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string name = (const char*)sqlite3_column_text(stmt, 1);
        int qty = sqlite3_column_int(stmt, 2);
        double price = sqlite3_column_double(stmt, 3);
        std::string cat = (const char*)sqlite3_column_text(stmt, 4);
        items.push_back(Item(id, name, qty, price, cat));
    }
    sqlite3_finalize(stmt);
    return items;
}
