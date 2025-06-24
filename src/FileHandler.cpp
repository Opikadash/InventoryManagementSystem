#include "FileHandler.h"
#include <fstream>
#include <sstream>

FileHandler::FileHandler(const std::string& fname) : filename(fname) {}

bool FileHandler::saveInventory(const Inventory& inventory) const {
    std::ofstream ofs(filename);
    if (!ofs) return false;

    for (const auto& item : inventory.getItems()) {
        ofs << item.getId() << "," << item.getName() << "," << item.getQuantity() << ","
            << item.getPrice() << "," << item.getCategory() << "\n";
    }
    ofs.close();
    return true;
}

bool FileHandler::loadInventory(Inventory& inventory) const {
    std::ifstream ifs(filename);
    if (!ifs) return false;

    inventory.clear();
    std::string line;
    while (std::getline(ifs, line)) {
        std::stringstream ss(line);
        std::string id, name, qty, price, category;
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, qty, ',');
        std::getline(ss, price, ',');
        std::getline(ss, category, ',');
        try {
            inventory.addItem(Item(std::stoi(id), name, std::stoi(qty), std::stod(price), category));
        } catch (...) {
            continue;
        }
    }
    ifs.close();
    return true;
}
