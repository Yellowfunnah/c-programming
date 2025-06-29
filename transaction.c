#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transaction.h"

Transaction transactions[MAX_TRANSACTIONS];
User users[MAX_TRANSACTIONS];
int transactionCount = 0;
int userCount = 0;

// Append a single transaction to the file
void appendTransactionToFile(Transaction t) {
    FILE *f = fopen("transactions.txt", "a");
    if (f != NULL) {
        fprintf(f, "%s %s %s %d %.2lf %s\n",
                t.transactionID,
                t.userID,
                t.productID,
                t.quantity,
                t.totalPrice,
                t.date);
        fclose(f);
    } else {
        printf("Error opening transactions.txt for appending.\n");
    }
}

// User functions
void addUser() {
    if (userCount >= MAX_TRANSACTIONS) {
        printf("User limit reached.\n");
        return;
    }
    printf("Enter User ID: ");
    scanf("%s", users[userCount].userID);
    printf("Enter Username: ");
    scanf("%s", users[userCount].username);
    userCount++;
    saveUserData();
    printf("User added successfully!\n");
}

void viewUsers() {
    loadUserData();
    if (userCount == 0) {
        printf("No users registered yet.\n");
        return;
    }
    printf("\nRegistered Users:\n");
    for (int i = 0; i < userCount; i++) {
        printf("ID: %s, Name: %s\n", users[i].userID, users[i].username);
    }
}

void updateUser() {
    viewUsers();
    loadUserData();

    if (userCount == 0) {
        printf("No users found to update.\n");
        return;
    }

    char id[10];
    int found = 0;
    printf("\nEnter User ID to update: ");
    scanf("%s", id);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userID, id) == 0) {
            printf("Enter new username: ");
            scanf("%s", users[i].username);
            found = 1;
            break;
        }
    }

    if (found) {
        saveUserData();
        printf("User updated successfully!\n");
    } else {
        printf("User not found.\n");
    }
}

