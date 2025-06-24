#include "UI.h"
#include <commctrl.h>
#include <cstring>
#include <cstdio>

UI* g_ui = nullptr;

UI::UI(HWND h, Inventory& inv, FileHandler& fh)
    : hwnd(h), inventory(inv), fileHandler(fh) {
    initializeControls();
    fileHandler.loadInventory(inventory);
    populateListView();
}

void UI::initializeControls() {
    InitCommonControls();

    hwndListView = CreateWindow(WC_LISTVIEW, "", WS_CHILD | WS_VISIBLE | LVS_REPORT,
        20, 20, 540, 200, hwnd, (HMENU)100, GetModuleHandle(NULL), NULL);

    LVCOLUMN col;
    col.mask = LVCF_TEXT | LVCF_WIDTH;
    col.pszText = (char*)"ID"; col.cx = 60; ListView_InsertColumn(hwndListView, 0, &col);
    col.pszText = (char*)"Name"; col.cx = 150; ListView_InsertColumn(hwndListView, 1, &col);
    col.pszText = (char*)"Quantity"; col.cx = 100; ListView_InsertColumn(hwndListView, 2, &col);
    col.pszText = (char*)"Price"; col.cx = 100; ListView_InsertColumn(hwndListView, 3, &col);
    col.pszText = (char*)"Category"; col.cx = 110; ListView_InsertColumn(hwndListView, 4, &col);

    hwndIdEdit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
        20, 240, 80, 25, hwnd, (HMENU)101, GetModuleHandle(NULL), NULL);
    hwndNameEdit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
        120, 240, 120, 25, hwnd, (HMENU)102, GetModuleHandle(NULL), NULL);
    hwndQtyEdit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
        260, 240, 80, 25, hwnd, (HMENU)103, GetModuleHandle(NULL), NULL);
    hwndPriceEdit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
        360, 240, 80, 25, hwnd, (HMENU)104, GetModuleHandle(NULL), NULL);
    hwndCatEdit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
        460, 240, 100, 25, hwnd, (HMENU)105, GetModuleHandle(NULL), NULL);

    hwndAddButton = CreateWindow("BUTTON", "Add", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 280, 80, 30, hwnd, (HMENU)201, GetModuleHandle(NULL), NULL);
    hwndUpdateButton = CreateWindow("BUTTON", "Update", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        120, 280, 80, 30, hwnd, (HMENU)202, GetModuleHandle(NULL), NULL);
    hwndDeleteButton = CreateWindow("BUTTON", "Delete", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        220, 280, 80, 30, hwnd, (HMENU)203, GetModuleHandle(NULL), NULL);
    hwndSearchButton = CreateWindow("BUTTON", "Search", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        320, 280, 80, 30, hwnd, (HMENU)204, GetModuleHandle(NULL), NULL);

    hwndSearchEdit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
        420, 280, 140, 25, hwnd, (HMENU)106, GetModuleHandle(NULL), NULL);
}

void UI::populateListView() {
    ListView_DeleteAllItems(hwndListView);
    const std::vector<Item>& items = inventory.getItems();
    for (size_t i = 0; i < items.size(); ++i) {
        const Item& item = items[i];
        LVITEM lvi = { 0 };
        lvi.mask = LVIF_TEXT;
        lvi.iItem = (int)i;

        char id[10]; sprintf(id, "%d", item.getId());
        lvi.pszText = id;
        ListView_InsertItem(hwndListView, &lvi);

        char name[256]; strncpy(name, item.getName().c_str(), sizeof(name)); name[sizeof(name)-1] = '\0';
        ListView_SetItemText(hwndListView, (int)i, 1, name);

        char qty[10]; sprintf(qty, "%d", item.getQuantity());
        ListView_SetItemText(hwndListView, (int)i, 2, qty);

        char price[20]; sprintf(price, "%.2f", item.getPrice());
        ListView_SetItemText(hwndListView, (int)i, 3, price);

        char cat[256]; strncpy(cat, item.getCategory().c_str(), sizeof(cat)); cat[sizeof(cat)-1] = '\0';
        ListView_SetItemText(hwndListView, (int)i, 4, cat);
    }
}

