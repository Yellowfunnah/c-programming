#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "category_supplier.h"

Category categories[MAX];
Supplier suppliers[MAX];
int catCount = 0, suppCount = 0;

// Adds a new category to the system
void addCategory() {
    if (catCount >= MAX) {
        printf("Category limit has been reached.\n");
        return;
    }
    printf("Enter category ID: ");
    scanf("%s", categories[catCount].categoryId);
    printf("Enter category name: ");
    scanf("%s", categories[catCount].categoryName);
    catCount++;
    printf("The category was successfully added!\n");
    saveData();
}

// Updates the name of an existing category
void updateCategory() {
    char id[10];
    int found = 0;
    printf("Enter the category ID you need to update: ");
    scanf("%s", id);
    for (int i = 0; i < catCount; i++) {
        if (strcmp(categories[i].categoryId, id) == 0) {
            printf("Enter a new category name: ");
            scanf("%s", categories[i].categoryName);
            printf("The category has been successfully updated!\n");
            found = 1;
            saveData();
            break;
        }
    }
    if (!found) printf("The category ID does not match!\n");
}

// Deletes a category from the system
void deleteCategory() {
    char id[10];
    int found = 0;
    printf("Enter category ID to delete: ");
    scanf("%s", id);
    for (int i = 0; i < catCount; i++) {
        if (strcmp(categories[i].categoryId, id) == 0) {
            for (int j = i; j < catCount - 1; j++) {
                categories[j] = categories[j + 1];
            }
            catCount--;
            printf("The category was deleted successfully!\n");
            found = 1;
            saveData();
            break;
        }
    }
    if (!found) printf("Category not found.\n");
}

// Displays all existing categories
void displayCategories() {
    printf("\nThe Categories:\n");
    for (int i = 0; i < catCount; i++) {
        printf("ID: %s, Name: %s\n", categories[i].categoryId, categories[i].categoryName);
    }
}

// Adds a new supplier with category reference
void addSupplier() {
    if (suppCount >= MAX) {
        printf("The limit for suppliers has been reached!\n");
        return;
    }
    printf("Enter supplier ID: ");
    scanf("%s", suppliers[suppCount].supplierId);
    printf("Enter supplier name: ");
    scanf("%s", suppliers[suppCount].supplierName);
    printf("Enter category ID this supplier belongs to: ");
    scanf("%s", suppliers[suppCount].categoryId);
    suppCount++;
    printf("Supplier added successfully.\n");
    saveData();
}

// Updates supplier information and category
void updateSupplier() {
    char id[10];
    int found = 0;
    printf("Enter the supplier ID you need to update: ");
    scanf("%s", id);
    for (int i = 0; i < suppCount; i++) {
        if (strcmp(suppliers[i].supplierId, id) == 0) {
            printf("Enter a new supplier name: ");
            scanf("%s", suppliers[i].supplierName);
            printf("Enter new category ID: ");
            scanf("%s", suppliers[i].categoryId);
            printf("The supplier has been successfully updated!\n");
            found = 1;
            saveData();
            break;
        }
    }
    if (!found) printf("Supplier ID not found!\n");
}

// Deletes a supplier from the list
void deleteSupplier() {
    char id[10];
    int found = 0;
    printf("Enter supplier ID to delete: ");
    scanf("%s", id);
    for (int i = 0; i < suppCount; i++) {
        if (strcmp(suppliers[i].supplierId, id) == 0) {
            for (int j = i; j < suppCount - 1; j++) {
                suppliers[j] = suppliers[j + 1];
            }
            suppCount--;
            printf("Supplier deleted successfully.\n");
            found = 1;
            saveData();
            break;
        }
    }
    if (!found) printf("Invalid supplier ID!\n");
}

// Displays all supplier details
void displaySuppliers() {
    printf("Total suppliers:\n");
    for (int i = 0; i < suppCount; i++) {
        printf("ID: %s, Name: %s, Category ID: %s\n", suppliers[i].supplierId, suppliers[i].supplierName, suppliers[i].categoryId);
    }
}

// Shows suppliers that belong to a specific category
void filterSuppliersByCategory() {
    char catId[10];
    printf("Enter category ID to filter suppliers: ");
    scanf("%s", catId);
    printf("\nSuppliers under Category ID %s:\n", catId);
    for (int i = 0; i < suppCount; i++) {
        if (strcmp(suppliers[i].categoryId, catId) == 0) {
            printf("ID: %s, Name: %s\n", suppliers[i].supplierId, suppliers[i].supplierName);
        }
    }
}

