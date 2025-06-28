#ifndef TRANSACTION_H
#define TRANSACTION_H

#define MAX_TRANSACTIONS 100

// Transaction structure
typedef struct {
    char transactionID[10];
    char userID[10];
    char productID[10];
    int quantity;
    double totalPrice;
    char date[20];
} Transaction;

// User structure
typedef struct {
    char userID[10];
    char username[50];
} User;

// Function declarations
void flushInput();
// User management
void transactionMenu();
void addUser();
void viewUsers();
void updateUser();
void deleteUser();
void saveUserData();
void loadUserData();

// Transaction management
void addTransaction();
void viewTransactions();
void deleteTransaction();
void saveTransactionData();
void loadTransactionData();
void reportTransactions();  

// Utility
void flushInput();

#endif
