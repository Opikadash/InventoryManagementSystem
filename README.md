Here is a professional GitHub repository description tailored for your Inventory Management System project, clearly highlighting the two parts: one using file handling and the other using database integration.

---

# Inventory Management System

Welcome to the **Inventory Management System** — a comprehensive C++ project designed to demonstrate two robust approaches for managing inventory data efficiently and effectively.

---

## Overview

This repository contains two distinct implementations of an inventory management system:

### 1. File Handler Based Inventory Management

- Utilizes traditional file I/O operations to store and manage inventory data in text files.
- Implements core functionalities such as adding, updating, deleting, and searching inventory items.
- Features a Win32 API-based graphical user interface (GUI) for seamless user interaction.
- Ideal for learning purposes and small-scale applications where simplicity and quick setup are priorities.

### 2. Database Integration Based Inventory Management

- Employs SQLite as a lightweight, embedded database to persist inventory data.
- Encapsulates database operations within a dedicated `DatabaseHandler` module, providing SQL-based CRUD (Create, Read, Update, Delete) functionality.
- Offers enhanced scalability, data integrity, and query capabilities compared to file-based storage.
- Maintains the same Win32 API GUI, now backed by a robust database backend, suitable for real-world applications.

---

## Features

- Object-Oriented Design with clear separation of concerns.
- User-friendly Win32 API GUI with list views, input forms, and control buttons.
- Two persistence options: file-based and SQLite database-based.
- Unit testing implemented using Google Test framework.
- Modular codebase facilitating easy extension and maintenance.

---

## Getting Started

### Prerequisites

- C++17 compatible compiler (GCC 9+ recommended or MSVC)
- CMake 3.10 or higher
- Windows OS (for Win32 GUI)
- SQLite3 (for database integration)
- Google Test (for unit testing)

### Building the Project

1. Clone the repository.
2. Navigate to the project directory.
3. Choose your preferred implementation:
   - For file handler version, build the `InventorySystem` target with file I/O source files.
   - For database integration, include `DatabaseHandler.cpp` and `sqlite3.c` in the build.
4. Use CMake to configure and build the project.
5. Run the executable to launch the GUI.

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
Feel free to fork the repository and submit pull requests.

---

## License

This project is licensed under the MIT License.

---

