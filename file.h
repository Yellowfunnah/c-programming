// file.h
#ifndef FILE_H
#define FILE_H

// ===== Product Structure =====
typedef struct Product {
    int id;
    char name[50];
    int quantity;
    float price;
    struct Product* next;
} Product;

// ===== Linked List Functions =====
Product* createProduct(int id, const char* name, int quantity, float price);
void freeProductList(Product* head);

// ===== File Operations =====
void saveProductToFile(Product* p);
Product* loadProductsFromFile();
void writeAllProductsToFile(Product* head);

// ===== CRUD Operations =====
void displayAllProducts(Product* head);
void updateProductQuantity(Product* head, int id, int newQty);
Product* deleteProductById(Product* head, int id);

// ===== Menu =====
void fileOperationsMenu();  // So meh.c can call your file menu

#endif
