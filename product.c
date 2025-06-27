#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

// the update function doesn't loop back
// no validation (enter your choice)+(inputing data) 
// no password 

#define FILENAME "products.txt"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "product.h"

#define FILENAME "products.txt"

int isValidName(const char* name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != ' ') return 0;
    }
    return 1;
}

void add_product() {
    FILE *fp;
    product new_product;

    fp = fopen("products.txt", "a");
    if (fp == NULL) {
        printf("Oops! Error opening file!\n");
        return;
    }

    printf("\n~~~~ Add New Product ~~~~\n");

    // Product ID input and duplicate check
    printf("Enter Product ID: ");
    scanf("%s", new_product.productID);
    while (getchar() != '\n');

    FILE *check_fp = fopen(FILENAME, "r");
    product temp;
    while (fscanf(check_fp, "%s %s %lf %d %s", temp.productID, temp.product_name, &temp.price, &temp.quantity, temp.categoryId) != EOF) {
        if (strcmp(temp.productID, new_product.productID) == 0) {
            printf("Product ID already exists! Please enter a unique ID.\n");
            fclose(check_fp);
            fclose(fp);
            return;
        }
    }
    fclose(check_fp);

    // Product name input
    printf("Enter Product Name: ");
    fgets(new_product.product_name, MAX_NAME_LENGTH, stdin);
    new_product.product_name[strcspn(new_product.product_name, "\n")] = 0;

    if (!isValidName(new_product.product_name)) {
        printf("Invalid product name! Only letters and spaces allowed.\n");
        fclose(fp);
        return;
    }

    // Price input
    printf("Enter Price: ");
    scanf("%lf", &new_product.price);
    while (getchar() != '\n');
    if (new_product.price <= 0 || new_product.price > 100000) {
        printf("Invalid price! Must be between 0.01 and 100000.\n");
        fclose(fp);
        return;
    }
    

    // Category ID input + validation
    printf("Enter Category ID: ");
    scanf("%s", new_product.categoryId);
    FILE *cat_fp = fopen("category.txt", "r");
    int catFound = 0;
    char catID[10], catName[50];
    if (cat_fp == NULL) {
        printf("Error opening category file!\n");
        fclose(fp);
        return;
    }
    while (fscanf(cat_fp, "%s %s", catID, catName) != EOF) {
        if (strcmp(catID, new_product.categoryId) == 0) {
            catFound = 1;
            break;
        }
    }
    fclose(cat_fp);
    if (!catFound) {
        printf("Invalid Category ID! Category does not exist.\n");
        fclose(fp);
        return;
    }

    // Save to file
    fprintf(fp, "%s %s %.2lf %d %s\n",
            new_product.productID,
            new_product.product_name,
            new_product.price,
            new_product.quantity,
            new_product.categoryId);

    fclose(fp);
    printf("Product added successfully!\n");
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



void update_product(){
    FILE *fp = fopen(FILENAME, "r");
    FILE *temp_fp = fopen("temp.txt", "w");
    product temp;
    char target_id[20];
    int found = 0;

    if (fp == NULL || temp_fp == NULL){
        printf("Error Opening file.\n");
        return;
    }

    printf("Enter Product Id to Update: ");
    scanf("%s", target_id);

    while (fscanf(fp,"%s %s%lf %d", temp.productID, temp.product_name, &temp.price, &temp.quantity) !=EOF ){
        if(strcmp(temp.productID, target_id)==0){
            printf("Enter new name: ");
            scanf("%s", temp.product_name);
            printf("Enter new price: ");
            scanf("%lf", &temp.price);
            printf("Enter new quantity; ");
            scanf("%d", &temp.quantity);
            found = 1;
        }
        fprintf(temp_fp,"%s %s %.2lf %d\n",temp.productID, temp.product_name, temp.price, temp.quantity);
    }
    fclose(fp);
    fclose(temp_fp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found)
        printf("Product updated successfully!\n");
    else
        printf("Product ID not found.\n");

}


void  delete_product(){
    FILE *fp = fopen(FILENAME, "r");
    FILE *temp_fp = fopen("temp.txt", "w");

    product temp;
    char target_id[20];
    int found = 0;

    if(fp == NULL || temp_fp == NULL){
        printf("Error Opening file. \n");
        return;
    }
    printf("Enter Product ID to delete: ");
    scanf("%s", target_id);

    while (fscanf(fp, "%s %s %lf %d", temp.productID, temp.product_name, &temp.price, &temp.quantity) !=EOF){

        if (strcmp(temp.productID, target_id) ==0) {
            found = 1;
            continue;
        }
        fprintf(temp_fp, "%s %s %2lf %d\n", temp.productID, temp.product_name, temp.price, temp.quantity);

    }
fclose(fp);
fclose(temp_fp);
remove(FILENAME);
rename("temp.txt", FILENAME);

if (found)
    printf("Product deleted successfully!!\n");
else
    printf("Product ID not found.\n");


}

    void productMenu() {
        int choice;

        do{
            printf("\n~~~~ Product Management ~~~~\n");
            printf("1. Add Product\n");
            printf("2. View All Products\n");
            printf("3. Update Product\n");
            printf("4. Delete Product\n");
            printf("5. Exit to main\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice){
                case 1: add_product(); break;
                case 2: view_products(); break;
                case 3: update_product(); break;
                case 4: delete_product(); break;
                case 5: printf("Returning to main menu...\n"); break; 
                default: printf("invalid choice. please try again.\n");
            }
        } while (choice != 5);

    }