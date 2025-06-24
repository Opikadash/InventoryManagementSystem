#include <gtest/gtest.h>
#include "Item.h"

TEST(ItemTest, CreateItem) {
    Item item(1, "Laptop", 100, 999.99, "Electronics");
    EXPECT_EQ(1, item.getId());
    EXPECT_EQ("Laptop", item.getName());
    EXPECT_EQ(100, item.getQuantity());
    EXPECT_DOUBLE_EQ(999.99, item.getPrice());
    EXPECT_EQ("Electronics", item.getCategory());
}

TEST(ItemTest, UpdateAttributes) {
    Item item(2, "Mouse", 10, 19.99, "Accessories");
    item.setQuantity(20);
    item.setPrice(24.99);
    item.setCategory("Peripherals");
    EXPECT_EQ(20, item.getQuantity());
    EXPECT_DOUBLE_EQ(24.99, item.getPrice());
    EXPECT_EQ("Peripherals", item.getCategory());
}

