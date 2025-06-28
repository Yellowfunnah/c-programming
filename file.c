#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h" 
#define PRODUCT_FILE "products.txt"

// ========== Linked List Functions ==========

// Create a new product node
Product* createProduct(int id, const char* name, int quantity, float price) {
    Product* newProduct = (Product*)malloc(sizeof(Product));
    newProduct->id = id;
    strcpy(newProduct->name, name);
    newProduct->quantity = quantity;
    newProduct->price = price;
    newProduct->next = NULL;
    return newProduct;
}

// Free the entire list
void freeProductList(Product* head) {
    Product* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// ========== File Handling Functions ==========

// Save a single product to the file
void saveProductToFile(Product* p) {
    FILE* file = fopen(PRODUCT_FILE, "a");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "%d,%s,%d,%.2f\n", p->id, p->name, p->quantity, p->price);
    fclose(file);
}

// Load all products from file into a linked list
Product* loadProductsFromFile() {
    FILE* file = fopen(PRODUCT_FILE, "r");
    if (!file) {
        printf("No products found yet.\n");
        return NULL;
    }

    Product* head = NULL;
    Product* tail = NULL;
    while (!feof(file)) {
        Product* p = (Product*)malloc(sizeof(Product));
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

// Rewrite the whole file with the current list
void writeAllProductsToFile(Product* head) {
    FILE* file = fopen(PRODUCT_FILE, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    Product* current = head;
    while (current != NULL) {
        fprintf(file, "%d,%s,%d,%.2f\n", current->id, current->name, current->quantity, current->price);
        current = current->next;
    }

    fclose(file);
}

// ========== CRUD Operations ==========

// Display all products
void displayAllProducts(Product* head) {
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

// Update quantity of a product
void updateProductQuantity(Product* head, int id, int newQty) {
    Product* current = head;
    while (current != NULL) {
        if (current->id == id) {
            current->quantity = newQty;
            writeAllProductsToFile(head);
            printf("Quantity updated for product ID %d.\n", id);
            return;
        }
        current = current->next;
    }
    printf("Product ID not found.\n");
}

// Delete a product by ID
Product* deleteProductById(Product* head, int id) {
    Product *current = head, *prev = NULL;

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


// ========== FILE OPERATIONS MENU (NOW OUTSIDE deleteProductById) ==========
void fileOperationsMenu() {
    Product* list = NULL;
    int choice;

    do {
        printf("\n========== FILE OPERATIONS MENU ==========\n");
        printf("1. Add New Product\n");
        printf("2. View All Products\n");
        printf("3. Update Product Quantity\n");
        printf("4. Delete Product by ID\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int id, qty;
            float price;
            char name[50];

            printf("Enter product ID: ");
            scanf("%d", &id);
            printf("Enter product name: ");
            scanf(" %[^\n]", name); // Note: space before % to consume newline from previous scanf
            printf("Enter quantity: ");
            scanf("%d", &qty);
            printf("Enter price: ");
            scanf("%f", &price);

            Product* newProduct = createProduct(id, name, qty, price);
            saveProductToFile(newProduct);
            free(newProduct); // Free the allocated product node
            printf("Product added successfully.\n");

        } else if (choice == 2) {
            list = loadProductsFromFile();
            displayAllProducts(list);
            freeProductList(list); // Free the list after use
            list = NULL; // Best practice: set to NULL after freeing
        } else if (choice == 3) {
            int id, newQty;
            printf("Enter product ID to update: ");
            scanf("%d", &id);
            printf("Enter new quantity: ");
            scanf("%d", &newQty);
            list = loadProductsFromFile();
            updateProductQuantity(list, id, newQty);
            freeProductList(list);
            list = NULL;
        } else if (choice == 4) {
            int id;
            printf("Enter product ID to delete: ");
            scanf("%d", &id);
            list = loadProductsFromFile();
            list = deleteProductById(list, id); // deleteProductById returns the new head
            freeProductList(list); // Free the (potentially modified) list
            list = NULL;
        } else if (choice != 0) {
            printf("Invalid choice.\n");
        }

    } while (choice != 0);
}
