
# Inventory Management System

Welcome to the **Inventory Management System** — a comprehensive C++ project demonstrating two robust approaches for managing inventory data with a Win32 GUI, file I/O, database integration, and unit testing.

---

## Overview

This repository contains two distinct implementations:

### 1. File Handler Based Inventory Management

- Uses standard file I/O to store and manage inventory data in text files.
- Implements adding, updating, deleting, and searching inventory items.
- Features a Win32 API graphical user interface (GUI).
- Ideal for educational use and small-scale applications.

### 2. Database Integration Based Inventory Management

- Uses SQLite as the backend database for persistent storage.
- Encapsulates all SQL operations in a `DatabaseHandler` module.
- Offers enhanced scalability, data integrity, and query capabilities.
- Maintains the same Win32 API GUI, now powered by a robust database backend.

---

## Features

- Object-oriented design for maintainability and extensibility.
- User-friendly Win32 GUI with list view, input forms, and control buttons.
- Two persistence options: file-based and SQLite database-based.
- Comprehensive unit testing with Google Test.
- Modular codebase and CMake-based build system.

---

## Getting Started

### Prerequisites

- C++17 compatible compiler (GCC 9+ recommended, or MSVC)
- CMake 3.10 or higher
- Windows OS (for GUI)
- SQLite3 (for database integration)
- **Google Test** (for unit testing)

---

### Cloning Google Test

To enable unit testing, clone the Google Test repository into your project root:

```sh
git clone https://github.com/google/googletest.git
```

This will create a `googletest/` directory.  
The provided `CMakeLists.txt` is configured to automatically build and link Google Test from this folder.

---

### Building the Project

1. Clone this repository.
2. (Optional) Clone Google Test as shown above.
3. Open a terminal (preferably MSYS2 MinGW UCRT64 shell for GCC/MinGW users).
4. Run:
   ```sh
   mkdir build
   cd build
   cmake .. -G "MinGW Makefiles"
   cmake --build .
   ```
5. Run the application:
   ```sh
   ./InventorySystem.exe
   ```
6. Run unit tests:
   ```sh
   ./runTests.exe
   ```
   or
   ```sh
   ctest
   ```

---

## Repository Structure

```
InventoryManagementSystem/
├── include/
│   ├── Item.h
│   ├── Inventory.h
│   ├── FileHandler.h
│   ├── DatabaseHandler.h
│   ├── UI.h
├── src/
│   ├── Item.cpp
│   ├── Inventory.cpp
│   ├── FileHandler.cpp
│   ├── DatabaseHandler.cpp
│   ├── UI.cpp
│   ├── main.cpp
│   ├── sqlite3.c
├── tests/
│   ├── test_item.cpp
│   ├── test_inventory.cpp
│   ├── test_database.cpp
├── googletest/
│   └── ... (cloned Google Test sources)
├── data/
│   ├── inventory.txt
│   ├── inventory.db
├── docs/
│   ├── README.md
├── CMakeLists.txt
```

---

## Contributing

Contributions, issues, and feature requests are welcome!  
Fork the repository and submit a pull request.

---

## License

This project is licensed under the MIT License.

---


