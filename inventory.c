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

int isProductExists(const char* id) {
    FILE* f = fopen("product.txt", "r");
    if (!f) return 0;

    char pid[10], name[50];
    float price;
    while (fscanf(f, "%s %s %f", pid, name, &price) == 3) {
        if (strcmp(pid, id) == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void addstock() {
    if (stockCount >= MAX) {
        printf("Stock storage is full.\n");
        return;
    }

    Inventory newItem;

    printf("Enter product ID: ");
    fgets(newItem.productId, sizeof(newItem.productId), stdin);
    newItem.productId[strcspn(newItem.productId, "\n")] = 0;

    if (!isProductExists(newItem.productId)) {
        printf("Product ID not found in product list.\n");
        return;
    }

    printf("Enter product name: ");
    fgets(newItem.productName, sizeof(newItem.productName), stdin);
    newItem.productName[strcspn(newItem.productName, "\n")] = 0;

    printf("Enter quantity: ");
    if (scanf("%d", &newItem.quantity) != 1 || newItem.quantity < 0) {
        printf("Invalid input for quantity.\n");
        flushInput();
        return;
    }

    printf("Enter threshold for low stock alert: ");
    if (scanf("%d", &newItem.threshold) != 1 || newItem.threshold < 0) {
        printf("Invalid input for threshold.\n");
        flushInput();
        return;
    }
    flushInput();

    strcpy(newItem.status, "live");
    stock[stockCount++] = newItem;
    printf("Stock added successfully.\n");
}

void updatestock() {
    viewstock();
    char id[10];
    int newThreshold;
    printf("\nEnter product ID to update threshold: ");
    scanf("%9s", id);
    flushInput();

    for (int i = 0; i < stockCount; i++) {
        if (strcmp(stock[i].productId, id) == 0) {
            printf("Current threshold: %d\n", stock[i].threshold);
            printf("Enter new threshold: ");
            if (scanf("%d", &newThreshold) != 1 || newThreshold < 0) {
                printf("Invalid threshold.\n");
                flushInput();
                return;
            }
            stock[i].threshold = newThreshold;
            printf("Threshold updated successfully.\n");
            flushInput();
            return;
        }
    }
    printf("Product ID not found.\n");
}

void updatestatus() {
    viewstock();
    char id[10];
    char newStatus[15];
    printf("\nEnter product ID to update status: ");
    scanf("%9s", id);
    flushInput();

    for (int i = 0; i < stockCount; i++) {
        if (strcmp(stock[i].productId, id) == 0) {
            printf("Current status: %s\n", stock[i].status);
            printf("Enter new status (live/discontinued): ");
            fgets(newStatus, sizeof(newStatus), stdin);
            newStatus[strcspn(newStatus, "\n")] = 0;

            if (strcmp(newStatus, "live") != 0 && strcmp(newStatus, "discontinued") != 0) {
                printf("Invalid status. Use 'live' or 'discontinued'.\n");
                return;
            }

            strcpy(stock[i].status, newStatus);
            printf("Status updated successfully.\n");
            return;
        }
    }
    printf("Product ID not found.\n");
}

void removestock() {
    for (int i = 0; i < stockCount; i++) {
        if (strcmp(stock[i].status, "live") == 0 && stock[i].quantity == 0) {
            strcpy(stock[i].status, "discontinued");
        }
    }
    printf("All discontinued items marked successfully.\n");
}

void viewstock() {
    printf("\nCurrent Inventory:\n");
    for (int i = 0; i < stockCount; i++) {
        printf("ID: %s, Name: %s, Quantity: %d, Threshold: %d, Status: %s\n",
               stock[i].productId, stock[i].productName,
               stock[i].quantity, stock[i].threshold, stock[i].status);
    }
}

void lowstockAlert() {
    printf("\nLow Stock Alerts:\n");
    for (int i = 0; i < stockCount; i++) {
        if (stock[i].quantity < stock[i].threshold && strcmp(stock[i].status, "live") == 0) {
            printf("Product %s (%s) is low on stock. Quantity: %d\n",
                   stock[i].productId, stock[i].productName, stock[i].quantity);
        }
    }
}

void reportInventory() {
    int option;
    char input[50];
    printf("\nInventory Report Options:\n1. Report by Product ID\n2. Report by Status\nChoose option: ");
    scanf("%d", &option);
    flushInput();

    if (option == 1) {
        printf("Enter Product ID: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        for (int i = 0; i < stockCount; i++) {
            if (strcmp(stock[i].productId, input) == 0) {
                printf("ID: %s, Name: %s, Quantity: %d, Threshold: %d, Status: %s\n",
                       stock[i].productId, stock[i].productName,
                       stock[i].quantity, stock[i].threshold, stock[i].status);
                return;
            }
        }
        printf("Product not found.\n");
    } else if (option == 2) {
        printf("Enter Status (live/discontinued): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        for (int i = 0; i < stockCount; i++) {
            if (strcmp(stock[i].status, input) == 0) {
                printf("ID: %s, Name: %s, Quantity: %d, Threshold: %d, Status: %s\n",
                       stock[i].productId, stock[i].productName,
                       stock[i].quantity, stock[i].threshold, stock[i].status);
            }
        }
    } else {
        printf("Invalid option.\n");
    }
}

void saveInventory() {
    FILE* f = fopen("inventory.txt", "w");
    if (!f) {
        printf("Failed to open inventory file for saving.\n");
        return;
    }
    for (int i = 0; i < stockCount; i++) {
        fprintf(f, "%s %s %d %d %s\n",
                stock[i].productId, stock[i].productName,
                stock[i].quantity, stock[i].threshold, stock[i].status);
    }
    fclose(f);
    printf("Inventory successfully saved.\n");
}

void loadInventory() {
    FILE* f = fopen("inventory.txt", "r");
    if (!f) {
        printf("Inventory file not found, starting with empty inventory.\n");
        return;
    }

    Inventory tempItem;
    stockCount = 0;
    while (fscanf(f, "%9s %49s %d %d %9s",
                  tempItem.productId, tempItem.productName,
                  &tempItem.quantity, &tempItem.threshold, tempItem.status) == 5) {
        if (stockCount < MAX) {
            stock[stockCount++] = tempItem;
        }
    }
    fclose(f);
}

void inventoryMenu() {
    loadInventory();
    int choice;
    do {
        printf("\nInventory Management Menu:\n");
        printf("1. Add Stock Inventory Records\n");
        printf("2. Update Stock Thresholds\n");
        printf("3. Remove Discontinued Stock (status-based)\n");
        printf("4. View Current Inventory Levels and Status\n");
        printf("5. Low Stock Alerts\n");
        printf("6. Inventory Reporting (by ID or status)\n");
        printf("7. Update Product Status (live/discontinued)\n");
        printf("0. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        flushInput();

        switch (choice) {
            case 1: addstock(); break;
            case 2: updatestock(); break;
            case 3: removestock(); break;
            case 4: viewstock(); break;
            case 5: lowstockAlert(); break;
            case 6: reportInventory(); break;
            case 7: updatestatus(); break;
            case 0: saveInventory(); printf("Exiting. Inventory saved.\n"); break;
            default: printf("Invalid choice.\n"); break;
        }
    } while (choice != 0);
}
