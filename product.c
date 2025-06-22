#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

#define FILENAME "products.txt"

void add_product(){

    FILE *fp;
    product new_product;
    fp = fopen(products.txt, "a");
    if (fp ==NULL){
        printf("Oops! Error opening file!\n");
        return;
    }
    printf("\n~~~~Add New Product~~~~\n");
    printf("Enter Product ID: ");
    Scanf("%s". new_product.productID);
    while (getchar() != '\n');

    printf("Enter Product Name: ");
    fgets(new_product.product_name, MAX_NAME_LENGTH, stdin);
    new_product.product_name[strcspn(new_Product.product_name, "\n")]=0

    printf("Enter Price: ");
    scanf("%lf", &new_product.price);
    while (getchar() != '\n');

    if (new_product.price < 0){
        printf("Invaild Price! price can't be Negative")
        return;
    }

    printf("Enter Quantity: "):
    scanf("%d", &new_product.quantity);
    while (getchar() != '\n');

    if (new_product.price < 0){
        printf("Invaild Price! price can't be Negative")
        return;
    }

}