#ifndef PRODUCT_H
#define PRODUCT_H
#define MAX_NAME_LENGTH 100

typedef struct{
    char productID[10];
    char product_name[MAX_NAME_LENGTH];
    double price;
    int quantity;
    char categoryId[10];
} product;

void add_product();
void update_product();
void delete_product();
void view_products();
void productMenu();

#endif