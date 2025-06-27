#ifndef CATEGORY_SUPPLIER_H
#define CATEGORY_SUPPLIER_H

#define MAX 100

typedef struct {
    char categoryId[10];     // ✅ MUST be a string
    char categoryName[50];
} Category;


typedef struct {
    char supplierId[10];       // instead of just char
    char supplierName[50];
    char categoryId[10];       // match Category's ID format
} Supplier;


extern Category categories[MAX];
extern Supplier suppliers[MAX];
extern int catCount, suppCount;

void addCategory();
void updateCategory();
void deleteCategory();
void displayCategories();

void addSupplier();
void updateSupplier();
void deleteSupplier();
void displaySuppliers();
void filterSuppliersByCategory();
void displayInventoryFromFile();
void restockInventory();


void saveData();
void loadData();
void manageMenu();

#endif