void UI::addItem() {
    char idStr[16], name[256], qtyStr[16], priceStr[32], cat[256];
    GetWindowText(hwndIdEdit, idStr, 16);
    GetWindowText(hwndNameEdit, name, 256);
    GetWindowText(hwndQtyEdit, qtyStr, 16);
    GetWindowText(hwndPriceEdit, priceStr, 32);
    GetWindowText(hwndCatEdit, cat, 256);

    int id = atoi(idStr);
    int qty = atoi(qtyStr);
    double price = atof(priceStr);

    if (id > 0 && strlen(name) > 0 && qty >= 0 && price >= 0) {
        inventory.addItem(Item(id, name, qty, price, cat));
        fileHandler.saveInventory(inventory);
        populateListView();
        MessageBox(hwnd, "Item added successfully!", "Success", MB_OK);
    } else {
        MessageBox(hwnd, "Invalid input!", "Error", MB_OK | MB_ICONERROR);
    }
}

void UI::updateItem() {
    char idStr[16], qtyStr[16], priceStr[32], cat[256];
    GetWindowText(hwndIdEdit, idStr, 16);
    GetWindowText(hwndQtyEdit, qtyStr, 16);
    GetWindowText(hwndPriceEdit, priceStr, 32);
    GetWindowText(hwndCatEdit, cat, 256);

    int id = atoi(idStr);
    int qty = atoi(qtyStr);
    double price = atof(priceStr);

    if (inventory.updateItem(id, qty, price, cat)) {
        fileHandler.saveInventory(inventory);
        populateListView();
        MessageBox(hwnd, "Item updated successfully!", "Success", MB_OK);
    } else {
        MessageBox(hwnd, "Item not found!", "Error", MB_OK | MB_ICONERROR);
    }
}

void UI::deleteItem() {
    char idStr[16];
    GetWindowText(hwndIdEdit, idStr, 16);
    int id = atoi(idStr);

    if (inventory.deleteItem(id)) {
        fileHandler.saveInventory(inventory);
        populateListView();
        MessageBox(hwnd, "Item deleted successfully!", "Success", MB_OK);
    } else {
        MessageBox(hwnd, "Item not found!", "Error", MB_OK | MB_ICONERROR);
    }
}

void UI::searchItems() {
    char search[256];
    GetWindowText(hwndSearchEdit, search, 256);

    ListView_DeleteAllItems(hwndListView);
    std::vector<Item> results = inventory.searchByName(search);
    for (size_t i = 0; i < results.size(); ++i) {
        const Item& item = results[i];
        LVITEM lvi = { 0 };
        lvi.mask = LVIF_TEXT;
        lvi.iItem = (int)i;

        char id[10]; sprintf(id, "%d", item.getId());
        lvi.pszText = id;
        ListView_InsertItem(hwndListView, &lvi);

        char name[256]; strncpy(name, item.getName().c_str(), sizeof(name)); name[sizeof(name)-1] = '\0';
        ListView_SetItemText(hwndListView, (int)i, 1, name);

        char qty[10]; sprintf(qty, "%d", item.getQuantity());
        ListView_SetItemText(hwndListView, (int)i, 2, qty);

        char price[20]; sprintf(price, "%.2f", item.getPrice());
        ListView_SetItemText(hwndListView, (int)i, 3, price);

        char cat[256]; strncpy(cat, item.getCategory().c_str(), sizeof(cat)); cat[sizeof(cat)-1] = '\0';
        ListView_SetItemText(hwndListView, (int)i, 4, cat);
    }
}

void UI::handleCommand(WPARAM wParam) {
    switch (LOWORD(wParam)) {
    case 201: addItem(); break;
    case 202: updateItem(); break;
    case 203: deleteItem(); break;
    case 204: searchItems(); break;
    }
}

LRESULT CALLBACK UI::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static Inventory inventory;
    static FileHandler fileHandler("data/inventory.txt");
    switch (msg) {
    case WM_CREATE:
        g_ui = new UI(hwnd, inventory, fileHandler);
        break;
    case WM_COMMAND:
        if (g_ui) g_ui->handleCommand(wParam);
        break;
    case WM_DESTROY:
        delete g_ui;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
