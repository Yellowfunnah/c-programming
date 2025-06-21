//assignment file  :)
#include <stdio.h>
#include "inventory.h" //Inventory header file


#define INVENTORY_FILE "inventory.txt"// Defining the inventory file name

//Role 1
void role1(){
    printf("\nAAAAAAAAAA\n");
}

//Role 2
void role2(){
    printf("\nwaiting for Abjz\n");
}

//Role 3
void role3(){
    printf("\nbetaaaa hellooooo\n"); //betaa im going to work here 
}

//Role 4
void role4(){
    printf("\nWaiting for LATFIIAAAA\n");
}

//Role 5
void role5(){
    printf("\nWating for Oronniii\n");
}

// THHEE MENUU :))))))

void RolesMenu(){
    InventoryItem *inventoryHead = NULL;

    inventoryHead = loadInventoryFromFile(INVENTORY_FILE);

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
        runInventoryManagementMenu(&inventoryHead);
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
