//
// Created by r1ken on 11-12-2022.
//

#include "clients.h"
#include "orders.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Bellow function appears when an error appears, it receives the error message
 * as a parameter, and then waits for the user to press a key, if so, the screen is cleaned
 * and the function ends.
 */
void errorMessage(char message[]) {
    char any_key[20];
    system("cls || clear");
    puts(message);
    printf("\t\t\tPress any key to exit ");
    scanf("%s", any_key);
    system("cls || clear");
}

/*
 * Bellow function checks if the given value
 * is between two values, if not, the cycle continues.
 */

int menuRead(char message[], int min, int max) {
    int option = 0;
    char verify[MAX_VERIFY_CHARS] = "";
    do {
        do {
            puts(message);
            printf("\t\t\tInsert here - ");
            scanf("%s", verify);
            if (strcmp(verify, "0") == 0) {
                system("cls || clear");
                return option;
            }
            if (!(option = atoi(verify))) {
                errorMessage(MSG_ERROR_MESSAGE);
            }
        } while (!(option = atoi(verify)));

        system("cls || clear");
        if (option < min || option > max) {
            errorMessage(MSG_ERROR_MESSAGE);
        }
    } while (option < min || option > max);
    return option;
}

/*
 * Bellow function receives a message and depending on the character that was written
 * the value that is returned is different.
 */
int yesOrNoFunction(char message[]) {
    char option;
    do {
        printf(message);
        scanf(" %c", &option);
    } while (option != 'y' && option != 'n' && option != 'Y' && option != 'N');
    switch (option) {
        case 'y':
        case 'Y':
            return 1;
            break;
        case 'n':
        case 'N':
            return 2;
            break;
    }
}

/*
 * Bellow function checks for an id in the struct array,
 * if found, returns the value 1, if not, returns the value 0.
 */
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
 * Bellow function takes a given name and stores it in the struct array
 * in the given position. The first scanf makes sure the buffer is clean,
 * the second scanf gets the value given by the user.
 *
 */
void customerName(char name[]) {
    char temp;
    printf("\n"MSG_CUSTOMER_NAME);
    scanf("%c", &temp);
    scanf("%[^\n]", name);
}

/*
 * Bellow function takes a given address and stores it in the struct array
 * In the given position. The first scanf makes sure the buffer is clean,
 * the second scanf gets the value given by the user.
 */
void customerAddress(char address[]) {
    char temp;
    printf("\n"MSG_CUSTOMER_ADDRESS);
    scanf("%c", &temp);
    scanf("%[^\n]", address);
}

/*
 * Bellow function verifies if the nif is a number and if the number is greater than zero
 * if not, the loop continues, if so the value is returned as an integer
 */
int nifVerify() {
    int nif;
    char verify[MAX_VERIFY_CHARS];
    do {
        do {
            printf("\n"MSG_CUSTOMER_NIF);
            scanf("%s", verify);
            if (!(nif = atoi(verify))) {
                puts(MSG_ERROR_MESSAGE);
            }
        } while (!(nif = atoi(verify)));
        if (nif <= 0) {
            puts(MSG_ERROR_MESSAGE);
        }
    } while (nif <= 0);
    return nif;
}

/*
 * Bellow function takes a given integer and passes the value as an
 * argument to a function that verifies the data, if the written field is an
 * integer greater than zero, the value is returned, if not, the loop continues.
 */
int customerNif() {
    int nif;

    nif = nifVerify();

    return nif;
}

/*
 * Bellow function takes a given country name and stores it in the struct array
 * in the given position. The first scanf makes sure the buffer is clean,
 * the second scanf gets the value given by the user.
 */
void customerCountry(char country[]) {
    char temp;
    printf("\n"MSG_CUSTOMER_COUNTRY);
    scanf("%c", &temp);
    scanf("%[^\n]", country);
}

/*
 * Bellow function creates an id for the user who is beeing created,
 * the given id is equal to the last given id (from the last created user)
 * incremented by one.
 */
int customerId(int curentID) {
    return (curentID + 1);
}

/*
 * Bellow function saves a specific customer data, it receives the position and the input data, and then
 * saves the data of the customer in the given position
 */
