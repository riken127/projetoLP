#include <stdio.h>
#include <stdlib.h>

#define MAX_CLIENTS 20
#define MSG_MAIN_MENU  "[1] Regist\n[2] Edit\n[3] Delete\n[4] List"

/*
 * 
 */

int menuRead(char message[], int min, int max) {
    int option;
    do {
        puts(message);
        printf("\nInsert here - ");
        scanf("%d", &option);
    } while (option < min || option > max);
    return option;
}

int registCustomers(int customer[], int contCustomers) {
    int id;
    printf("Regist - ");
    scanf("%d", &id);
    customer[contCustomers] = id;
    return contCustomers + 1;
}

int deleteCustomers(int customer[], int contCustomers) {
    int id, i;
    printf("Delete - ");
    scanf("%d", &id);
    for (i = 0; i < contCustomers; i++) {
        if (customer[i] == id) {
            customer[i] = customer[i + 1];
        }
    }
    return contCustomers - 1;
}

void listCustomers(int customer[], int contCustomers) {
    int i;
    printf("\n");
    for (i = 0; i < contCustomers; i++) {
        printf("%d\t", customer[i]);
    }
    printf("\n");
}

void mainMenu(int customers[], int contCustomers) {
    int option;

    do {
        option = menuRead(MSG_MAIN_MENU, 0, 4);

        switch (option) {
            case 0:
                break;
            case 1:
                contCustomers = registCustomers(customers, contCustomers);
                break;
            case 2:
                break;
            case 3:
                contCustomers = deleteCustomers(customers, contCustomers);
                break;
            case 4:
                listCustomers(customers, contCustomers);
                break;
        }
    } while (option != 0);
}

int main(int argc, char** argv) {

    int customers[MAX_CLIENTS], contCustomers = 0;

    mainMenu(customers, contCustomers);

    return (EXIT_SUCCESS);
}

