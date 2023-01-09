//
// Created by r1ken on 11-12-2022.
//

#include "clients.h"
#include "orders.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void errorMessage(char message[]) {
    char any_key[20];
    system("cls || clear");
    puts(message);
    printf("\t\t\tPress any key to exit ");
    scanf("%s", any_key);
    system("cls || clear");
}

int menuRead(char message[], int min, int max) {
    int option;
    do {
        puts(message);
        printf("\t\t\tInsert here - ");
        scanf("%d", &option);
        system("cls || clear");
        if (option < min || option > max) {
            errorMessage(MSG_ERROR_MESSAGE);
        }
    } while (option < min || option > max);
    return option;
}

/*
 * Above function checks if the given value
 * is between to values, if not, the cycle continues.
 */

int yesOrNoFunction(char message[]) {
    char option;
    do {
        printf(message);
        scanf(" %c", &option);
    } while (option != 'y' && option != 'n');
    switch (option) {
        case 'y':
            return 1;
            break;
        case 'n':
            return 2;
            break;
    }
}

int verifyCustomersId(Customers *customer, int requestedId) {
    int i = 0, count = 0;
    for (i = 0; i < customer->counter; i++) {
        if (*(&customer->customers[i].id) == requestedId) {
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

void customerName(char name[]) {
    char temp;
    printf("\n"MSG_CUSTOMER_NAME);
    scanf("%c", &temp);
    scanf("%[^\n]", name);
}

/*
 * Above function takes a given name and stores it in the struct array
 * in the given position. The first scanf makes sure the buffer is clean,
 * the second scanf gets the value given by the user.
 *
 */

void customerAddress(char address[]) {
    char temp;
    printf("\n"MSG_CUSTOMER_ADDRESS);
    scanf("%c", &temp);
    scanf("%[^\n]", address);
}

/*
 * Above function takes a given address and stores it in the struct array
 * In the given position. The first scanf makes sure the buffer is clean,
 * the second scanf gets the value given by the user.
 */

int customerNif() {
    int verifyNif, nif;
    do {
        printf("\n"MSG_CUSTOMER_NIF);
        scanf("%d", &nif);
        if (nif <= 0) {
            printf("Invalid Nif\n");
        } else
            verifyNif = 1;
    } while (verifyNif != 1);

    return nif;
}

/*
 * Above function takes a given integer and stores it in the struct array
 * in the given position . checks if the given value
 * is equal or below zero, if so, the cycle continues.
 */
void customerCountry(char country[]) {
    char temp;
    printf("\n"MSG_CUSTOMER_COUNTRY);
    scanf("%c", &temp);
    scanf("%[^\n]", country);
}

/*
 * Above function takes a given country name and stores it in the struct array
 * in the given position. The first scanf makes sure the buffer is clean,
 * the second scanf gets the value given by the user.
 */
int customerId(int curentID) {
    return (curentID + 1);
}

/*
 * Above function creates an id for the user who is beeing created,
 * the given id is equal to the last given id (from the last created user)
 * incremented by one.
 */
void saveCustomer(char name[], char address[], int nif, char country[], int id,
        Customers *customer, int pos) {
    *(&customer->customers[pos].id) = id;
    strcpy(*(&customer->customers[pos].name), name);
    strcpy(*(&customer->customers[pos].address), address);
    *(&customer->customers[pos].nif) = nif;
    strcpy(*(&customer->customers[pos].country), country);
}

void recordCustomers(Customers *customer) {
    char name[MAX_NAME_CHARS], address[MAX_ADDRESS_CHARS],
            country[MAX_COUNTRY_CHARS];
    int nif, option = 1;
    do {
        printf("\t\t\t__________________________________\n");
        customerName(name);
        customerAddress(address);
        nif = customerNif();
        customerCountry(country);
        printf("\t\t\t__________________________________\n");
        saveCustomer(name, address, nif, country, customerId(customer->counter),
                *(&customer), customer->counter);
        customer->counter++;
        option = yesOrNoFunction(YES_OR_NO_MESSAGE_RECORD);
        system("cls || clear");
    } while (option != 2);
}

void changeCustomerData(Customers *customer, int pos, int id) {
    int option, nif;
    char name[MAX_NAME_CHARS], address[MAX_ADDRESS_CHARS],
            country[MAX_COUNTRY_CHARS];
    strcpy(name, *(&customer->customers[pos].name));
    strcpy(address, *(&customer->customers[pos].address));
    nif = *(&customer->customers[pos].nif);
    strcpy(country, *(&customer->customers[pos].country));
    do {
        option = menuRead(MSG_CHANGE_CUSTOMER_DATA, 0, 4);

        switch (option) {
            case 0:
                break;
            case 1:
                printf("\n\t\t\tPrevious - %s", name);
                customerName(name);
                system("cls || clear");
                break;
            case 2:
                printf("\n\t\t\tPrevious - %s", address);
                customerAddress(address);
                system("cls || clear");
                break;
            case 3:
                printf("\n\t\t\tPrevious - %d", nif);
                nif = customerNif();
                system("cls || clear");
                break;
            case 4:
                printf("\n\t\t\tPrevious - %s", country);
                customerCountry(country);
                system("cls || clear");
                break;
        }
    } while (option != 0);

    saveCustomer(name, address, nif, country, id, *(&customer), pos);
}

/*
 * The above function calls other 5 functions that help create the customer,
 * each function fills a field in the new user's position in the struct array.
 */
void editCustomers(Customers *customer) {
    int id, i, verify;
    do {
        printf(CLIENT_ID_MSG);
        scanf("%d", &id);
        system("cls || clear");
        if (id == 0)
            break;
        verify = verifyCustomersId(*(&customer), id);
        if (verify == 1) {
            for (i = 0; i < customer->counter; i++) {
                if (*(&customer->customers[i].id) == id) {
                    changeCustomerData(*(&customer), i, id);
                }
            }
        } else
            errorMessage(MSG_ERROR_MESSAGE);
    } while (verify != 1);
}

/*
 * The above function edit's a line in the struct array. It gets the struct and
 * the amount of customers, Then asks the user for a value and loops tru the
 * struct trying to find the given id, if found the functions used to create a
 * user are invoked, if not an error message is displayed.
 */
int deleteCustomers(Customers *customer) {
    int id, i, verify;
    do {
        printf(CLIENT_ID_MSG);
        scanf("%d", &id);
        if (id == 0) {
            break;
        } else {
            verify = verifyCustomersId(*(&customer), id);
            if (verify == 0) {
                errorMessage(MSG_ERROR_MESSAGE);
            } else {
                for (i = 0; i < *(&customer->counter); i++) {
                    if (*(&customer->customers[i].id) == id) {
                        *(&customer->customers[i].id) = *(&customer->customers[i + 1].id);
                        strcpy(*(&customer->customers[i].name),
                                *(&customer->customers[i + 1].name));
                        strcpy(*(&customer->customers[i].address),
                                *(&customer->customers[i + 1].address));
                        *(&customer->customers[i].nif) = *(&customer->customers[i + 1].nif);
                        strcpy(*(&customer->customers[i].country),
                                *(&customer->customers[i + 1].country));
                    }
                }
            }
        }
    } while (verify != 1);
    system("cls || clear");
    if (id == 0)
        return customer->counter;
    else
        return customer->counter--;
}

/*
 * The above function deletes a user in the struct array. It gets the struct and
 * the amount of users by parameter then asks the user for an integer and loops
 * tru the struct trying to find the given id, if found, the user is deleted, if
 * not an error message is displayed.
 */

void listCustomers(Customers *customer) {
    int i;
    char any_key[20];
    if (customer->counter == 0) {
        printf("\n\t\t\tNo customers were found\n\t\t\t__________________________________");
    } else {
        printf("\n\t\t\tList Of Clients\n\t\t\t__________________________________");
        for (i = 0; i < customer->counter; i++) {
            printf("\n\n\t\t\tClient Id : %d", customer->customers[i].id);
            printf("\n\t\t\tName      : %s", customer->customers[i].name);
            printf("\n\t\t\tAddress   : %s", customer->customers[i].address);
            printf("\n\t\t\tNif       : %d", customer->customers[i].nif);
            printf("\n\t\t\tCountry   : %s", customer->customers[i].country);
            printf("\n\t\t\t__________________________________");
        }
    }
    printf("\n\t\t\tPress any key to exit ");
    scanf("%s", any_key);
    system("cls || clear");
}

/*
 * The above function displays all customers.
 */
void exportCustomers(Customers *customer) {
    FILE *fp;
    int i;
    char fn[MAX_FN_CHARS];
    askFileName(fn);
    fp = fopen(fn, "w");
    if (fp == NULL) {
        printf(ERROR_IN_WRITING_CUSTOMERS);
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < customer->counter; i++) {
        fprintf(fp, "%s,%s,%d,%s\n",
                customer->customers[i].name,
                customer->customers[i].address,
                customer->customers[i].nif,
                customer->customers[i].country);
    }
    fclose(fp);
    printf(SUCCESS_IN_WRITING_CUSTOMERS);
}

void importCustomers(Customers *customer) {
    FILE *fp;
    char fn[MAX_FN_CHARS], buff[1024], *sp;
    askFileName(fn);
    fp = fopen(fn, "r");
    if (fp == NULL) {
        printf(ERROR_IN_WRITING_CUSTOMERS);
    } else {
        while (fgets(buff, 1024, fp) != NULL) {
            customer->customers = (Customer*) realloc(customer->customers, sizeof (Customer) * (customer->counter + 1));
            customer->customers[customer->counter].id = (customer->counter + 1);
            sp = strtok(buff, ",");
            strcpy(customer->customers[customer->counter].name, sp);
            sp = strtok(NULL, ",");
            strcpy(customer->customers[customer->counter].address, sp);
            sp = strtok(NULL, ",");
            customer->customers[customer->counter].nif = atoi(sp);
            sp = strtok(NULL, ",");
            strcpy(customer->customers[customer->counter].country, sp);
            ++customer->counter;
        }
        fclose(fp);
        printf(SUCCESS_IN_IMPORTING_CUSTOMERS);
    }
}

void customerManagementMenu(Customers *customer) {
    int option;
    do {
        option = menuRead(MSG_CUSTOMER_MANAGEMENT_MENU, 0, 6);

        switch (option) {
            case 0:
                break;
            case 1:
                recordCustomers(*(&customer));
                break;
            case 2:
                editCustomers(customer);
                break;
            case 3:
                deleteCustomers(customer);
                break;
            case 4:
                listCustomers(customer);
                break;
            case 5:
                exportCustomers(customer);
                break;
            case 6:
                importCustomers(customer);
                break;
        }
    } while (option != 0);
}
/*
 * This menu manages the customers, it loops until the integer [option] given by
 * the user is equal to zero.
 */