#include <gtest/gtest.h>
#include "Inventory.h"

TEST(InventoryTest, AddAndGetItems) {
    Inventory inv;
    Item item1(1, "Laptop", 5, 1000.0, "Electronics");
    Item item2(2, "Mouse", 10, 20.0, "Accessories");
    inv.addItem(item1);
    inv.addItem(item2);

    const auto& items = inv.getItems();
    ASSERT_EQ(2, items.size());
    EXPECT_EQ("Laptop", items[0].getName());
    EXPECT_EQ("Mouse", items[1].getName());
}

TEST(InventoryTest, UpdateItem) {
    Inventory inv;
    inv.addItem(Item(1, "Laptop", 5, 1000.0, "Electronics"));
    EXPECT_TRUE(inv.updateItem(1, 10, 900.0, "Computers"));
    const auto& items = inv.getItems();
    EXPECT_EQ(10, items[0].getQuantity());
    EXPECT_DOUBLE_EQ(900.0, items[0].getPrice());
    EXPECT_EQ("Computers", items[0].getCategory());
}

TEST(InventoryTest, DeleteItem) {
    Inventory inv;
    inv.addItem(Item(1, "Laptop", 5, 1000.0, "Electronics"));
    EXPECT_TRUE(inv.deleteItem(1));
    EXPECT_TRUE(inv.getItems().empty());
    EXPECT_FALSE(inv.deleteItem(2)); // Non-existent
}

TEST(InventoryTest, SearchByNameAndCategory) {
    Inventory inv;
    inv.addItem(Item(1, "Laptop", 5, 1000.0, "Electronics"));
    inv.addItem(Item(2, "Mouse", 10, 20.0, "Accessories"));
    inv.addItem(Item(3, "Keyboard", 7, 50.0, "Accessories"));

    auto results = inv.searchByName("Lap");
    ASSERT_EQ(1, results.size());
    EXPECT_EQ("Laptop", results[0].getName());

    results = inv.searchByCategory("Accessories");
    ASSERT_EQ(2, results.size());
}

