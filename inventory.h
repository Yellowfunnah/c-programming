#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX 100

typedef struct InventoryItem {
    char productId[10];
    char productName[50];
    int quantity;
    int threshold;
    char status[10];
} Inventory;

extern Inventory stock[MAX];
extern int stockCount;

void flushInput();
void addstock();
void updatestock();
void updatestatus();
void removestock();
void viewstock();
void lowstockAlert();
void reportInventory();
void saveInventory();
void loadInventory();
void inventoryMenu();
int isProductExists(const char* id);
int getProductDetails(const char* id, char* nameOut, float* priceOut);
#endif