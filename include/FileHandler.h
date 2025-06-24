#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Inventory.h"
#include <string>

class FileHandler {
private:
    std::string filename;

public:
    FileHandler(const std::string& fname);
    bool saveInventory(const Inventory& inventory) const;
    bool loadInventory(Inventory& inventory) const;
};

#endif

