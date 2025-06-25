#ifndef FILE_H
#define FILE_H

// Define the Product struct
typedef struct Product {
    int id;
    char name[50];
    int quantity;
    float price;
    struct Product* next; // Pointer to next product
} Product;

// ===== Linked List Functions =====
Product* createProduct(int id, const char* name, int quantity, float price);
void freeProductList(Product* head);

// ===== File Handling Functions =====
void saveProductToFile(Product* p);
Product* loadProductsFromFile();
void writeAllProductsToFile(Product* head);

// ===== Product Operations =====
void displayAllProducts(Product* head);
void updateProductQuantity(Product* head, int id, int newQty);
Product* deleteProductById(Product* head, int id);


#endif
