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

int verifyCustomersId(int customer[], int contCustomers, int requestedId) {
    int i = 0, count = 0;
    for (i = 0; i < contCustomers; i++) {
        if (customer[i] == requestedId) {
            ++count;
            break;
        }
    }
    return count;
}

int registCustomers(int customer[], int contCustomers) {
    int id, verify;
    do {
        printf("Regist - ");
        scanf("%d", &id);
        verify = verifyCustomersId(customer, contCustomers, id);
        if (verify == 1)
            printf("The given id is already taken.\n");
        else
            customer[contCustomers] = id;
    } while (verify != 0);
    return contCustomers + 1;
}

void editCustomers(int customer[], int contCustomers) {
    int id, i, verify;
    do {
        printf("Edit - ");
        scanf("%d", &id);

        verify = verifyCustomersId(customer, contCustomers, id);
        if (verify == 1) {
            for (i = 0; i < contCustomers; i++) {
                if (customer[i] == id) {
                    printf("Change %d's id:\n", id);
                    scanf(" %d", &customer[i]);
                }
            }
        } else printf("");
    } while (verify != 1);
}

int deleteCustomers(int customer[], int contCustomers) {
    int id, i, verify;
    do {
        printf("Delete - ");
        scanf("%d", &id);
        verify = verifyCustomersId(customer, contCustomers, id);
        if (verify == 0)
            printf("The given id does not exist.\n");
        else {
            for (i = 0; i < contCustomers; i++) {
                if (customer[i] == id) {
                    customer[i] = customer[i + 1];
                }
            }
        }
    } while (verify != 1);
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
                editCustomers(customers, contCustomers);
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

