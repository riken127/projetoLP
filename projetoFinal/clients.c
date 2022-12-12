//
// Created by r1ken on 11-12-2022.
//

#include "clients.h"
#include <stdio.h>
#include <string.h>
#define MSG_CUSTOMER_MANAGEMENT_MENU  "[1] - Record.\n[2] - Edit.\n[3] - Delete.\n[4] - List."


/*
 * Struct definition
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



/*
 * Above function checks if the given value
 * is between to values, if not, the cycle continues.
*/
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
/*
 * Above function checks for an id in the struct array,
 * if found, returns the value 1, if not, returns the value 0.
*/

void customerName(Customer customer[], int contCustomers) {
    char temp;
    printf("Name - ");
    scanf("%c", &temp);
    scanf("%[^\n]", customer[contCustomers].name);
}
/*
 * Above function takes a given name and stores it in the struct array
 * in the given position. The first scanf makes sure the buffer is clean,
 * the second scanf gets the value given by the user.
 *
*/

void customerAddress(Customer customer[], int contCustomers) {
    char temp;
    printf("Adress - ");
    scanf("%c", &temp);
    scanf("%[^\n]", customer[contCustomers].address);
}
/*
 * Above function takes a given address and stores it in the struct array
 * In the given position. The first scanf makes sure the buffer is clean,
 * the second scanf gets the value given by the user.
 */

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
/*
 * Above function takes a given integer and stores it in the struct array
 * in the given position . checks if the given value
 * is equal or below zero, if so, the cycle continues.
*/
void customerCountry(Customer customer[], int contCustomers) {
    char temp;
    printf("Country - ");
    scanf("%c", &temp);
    scanf("%[^\n]", customer[contCustomers].country);
}

/*
 * Above function takes a given country name and stores it in the struct array
 * in the given position. The first scanf makes sure the buffer is clean,
 * the second scanf gets the value given by the user.
*/
void customerId(Customer customer[], int contCustomers, int curentID) {
    customer[contCustomers].id = curentID + 1;
}
/*
 * Above function creates an id for the user who is beeing created,
 * the given id is equal to the last given id (from the last created user)
 * incremented by one.
*/
int recordCustomers(Customer customer[], int contCustomers, int curentID) {

    customerId(customer, contCustomers, curentID);
    customerName(customer, contCustomers);
    customerAddress(customer, contCustomers);
    customerNif(customer, contCustomers);
    customerCountry(customer, contCustomers);

    return contCustomers + 1;
}
/*
 * The above function calls other 5 functions that help create the customer,
 * each function fills a field in the new user's position in the struct array.
*/
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
/*
 * The above function edit's a line in the struct array. It gets the struct and the amount of customers,
 * Then asks the user for a value and loops tru the struct trying to find the given id, if found the functions used to create a user
 * are invoked, if not an error message is displayed.
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

/*
 * The above function deletes a user in the struct array. It gets the struct and the amount of users by parameter
 * then asks the user for an integer and loops tru the struct trying to find the given id, if found, the user is deleted,
 * if not an error message is displayed.
*/

void listCustomers(Customer customer[], int contCustomers) {
    int i;
    printf("\n");
    for (i = 0; i < contCustomers; i++) {
        printf("| %d | %s | %s | %d | %s |\n", customer[i].id, customer[i].name, customer[i].address, customer[i].nif, customer[i].country);
    }
    printf("\n");
}
/*
 * The above function displays all customers.
 */
void customerManagementMenu(Customer customer[], int *contCustomers, int curentID) {
    int option;

    do {
        option = menuRead(MSG_CUSTOMER_MANAGEMENT_MENU, 0, 4);

        switch (option) {
            case 0:
                break;
            case 1:
                *(contCustomers) = recordCustomers(customer, *contCustomers, curentID);
                curentID++;
                break;
            case 2:
                editCustomers(customer, *contCustomers);
                break;
            case 3:
                *contCustomers = deleteCustomers(customer, *contCustomers);
                break;
            case 4:
                listCustomers(customer, *contCustomers);
                break;
        }
    } while (option != 0);
}
/*
 * This menu manages the customers, it loops until the integer [option] given by the user is equal to zero.
 */
