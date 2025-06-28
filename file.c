#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "product.h"
#include "inventory.h"
#include "category_supplier.h"
#include "transaction.h"

void addDataMenu() {
    int choice;
    printf("\n== ADD DATA MENU ==\n");
    printf("1. Add Product\n");
    printf("2. Add Stock\n");
    printf("3. Add Category\n");
    printf("4. Add Supplier\n");
    printf("5. Add User\n");
    printf("6. Add Transaction\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: add_product(); break;
        case 2: addstock(); break;
        case 3: addCategory(); break;
        case 4: addSupplier(); break;
        case 5: addUser(); break;
        case 6: addTransaction(); break;
        default: printf("Invalid choice.\n");
    }
}

void updateDataMenu() {
    int choice;
    printf("\n== UPDATE DATA MENU ==\n");
    printf("1. Update Product\n");
    printf("2. Update Stock\n");
    printf("3. Update Category\n");
    printf("4. Update Supplier\n");
    printf("5. Update User\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: update_product(); break;
        case 2: updatestock(); break;
        case 3: updateCategory(); break;
        case 4: updateSupplier(); break;
        case 5: updateUser(); break;
        default: printf("Invalid choice.\n");
    }
}

void deleteDataMenu() {
    int choice;
    printf("\n== DELETE DATA MENU ==\n");
    printf("1. Delete Product\n");
    printf("2. Delete Stock\n");
    printf("3. Delete Category\n");
    printf("4. Delete Supplier\n");
    printf("5. Delete User\n");
    printf("6. Delete Transaction\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: delete_product(); break;
        case 2: removestock(); break;
        case 3: deleteCategory(); break;
        case 4: deleteSupplier(); break;
        case 5: deleteUser(); break;
        case 6: deleteTransaction(); break;
        default: printf("Invalid choice.\n");
    }
}

void viewAllData() {
    printf("\n===== ALL SYSTEM DATA =====\n");

    printf("\n--- Products ---\n");
    view_products();

    printf("\n--- Inventory ---\n");
    loadInventory();
    viewstock();

    printf("\n--- Categories ---\n");
    loadData();
    displayCategories();

    printf("\n--- Suppliers ---\n");
    displaySuppliers();

    printf("\n--- Users ---\n");
    loadUserData();
    viewUsers();

    printf("\n--- Transactions ---\n");
    loadTransactionData();
    viewTransactions();

    saveData();
    saveInventory();
    saveUserData();
    saveTransactionData();

    printf("\n All module data reloaded and saved.\n");
}

void fileOperationsMenu() {
    int choice;

    do {
        printf("\n===== FILE OPERATIONS MENU (ROLE 5) =====\n");
        printf("1. Add Data\n");
        printf("2. Update Data\n");
        printf("3. Delete Data\n");
        printf("4. View All Data\n");
        printf("0. Exit File Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addDataMenu(); break;
            case 2: updateDataMenu(); break;
            case 3: deleteDataMenu(); break;
            case 4: viewAllData(); break;
            case 0: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}
