#include "Inventory.h"
#include <algorithm>
#include <cctype>

void Inventory::addItem(const Item& item) {
    items.push_back(item);
}

bool Inventory::updateItem(int id, int quantity, double price, std::string category) {
    for (auto& item : items) {
        if (item.getId() == id) {
            item.setQuantity(quantity);
            item.setPrice(price);
            item.setCategory(category);
            return true;
        }
    }
    return false;
}

bool Inventory::deleteItem(int id) {
    auto it = std::remove_if(items.begin(), items.end(),
        [id](const Item& item) { return item.getId() == id; });
    if (it != items.end()) {
        items.erase(it, items.end());
        return true;
    }
    return false;
}

std::vector<Item> Inventory::searchByName(const std::string& name) const {
    std::vector<Item> results;
    std::string lowerName = name;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    for (const auto& item : items) {
        std::string itemName = item.getName();
        std::transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);
        if (itemName.find(lowerName) != std::string::npos) {
            results.push_back(item);
        }
    }
    return results;
}

std::vector<Item> Inventory::searchByCategory(const std::string& category) const {
    std::vector<Item> results;
    std::string lowerCat = category;
    std::transform(lowerCat.begin(), lowerCat.end(), lowerCat.begin(), ::tolower);
    for (const auto& item : items) {
        std::string itemCat = item.getCategory();
        std::transform(itemCat.begin(), itemCat.end(), itemCat.begin(), ::tolower);
        if (itemCat.find(lowerCat) != std::string::npos) {
            results.push_back(item);
        }
    }
    return results;
}
