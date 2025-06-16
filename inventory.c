// inventory.c (add this new function)
#include "inventory.h"

// Implementation of loadInventoryFromFile, saveInventoryToFile, addStockRecord, etc.
#include <stdio.h>
void runInventoryManagementMenu(InventoryItem **head_ptr) {
    int choice;
    do {
        printf("\n--- Inventory and Stock Management Menu ---\n");
        printf("1. Add New Stock Item\n");
        printf("2. Update Stock Levels\n");
        printf("3. Remove Discontinued Stock Item\n");
        printf("4. View Current Inventory\n");
        printf("5. Check Low Stock Alerts\n");
        printf("6. Generate Inventory Report\n");
        printf("7. Back to Main Menu\n"); // Option to return to the main RolesMenu
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            choice = 0; 
            while (getchar() != '\n'); 
        } else {
            while (getchar() != '\n'); 
        }

        switch (choice) {
            case 1:
                addStockRecord(head_ptr); 
                break;
            case 2:
                updateStockLevels(*head_ptr); 
                break;
            case 3:
                removeStockItem(head_ptr); 
                break;
            case 4:
                viewCurrentInventory(*head_ptr); 
                break;
            case 5:
                checkLowStockAlerts(*head_ptr); 
                break;
            case 6:
                generateInventoryReport(*head_ptr); 
                break;
            case 7:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
}