// assignment file :)
#include <stdio.h>
#include "inventory.h" 
#include "product.h"
#include "category_supplier.h"
#include "transaction.h"  
#include "file.h"
#include "login.h" // Include login function

// Role 1
void role1() {
    productMenu();
}

// Role 2
void role2() {
    loadInventory();
    inventoryMenu();
}

// Role 3
void role3() {
    loadData();        // ✅ This loads categories.txt and suppliers.txt
    manageMenu();      // Then launches the menu
}

// Role 4
void role4() {
    transactionMenu();
}

// Role 5
void role5() {
    fileOperationsMenu();
}

int main() {
    int choice;
    int userRole;
    char currentUser[50];

    do {
        printf("\n~~~~ Retail Inventory Management System ~~~~\n");
        printf("1. Core System and Product Management\n");
        printf("2. Inventory and Stock Management\n");
        printf("3. Category and Supplier Management\n");
        printf("4. User and Transaction Management\n");
        printf("5. File Operations and Advanced Features\n");
        printf("6. Terminate\n");
        printf("Select a role to log into (1-6): ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 5) {
            userRole = login(currentUser); // Prompt login

            if (userRole == choice) {
                // Access granted
                switch (userRole) {
                    case 1: role1(); break;
                    case 2: role2(); break;
                    case 3: role3(); break;
                    case 4: role4(); break;
                    case 5: role5(); break;
                }
            } else {
                printf(" Access Denied: You are not authorized for this role.\n");
            }
        } else if (choice != 6) {
            printf("Invalid choice. Please select a valid role (1-5) or 6 to exit.\n");
        }

    } while (choice != 6);

    printf("Exiting system.\n");
    return 0;
}
