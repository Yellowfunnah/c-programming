#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

#define FILENAME "products.txt"

void add_product(){

    FILE *fp;
    product new_product;
    fp = fopen("products.txt", "a");
    if (fp ==NULL){
        printf("Oops! Error opening file!\n");
        return;
    }
    printf("\n~~~~Add New Product~~~~\n");
    printf("Enter Product ID: ");
    scanf("%s", new_product.productID);
    while (getchar() != '\n');

    printf("Enter Product Name: ");
    fgets(new_product.product_name, MAX_NAME_LENGTH, stdin);
    new_product.product_name[strcspn(new_product.product_name, "\n")]=0;

    printf("Enter Price: ");
    scanf("%lf", &new_product.price);
    while (getchar() != '\n');

    if (new_product.price < 0){
        printf("Invaild Price! price can't be Negative");
        return;
    }

    printf("Enter Quantity: ");
    scanf("%d", &new_product.quantity);
    while (getchar() != '\n');

    if (new_product.quantity < 0){
        printf("Invaild Quantity! Quantity can't be Negative");
        return;
    }
    
    fprintf(fp, "%s %s %.2lf %d\n",
        new_product.productID,
        new_product.product_name,
        new_product.price,
        new_product.quantity);
    fclose(fp);
}

void view_products(){

    FILE *fp;
    product view;
    
    fp = fopen(FILENAME, "r");

    if (fp == NULL) {
        printf("Oops! The product can't be found.\n");
        return;
    }

    printf("~~~~ All The Products ~~~~\n");
    printf("%-10s %-25s %-10s %-10s\n", "ID", "Name", "Price", "Qty");
    printf("\n");
    while (fscanf(fp, "%s %s %lf %d", view.productID, view.product_name, &view.price, &view.quantity) != EOF) {
                printf("%-10s %-25s RM%-9.2lf %-10d\n", view.productID, view.product_name, view.price, view.quantity);
    }
    fclose(fp);

}






    void productMenu() {
        int choice;

        do{
            printf("\n~~~~ Product Management ~~~~\n");
            printf("1. Add Product\n");
            printf("2. View All Products\n");
            printf("3. Exit to main\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice){
                case 1: add_product(); break;
                case 2: view_products(); break;
                case 3: printf("Returning to main menu...\n"); break;
                default: printf("invalid choice. please try again.\n");
            }
        } while (choice != 3);









    }


