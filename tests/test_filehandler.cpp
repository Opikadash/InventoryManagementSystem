#include <gtest/gtest.h>
#include "FileHandler.h"
#include <cstdio> // For remove()

TEST(FileHandlerTest, SaveAndLoadInventory) {
    const std::string testfile = "test_inventory.txt";
    Inventory inv;
    inv.addItem(Item(1, "Laptop", 5, 1000.0, "Electronics"));
    inv.addItem(Item(2, "Mouse", 10, 20.0, "Accessories"));

    FileHandler fh(testfile);
    EXPECT_TRUE(fh.saveInventory(inv));

    Inventory loaded;
    EXPECT_TRUE(fh.loadInventory(loaded));
    const auto& items = loaded.getItems();
    ASSERT_EQ(2, items.size());
    EXPECT_EQ("Laptop", items[0].getName());
    EXPECT_EQ("Mouse", items[1].getName());

    // Clean up test file
    std::remove(testfile.c_str());
}
