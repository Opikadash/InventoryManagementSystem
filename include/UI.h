#ifndef UI_H
#define UI_H

#include "Inventory.h"
#include "FileHandler.h"
#include <windows.h>

class UI {
private:
    HWND hwnd;
    HWND hwndListView;
    HWND hwndAddButton, hwndUpdateButton, hwndDeleteButton, hwndSearchButton;
    HWND hwndIdEdit, hwndNameEdit, hwndQtyEdit, hwndPriceEdit, hwndCatEdit, hwndSearchEdit;
    Inventory& inventory;
    FileHandler& fileHandler;

    void initializeControls();
    void populateListView();
    void addItem();
    void updateItem();
    void deleteItem();
    void searchItems();

public:
    UI(HWND h, Inventory& inv, FileHandler& fh);
    void handleCommand(WPARAM wParam);
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif

