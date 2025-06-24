#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include "Item.h"
#include <vector>
#include <string>
#include <sqlite3.h>

class DatabaseHandler {
private:
    sqlite3* db;
    std::string dbName;
public:
    DatabaseHandler(const std::string& dbName);
    ~DatabaseHandler();
    bool open();
    void close();
    bool createTable();
    bool addItem(const Item& item);
    bool updateItem(const Item& item);
    bool deleteItem(int id);
    std::vector<Item> getAllItems();
    std::vector<Item> searchByName(const std::string& name);
};

#endif

