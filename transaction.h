#ifndef TRANSACTION_H
#define TRANSACTION_H

#define MAX_TRANSACTIONS 100

typedef struct {
    char transactionID[10];
    char userID[10];
    char productID[10];
    int quantity;
    double totalPrice;
    char date[20];
} Transaction;

typedef struct {
    char userID[10];
    char username[50];
} User;

extern Transaction transactions[MAX_TRANSACTIONS];
extern User users[MAX_TRANSACTIONS];
extern int transactionCount;
extern int userCount;

void addUser();
void viewUsers();
void updateUser();
void deleteUser();

void addTransaction();
void viewTransactions();
void deleteTransaction();

void loadUserData();
void saveUserData();
void loadTransactionData();
void saveTransactionData();

void transactionMenu();

#endif