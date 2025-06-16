// inventory.h 
#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCT_NAME_LENGTH 50
#define MAX_DATE_LENGTH 20

typedef struct InventoryItem {
    int productId;
    char productName[MAX_PRODUCT_NAME_LENGTH];
    int quantityInStock;
    int reorderThreshold;
    char lastUpdated[MAX_DATE_LENGTH];
    struct InventoryItem *next;
} InventoryItem;

void runInventoryManagementMenu(InventoryItem **head_ptr); 

InventoryItem* loadInventoryFromFile(const char *filename);
void saveInventoryToFile(const char *filename, InventoryItem *head);
void addStockRecord(InventoryItem **head);
void updateStockLevels(InventoryItem *head);
void removeStockItem(InventoryItem **head);
void viewCurrentInventory(InventoryItem *head);
void checkLowStockAlerts(InventoryItem *head);
void generateInventoryReport(InventoryItem *head);
void freeInventoryList(InventoryItem *head);

#endif // INVENTORY_H