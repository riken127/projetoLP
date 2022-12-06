#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTS 20
#define MSG_MAIN_MENU  "[1] - Record.\n[2] - Edit.\n[3] - Delete.\n[4] - List."

/*
 * 
 */

typedef struct {
    int id;
    char name[50];
    char address[50];
    int nif;
    char country[50];
} Customer;

int menuRead(char message[], int min, int max) {
    int option;
    do {
        puts(message);
        printf("\nInsert here - ");
        scanf("%d", &option);
    } while (option < min || option > max);
    return option;
}

int verifyCustomersId(Customer customer[], int contCustomers, int requestedId) {
    int i = 0, count = 0;
    for (i = 0; i < contCustomers; i++) {
        if (customer[i].id == requestedId) {
            ++count;
            break;
        }
    }
    return count;
}

void customerName(Customer customer[], int contCustomers) {
    printf("Name - ");
    scanf("%s", customer[contCustomers].name);
}

void customerAddress(Customer customer[], int contCustomers) {
    printf("Address - ");
    scanf("%s", customer[contCustomers].address);
}

void customerNif(Customer customer[], int contCustomers) {
    int verifyNif;

    do {
        printf("Nif - ");
        scanf("%d", &customer[contCustomers].nif);
        if (customer[contCustomers].nif <= 0) {
            printf("Invalid Nif\n");
        } else
            verifyNif = 1;
    } while (verifyNif != 1);
}

void customerCountry(Customer customer[], int contCustomers) {
    printf("Country - ");
    scanf("%s", customer[contCustomers].country);
}

void customerId(Customer customer[], int contCustomers, int curentID) {
    customer[contCustomers].id = curentID + 1;
}

int recordCustomers(Customer customer[], int contCustomers, int curentID) {

    customerId(customer, contCustomers, curentID);
    customerName(customer, contCustomers);
    customerAddress(customer, contCustomers);
    customerNif(customer, contCustomers);
    customerCountry(customer, contCustomers);

    return contCustomers + 1;
}

/*void editCustomers(Customer customer[], int contCustomers) {
    int id, i, verify, newValue;
    do {
        printf("Edit - ");
        scanf("%d", &id);

        verify = verifyCustomersId(customer, contCustomers, id);
        if (verify == 1) {
            for (i = 0; i < contCustomers; i++) {
                if (customer[i] == id) {
                    printf("Change %d's id:\n", id);
                    scanf("%d", &newValue);
                    if (newValue == 0)
                        break;
                    else
                        customer[i] = newValue;
                }
            }
        } else printf("Given id was not found. Try again.\n");
    } while (verify != 1);
}
 */
int deleteCustomers(Customer customer[], int contCustomers) {
    int id, i, verify;
    do {
        printf("Delete - ");
        scanf("%d", &id);
        if (id == 0) {
            break;
        } else {
            verify = verifyCustomersId(customer, contCustomers, id);
            if (verify == 0) {
                printf("The given id does not exist.\n");
            } else {
                for (i = 0; i < contCustomers; i++) {
                    if (customer[i].id == id) {
                        customer[i].id = customer[i + 1].id;
                        strcpy(customer[i].name, customer[i + 1].name);
                        strcpy(customer[i].address, customer[i + 1].address);
                        customer[i].nif = customer[i + 1].nif;
                        strcpy(customer[i].country, customer[i + 1].country);
                    }
                }
            }
        }
    } while (verify != 1);

    if (id == 0)
        return contCustomers;
    else
        return contCustomers - 1;
}

void listCustomers(Customer customer[], int contCustomers) {
    int i;
    printf("\n");
    for (i = 0; i < contCustomers; i++) {
        printf("%d %s %s %d %s\n", customer[i].id, customer[i].name, customer[i].address, customer[i].nif, customer[i].country);
    }
    printf("\n");
}

void mainMenu(Customer customer[], int contCustomers, int curentID) {
    int option;

    do {
        option = menuRead(MSG_MAIN_MENU, 0, 4);

        switch (option) {
            case 0:
                break;
            case 1:
                contCustomers = recordCustomers(customer, contCustomers, curentID);
                curentID++;
                break;
            case 2:
                //editCustomers(customer, contCustomers);
                break;
            case 3:
                contCustomers = deleteCustomers(customer, contCustomers);
                break;
            case 4:
                listCustomers(customer, contCustomers);
                break;
        }
    } while (option != 0);
}

int main(int argc, char** argv) {

    int contCustomers = 0, curentID = 0;
    Customer customer[MAX_CLIENTS];

    mainMenu(customer, contCustomers, curentID);

    return (EXIT_SUCCESS);
}

