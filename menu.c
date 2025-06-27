//assignment file  :)
#include <stdio.h>
#include "inventory.h" 
#include "product.h"
#include "category_supplier.h"
#include "transaction.h"  
#include "file.h"



//Role 1
void role1(){
    productMenu();
}

//Role 2
void role2(){
    loadInventory();
    inventoryMenu();
 }

//Role 3
void role3(){
    manageMenu();
}

//Role 4
void role4(){
    transactionMenu();
}

//Role 5
void role5(){
    fileOperationsMenu();
}


// THE MENUU :)

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
