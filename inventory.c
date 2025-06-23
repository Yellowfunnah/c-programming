#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

Inventory stock[MAX];
int stockCount = 0;

void flushInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addstock() {
    if (stockCount >= MAX) {
        printf("Stock storage is full.\n");
        return;
    }

    Inventory newItem;

    printf("Enter product ID: \n");
    fgets(newItem.productId, sizeof(newItem.productId), stdin);
    newItem.productId[strcspn(newItem.productId, "\n")] = 0;

    printf("Enter product name: \n");
    fgets(newItem.productName, sizeof(newItem.productName), stdin);
    newItem.productName[strcspn(newItem.productName, "\n")] = 0;

    printf("Enter quantity: \n");
    if (scanf("%d", &newItem.quantity) != 1 || newItem.quantity < 0) {
        printf("Invalid input for quantity.\n");
        flushInput();
        return;
    }

    printf("Enter threshold for low stock alert: \n");
    if (scanf("%d", &newItem.threshold) != 1 || newItem.threshold < 0) {
        printf("Invalid input for threshold.\n");
        flushInput();
        return;
    }

    flushInput();
    stock[stockCount++] = newItem;
    printf("Stock added successfully.\n");
}

void updatestock() {
    char id[10];
    int change;
    printf("Enter product ID to update stock: ");
    scanf("%9s", id);
    flushInput();

    int found = 0;
    for (int i = 0; i < stockCount; i++) {
        if (strcmp(stock[i].productId, id) == 0) {
            printf("Current quantity: %d\n", stock[i].quantity);
            printf("Enter change in quantity (positive to add, negative to remove): ");
            if (scanf("%d", &change) != 1) {
                printf("Invalid input for quantity change.\n");
                flushInput();
                return;
            }
            if (stock[i].quantity + change < 0) {
                printf("Error: Quantity cannot be negative.\n");
                return;
            }
            stock[i].quantity += change;
            printf("Stock updated successfully. New quantity: %d\n", stock[i].quantity);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Product ID not found.\n");
    }
    flushInput();
}

void removestock() {
    char id[10];
    int found = 0;
    printf("Enter product ID to remove: ");
    scanf("%9s", id);
    flushInput();

    for (int i = 0; i < stockCount; i++) {
        if (strcmp(stock[i].productId, id) == 0) {
            for (int j = i; j < stockCount - 1; j++) {
                stock[j] = stock[j + 1];
            }
            stockCount--;
            found = 1;
            printf("Product removed successfully.\n");
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
        printf("ID: %s, Name: %s, Quantity: %d, Threshold: %d\n",
               stock[i].productId, stock[i].productName,
               stock[i].quantity, stock[i].threshold);
    }
}

void lowstockAlert() {
    printf("\nLow Stock Alerts:\n");
    for (int i = 0; i < stockCount; i++) {
        if (stock[i].quantity < stock[i].threshold) {
            printf("Product %s (%s) is low on stock. Quantity: %d\n",
                   stock[i].productId, stock[i].productName, stock[i].quantity);
        }
    }
}

void saveInventory() {
    FILE *f = fopen("inventory.txt", "w");
    if (f == NULL) {
        printf("Failed to open inventory file for saving.\n");
        return;
    }
    for (int i = 0; i < stockCount; i++) {
        fprintf(f, "%s %s %d %d\n",
                stock[i].productId, stock[i].productName,
                stock[i].quantity, stock[i].threshold);
    }
    fclose(f);
    printf("Inventory successfully saved.\n");
}

void loadInventory() {
    FILE *f = fopen("inventory.txt", "r");
    if (f != NULL) {
        stockCount = 0;
        while (fscanf(f, "%9s %49s %d %d",
                      stock[stockCount].productId,
                      stock[stockCount].productName,
                      &stock[stockCount].quantity,
                      &stock[stockCount].threshold) == 4) {
            stockCount++;
            if (stockCount >= MAX) {
                printf("Inventory loaded reached max capacity, some items may not be loaded.\n");
                break;
            }
        }
        fclose(f);
    } else {
        printf("Inventory file not found, starting with an empty inventory.\n");
    }
}

void inventoryMenu() {
    int choice;
    do {
        printf("\nInventory Management Menu:\n");
        printf("1. Add Stock\n");
        printf("2. Update Stock\n");
        printf("3. Remove Stock\n");
        printf("4. View Stock\n");
        printf("5. Low Stock Alert\n");
        printf("6. Save Inventory\n");
        printf("7. Load Inventory\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        flushInput();

        switch (choice) {
            case 1: addstock(); break;
            case 2: updatestock(); break;
            case 3: removestock(); break;
            case 4: viewstock(); break;
            case 5: lowstockAlert(); break;
            case 6: saveInventory(); break;
            case 7: loadInventory(); break;
            case 0: printf("Exiting Inventory Menu.\n"); break;
            default: printf("Invalid choice.\n"); break;
        }
    } while (choice != 0);
}
