//assignment file  :)
#include <stdio.h>
#include "inventory.h" //Inventory header file
#include "product.h"
#include "category_supplier.h"
#include "file.h"

//Role 1
void role1(){
    roductMenu();
}

//Role 2
void role2(){
    loadInventory();
    inventoryMenu();
 }


//Role 3
void role3(){
    //manageMenu();
}

//Role 4
void role4(){
    printf("\nWaiting for Oroni\n");
}

//Role 5
void role5(){
    #include "file.h"  // Gives access to fileOperationsMenu()

int main() {
    int choice;
    do {
        printf("\n=== MAIN SYSTEM MENU ===\n");
        printf("1. Product Management\n");
        printf("2. Inventory Management\n");
        printf("3. Category & Supplier\n");
        printf("4. User & Transactions\n");
        printf("5. File Operations (Role 5)\n");  // YOUR ROLE
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                   manageMenu();
                   break;
            case 2:
                   inventoryMenu();
                   break;
            case 3:
                   productMenu();
                   break;
            case 4:
                   RolesMenu();
                   break;
            case 5:
                   
                   
                fileOperationsMenu();  // ← Calls your menu
                break;
            
            // other roles...
        }
    } while (choice != 0);
    return 0;
}

// THHEE MENUU :))))))

void RolesMenu(){


    int choice;

    do{
     printf("\n~~~~Retail Inventory Management System:))~~~~~\n");

     printf("\n1.  Core System and Product Management\n");
     printf("2.  Inventory and Stock Management\n");
     printf("3.  Category and Supplier Management\n");
     printf("4.  User and Transaction Management\n");
     printf("5.  File Operations and Advanced Features\n");
     printf("6.  terminate\n");

     printf("Please Enter Your Choice (pick from 1-5): ");
     scanf("%d", &choice);

    switch(choice) {

        case 1: role1();
        break;
        

        case 2: role2();
        break;


        case 3: role3();
        break;
        

        case 4: role4();
        break;
        

        case 5: role5();
        break;
        

        case 6: printf("\nTerminating the System...");
        break;

        default: printf("\nInvaild choice! Please choose from 1-6.\n");
    }

        

    }  while (choice !=6 );
}

int main(){
    RolesMenu();
    return 0;
}
