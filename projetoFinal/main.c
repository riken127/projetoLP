#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTS 20
#define MSG_CUSTOMER_MANAGMENT_MENU  "[1] - Record.\n[2] - Edit.\n[3] - Delete.\n[4] - List."
#define MSG_MAIN_MENU  "[1] - User.\n[2] - Admin."
#define MSG_ADMIN_MENU  "[1] - Clients Managment.\n[2] - Products Managment.\n[3] - Production Managment."

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
    char temp;
    printf("Name - ");
    scanf("%c", &temp);
    /*É colocado o scanf da linha pois sem esta linha o compilador
      guarda sempre o valor nulo na variavel .name .
      Para arranjar isso é colocado o scanf para ler o valor do input buffer
      e guarda-lo numa variavel temporaria.
     */
    scanf("%[^\n]", customer[contCustomers].name);
}

void customerAddress(Customer customer[], int contCustomers) {
    char temp;
    printf("Adress - ");
    scanf("%c", &temp);
    scanf("%[^\n]", customer[contCustomers].address);
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
    char temp;
    printf("Country - ");
    scanf("%c", &temp);
    scanf("%[^\n]", customer[contCustomers].country);
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

void editCustomers(Customer customer[], int contCustomers) {
    int id, i, verify;
    do {
        printf("Edit - ");
        scanf("%d", &id);
        if (id == 0)
            break;
        verify = verifyCustomersId(customer, contCustomers, id);
        if (verify == 1) {
            for (i = 0; i < contCustomers; i++) {
                if (customer[i].id == id) {
                    customerName(customer, i);
                    customerAddress(customer, i);
                    customerNif(customer, i);
                    customerCountry(customer, i);
                }
            }
        } else printf("Given id was not found. Try again.\n");
    } while (verify != 1);
}

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
        printf("| %d | %s | %s | %d | %s |\n", customer[i].id, customer[i].name, customer[i].address, customer[i].nif, customer[i].country);
    }
    printf("\n");
}

void customerManagmentMenu(Customer customer[], int contCustomers, int curentID) {
    int option;

    do {
        option = menuRead(MSG_CUSTOMER_MANAGMENT_MENU, 0, 4);

        switch (option) {
            case 0:
                break;
            case 1:
                contCustomers = recordCustomers(customer, contCustomers, curentID);
                curentID++;
                break;
            case 2:
                editCustomers(customer, contCustomers);
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

void adminMenu(Customer customer[], int contCustomers, int curentID) {
    int option;

    do {
        option = menuRead(MSG_ADMIN_MENU, 0, 3);

        switch (option) {
            case 0:
                break;
            case 1:
                customerManagmentMenu(customer, contCustomers, curentID);
                break;
            case 2:
                break;
            case 3:
                break;
        }
    } while (option != 0);
}

void mainMenu(Customer customer[], int contCustomers, int curentID) {
    int option;

    do {
        option = menuRead(MSG_MAIN_MENU, 0, 2);

        switch (option) {
            case 0:
                break;
            case 1:

                break;
            case 2:
                adminMenu(customer, contCustomers, curentID);
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

