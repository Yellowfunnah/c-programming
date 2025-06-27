#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "category_supplier.h"

Category categories[MAX];
Supplier suppliers[MAX];
int catCount = 0, suppCount = 0;

void addCategory() {
    if (catCount >= MAX) {
        printf("Category limit has been reached.\n");
        return;
    }
    printf("Enter category ID: ");
    scanf("%d", &categories[catCount].categoryId);
    printf("Enter category name: ");
    scanf("%s", categories[catCount].categoryName);
    catCount++;
    printf("The category was successfully added!\n");
}

void updateCategory() {
    int id, found = 0;
    printf("Enter the category ID you need to update: ");
    scanf("%d", &id);
    for (int i = 0; i < catCount; i++) {
        if (categories[i].categoryId == id) {
            printf("Enter a new category name: ");
            scanf("%s", categories[i].categoryName);
            printf("The category has been successfully updated!\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("The category ID does not match!\n");
}

void deleteCategory() {
    int id, found = 0;
    printf("Enter category ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < catCount; i++) {
        if (categories[i].categoryId == id) {
            for (int j = i; j < catCount - 1; j++) {
                categories[j] = categories[j + 1];
            }
            catCount--;
            printf("The category was deleted successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Category not found.\n");
}

void displayCategories() {
    printf("\nThe Categories:\n");
    for (int i = 0; i < catCount; i++) {
        printf("ID: %d, Name: %s\n", categories[i].categoryId, categories[i].categoryName);
    }
}

void addSupplier() {
    if (suppCount >= MAX) {
        printf("The limit for suppliers has been reached!\n");
        return;
    }
    printf("Enter supplier ID: ");
    scanf("%d", &suppliers[suppCount].supplierId);
    printf("Enter supplier name: ");
    scanf("%s", suppliers[suppCount].supplierName);
    printf("Enter category ID this supplier belongs to: ");
    scanf("%d", &suppliers[suppCount].categoryId);
    suppCount++;
    printf("Supplier added successfully.\n");
}

void updateSupplier() {
    int id, found = 0;
    printf("Enter the supplier ID you need to update: ");
    scanf("%d", &id);
    for (int i = 0; i < suppCount; i++) {
        if (suppliers[i].supplierId == id) {
            printf("Enter a new supplier name: ");
            scanf("%s", suppliers[i].supplierName);
            printf("Enter new category ID: ");
            scanf("%d", &suppliers[i].categoryId);
            printf("The supplier has been successfully updated!\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Supplier ID not found!\n");
}

void deleteSupplier() {
    int id, found = 0;
    printf("Enter supplier ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < suppCount; i++) {
        if (suppliers[i].supplierId == id) {
            for (int j = i; j < suppCount - 1; j++) {
                suppliers[j] = suppliers[j + 1];
            }
            suppCount--;
            printf("Supplier deleted successfully.\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Invalid supplier ID!\n");
}

void displaySuppliers() {
    printf("Total suppliers:\n");
    for (int i = 0; i < suppCount; i++) {
        printf("ID: %d, Name: %s, Category ID: %d\n", suppliers[i].supplierId, suppliers[i].supplierName, suppliers[i].categoryId);
    }
}

void filterSuppliersByCategory() {
    int catId;
    printf("Enter category ID to filter suppliers: ");
    scanf("%d", &catId);
    printf("\nSuppliers under Category ID %d:\n", catId);
    for (int i = 0; i < suppCount; i++) {
        if (suppliers[i].categoryId == catId) {
            printf("ID: %d, Name: %s\n", suppliers[i].supplierId, suppliers[i].supplierName);
        }
    }
}

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

void restockInventory() {
    // Shows inventory before asking anything
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


void saveData() {
    FILE *cf = fopen("categories.txt", "w");
    FILE *sf = fopen("suppliers.txt", "w");
    for (int i = 0; i < catCount; i++)
        fprintf(cf, "%d %s\n", categories[i].categoryId, categories[i].categoryName);
    for (int i = 0; i < suppCount; i++)
        fprintf(sf, "%d %s %d\n", suppliers[i].supplierId, suppliers[i].supplierName, suppliers[i].categoryId);
    fclose(cf);
    fclose(sf);
}

void loadData() {
    FILE *cf = fopen("categories.txt", "r");
    FILE *sf = fopen("suppliers.txt", "r");
    catCount = suppCount = 0;
    if (cf != NULL) {
        while (fscanf(cf, "%d %s", &categories[catCount].categoryId, categories[catCount].categoryName) != EOF)
            catCount++;
        fclose(cf);
    }
    if (sf != NULL) {
        while (fscanf(sf, "%d %s %d", &suppliers[suppCount].supplierId, suppliers[suppCount].supplierName, &suppliers[suppCount].categoryId) != EOF)
            suppCount++;
        fclose(sf);
    }
}

void manageMenu() {
    int choice;
    do {
        printf("\n== Category and Supplier Management =====\n");
        printf("1. Add Category\n2. Add Supplier\n3. Update Category\n4. Update Supplier\n5. Delete Category\n6. Delete Supplier\n7. View Categories\n8. View Suppliers\n9. Filter Suppliers by Category\n10. Show Inventory from File\n11. Restock Inventory (Add Quantity)\n12. Save & Exit\nChoose option: ");
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
            case 12: saveData(); break;
            default: printf("Invalid choice, please try again!\n");
        }
    } while (choice != 12);
}
