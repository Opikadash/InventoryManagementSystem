cmake_minimum_required(VERSION 3.10)
project(InventoryManagementSystem)

set(CMAKE_CXX_STANDARD 17)

# Include headers
include_directories(include)

# Main application
add_executable(InventorySystem
    src/main.cpp
    src/Item.cpp
    src/FileHandler.cpp
    src/UI.cpp
    src/Inventory.cpp
)

# Link Win32 common controls for GUI
target_link_libraries(InventorySystem comctl32)

# Google Test
# Add googletest as a subdirectory (assumes you cloned it to ./googletest)
add_subdirectory(googletest)

enable_testing()

add_executable(runTests
    tests/test_item.cpp
    tests/test_filehandler.cpp
    tests/test_inventory.cpp
    src/Item.cpp
    src/Inventory.cpp
    src/FileHandler.cpp
)

target_link_libraries(runTests gtest gtest_main)

add_test(NAME AllTests COMMAND runTests)
