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

int getProductDetails(const char* id, char* nameOut, float* priceOut) {
    FILE* f = fopen("products.txt", "r");
    if (!f) {
        printf("Error opening products.txt\n");
        return 0;
    }

    char pid[10], pname[50], categoryId[10];
    float price;

    while (fscanf(f, "%s %s %f %s", pid, pname, &price, categoryId) == 4) {
        if (strcmp(pid, id) == 0) {
            strcpy(nameOut, pname);
            *priceOut = price;
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}
int isProductExists(const char* id) {
    FILE* f = fopen("products.txt", "r");
    if (!f) {
        printf("DEBUG: Could not open products.txt\n");
        return 0;
    }

    char pid[10], pname[50], categoryId[10];
    float price;

    while (fscanf(f, "%s %s %f %s", pid, pname, &price, categoryId) == 4) {
        if (strcmp(pid, id) == 0) {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

void displayAvailableProducts() {
    FILE* f = fopen("products.txt", "r");
    if (!f) {
        printf("Unable to open products.txt\n");
        return;
    }

    char pid[10], pname[50], categoryId[10];
    float price;

    printf("\n\U0001F4E6 Available Products:\n");
    printf("-----------------------------\n");
    while (fscanf(f, "%s %s %f %s", pid, pname, &price, categoryId) == 4) {
        printf("ID: %s | Name: %s | Price: %.2f | Category: %s\n", pid, pname, price, categoryId);
    }
    fclose(f);
}

void saveInventory() {
    FILE* f = fopen("inventory.txt", "w");
    if (!f) {
        printf("Error saving inventory to file.\n");
        return;
    }
    for (int i = 0; i < stockCount; i++) {
        fprintf(f, "%s %s %d %d %s\n", stock[i].productId, stock[i].productName,
                stock[i].quantity, stock[i].threshold, stock[i].status);
    }
    fclose(f);
    printf("Inventory saved successfully.\n");
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

    if (strlen(newItem.productId) < 4 || newItem.productId[0] != 'P') {
        printf(" Invalid product ID format. Use something like P001.\n");
        return;
    }

    if (!isProductExists(newItem.productId)) {
        printf(" Product ID not found in product list.\n");
        displayAvailableProducts();
        return;
    }

    char pname[50];
    float price;
    if (!getProductDetails(newItem.productId, pname, &price)) {
        printf("Product details could not be retrieved.\n");
        return;
    }
    strcpy(newItem.productName, pname);

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
    printf("Stock added successfully for %s.\n", newItem.productName);
    saveInventory(); 
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
            saveInventory();
            return;
        }
    }
    printf("Product ID not found.\n");
}

void updatestatus() {
    char id[10];
    printf("Enter product ID to update status: ");
    scanf("%s", id);

    for (int i = 0; i < stockCount; i++) {
        if (strcmp(stock[i].productId, id) == 0) {
            printf("Current status: %s\n", stock[i].status);
            printf("Enter new status (live/discontinued): ");
            scanf("%s", stock[i].status);
            printf("Status updated.\n");
            saveInventory();
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
    saveInventory();
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
