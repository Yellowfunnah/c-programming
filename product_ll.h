#ifndef PRODUCT_LL_H
#define PRODUCT_LL_H

typedef struct LLProduct {
    int id;
    char name[50];
    int quantity;
    float price;
    struct LLProduct* next;
} LLProduct;

LLProduct* createProduct(int id, const char* name, int quantity, float price);
void freeProductList(LLProduct* head);
void saveProductToFile(LLProduct* p);
LLProduct* loadProductsFromFile();
void writeAllProductsToFile(LLProduct* head);
void displayAllProducts(LLProduct* head);
void updateProductQuantity(LLProduct* head, int id, int newQty);
LLProduct* deleteProductById(LLProduct* head, int id);

#endif
