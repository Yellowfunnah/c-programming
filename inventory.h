#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX 100


typedef struct InventoryItem {
    char productId[10];
    char productName[50];
    int quantity;
    int threshold;
} Inventory;

extern Inventory stock[MAX];
extern int stockCount;

void addstock();
void updatestock();
void removestock();
void viewstock();
void lowstockAlert();
void saveInventory();
void loadInventory();
void inventoryMenu();


#endif