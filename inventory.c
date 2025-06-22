#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Inventory stock[MAX];
int stockCount = 0;

void addstock(){
    if (stockCount >= MAX) {
        printf("stock storage is full.\n");
        return;
    }
    printf("Enter product ID: ");
    scanf("%d", &stock[stockCount].productId);
    printf("Enter product name: ");
    scanf("%s", stock[stockCount].productName);
    printf("Enter quantity: ");
    scanf("%d", &stock[stockCount].quantity);
    printf("Enter threshold for low stock alert: ");
    scanf("%d", &stock[stockCount].threshold);
    stockCount++;
    printf("Stock added successfully.\n");
}

void updatestock() {
    int id, change, found = 0;
    printf("Enter product ID to update stock: ");
    scanf("%d", &id);
    for (int i = 0; i < stockCount; i++) {
        if (stock[i].productId == id) {
            printf("Current quantity: %d\n", stock[i].quantity);
            printf("Enter change in quantity (positive to add, negative to remove): ");
            scanf("%d", &change);
            stock[i].quantity += change;
            if (stock[i].quantity < 0) stock[i].quantity = 0; // Prevent negative stock
            printf("Stock updated successfully. New quantity: %d\n", stock[i].quantity);
            found = 1;
            break;

        }
                
    }
    if (!found) {
        printf("Product ID not found.\n");
    }
}

void removestock() {
    int id, found = 0;
    printf("Enter product ID to remove: ");
    scanf("%d", &id);
    for (int i = 0; i < stockCount; i++) {
        if (stock[i].productId == id) {
            for (int j = i; j < stockCount - 1; j++) {
                stock[j] = stock[j + 1]; // Shift items left
            }
            stockCount--;
            printf("Stock removed successfully.\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Product ID not found.\n");
    }
}

void viewstock() {
    printf("\nCurrent Inventory:\n");
    for (int i = 0; i < stockCount; i++) {
        printf("ID: %d, Name: %s, Quantity: %d, Threshold: %d\n",
               stock[i].productId, stock[i].productName,
               stock[i].quantity, stock[i].threshold);
    }
}

void lowstockAlert() {
    printf("\nLow Stock Items:\n");
    for (int i = 0; i < stockCount; i++) {
        if (stock[i].quantity <= stock[i].threshold) {
            printf("ID: %d, Name: %s, Quantity: %d\n",
                   stock[i].productId, stock[i].productName,
                   stock[i].quantity);
        }    
    }
}

void saveInventory() {
    FILE *f = fopen("inventory.txt", "w");
    for (int i = 0; i < stockCount; i++) {
        fprintf(f,"%d %s %d %d\n",
                stock[i].productId, stock[i].productName,
                stock[i].quantity, stock[i].threshold);
        }
    fclose(f);
}

void loadInventory() {
    FILE *f = fopen("inventory.txt", "r");
    if (f == NULL) {
        while (fscanf(f, "%d %s %d %d",
               &stock[stockCount].productId,
               stock[stockCount].productName,
               &stock[stockCount].quantity,
               &stock[stockCount].threshold) != EOF) {
            stockCount++;
        }
        fclose(f);
    }
}

void inventoryMenu() {
    int choice;
    do {
        printf("\n===== Inventory Management Menu =====\n");
        printf("1. Add Stock\n2. Update Stock\n3. Remove Stock\n4. View Stock\n5. Low Stock Alert\n6. Save & Exit\nChoose: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addstock(); break;
            case 2: updatestock(); break;
            case 3: removestock(); break;
            case 4: viewstock(); break;
            case 5: lowstockAlert(); break;
            case 6: saveInventory(); break;
            default: printf("Invalid option.\n");
        }
    } while (choice != 6);
}