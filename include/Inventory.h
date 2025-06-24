#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include <vector>
#include <string>

class Inventory {
private:
    std::vector<Item> items;

public:
    void addItem(const Item& item);
    bool updateItem(int id, int quantity, double price, std::string category);
    bool deleteItem(int id);
    std::vector<Item> searchByName(const std::string& name) const;
    std::vector<Item> searchByCategory(const std::string& category) const;
    const std::vector<Item>& getItems() const { return items; }
    void clear() { items.clear(); }
};

#endif

