#ifndef CATEGORY_SUPPLIER_H
#define CATEGORY_SUPPLIER_H

#define MAX 100

typedef struct {
    int categoryId;               // ✅ CORRECTED to single integer
    char categoryName[50];
} Category;

typedef struct {
    int supplierId;
    char supplierName[50];
    int categoryId;
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