void saveCustomer(char name[], char address[], int nif, char country[], int id,
        Customers *customer, int pos) {
    *(&customer->customers[pos].id) = id;
    strcpy(*(&customer->customers[pos].name), name);
    strcpy(*(&customer->customers[pos].address), address);
    *(&customer->customers[pos].nif) = nif;
    strcpy(*(&customer->customers[pos].country), country);
    *(&customer->customers[pos].state) = 1;
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
 * Bellow function records a customer, it gets the customer struct as an argument and
 * then goes tru every field function so that the data is passed to the variables, at the end,
 * all the data that was written goes on the saveCustomer function where the user is created and
 * then the program asks the user tru the yesOrNoFunction if the user wants to add another user,
 * if so the loop continues.
 */
void recordCustomers(Customers *customer) {
    char name[MAX_NAME_CHARS], address[MAX_ADDRESS_CHARS],
            country[MAX_COUNTRY_CHARS];
    int nif, option = 1;
    do {
        printf("\t\t\t__________________________________\n");
        customerName(name);
        customerAddress(address);
        customerCountry(country);
        nif = customerNif();

        printf("\t\t\t__________________________________\n");
        saveCustomer(name, address, nif, country, customerId(customer->counter),
                *(&customer), customer->counter);
        customer->counter++;
        option = yesOrNoFunction(YES_OR_NO_MESSAGE_RECORD);
        system("cls || clear");
    } while (option != 2);
}

/*
 * The Bellow function edit's a line in the struct array. It receives the struct array,
 * the current id of the customer, and the position in the struct array, it then passes all the
 * user information to some local variables and asks the user what field does he want to change,
 * when the user exits all the changes made are saved.
 */
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
 * The bellow function deletes a user in the struct array. It receives the struct and
 * the amount of users by parameter then asks the user for an integer and loops
 * tru the struct trying to find the given id, if found, the user is deleted, if
 * not an error message is displayed.
 */

int deleteCustomers(Customers *customer) {
    int id, i, verify,verifyOrders;
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
                        //verifyOrders = verifyCustomerOrders(*(&customer->customers[i].nif));
                        //if (verifyOrders == 0) {
                            *(&customer->customers[i].id) = *(&customer->customers[i + 1].id);
                            strcpy(*(&customer->customers[i].name),
                                    *(&customer->customers[i + 1].name));
                            strcpy(*(&customer->customers[i].address),
                                    *(&customer->customers[i + 1].address));
                            *(&customer->customers[i].nif) = *(&customer->customers[i + 1].nif);
                            strcpy(*(&customer->customers[i].country),
                                    *(&customer->customers[i + 1].country));
                            *(&customer->customers[i].state) = *(&customer->customers[i + 1].state);
                        /*}
                        else{
                            *(&customer->customers[i].state) = 0;
                        }*/
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
 * The bellow function displays all available customers if possible, if not a message appears saying
 * that no customers where found, the list will appear until the user presses any keu, then the list will
 * be closed.
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
            printf("\n\t\t\tState     : %s", customer->customers[i].state == 1 ? "Active" : "Inactive");
            printf("\n\t\t\t__________________________________");
        }
    }
    printf("\n\t\t\tPress any key to exit ");
    scanf("%s", any_key);
    system("cls || clear");
}

/*
 * The bellow function exports all the customer data, it does so by looping tru the struct array
 * and saving all the customer fields separated by a comma.
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

        fprintf(fp, "%s,%s,%d,%s,%d\n",
                customer->customers[i].name,
                customer->customers[i].address,
                customer->customers[i].nif,
                customer->customers[i].country,
                customer->customers[i].state);
    }
    fclose(fp);
    printf(SUCCESS_IN_WRITING_CUSTOMERS);
}

/*
 * The bellow function imports customers to the program, it does so by asking the user for the file name,
 * then it passes all the data in the file to a string, and reallocates one more position (until the end of the file),
 * then it parses the string tru the commas, after every user is written to the struct a success message appears and file
 * pointer closes.
 */
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
            sp = strtok(NULL, ",");
            customer->customers[customer->counter].state = atoi(sp);
            ++customer->counter;
        }
        fclose(fp);
        printf(SUCCESS_IN_IMPORTING_CUSTOMERS);
    }
}

/*
 * The bellow menu manages the customers, it loops until the integer [option] given by
 * the user is equal to zero.
 */
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
