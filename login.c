#include <stdio.h>
#include <string.h>
#include "login.h"

int login(char *username_out) {
    char inputUser[50], inputPass[50];
    char fileUser[50], filePass[50];
    int role;
    FILE *fp = fopen("login.txt", "r");

    if (!fp) {
        printf("Error opening user file.\n");
        return -1;
    }

    printf("Username: ");
    scanf("%s", inputUser);
    printf("Password: ");
    scanf("%s", inputPass);

    while (fscanf(fp, "%[^,],%[^,],%d\n", fileUser, filePass, &role) == 3) {
        if (strcmp(inputUser, fileUser) == 0 && strcmp(inputPass, filePass) == 0) {
            fclose(fp);
            strcpy(username_out, inputUser);
            return role;
        }
    }

    fclose(fp);
    printf("Login failed. Invalid credentials.\n");
    return -1;
}