void deleteUser() {
    char id[10];
    int found = 0;
    printf("Enter User ID to delete: ");
    scanf("%s", id);
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userID, id) == 0) {
            for (int j = i; j < userCount - 1; j++) {
                users[j] = users[j + 1];
            }
            userCount--;
            saveUserData();
            printf("User deleted.\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("User ID not found.\n");
}
void addTransaction() {
    if (transactionCount >= MAX_TRANSACTIONS) {
        printf("Transaction limit reached.\n");
        return;
    }

    char productId[10];
    int purchaseQty;
    int found = 0;

    Transaction newTransaction;

    printf("Enter Transaction ID: ");
    scanf("%s", newTransaction.transactionID);
    printf("Enter User ID: ");
    scanf("%s", newTransaction.userID);
    printf("Enter Product ID: ");
    scanf("%s", productId);
    printf("Enter Quantity: ");
    scanf("%d", &purchaseQty);
    printf("Enter Date (DD-MM-YYYY): ");
    scanf("%s", newTransaction.date);

    FILE *inv = fopen("inventory.txt", "r");
    FILE *temp = fopen("temp_inventory.txt", "w");

    if (!inv || !temp) {
        printf("Error opening inventory file.\n");
        return;
    }

    char pid[10], pname[50], status[10];
    int qty, threshold;
    double unitPrice = 0.0;

    while (fscanf(inv, "%s %s %d %d %s", pid, pname, &qty, &threshold, status) == 5) {
        if (strcmp(pid, productId) == 0) {
            found = 1;

            if (qty < purchaseQty) {
                printf("Insufficient stock for %s. Available: %d\n", pname, qty);
                fclose(inv);
                fclose(temp);
                remove("temp_inventory.txt");
                return;
            }

            qty -= purchaseQty;

            FILE *pf = fopen("products.txt", "r");
            if (pf != NULL) {
                char prodID[10], prodName[100], catID[10];
                double price;

                while (fscanf(pf, "%s %s %lf %s", prodID, prodName, &price, catID) == 4) {
                    if (strcmp(prodID, productId) == 0) {
                        unitPrice = price;
                        break;
                    }
                }

                fclose(pf);
            } else {
                printf("Error opening products.txt\n");
                fclose(inv);
                fclose(temp);
                remove("temp_inventory.txt");
                return;
            }
        }

        fprintf(temp, "%s %s %d %d %s\n", pid, pname, qty, threshold, status);
    }

    fclose(inv);
    fclose(temp);

    if (!found) {
        printf("Product ID not found in inventory.\n");
        remove("temp_inventory.txt");
        return;
    }

    remove("inventory.txt");
    rename("temp_inventory.txt", "inventory.txt");

    // Save to memory
    strcpy(newTransaction.productID, productId);
    newTransaction.quantity = purchaseQty;
    newTransaction.totalPrice = purchaseQty * unitPrice;

    transactions[transactionCount++] = newTransaction;  // Store in memory
    appendTransactionToFile(newTransaction);            // Append only the new one

    printf("Transaction recorded successfully!\n");
    printf("Total Price: RM%.2lf | Inventory updated for product %s.\n", newTransaction.totalPrice, productId);
}

// Displays all recorded transactions
void viewTransactions() {
    if (transactionCount == 0) {
        printf("No transactions recorded yet.\n");
        return;
    }
    printf("\nTransactions:\n");
    for (int i = 0; i < transactionCount; i++) {
        printf("TID: %s, User: %s, Product: %s, Qty: %d, Total: RM%.2lf, Date: %s\n",
               transactions[i].transactionID,
               transactions[i].userID,
               transactions[i].productID,
               transactions[i].quantity,
               transactions[i].totalPrice,
               transactions[i].date);
    }
}

// Deletes a transaction by matching the entered Transaction ID
void deleteTransaction() {
    loadTransactionData();
    char id[10];
    int found = 0;
    printf("Enter Transaction ID to delete: ");
    scanf("%s", id);
    for (int i = 0; i < transactionCount; i++) {
        if (strcmp(transactions[i].transactionID, id) == 0) {
            for (int j = i; j < transactionCount - 1; j++) {
                transactions[j] = transactions[j + 1];
            }
            transactionCount--;
            saveTransactionData();
            printf("Transaction deleted.\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Transaction ID not found.\n");
}

// Generates a filtered transaction report by User ID or Product ID
void reportTransactions() {
    int option;
    char input[20];
    printf("\nTransaction Report Options:\n1. By User ID\n2. By Product ID\nChoose option: ");
    scanf("%d", &option);
    flushInput();

    if (option == 1) {
        printf("Enter User ID: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        printf("\nTransactions for User ID: %s\n", input);
        int found = 0;
        for (int i = 0; i < transactionCount; i++) {
            if (strcmp(transactions[i].userID, input) == 0) {
                printf("TID: %s, Product: %s, Qty: %d, Total: RM%.2lf, Date: %s\n",
                       transactions[i].transactionID,
                       transactions[i].productID,
                       transactions[i].quantity,
                       transactions[i].totalPrice,
                       transactions[i].date);
                found = 1;
            }
        }
        if (!found) printf("No transactions found for this user.\n");
    } else if (option == 2) {
        printf("Enter Product ID: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        printf("\nTransactions for Product ID: %s\n", input);
        int found = 0;
        for (int i = 0; i < transactionCount; i++) {
            if (strcmp(transactions[i].productID, input) == 0) {
                printf("TID: %s, User: %s, Qty: %d, Total: RM%.2lf, Date: %s\n",
                       transactions[i].transactionID,
                       transactions[i].userID,
                       transactions[i].quantity,
                       transactions[i].totalPrice,
                       transactions[i].date);
                found = 1;
            }
        }
        if (!found) printf("No transactions found for this product.\n");
    } else {
        printf("Invalid option.\n");
    }
}

// File I/O
void saveUserData() {
    FILE *f = fopen("users.txt", "w");
    for (int i = 0; i < userCount; i++) {
        fprintf(f, "%s %s\n", users[i].userID, users[i].username);
    }
    fclose(f);
}

void loadUserData() {
    userCount = 0;
    FILE *f = fopen("users.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%s %s", users[userCount].userID, users[userCount].username) != EOF)
            userCount++;
        fclose(f);
    }
}

void saveTransactionData() {
    FILE *f = fopen("transactions.txt", "w");
    for (int i = 0; i < transactionCount; i++) {
        fprintf(f, "%s %s %s %d %.2lf %s\n",
                transactions[i].transactionID,
                transactions[i].userID,
                transactions[i].productID,
                transactions[i].quantity,
                transactions[i].totalPrice,
                transactions[i].date);
    }
    fclose(f);
}


void loadTransactionData() {
    transactionCount = 0;  
    FILE *f = fopen("transactions.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%s %s %s %d %lf %s",
                      transactions[transactionCount].transactionID,
                      transactions[transactionCount].userID,
                      transactions[transactionCount].productID,
                      &transactions[transactionCount].quantity,
                      &transactions[transactionCount].totalPrice,
                      transactions[transactionCount].date) != EOF)
            transactionCount++;
        fclose(f);
    }
}


// Main menu
void transactionMenu() {
    loadUserData();
    loadTransactionData();

    int choice;
    do {
        printf("\n=== User & Transaction Management ===\n");
        printf("1. Add User\n2. View Users\n3. Update User\n4. Delete User\n");
        printf("5. Add Transaction\n6. View Transactions\n7. Delete Transaction\n");
        printf("8. Report Transactions\n9. Exit\nChoose option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addUser(); break;
            case 2: viewUsers(); break;
            case 3: updateUser(); break;
            case 4: deleteUser(); break;
            case 5: addTransaction(); break;
            case 6: viewTransactions(); break;
            case 7: deleteTransaction(); break;
            case 8: reportTransactions(); break;
            case 9:
                printf("Exiting...\n");
                break;
            default: printf("Invalid choice.\n");
        }

    } while (choice != 9);
}


