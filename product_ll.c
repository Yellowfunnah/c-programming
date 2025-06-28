#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product_ll.h"

LLProduct* createProduct(int id, const char* name, int quantity, float price) {
    LLProduct* newProduct = (LLProduct*)malloc(sizeof(LLProduct));
    newProduct->id = id;
    strcpy(newProduct->name, name);
    newProduct->quantity = quantity;
    newProduct->price = price;
    newProduct->next = NULL;
    return newProduct;
}

void freeProductList(LLProduct* head) {
    LLProduct* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

#define PRODUCT_FILE "products.txt"

LLProduct* loadProductsFromFile() {
    FILE* file = fopen(PRODUCT_FILE, "r");
    if (!file) {
        printf("No products found yet.\n");
        return NULL;
    }

    LLProduct* head = NULL;
    LLProduct* tail = NULL;
    while (!feof(file)) {
        LLProduct* p = (LLProduct*)malloc(sizeof(LLProduct));
        if (fscanf(file, "%d,%49[^,],%d,%f\n", &p->id, p->name, &p->quantity, &p->price) == 4) {
            p->next = NULL;
            if (head == NULL) {
                head = tail = p;
            } else {
                tail->next = p;
                tail = p;
            }
        } else {
            free(p);
        }
    }

    fclose(file);
    return head;
}

void saveProductToFile(LLProduct* p) {
    FILE* file = fopen(PRODUCT_FILE, "a");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "%d,%s,%d,%.2f\n", p->id, p->name, p->quantity, p->price);
    fclose(file);
}

void writeAllProductsToFile(LLProduct* head) {
    FILE* file = fopen(PRODUCT_FILE, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    LLProduct* current = head;
    while (current != NULL) {
        fprintf(file, "%d,%s,%d,%.2f\n", current->id, current->name, current->quantity, current->price);
        current = current->next;
    }

    fclose(file);
}

void displayAllProducts(LLProduct* head) {
    if (!head) {
        printf("No products to display.\n");
        return;
    }

    printf("\n=== Product List ===\n");
    while (head != NULL) {
        printf("ID: %d | Name: %s | Qty: %d | Price: RM%.2f\n",
               head->id, head->name, head->quantity, head->price);
        head = head->next;
    }
}

void updateProductQuantity(LLProduct* head, int id, int newQty) {
    LLProduct* current = head;
    while (current != NULL) {
        if (current->id == id) {
            current->quantity = newQty;
            writeAllProductsToFile(head);
            printf("✅ Quantity updated for product ID %d.\n", id);
            return;
        }
        current = current->next;
    }
    printf("Product ID not found.\n");
}

LLProduct* deleteProductById(LLProduct* head, int id) {
    LLProduct *current = head, *prev = NULL;

    while (current != NULL) {
        if (current->id == id) {
            if (prev == NULL)
                head = current->next;
            else
                prev->next = current->next;

            free(current);
            writeAllProductsToFile(head);
            printf("Product with ID %d deleted.\n", id);
            return head;
        }
        prev = current;
        current = current->next;
    }

    printf("Product ID not found.\n");
    return head;
}