// Reads and displays product inventory from a file
void displayInventoryFromFile() {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("Unable to open inventory.txt.\n");
        return;
    }

    char productId[10], productName[50], status[10];
    int quantity, threshold;

    printf("\n===== Inventory Records =====\n");
    printf("%-10s %-20s %-10s %-10s %-12s\n", "Product ID", "Product Name", "Qty", "Threshold", "Status");

    while (fscanf(file, "%s %s %d %d %s", productId, productName, &quantity, &threshold, status) == 5) {
        printf("%-10s %-20s %-10d %-10d %-12s\n", productId, productName, quantity, threshold, status);
    }

    fclose(file);
}

// Allows restocking an existing product in the inventory file
void restockInventory() {
    displayInventoryFromFile();

    char productId[10];
    int addedQty, found = 0;

    printf("Enter Product ID to restock: ");
    scanf("%s", productId);

    FILE *f = fopen("inventory.txt", "r");
    FILE *temp = fopen("temp_inventory.txt", "w");

    if (!f || !temp) {
        printf("Error opening inventory file.\n");
        return;
    }

    char pid[10], name[50], status[10];
    int qty, threshold;

    printf("Enter quantity to add: ");
    scanf("%d", &addedQty);

    while (fscanf(f, "%s %s %d %d %s", pid, name, &qty, &threshold, status) == 5) {
        if (strcmp(pid, productId) == 0) {
            qty += addedQty;
            found = 1;
        }
        fprintf(temp, "%s %s %d %d %s\n", pid, name, qty, threshold, status);
    }

    fclose(f);
    fclose(temp);

    remove("inventory.txt");
    rename("temp_inventory.txt", "inventory.txt");

    if (found)
        printf(" Quantity updated successfully for %s.\n", productId);
    else
        printf(" Product ID not found in inventory.\n");
}

// Saves categories and suppliers to their respective text files
void saveData() {
    FILE *cf = fopen("categories.txt", "w");
    FILE *sf = fopen("suppliers.txt", "w");
    for (int i = 0; i < catCount; i++)
        fprintf(cf, "%s %s\n", categories[i].categoryId, categories[i].categoryName);
    for (int i = 0; i < suppCount; i++)
        fprintf(sf, "%s %s %s\n", suppliers[i].supplierId, suppliers[i].supplierName, suppliers[i].categoryId);
    fclose(cf);
    fclose(sf);
}

// Loads category and supplier data from files at program start
void loadData() {
    FILE *cf = fopen("categories.txt", "r");
    FILE *sf = fopen("suppliers.txt", "r");
    catCount = suppCount = 0;

    if (cf != NULL) {
        printf("\nReading categories.txt...\n");
        while (fscanf(cf, "%s %s", categories[catCount].categoryId, categories[catCount].categoryName) != EOF) {
            printf("Loaded category: %s %s\n", categories[catCount].categoryId, categories[catCount].categoryName);
            catCount++;
        }
        fclose(cf);
    } else {
        printf(" Failed to open categories.txt\n");
    }

    if (sf != NULL) {
        while (fscanf(sf, "%s %s %s", suppliers[suppCount].supplierId, suppliers[suppCount].supplierName, suppliers[suppCount].categoryId) != EOF)
            suppCount++;
        fclose(sf);
    }
}

// Main menu for managing categories, suppliers, and inventory
void manageMenu() {
    loadData();
    int choice;
    do {
        printf("\n== Category and Supplier Management =====\n");
        printf("1. Add Category\n2. Add Supplier\n3. Update Category\n4. Update Supplier\n5. Delete Category\n6. Delete Supplier\n7. View Categories\n8. View Suppliers\n9. Filter Suppliers by Category\n10. Show Inventory from File\n11. Restock Inventory (Add Quantity)\n12. Exit\nChoose option: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addCategory(); break;
            case 2: addSupplier(); break;
            case 3: updateCategory(); break;
            case 4: updateSupplier(); break;
            case 5: deleteCategory(); break;
            case 6: deleteSupplier(); break;
            case 7: displayCategories(); break;
            case 8: displaySuppliers(); break;
            case 9: filterSuppliersByCategory(); break;
            case 10: displayInventoryFromFile(); break;
            case 11: restockInventory(); break;
            case 12: printf("\nExiting...\n"); break;
            default: printf("Invalid choice, please try again!\n");
        }
    } while (choice != 12);
}
